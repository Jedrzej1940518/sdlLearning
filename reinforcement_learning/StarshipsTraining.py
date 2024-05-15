
import math

from PpoAgent import *
import torch.nn.init as init
import Starships


base_obs_size = 6
relative_obs_size = 9

obs_space_scenario0 = base_obs_size + relative_obs_size # 1v1
obs_space_scenario1 = base_obs_size + relative_obs_size * 3 # 1v3 
obs_space_scenario2 = base_obs_size + relative_obs_size * 4 # 2v3

a_space = 4 # rotation, x, y, shoot?
device = 'cuda'

log_path = "Trainings/Starships"

def init_weights(m):
    if isinstance(m, nn.Linear):
        init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
        if m.bias is not None:
            init.constant_(m.bias, 0)

def make_critic_net(obs_space):
    net =  nn.Sequential(  nn.Linear(obs_space, 512),
                                        nn.ReLU(),
                                        nn.Linear(512, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, 1))
    net.apply(init_weights)
    return net

def make_actor_net(obs_space):
    net =  nn.Sequential(    nn.Linear(obs_space, 512),
                                        nn.ReLU(),
                                        nn.Linear(512, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, a_space * 2)) # times 2 because we're outputting mean and std

    net.apply(init_weights)
    return net


def translate_observation(obs):
    #print("obs ", obs)
    return torch.tensor(obs, device = device)


"""
action space:
targetAngle = r(0);
targetVelocity (x, y) = {r(1), r(2)};
shoot = {r(3) > 0.5};
"""

def translate_output(net_output):
    actions = net_output.clamp(-1,1)
    result = np.array(actions.cpu())
    result[0] *=180
    result[1] *=10
    result[2] *=10
    return result

def train(scenario, iterations):
    env = Starships.Starships(2048, 300, 1, scenario) #max steps, video record, frame skip
    obs_space = obs_space_scenario0 if scenario == 0 else (obs_space_scenario1 if scenario == 1 else obs_space_scenario2)
    print(f"Training scenario {scenario} for {iterations} iterations, obs_space {obs_space}")
    ppo = SimplePPO(make_actor_net(obs_space), a_space, make_critic_net(obs_space), log_path+f"/timing_{scenario}", debug=True, horizon=4096, epochs=10, discount=0.95, gae=0.95,debug_period = 100, minibatch_size=2048, actor_lr=0.000003, critic_lr= 0.000003, entropy_factor=0.00005, translate_observation = translate_observation, translate_ouput= translate_output, target_device=device)
    ppo.train(env, iterations, export_model=True, resume=False, export_iteration_period=100)


def main(): 
    #train(0, 200)
    train(1, 50)
    #train(2, 8000)

if __name__ == "__main__":
    main()


#add a new layer / make the network bigger ONE BY ONE
#grad norm?

#optimize this env to make it way faster ey? TIME IT and stuff