
import Starships

import numpy as np

def test_rendering():
    env = Starships.Starships()
    env.init_rendering()
    env.reset()

    done = False
    cum_r = 0
    step = 0

    while not done:
        action = np.array([0, -10, 0, 1], dtype=np.float32)
        obs, reward, done, trunc = env.step(action)
        env.draw()
        done = done or trunc
        cum_r += reward
        print(f"Step: {step}, State: {obs}, Reward: {reward}, Done: {done}, Cum_r: {cum_r}")
        step+=1


def fake_actions(obs):
    shape = obs.shape
    total_elements = np.prod(shape)
    actions = np.arange(total_elements).reshape(shape)
    return actions

def test():
    env = Starships.Starships(2048, 100, 2)
    obs, _ = env.reset()

    done = False
    cum_r = 0
    step = 0

    while not done:
        print("obs", obs)
        actions = fake_actions(obs)
        print("actions", actions)
        obs, reward, done, trunc, _ = env.step(actions)
        done = done or trunc
        cum_r += reward
        print(f"Step: {step}, State: {obs}, Reward: {reward}, Done: {done}, Cum_r: {cum_r}")
        step+=1


"""
    tactic.targetAngle = r(0);
    tactic.targetVelocity = {r(1), r(2)};
    tactic.shoot = {r(3) > 0.5};
"""

def main():
    test()
    #test_rendering()


main()