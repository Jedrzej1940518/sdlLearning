
import math

from PpoAgent import *
import torch.nn.init as init
import Starships

obs_space = 8 #
a_space = 4 # shoot, x, y


log_path = "Trainings/Starships"

def init_weights(m):
    if isinstance(m, nn.Linear):
        init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
        if m.bias is not None:
            init.constant_(m.bias, 0)

#critic
critic_net =  nn.Sequential(  nn.Linear(obs_space, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 64),
                                        nn.ReLU(),
                                        nn.Linear(64, 1))

#actor 
actor_net = nn.Sequential(    nn.Linear(obs_space, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 64),
                                        nn.ReLU(),
                                        nn.Linear(64, a_space * 2)) # times 2 because we're outputting mean and std

critic_net.apply(init_weights)
actor_net.apply(init_weights)



def translate_observation(obs):
    #print("obs ", obs)
    return torch.tensor(obs)


"""
action space:
targetAngle = r(0);
targetVelocity (x, y) = {r(1), r(2)};
shoot = {r(3) > 0.5};
"""


def translate_output(net_output):
    actions = net_output.clamp(-1, 1)
    result = np.array(actions)
    result[0] *=180
    result[1] *=10
    result[2] *=10
    return result

def train():
    env = Starships.Starships(10000, 20)
    ppo = SimplePPO(actor_net, a_space, critic_net, log_path, translate_observation = translate_observation, translate_ouput= translate_output, debug=True, debug_period = 25, target_device='cpu', minibatch_size=64, entropy_factor=0.00001)
    ppo.train(env, 5000, export_model=True, resume=False, export_iteration_period=50)


def test():
    env = Starships.Starships()
    ppo = SimplePPO(actor_net, a_space, critic_net, log_path, translate_observation = translate_observation, translate_ouput= translate_output)
    ppo.test(env)

def main(): 
    train()
    #test()

if __name__ == "__main__":
    main()
