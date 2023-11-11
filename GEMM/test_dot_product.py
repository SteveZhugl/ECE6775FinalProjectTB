import numpy as np

# Define the input matrices
matrix1 = np.array([[96.54493539, 18.1994501, -14.02076167, 22.28588434],
                    [51.7997013, 34.57728339, 49.82446559, 25.024654],
                    [60.43237102, -7.64353912, 39.64862952, 77.45566335],
                    [30.80886715, 34.26991719, 66.72238357, 12.34125062]])

matrix2 = np.array([[-21.39921686, 60.27895566, -26.737447, 57.18196083],
                    [68.00066812, 87.07713878, 22.7776964, 14.02618478],
                    [45.87307151, 22.227748, 4.65822092, -5.92220942],
                    [42.71188323, 6.12616536, 82.26174545, 85.44987527]])

# Calculate the dot product
dot_product_result = np.dot(matrix1, matrix2)

print("Matrix 1:")
print(matrix1)

print("\nMatrix 2:")
print(matrix2)

print("\nDot Product Result:")
print(dot_product_result)
