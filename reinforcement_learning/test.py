
import Starships

import numpy as np

def test():
    print("hellp world!")
    env = Starships.Starships()

    env.reset()

    done = False
    cum_r = 0
    step = 0

    while not done:
        action = np.array([0, 0, 0, 1], dtype=np.float32)
        obs, reward, done, trunc = env.step(action)
        print(f"done {done} trunc {trunc}")
        done = done or trunc
        cum_r += reward
        print(f"Step: {step}, State: {obs}, Reward: {reward}, Done: {done}, Cum_r: {cum_r}")
        step+=1

    print("done! world!")


def main():
    test()


main()