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
                    equation += f" - {-format_number(coef)}x{j+1}"
                else:
                    equation += f" + {format_number(coef)}x{j+1}"
        equation += f" = {b[i]}"
        print(equation)
    print("\nSolving using Gaussian Elimination with Partial Pivoting:\n")

def gaussian_elimination_partial_pivot(A, b):
    """
    Solves the system of linear equations Ax = b using Gaussian elimination with partial pivoting.

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

    # Forward elimination with partial pivoting
    for i in range(n):
        # Partial pivoting: find the maximum element in the current column
        max_row = np.argmax(np.abs(Ab[i:, i])) + i
        if i != max_row:
            Ab[[i, max_row]] = Ab[[max_row, i]]

        print(f"After partial pivoting for column {i+1}:")
        print(Ab)
        print()

        # Make the diagonal element 1 and eliminate below
        for j in range(i+1, n):
            factor = Ab[j, i] / Ab[i, i]
            Ab[j, i:] -= factor * Ab[i, i:]

        print(f"After elimination for column {i+1}:")
        print(Ab)
        print()

    # Back substitution
    x = np.zeros(n)
    for i in range(n-1, -1, -1):
        x[i] = (Ab[i, -1] - np.dot(Ab[i, i+1:n], x[i+1:])) / Ab[i, i]
        print(f"Back substitution step {n-i}: x{i+1} = {format_number(x[i])}")

    return x

# Example usage
if __name__ == "__main__":
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = f'gauss_elimination_with_pivot_output.txt'
    sys.stdout = OutputLogger(output_file)
    
    df = pd.read_csv('sorted_ids.csv')
    for i in df['ID']:
        print(f"\nExample {i}:")
        A = np.array([[1, 1, 1],
                      [2, -3, 4],
                      [3, 4, 5]])
        b = np.array([9, 13, 40])
        # A = np.array([[2, 2, 4],
        #               [3, 1, 2],
        #               [1, 4, 3]])
        # b = np.array([60, 60, 60])
        print_equations(A, b)
        try:
            solution = gaussian_elimination_partial_pivot(A, b)
            for index,i in enumerate(solution):
                print(f"x{index+1}= {format_number(i)}", end=' ')
            print()
        except Exception as e:
            print(e)
        break
