import torch

sigma = torch.tensor([-3, -1, 0, 1, 3])  # Example tensor with negative and positive values
bounded_sigma = 1 - torch.exp(-sigma)

print(bounded_sigma)
