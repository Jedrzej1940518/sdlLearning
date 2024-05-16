
from PpoAgent import *
from MakeNets import *

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

def translate_observation(obs):
    return torch.tensor(obs, device = device)

def translate_output(net_output):
    actions = net_output.clamp(-1,1)
    result = np.array(actions.cpu())
    result[0] *=180
    result[1] *=10
    result[2] *=10
    return result

def train(log_path, iterations, make_actor_net, make_critic_net, env_parameters, hyperparameters, resume=False):
    full_log_path = base_log_path+log_path
    max_steps = env_parameters.get('max_steps', 2048)
    record_episode_period = env_parameters.get('record_episode_period', 300)
    frame_skip = env_parameters.get('frame_skip', 10)
    scenario = env_parameters.get('scenario', 1)

    env = Starships.Starships(max_steps, record_episode_period, frame_skip, scenario, full_log_path)
    obs_space = obs_space_scenario0 if scenario == 0 else (obs_space_scenario1 if scenario == 1 else obs_space_scenario2)
    actor_net = make_actor_net(obs_space, a_space*2)
    critic_net = make_critic_net(obs_space, 1)


    ppo = SimplePPO(actor_net, a_space, critic_net, full_log_path, hyperparameters)
    
    visualise_net(actor_net, obs_space, full_log_path, 'actor_net')
    visualise_net(critic_net, obs_space, full_log_path, 'critic_net')
    save_training_info(max_steps, frame_skip, scenario, iterations, full_log_path)
    save_hyperparams(ppo.export_hyperparameters(), full_log_path)

    print(f"Training scenario {scenario} for {iterations} iterations, obs_space {obs_space}")
    
    ppo.train(env, iterations, export_model=True, resume=resume, export_iteration_period=100)

def main(): 
    hyperparameters = {'translate_output': translate_output, 'translate_observation': translate_observation, 'target_device': 'cuda'}
    env_parameters = {'record_episode_period' : 10}
    train('base_training', 200, make_narrow_net, make_narrow_net, env_parameters, hyperparameters)

if __name__ == "__main__":
    main()

#grad norm? CHECK LATER
