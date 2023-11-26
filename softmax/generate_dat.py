import random
import numpy as np

def generate_data():
    vector_size = 10
    input_file = open("data/vector_dat.dat", "w")   
    output_file = open("data/output_dat.dat", "w")
    
    vector_values = []

    for i in range(0, vector_size):
        vector_value = input_file.write(str(random.uniform(-128, 128)) + "\n")
        vector_values.append(vector_value)

    exponential_logits = np.exp(vector_values)
    probabilities = exponential_logits / np.sum(exponential_logits)

    for j in range(0, vector_size):
        output_file.write(str(probabilities[j]) + "\n")

if __name__ == "__main__":
    generate_data()