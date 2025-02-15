import numpy as np
import pandas as pd
import sys
from datetime import datetime

class OutputLogger:
    def __init__(self, filename):
        self.terminal = sys.stdout
        self.log = open(filename, 'a', encoding='utf-8')

    def write(self, message):
        self.terminal.write(message)
        self.log.write(message)

    def flush(self):
        self.terminal.flush()
        self.log.flush()
        
def format_number(num):
    # Check if effectively integer
    
    if abs(num - round(num)) < 1e-10:
        return int(num)
    
    # Try different decimal places
    for decimals in range(1, 4):
        rounded = round(num, decimals)
        if abs(num - rounded) < 1e-10:
            return f"{rounded:.{decimals}f}"
    
    # Default to 3 decimals
    return f"{num:.3f}"

def print_equations(A, b):
    n = len(A)
    print("\nSystem of equations:")
    for i in range(n):
        equation = ""
        for j in range(n):
            coef = A[i][j] 
            if j == 0:
                if coef == 1:
                    equation += f"x{j+1}"
                else:
                    equation += f"{format_number(coef)}x{j+1}"
            else:
                if coef == 1:
                    equation += f" + x{j+1}"
                elif coef == -1:
                    equation += f" - x{j+1}"
                elif coef < 0:
                    equation += f" - {-1*format_number(coef)}x{j+1}"
                else:
                    equation += f" + {format_number(coef)}x{j+1}"
        equation += f" = {b[i]}"
        print(equation)
    print("\nSolving using Gauss-Jordan Elimination:\n")

def format_matrix(matrix):
    # Format each element in matrix
    n, m = matrix.shape
    formatted = np.zeros_like(matrix)
    for i in range(n):
        for j in range(m):
            val = matrix[i,j]
            if abs(val - round(val)) < 1e-10:
                formatted[i,j] = int(round(val))
            else:
                formatted[i,j] = round(val, 3)
    return formatted

def gauss_jordan_elimination(A, b):
    """
    Solves the system of linear equations Ax = b using Gauss-Jordan elimination.

    Parameters:
    A : numpy.ndarray
        Coefficient matrix (n x n).
    b : numpy.ndarray
        Right-hand side vector (n).

    Returns:
    x : numpy.ndarray
        Solution vector.
    """
    A = np.array(A, dtype=np.float64)
    b = np.array(b, dtype=np.float64)
    n = len(b)

    # Augment matrix A with vector b
    Ab = np.column_stack([A, b])

    # Gauss-Jordan elimination
    for i in range(n):
        # Partial pivoting: ensure the pivot element is the largest in the column
        max_row = np.argmax(np.abs(Ab[i:, i])) + i
        if i != max_row:
            Ab[[i, max_row]] = Ab[[max_row, i]]

        # Normalize the pivot row
        Ab[i] = Ab[i] / Ab[i, i]
        Ab = format_matrix(Ab)
        
        print(f"After normalizing row {i+1}:")
        print(Ab)
        print()

        # Eliminate all other entries in the current column
        for j in range(n):
            if j != i:
                factor = Ab[j, i]
                Ab[j] -= factor * Ab[i]
                Ab = format_matrix(Ab)

        print(f"After eliminating column {i+1}:")
        print(Ab)
        print()

    # Extract solution
    x = Ab[:, -1]
    return x

# Example usage
if __name__ == "__main__":
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = f'gauss_jordan_output_{timestamp}.txt'
    sys.stdout = OutputLogger(output_file)

    df = pd.read_csv('sorted_ids.csv')
    for i in range(0,10):
        print(f"\nExample {i}:")
        A = np.array([[3, -(i+2), 5, -1],
                      [-1, i+3, -1, 4],
                      [-2, -(i+1), 4, 9],
                      [1, i, 3, 1]])
        b = np.array([-8.0, 9.0, -9.0,-2.0])
        # A = np.array([[1, 1, 1],
        #               [2, -3, 4],
        #               [3, 4, 5]])
        # b = np.array([9, 13, 40])
        print_equations(A, b)
        try:
            solution = gauss_jordan_elimination(A, b)
            for index, value in enumerate(solution):
                print(f"x{index+1}= {format_number(value)}", end=' ')
            print()
        except Exception as e:
            print(e)
        # break
