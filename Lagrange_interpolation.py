import sympy as sp
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
        return int(num)
    
    # Try different decimal places
    for decimals in range(1, 4):
        rounded = round(num, decimals)
        if abs(num - rounded) < 1e-10:
            return f"{rounded:.{decimals}f}"
    
    # Default to 3 decimals
    return f"{num:.3f}"

def lagrange_interpolation(x_values, y_values):
    """
    Constructs the Lagrange Interpolation Polynomial.
    
    Parameters:
    x_values : list or array-like
        The x-coordinates of the data points.
    y_values : list or array-like
        The y-coordinates of the data points.

    Returns:
    polynomial : sympy expression
        The symbolic Lagrange Interpolation Polynomial.
    """
    # Define the symbolic variable
    x = sp.symbols('x')
    n = len(x_values)
    
    # Initialize the polynomial
    polynomial = 0

    # Compute the Lagrange basis polynomials and the full polynomial
    for i in range(n):
        print(f"\nStep {i+1}: Calculate L_{i}(x)")
        basis = 1
        print(f"L_{i}(x) = ", end="")
        
        for j in range(n):
            if j != i:
                term = (x - x_values[j])/(x_values[i] - x_values[j])
                basis *= term
                print(f"(x - {format_number(x_values[j])})/{format_number(x_values[i] - x_values[j])} × ", end="")
        
        term = basis * y_values[i]
        polynomial += term
        print(f"\nTerm {i+1}: {term}")
        print(f"Current polynomial: {polynomial}\n")
    
    print("\nFinal Lagrange Interpolation Polynomial:")
    print(f"P(x) = {polynomial.expand()}")
    
    return polynomial

# Example usage
if __name__ == "__main__":
    # timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = f'Lagrange_interpolation.txt'
    sys.stdout = OutputLogger(output_file)
    # Data points
    x_values = [1, 2, 3, 5]
    y_values = [10.0, 4.0, 4.0, 7.0]

    # Get the Lagrange Interpolation Polynomial
    polynomial = lagrange_interpolation(x_values, y_values)
    print("Lagrange Interpolation Polynomial:")
    print(polynomial)

    # Evaluate the polynomial at a specific point (optional)
    x_point = 7
    value_at_point = polynomial.subs('x', x_point)
    print(f"\nValue at x = {x_point}: {value_at_point}")
