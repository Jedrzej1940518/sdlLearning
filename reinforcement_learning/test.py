import numpy as np
import matplotlib.pyplot as plt
def smooth_l1_loss(x):
# Define the Smooth L1 Loss
    return np.where(np.abs(x) < 1, 0.5 * x**2, np.abs(x) - 0.5)
def rounded_mse(x):
# Define the Rounded MSE function
    return (np.round(x))**2
def visualize_functions(x_range):
    x_values = np.linspace(-3, 3, num=400) # Generate x values within the specified range
    y_smooth_l1 = smooth_l1_loss(x_values)
    y_rounded_mse = rounded_mse(x_values)
    plt.figure(figsize=(12, 6))
    plt.subplot(1, 2, 1)
    plt.plot(x_values, y_smooth_l1, label='Smooth L1 Loss')
    plt.title('Smooth L1 Loss')
    plt.xlabel('x')
    plt.ylabel('Loss')
    plt.grid(True)
    plt.legend()
    plt.subplot(1, 2, 2)
    plt.plot(x_values, y_rounded_mse, label='Rounded MSE', color='red')
    plt.title('Rounded MSE')
    plt.xlabel('x')
    plt.ylabel('Loss')
    plt.grid(True)
    plt.legend()
    plt.tight_layout()
    plt.show()
# Call the function to visualize
visualize_functions((-3, 3))
