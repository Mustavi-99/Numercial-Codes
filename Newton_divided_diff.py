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


def newton_divided_difference(x_values, y_values):
    """
    Constructs the Newton's Divided Difference Interpolation Polynomial.

    Parameters:
    x_values : list or array-like
        The x-coordinates of the data points.
    y_values : list or array-like
        The y-coordinates of the data points.

    Returns:
    polynomial : sympy expression
        The symbolic Newton's Divided Difference Interpolation Polynomial.
    """
    # Define the symbolic variable
    x = sp.symbols('x')
    n = len(x_values)

    # Create the divided difference table
    dd_table = [[0] * n for _ in range(n)]
    for i in range(n):
        dd_table[i][0] = y_values[i]

    # Fill the divided difference table
    for j in range(1, n):
        for i in range(n - j):
            dd_table[i][j] = (dd_table[i + 1][j - 1] - dd_table[i][j - 1]) / (x_values[i + j] - x_values[i])

    # Display the divided difference table
    print("Divided Difference Table:")
    for row in dd_table:
        print([format_number(val) for val in row])

    # Construct the Newton's Interpolation Polynomial
    polynomial = dd_table[0][0]
    term = 1

    for i in range(1, n):
        term *= (x - x_values[i - 1])
        polynomial += dd_table[0][i] * term
        print(f"Step {i}: Polynomial so far: {polynomial.expand()}")

    print("\nFinal Newton's Divided Difference Polynomial:")
    print(f"P(x) = {polynomial.expand()}")

    return polynomial


# Example usage
if __name__ == "__main__":
    output_file = f'Newtons_divided_difference.txt'
    sys.stdout = OutputLogger(output_file)

    # Data points
    x_values = [4, 5, 7, 10,11,13]
    y_values = [48.0, 100.0, 294.0, 900.0, 1210.0, 2028.0]

    # Get the Newton's Divided Difference Polynomial
    polynomial = newton_divided_difference(x_values, y_values)
    print("Newton's Divided Difference Polynomial:")
    print(polynomial)

    # Evaluate the polynomial at a specific point (optional)
    x_point = 8
    value_at_point = polynomial.subs('x', x_point)
    print(f"\nValue at x = {x_point}: {value_at_point}")
    
    x_point = 9
    value_at_point = polynomial.subs('x', x_point)
    print(f"\nValue at x = {x_point}: {value_at_point}")
