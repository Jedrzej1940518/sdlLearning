from reportlab.lib.pagesizes import letter
from reportlab.pdfgen import canvas

import cairosvg
import csv

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


_base_path = ""
_title = ""
_desc = ""
_scenario_name = ""
_runs = 1

left_margin = 20

title_height = 50
title_size = 18

dec_height = 30
desc_size = 12

image_top_margin = 30
image_y = 50

hyperparams_margin = 30
hyperparams_size = 10

scenario_size = 18

scenario_run_margin = 30
run_size = 14
run_margin = 30
run_image_margin = 0
run_image_height = 160
hyperparams_width = 100

eval_upper_margin = 10
eval_size = 16
run_eval_size = 8
run_eval_margin = 12

def load_report_data(path):
    
    config_dict = {}

    with open(path, mode='r') as file:
        reader = csv.reader(file)
        
        for row in reader:
            if row:
                key, value = row[0], row[1]
                config_dict[key] = value

    global _title, _desc, _runs, _scenario_name
    _title = config_dict['title']
    _desc = config_dict['desc']
    _scenario_name = config_dict['scenario_name']
    _runs = int(config_dict['runs'])

def load_hyperparams(path):
    
    config_dict = {}

    with open(path, mode='r') as file:
        reader = csv.reader(file)
        
        for row in reader:
            if row:
                key, value = row[0], row[1]
                config_dict[key] = value

    return config_dict

def make_chart(path, save_path):

    data = pd.read_csv(path)

    plt.figure(figsize=(10, 5))

    #cum_r
    ax1 = plt.gca()
    ax1.plot(data['iter'], data['mean_cum_r_1000'], color='b', label='Mean Cumulative Reward (1000)')
    ax1.set_xlabel('Iteration')
    ax1.set_ylabel('Mean Cumulative Reward (1000)', color='b')
    ax1.tick_params(axis='y', labelcolor='b')

    degree = 6 
    z = np.polyfit(data['iter'], data['mean_cum_r_1000'], degree)
    p = np.poly1d(z)
    ax1.plot(data['iter'], p(data['iter']), "b--")

    #vs
    ax2 = ax1.twinx()  
    ax2.plot(data['iter'], data['last_mean_vs'], color='r', label='Last Mean VS')
    ax2.set_ylabel('Last Mean VS', color='r')
    ax2.tick_params(axis='y', labelcolor='r')

    z2 = np.polyfit(data['iter'], data['last_mean_vs'], degree)
    p2 = np.poly1d(z2)
    ax2.plot(data['iter'], p2(data['iter']), "r--")

    # title/legend
    plt.title('Performance Metrics Over Iterations')
    ax1.legend(loc='upper left')
    ax2.legend(loc='upper right')

    plt.savefig(save_path)

def evaluate_run(path):

    df = pd.read_csv(path)

    max_row = df[df['mean_cum_r_1000'] == df['mean_cum_r_1000'].max()]

    max_iter = max_row['iter'].values[0]
    max_mean_cum_r_1000 = max_row['mean_cum_r_1000'].values[0]
    corresponding_last_mean_vs = max_row['last_mean_vs'].values[0]

    return max_iter, max_mean_cum_r_1000, corresponding_last_mean_vs


def draw_scenario(canvas, x, y, scenario_name, runs):

    canvas.setFont("Helvetica", scenario_size)  # Set font and size
    canvas.drawString(x, y, scenario_name)

    canvas.setFont("Helvetica", run_size)
    last_y = 0
    for i in range(runs):
        make_chart(f'{_base_path}/run_{i}/training.csv', f'{_base_path}/run_{i}/run_chart.png')
        chart_path = f'{_base_path}/run_{i}/run_chart.png'
    
        run_y = y - scenario_run_margin - i * (run_size + run_image_margin + run_image_height)
        canvas.drawString(x, run_y, f'run {i}')
        run_image_y = run_y - run_image_margin - run_image_height
        canvas.drawImage(chart_path, x, run_image_y, height=run_image_height, preserveAspectRatio=True, anchor='sw')
        last_y = run_image_y

    return last_y

def write_eval(canvas, x,y, runs):
    
    canvas.setFont("Helvetica", eval_size)  # Set font and size
    canvas.drawString(x, y, 'Evaluation')
    canvas.setFont("Helvetica", run_eval_size)  # Set font and size

    for i in range(runs):
        iter, max_cum_r, v_s = evaluate_run(f'{_base_path}/run_{i}/training.csv')
        run_eval_y = y - i*(run_eval_size +  run_eval_margin) - eval_size - run_eval_margin
        canvas.drawString(x, run_eval_y, f'Run {i}: Max avg cumulative reward: {max_cum_r:.1f} during iteration {iter} with avg. v_s {v_s:.1f}')


def create_pdf(path, hyperparams, scenario_name, runs):
    # Create a canvas
    c = canvas.Canvas(path, pagesize=letter)
    width, height = letter  

    #_title
    title_y = height - title_height  

    c.setFont("Helvetica", title_size)  
    c.drawString(left_margin, title_y, _title)

    #_desc
    desc_y = title_y - dec_height
    c.setFont("Helvetica", desc_size)  
    c.drawString(left_margin, desc_y, _desc)

    #image
    image_path = f"{_base_path}/actor_net.png" 
    image_network_path = f"{_base_path}/actor_net.svg" 

    cairosvg.svg2png(url=image_network_path, write_to=image_path)
    image_height = height - image_y - dec_height - title_height - image_top_margin
    image_width, _ = c.drawImage(image_path, left_margin, image_y, height=image_height, preserveAspectRatio=True, anchor='nw')

    #hyperparams
    c.setFont("Helvetica", hyperparams_size)
    hyperparams_height = image_height
    hyperparam_height = hyperparams_height / len(hyperparams.items())
    for indx, (key, val) in enumerate(hyperparams.items()):
        c.drawString(image_width -10, image_y+image_height - hyperparams_margin - indx * hyperparam_height, f"{key}: {val}")

    #scenarios
    scenario_x = image_width + hyperparams_width
    eval_y = draw_scenario(c, scenario_x, title_y, scenario_name, runs) - eval_upper_margin

    write_eval(c, scenario_x, eval_y, runs)

    c.showPage()
    c.save()


def generate_report(base_path):
    global _base_path
    _base_path = base_path

    load_report_data(f'{_base_path}/report_data.csv')
    hyperparams = load_hyperparams(f'{_base_path}/hyperparams.csv')
    env_params = load_hyperparams(f'{_base_path}/training_info.csv')
    create_pdf(_base_path+f'/{_title}.pdf', {**hyperparams, **env_params}, _scenario_name, _runs)

