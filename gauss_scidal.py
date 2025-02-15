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
    # Handle infinity and NaN
    if np.isinf(num) or np.isnan(num):
        return str(num)
    
    # Handle regular numbers
    try:
        if abs(num - round(num)) < 1e-10:
            return int(round(num))
        
        for decimals in range(1, 4):
            rounded = round(num, decimals)
            if abs(num - rounded) < 1e-10:
                return f"{rounded:.{decimals}f}"
        
        return f"{num:.3f}"
    except (OverflowError, ValueError):
        return str(num)

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
                    equation += f"{coef}x{j+1}"
            else:
                if coef == 1:
                    equation += f" + x{j+1}"
                elif coef == -1:
                    equation += f" - x{j+1}"
                elif coef < 0:
                    equation += f" - {-coef}x{j+1}"
                else:
                    equation += f" + {coef}x{j+1}"
        equation += f" = {b[i]}"
        print(equation)
    print("\nSolving using Gauss-Seidel method:\n")

def gauss_seidel_method(A, b, tolerance=1e-6, max_iterations=100,initial_guess=None):
    """
    Solves the system of linear equations Ax = b using the Gauss-Seidel method.

    Parameters:
    A : numpy.ndarray
        Coefficient matrix (n x n).
    b : numpy.ndarray
        Right-hand side vector (n).
    tolerance : float
        Stopping criterion for the solution.
    max_iterations : int
        Maximum number of iterations.

    Returns:
    x : numpy.ndarray
        Solution vector.
    iterations : int
        Number of iterations performed.
    """
    n = len(b)
    x = initial_guess if initial_guess is not None else np.zeros(n)

    for iteration in range(1, max_iterations + 1):
        x_old = np.copy(x)

        print(f"Iteration {iteration}:")
        for index,i in enumerate(x):
            print(f"x{index+1}= {format_number(i)}, ", end=' ')
        print()
        for i in range(n):
            sum_ = sum(A[i][j] * x[j] for j in range(n) if j != i)
            x[i] = (b[i] - sum_) / A[i][i]
            print(f"x{i+1} = ({format_number(b[i])}", end=" ")
            for j in range(n):
                if j != i:
                    print(f"- {format_number(A[i][j])} * {format_number(x[j])}", end=" ")
            print(f") / {format_number(A[i][i])} = {format_number(x[i])}")

        print()

        # Check stopping criterion (if any x changes below tolerance)
        for i in range(n):
            error = abs((x[i] - x_old[i]) / x[i])
            print(f"e{i+1}: {format_number(x[i])} - {format_number(x_old[i])} / {format_number(x[i])} = {(abs((x[i] - x_old[i]) / x[i]))} < {tolerance}, no")

        if np.any(np.abs((x - x_old) / x) < tolerance):
            return x, iteration

        print()

    raise ValueError("Solution did not converge within the maximum number of iterations")

# Example usage
if __name__ == "__main__":
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = f'gauss_seidel_output_{timestamp}.txt'
    sys.stdout = OutputLogger(output_file)

    df = pd.read_csv('sorted_ids.csv')
    for i in df['ID']:
        print(f"\nExample {i}:")
        # A = np.array([[2, i, 10],
        #               [5, i+1, 3],
        #               [1, i+2, 9]])
        # b = np.array([-17, 14, 7])
        A = np.array([[1, 1, 1],
                      [1, 3, 1],
                      [1, 2, 2]])
        b = np.array([7.0, 13.0, 13.0])
        initial_guess = np.array([0, 0., 0.])  # Initial guess
    
        tolerance = 1e-2
        print(tolerance)
        print_equations(A, b)
        try:
            solution, iterations = gauss_seidel_method(A, b, tolerance,max_iterations=6,initial_guess=initial_guess)
            for index,i in enumerate(solution):
                print(f"x{index+1}= {format_number(i)}", end=' ')
            print(f"\nConverged in {iterations} iterations")
        except ValueError as e:
            print(e)
        # break
