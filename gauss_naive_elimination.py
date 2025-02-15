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
    print("\nSolving using Naive Gauss Elimination:\n")

def naive_gaussian_elimination(A, b):
    """
    Solves the system of linear equations Ax = b using naive Gaussian elimination.

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

    # Forward elimination
    for i in range(n):
        # Ensure the pivot element is non-zero
        if Ab[i, i] == 0:
            raise ValueError("Zero pivot encountered. Cannot proceed with naive Gaussian elimination.")
        
        # Eliminate entries below the pivot
        for j in range(i+1, n):
            factor = Ab[j, i] / Ab[i, i]
            Ab[j, i:] -= factor * Ab[i, i:]
        
            print(f"After elimination for column {i+1}, row {j+1}:")
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
    output_file = f'gauss_naive_output_{timestamp}.txt'
    sys.stdout = OutputLogger(output_file)
    
    df = pd.read_csv('sorted_ids.csv')
    # for i in df['ID']:
    for i in range(4):	
        print(f"\nExample {i}:")
        # A = np.array([[i, 3, 4],
        #               [4, i-2, 6],
        #               [3, 4.5, i+2]])
        # b = np.array([5, 7, 6])
        A = np.array([[i+1, 1, 1],
                      [i+2, -1, 3],
                      [i+4, 5, -10]])
        b = np.array([6, 4, 13])
        print_equations(A, b)
        try:
            solution = naive_gaussian_elimination(A, b)
            for index, value in enumerate(solution):
                print(f"x{index+1}= {format_number(value)}", end=' ')
            print()
        except Exception as e:
            print(e)
        # break
