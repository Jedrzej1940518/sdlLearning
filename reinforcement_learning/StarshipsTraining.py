
from PpoAgent import *
from MakeNets import *
from GenerateReport import generate_report

import Starships

from torchview import draw_graph

base_obs_size = 6
relative_obs_size = 9

obs_space_scenario0 = base_obs_size + relative_obs_size # 1v1
obs_space_scenario1 = base_obs_size + relative_obs_size * 3 # 1v3 
obs_space_scenario2 = base_obs_size + relative_obs_size * 4 # 2v3

a_space = 4 # rotation, x, y, shoot?
device = 'cuda'

base_log_path = "Trainings/Starships/"

def visualise_net(net, obs_space, dir_path, net_name):
    model_graph = draw_graph(net, input_size=(1,obs_space), expand_nested=True)
    model_graph.resize_graph(scale=5.0) 
    model_graph.visual_graph.render(filename=net_name ,directory=dir_path,format='svg')

def save_hyperparams(hyperparams, dir_path):
    filename = 'hyperparams.csv'
    with open(f'{dir_path}/{filename}', 'w') as f:
        for key, val in hyperparams.items():
            f.write(f'{key},{val}\n')

def save_training_info(max_steps, frame_skip, scenario, iterations, dir_path):
    filename = 'training_info.csv'
    with open(f'{dir_path}/{filename}', 'w') as f:
        f.write(f'scenario,{scenario}\n')
        f.write(f'max_steps,{max_steps}\n')
        f.write(f'frame_skip,{frame_skip}\n')
        f.write(f'iterations,{iterations}\n')

def export_report_data(dir_path, title, desc, scenario_name, runs):
    filename = 'report_data.csv'
    with open(f'{dir_path}/{filename}', 'w') as f:
        f.write(f'title,{title}\n')
        f.write(f'desc,{desc}\n')
        f.write(f'scenario_name,{scenario_name}\n')
        f.write(f'runs,{runs}\n')

def translate_observation(obs):
    return torch.tensor(obs, device = device)

def translate_output(net_output):
    actions = net_output.clamp(-1,1)
    result = np.array(actions.cpu())
    result[0] *=180
    result[1] *=10
    result[2] *=10
    return result


def train(log_path, iterations, make_actor_net, make_critic_net, env_parameters, hyperparameters, runs = 1, export_model=True, resume=False):

    full_log_path = base_log_path+log_path
    max_steps = env_parameters.get('max_steps', 2048)
    record_episode_period = env_parameters.get('record_episode_period', 300)
    frame_skip = env_parameters.get('frame_skip', 10)
    scenario = env_parameters.get('scenario', 0)
    
    for i in range(runs):
        run_log_path = full_log_path + f'/run_{i}/'
        env = Starships.Starships(max_steps, record_episode_period, frame_skip, scenario, run_log_path)
        obs_space = obs_space_scenario0 if scenario == 0 else (obs_space_scenario1 if scenario == 1 else obs_space_scenario2)
        actor_net = make_actor_net(obs_space, a_space*2)
        critic_net = make_critic_net(obs_space, 1)

        visualise_net(actor_net, obs_space, full_log_path, 'actor_net')
        visualise_net(critic_net, obs_space, full_log_path, 'critic_net')
        ppo = SimplePPO(actor_net, a_space, critic_net, run_log_path, hyperparameters)
        save_hyperparams(ppo.export_hyperparameters(), full_log_path)
        save_training_info(max_steps, frame_skip, scenario, iterations, full_log_path)

        print(f"Run_{i}, training scenario {scenario} for {iterations} iterations, obs_space {obs_space}")
        
        ppo.train(env, iterations, export_model=export_model, resume=resume, export_iteration_period=100)
        env.write_times()

def main(): 
    hyperparameters = {'debug_period': 100, 'debug': True, 'translate_output': translate_output, 'translate_observation': translate_observation, 'target_device': device}
    env_parameters = {'scenario':0, 'record_episode_period' : 1000, 'frame_skip': 3}

    hyperparameters['actor_lr'] = 0.00003
    hyperparameters['critic_lr'] = 0.00003
    runs = 1
    training_name = f'scenario_{env_parameters["scenario"]}' + '_timing_results'
    train(training_name,100, make_base_net, make_base_net, env_parameters, hyperparameters, runs=runs)
    export_report_data(base_log_path + training_name, 'Base net', 'Base net with prefab multi', f'Scenario {env_parameters["scenario"]}', runs)
    generate_report(base_log_path + training_name)




if __name__ == "__main__":
    main()


#increase GAE probably, seems good 
#change optimizers
#change loss from l1 ?
#zoom out 
#MAKE IT FASTER !!!

#mean, std =  self.actor(obs_t)                                #todo probaby should use only indexes
#normal_dist = torch.distributions.Normal(mean, std)
#new_log_probs = normal_dist.log_prob(acts_t)
