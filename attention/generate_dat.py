import random
import numpy as np

def generate_data():
    # i = 8
    # j = 8
    # k = 8 
    i = 4
    j = 4
    k = 4
    f1 = open("data/input_matrix1.dat", "w")
    f2 = open("data/input_matrix2.dat", "w")
    f3 = open("data/output_matrix.dat", "w")
    f4 = open("data/intermediate_gemm.dat", "w")
    matrix_1 = np.zeros((i, j))
    matrix_2 = np.zeros((j, k))
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
        f1.write(str(random_data_ij[a]) + "\n")
    for b in range(0, j * k):
        matrix_2[int(b / k)][b % k] = random_data_jk[b]
        f2.write(str(random_data_jk[b]) + "\n")

    gemm_output = np.dot(matrix_1, matrix_2)

    for x in range(0, i):
        for z in range(0, j):
            f4.write(str(gemm_output[x][z]) + "\n")

    for i, row in enumerate(gemm_output):
        vector_values = np.array(row)
        exponential_logits = np.exp(vector_values)
        probabilities = exponential_logits / np.sum(exponential_logits)
        output_matrix[i, :] = probabilities
        for j in range(0, len(probabilities)):
            f3.write(str(probabilities[j]) + "\n")



    print("Input matrix 1: " + str(matrix_1))
    print("Input matrix 2: " + str(matrix_2))
    print("Output matrix: " + str(output_matrix))

if __name__ == "__main__":
    generate_data()