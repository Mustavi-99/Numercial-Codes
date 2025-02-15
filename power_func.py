import numpy as np
import pandas as pd
import math
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
    return f"{num:.4f}"

def power_func(x_values, y_values):
    x_logs = np.array([format_number(math.log(x)) for x in x_values])
    y_logs = np.array([format_number(math.log(y)) for y in y_values])
    
    x_logs2 = np.array([format_number(math.pow(float(x),2)) for x in x_logs])
    x_logs_y = np.array([format_number(float(x)*float(y)) for x,y in zip(x_logs, y_logs)])
    
    n = len(x_values)
    sum_x = np.sum([float(x) for x in x_values])
    sum_y = np.sum([float(y) for y in y_values])
    sum_x_log = np.sum([float(x) for x in x_logs])
    sum_y_log = np.sum([float(y) for y in y_logs])
    sum_x_log2 = np.sum([float(x) for x in x_logs2])
    sum_x_logy = np.sum([float(xy) for xy in x_logs_y])
    print("Converting to logarithmic form:")
    
    print("xi\t\tyi\t\tln(xi)\t\tln(yi)\t\tln(xi)^2\t\tln(xi) * ln(yi)")
    for x, y, x_log, y_log, x_log2, x_logy in zip(x_values, y_values, x_logs, y_logs, x_logs2, x_logs_y):
        print(f"{x}\t\t{y}\t\t{x_log}\t\t{y_log}\t\t{x_log2}\t\t\t{x_logy}")
    print("\nSums:")
    print(f"Σx = {format_number(sum_x)}")
    print(f"Σy = {format_number(sum_y)}")
    print(f"Σln(x) = {format_number(sum_x_log)}")
    print(f"Σln(y) = {format_number(sum_y_log)}")
    print(f"Σln(x)² = {format_number(sum_x_log2)}")
    print(f"Σ(ln(x)ln(y)) = {format_number(sum_x_logy)}")
    print(f"n = {n}")
    b = float(format_number((n*sum_x_logy - sum_x_log*sum_y_log) / (n*sum_x_log2 - sum_x_log**2)))
    print(f"b = {n}*{sum_x_logy} - {sum_x_log}*{sum_y_log} / {n}*{sum_x_log2} - {sum_x_log}² = {b}")
    a = float(format_number(math.exp((sum_y_log - b*sum_x_log) / n)))
    print(f"a = e^(({sum_y_log} - {b}*{sum_x_log}) / {n}) = {a}")
    return a,b
# Example usage
if __name__ == "__main__":
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = f'power_func.txt'
    sys.stdout = OutputLogger(output_file)
    # Data points
    x_values = [2, 3, 5, 7, 9]
    y_values = [4, 5, 7, 10, 15]

    # Get the Lagrange Interpolation Polynomial
    a,b = power_func(x_values, y_values)
    print("Power Function: y = a * x^b")
    print(f"a = {a}, b = {b}")
    print(f"Power Function: y = {a} * x^{b}")

    # Evaluate the polynomial at a specific point (optional)
    x_point = 8
    value_at_point = a * math.pow(x_point, b)
    print(f"\nValue at x = {x_point}: {value_at_point}")