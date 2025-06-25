import numpy as np

def read_vectors_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()
        iter1 = int(lines[0])
        vector1 = np.array([float(x) for x in lines[1].split()])
        iter2 = int(lines[2])
        vector2 = np.array([float(x) for x in lines[3].split()])
    return iter1, vector1, iter2, vector2

def relative_error(vector1, vector2):
    norm_diff = np.linalg.norm(vector1 - vector2, 2)
    norm_vector1 = np.linalg.norm(vector1, 2)
    return norm_diff / norm_vector1

def compare_vectors(filename, threshold=0.01):
    iter11, vector11, iter21, vector21 = read_vectors_from_file(filename[0])
    iter12, vector12, iter22, vector22 = read_vectors_from_file(filename[1])
    if iter11 != iter12 or iter21 != iter22:
        print("The iteration numbers do not match.")
    else:
        print("The iteration numbers match.")
    error1 = relative_error(vector11, vector12)
    error2 = relative_error(vector21, vector22)
    if error1 <= threshold and error2 <= threshold:
        print("The relative error is within the acceptable range.")
    else:
        print("The relative error exceeds the acceptable range.")

if __name__ == "__main__":
    compare_vectors(['output.dat', "Practical03_sample_output5.dat"])