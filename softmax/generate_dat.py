import random
import numpy as np

def generate_data():
    vector_size = 128
    input_file = open("data/vector_dat.dat", "w")   
    output_file = open("data/output_dat.dat", "w")
    
    vector_values = []

    for i in range(0, vector_size):
        vector_value = random.uniform(-8, 7)
        input_file.write(str(vector_value) + "\n")
        vector_values.append(vector_value)

    vector_values = np.array(vector_values)

    exponential_logits = np.exp(vector_values)
    probabilities = exponential_logits / np.sum(exponential_logits)

    for j in range(0, vector_size):
        output_file.write(str(probabilities[j]) + "\n")

if __name__ == "__main__":
    generate_data()