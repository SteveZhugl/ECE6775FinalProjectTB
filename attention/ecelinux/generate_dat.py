import random
import numpy as np
import math
import matplotlib.pyplot as plt
import scipy.stats as stats

def custom_round(number):
    if number >= 0:
        return int(math.floor(number))
    else:
        return int(math.ceil(number))

def generate_data():
    i = 64
    j = 64
    k = 64 
    # i = 4
    # j = 4
    # k = 4
    f1 = open("data/input_matrix1.dat", "w")
    f2 = open("data/input_matrix2.dat", "w")
    f1_quantized = open("data/quantized_input_matrix1.dat", "w")
    f2_quantized = open("data/quantized_input_matrix2.dat", "w")
    f3 = open("data/output_matrix.dat", "w")
    f3_quantized = open("data/quantized_output_matrix.dat", "w")
    f4 = open("data/intermediate_gemm.dat", "w")
    f4_quantized = open("data/quantized_intermediate_gemm.dat", "w")

    matrix_1 = np.zeros((i, j))
    matrix_2 = np.zeros((j, k))
    matrix_1_quantized = np.zeros((i, j))
    matrix_2_quantized = np.zeros((j, k))
    output_matrix = np.zeros((i, k))

    mean = 0
    std_dev = 1

    ij_points = i * j
    jk_points = j * k

    random_data_ij = np.random.normal(mean, std_dev, ij_points)
    random_data_jk = np.random.normal(mean, std_dev, jk_points)

    #! REMOVE LATER Plot a histogram to visualize the distribution
    # Create a figure and axis
    fig, ax = plt.subplots(figsize=(8, 6))

    # Histogram
    ax.hist(random_data_ij, bins=30, density=True, alpha=0.6, color='skyblue', edgecolor='black', label='Histogram')

    # Probability Density Function (PDF)
    xmin, xmax = plt.xlim()
    x = np.linspace(xmin, xmax, 100)
    p = stats.norm.pdf(x, mean, std_dev)
    ax.plot(x, p, 'k', linewidth=2, label='Distribution')

    # Points on the x-axis
    x_points = [-4, -2, -1, -0.5, -0.25, -0.125, -0.0625, 0, 0.0625, 0.125, 0.25, 0.5, 1, 2, 4]
    y_points = np.zeros(len(x_points))
    ax.scatter(x_points, y_points, color='red', label='NF4 Datatype Points', zorder=5)

    # Set labels and title
    ax.set_xlabel('Value')
    ax.set_ylabel('Probability Density')
    ax.set_title("Generated Data with Normal Distribution and NF4 Datatype")

    # Add a legend
    ax.legend()

    # Save the figure
    plt.savefig("output.png")

    for a in range(0, i * j):
        matrix_1[int(a / j)][a % j] = random_data_ij[a]
        matrix_1_quantized[int(a / j)][a % j] = int(custom_round(random_data_ij[a]))
        formatted_matrix_1_quantized = "{:.0f}".format(matrix_1_quantized[int(a / j)][a % j]) if matrix_1_quantized[int(a / j)][a % j].is_integer() else str(matrix_1_quantized[int(a / j)][a % j])
        f1.write(str(random_data_ij[a]) + "\n")
        f1_quantized.write(str(formatted_matrix_1_quantized) + "\n")
    for b in range(0, j * k):
        matrix_2[int(b / k)][b % k] = random_data_jk[b]
        matrix_2_quantized[int(b / k)][b % k] = int(custom_round(random_data_jk[b]))
        formatted_matrix_2_quantized = "{:.0f}".format(matrix_2_quantized[int(b / k)][b % k]) if matrix_2_quantized[int(b / k)][b % k].is_integer() else str(matrix_2_quantized[int(b / k)][b % k])
        f2.write(str(random_data_jk[b]) + "\n")
        f2_quantized.write(str(formatted_matrix_2_quantized) + "\n")

    gemm_output           = np.dot(matrix_1, matrix_2) / 2
    gemm_output_quantized = np.dot(matrix_1_quantized, matrix_2_quantized) / 2

    gemm_output = np.where(gemm_output >= 0, np.floor(gemm_output), np.ceil(gemm_output))
    gemm_output_quantized = np.where(gemm_output_quantized >= 0, np.floor(gemm_output_quantized), np.ceil(gemm_output_quantized))

    for x in range(0, i):
        for z in range(0, j):
            f4.write(str(gemm_output[x][z]) + "\n")
            formatted_quantized = "{:.0f}".format(gemm_output_quantized[x][z]) if gemm_output_quantized[x][z].is_integer() else str(gemm_output_quantized[x][z])
            f4_quantized.write(str(formatted_quantized) + "\n")

    for i, row in enumerate(gemm_output):
        vector_values = np.array(row)
        exponential_logits = np.exp(vector_values)
        probabilities = exponential_logits / np.sum(exponential_logits)
        output_matrix[i, :] = probabilities
        for j in range(0, len(probabilities)):
            f3.write(str(probabilities[j] * 100) + "\n")
            
    for i, row in enumerate(gemm_output_quantized):
        vector_values = np.array(row)
        exponential_logits = np.exp(vector_values)
        probabilities = exponential_logits / np.sum(exponential_logits)
        output_matrix[i, :] = probabilities
        for j in range(0, len(probabilities)):
            f3_quantized.write(str(probabilities[j] * 100) + "\n")

    # print("Input matrix 1: " + str(matrix_1))
    # print("Input matrix 2: " + str(matrix_2))
    # print("Output matrix: " + str(output_matrix))

if __name__ == "__main__":
    generate_data()