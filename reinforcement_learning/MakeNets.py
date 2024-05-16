

import torch.nn as nn
import torch.nn.init as init

def init_weights(m):
    if isinstance(m, nn.Linear):
        init.kaiming_normal_(m.weight, mode='fan_out', nonlinearity='relu')
        if m.bias is not None:
            init.constant_(m.bias, 0)

def make_narrow_net(obs_space, output_size):
    net =  nn.Sequential(  nn.Linear(obs_space, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, 64),
                                        nn.ReLU(),
                                        nn.Linear(64, output_size))
    net.apply(init_weights)
    return net

def make_base_net(obs_space, output_size):
    net =  nn.Sequential(  nn.Linear(obs_space, 512),
                                        nn.ReLU(),
                                        nn.Linear(512, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, output_size))
    net.apply(init_weights)
    return net

def make_wider_net(obs_space, output_size):
    net =  nn.Sequential(  nn.Linear(obs_space, 1024),
                                        nn.ReLU(),
                                        nn.Linear(1024, 512),
                                        nn.ReLU(),
                                        nn.Linear(512, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, output_size))
    net.apply(init_weights)
    return net


def make_deeper_net(obs_space, output_size):
    net =  nn.Sequential(  nn.Linear(obs_space, 512),
                                        nn.ReLU(),
                                        nn.Linear(512, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, 64),
                                        nn.ReLU(),
                                        nn.Linear(64, output_size))
    net.apply(init_weights)
    return net

def make_deeper_narrow_net(obs_space, output_size):
    net =  nn.Sequential(  nn.Linear(obs_space, 256),
                                        nn.ReLU(),
                                        nn.Linear(256, 128),
                                        nn.ReLU(),
                                        nn.Linear(128, 64),
                                        nn.ReLU(),
                                        nn.Linear(64, 32),
                                        nn.ReLU(),
                                        nn.Linear(32, output_size))
    net.apply(init_weights)
    return net
