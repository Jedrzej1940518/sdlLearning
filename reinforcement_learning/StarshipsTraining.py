
import math

from PpoAgent import *
import torch.nn.init as init
import Starships

obs_space = 116  #
a_space = 4 # rotate, x, y, shoot
device = 'cuda'

log_path = "Trainings/Starships"

def init_weights(m):
    if isinstance(m, nn.Linear):
        init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
        if m.bias is not None:
            init.constant_(m.bias, 0)

#critic
critic_net =  nn.Sequential(  nn.Linear(obs_space, 2048),
                                        nn.ReLU(),
                                        nn.Linear(2048, 2048),
                                        nn.ReLU(),
                                        nn.Linear(2048, 1024),
                                        nn.ReLU(),
                                        nn.Linear(1024, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, 1))

#actor 
actor_net = nn.Sequential(    nn.Linear(obs_space, 2048),
                                        nn.ReLU(),
                                        nn.Linear(2048, 2048),
                                        nn.ReLU(),
                                        nn.Linear(2048, 1024),
                                        nn.ReLU(),
                                        nn.Linear(1024, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, a_space * 2)) # times 2 because we're outputting mean and std

critic_net.apply(init_weights)
actor_net.apply(init_weights)



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
    result[..., 0] +=1
    result[..., 0] *=180
    result[..., 1] *=10
    result[..., 2] *=10
    return result

def train():
    env = Starships.Starships(2048, 200, 2) #max steps, video record, frame skip
    ppo = SimplePPO(actor_net, a_space, critic_net, log_path, debug=True, debug_period = 200, minibatch_size=2048, actor_lr=0.00001, min_actor_lr=0.000001, entropy_factor=0.000001, translate_observation = translate_observation, translate_ouput= translate_output, target_device=device)
    ppo.train(env, 10000, export_model=True, resume=False, export_iteration_period=50)


def test():
    env = Starships.Starships()
    ppo = SimplePPO(actor_net, a_space, critic_net, log_path, translate_observation = translate_observation, translate_ouput= translate_output)
    ppo.test(env)

def main(): 
    train()
    #test()

if __name__ == "__main__":
    main()
