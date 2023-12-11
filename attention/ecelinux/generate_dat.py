import random
import numpy as np
import math

def custom_round(number):
    if number >= 0:
        return int(math.floor(number))
    else:
        return int(math.ceil(number))

def generate_data():
    # i = 64
    # j = 64
    # k = 64 
    i = 4
    j = 4
    k = 4
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
    std_dev = 4

    ij_points = i * j
    jk_points = j * k

    random_data_ij = np.random.normal(mean, std_dev, ij_points)
    random_data_jk = np.random.normal(mean, std_dev, jk_points)

    #! REMOVE LATER Plot a histogram to visualize the distribution
    # plt.hist(random_data_ij, bins=30, density=True, alpha=0.6, color='g')

    # # Plot the probability density function (PDF)   
    # xmin, xmax = plt.xlim()
    # x = np.linspace(xmin, xmax, 100)
    # p = np.exp(-0.5 * ((x - mean) / std_dev) ** 2) / (std_dev * np.sqrt(2 * np.pi))
    # plt.plot(x, p, 'k', linewidth=2)

    # plt.title("Generated Data with Normal Distribution")
    # plt.savefig("output.png")

    for a in range(0, i * j):
        matrix_1[int(a / j)][a % j] = random_data_ij[a]
        matrix_1_quantized[int(a / j)][a % j] = int(custom_round(random_data_ij[a]))
        formatted_matrix_1_quantized = "{:.0f}".format(matrix_1_quantized[int(a / j)][a % j]) if matrix_1_quantized[int(a / j)][a % j].is_integer() else str(matrix_1_quantized[int(a / j)][a % j])
        f1.write(str(random_data_ij[a]) + "\n")
        f1_quantized.write(str(formatted_matrix_1_quantized) + "\n")
    for b in range(0, j * k):
        matrix_2[int(b / k)][b % k] = random_data_jk[b]
        matrix_2_quantized[int(b / j)][b % j] = int(custom_round(random_data_jk[b]))
        formatted_matrix_2_quantized = "{:.0f}".format(matrix_2_quantized[int(b / j)][b % j]) if matrix_2_quantized[int(b / j)][b % j].is_integer() else str(matrix_2_quantized[int(b / j)][b % j])
        f2.write(str(random_data_jk[b]) + "\n")
        f2_quantized.write(str(formatted_matrix_2_quantized) + "\n")

    gemm_output           = np.dot(matrix_1, matrix_2)
    gemm_output_quantized = np.dot(matrix_1_quantized, matrix_2_quantized)

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
            f3.write(str(probabilities[j]) + "\n")
            
    for i, row in enumerate(gemm_output_quantized):
        vector_values = np.array(row)
        exponential_logits = np.exp(vector_values)
        probabilities = exponential_logits / np.sum(exponential_logits)
        output_matrix[i, :] = probabilities
        for j in range(0, len(probabilities)):
            f3_quantized.write(str(probabilities[j]) + "\n")

    # print("Input matrix 1: " + str(matrix_1))
    # print("Input matrix 2: " + str(matrix_2))
    # print("Output matrix: " + str(output_matrix))

if __name__ == "__main__":
    generate_data()