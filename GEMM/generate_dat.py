import random
import numpy as np

def generate_data():
    # i = 128
    # j = 256
    # k = 64 
    i = 4
    j = 4
    k = 4
    f1 = open("data/matrix_a_dat.dat", "w")
    f2 = open("data/matrix_b_dat.dat", "w")
    f3 = open("data/matrix_c_dat.dat", "w")
    matrix_1 = np.zeros((i, j))
    matrix_2 = np.zeros((j, k))
    output_matrix = np.zeros((i, k))

    for a in range(0, i * j):
        random_float = random.uniform(-32.0, 100.0)  
        matrix_1[int(a / j)][a % j] = random_float
        f1.write(str(random_float) + "\n")
    for b in range(0, j * k):
        random_float = random.uniform(-32.0, 100.0)  
        matrix_2[int(b / k)][b % k] = random_float
        f2.write(str(random_float) + "\n")

    output_matrix = np.dot(matrix_1, matrix_2)

    for row in output_matrix:
        for element in row:
            f3.write(str(element) + "\n")

    print("Input matrix 1: " + str(matrix_1))
    print("Input matrix 2: " + str(matrix_2))
    print("Output matrix: " + str(output_matrix))

if __name__ == "__main__":
    generate_data()