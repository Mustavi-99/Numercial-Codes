import numpy as np
import sys
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
        return str(int(num))
    
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
    print("\nSolving using Jacobi method:\n")
def jacobi_method(A, b, tolerance=1e-6, max_iterations=100):
    """
    Solves the system of linear equations Ax = b using the Jacobi method.

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
    x = np.zeros(n)  # Initial guess
    x_new = np.zeros(n)

    for iteration in range(1, max_iterations + 1):
        for i in range(n):
            sum_ = sum(A[i][j] * x[j] for j in range(n) if j != i)
            x_new[i] = (b[i] - sum_) / A[i][i]
        print(f"Iteration {iteration}: ")
        for index,i in enumerate(x):
            print(f"x{index}= {format_number(i)}", end=' ')
        print()
        
        for i in range(n):
            print(f"x{i+1}= ({format_number(b[i])}", end=' ')
            for j in range(n):
                if j != i:
                    print(f"- {format_number(A[i][j])} * {format_number(x[j])}", end=' ')
            print(f") / {format_number(A[i][i])} = {format_number(x_new[i])}")
        print()
        
        # Check stopping criterion (if any x changes below tolerance)
        for index,i in enumerate(x_new):
            print(f"e{index+1}: {format_number(x_new[index])} - {format_number(x[index])}/{format_number(x_new[index])} = {format_number(np.abs((x_new[index] - x[index])/x_new[index]))} <{tolerance}, no")
        print()
        if np.any(np.abs((x_new - x)/x_new) < tolerance):
            return x_new, iteration
        
        
        x_new = np.round(x_new, decimals=3)
        x = np.copy(x_new)
        

    raise ValueError("Solution did not converge within the maximum number of iterations")

# Example usage
if __name__ == "__main__":
    # timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = f'Jacobi.txt'
    sys.stdout = OutputLogger(output_file)
    
    A = np.array([[26, 2, 2],
                  [3, 27, 1],
                  [2, 3, 17]])
    b = np.array([12.6, -14.3, 6])
    tolerance = 2e-3
    print_equations(A, b)
    try:
        solution, iterations = jacobi_method(A, b, tolerance)
        print(f"Solution: {solution}")
        print(f"Converged in {iterations} iterations")
    except ValueError as e:
        print(e)