import re
import matplotlib.pyplot as plt
from collections import defaultdict
import seaborn as sns

# Function to extract date and error level from log lines using regex
def extract_error_info(logfile):
    pattern = r'(\d{4}-\d{2}-\d{2}) (\w+):'
    error_data = defaultdict(int)  # Dictionary to store error count per date
    
    with open(logfile, 'r') as file:
        for line in file:
            match = re.search(pattern, line)
            if match:
                date = match.group(1)
                error_level = match.group(2)
                error_data[(date, error_level)] += 1
    
    return error_data

# Visualize the frequency of errors by date and level
def visualize_error_trends(error_data):
    # Prepare data for plotting
    dates = []
    error_levels = []
    counts = []

    for key, count in error_data.items():
        dates.append(key[0])  # Date
        error_levels.append(key[1])  # Error level
        counts.append(count)  # Count of errors

    # Create a bar plot
    plt.figure(figsize=(12, 8))
    sns.barplot(x=dates, y=counts, hue=error_levels, palette='viridis')

    plt.title('Error Occurrences by Date and Level')
    plt.xlabel('Date')
    plt.ylabel('Occurrences')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

# Main script
logfile = 'logfile-autogen.txt'
errors = extract_error_info(logfile)
visualize_error_trends(errors)
