import re
import matplotlib.pyplot as plt
from datetime import datetime
from collections import defaultdict

def create_log_file():
    """Function to create a sample logfile.txt for testing."""
    with open('logfile.txt', 'w') as file:
        log_entries = [
            '2024-10-23 08:30:22 10.0.0.1 ERROR - Permission denied',
            '2024-10-23 08:30:22 10.0.0.1 INFO - User logged in',
            '2024-10-23 08:31:10 10.0.0.2 ERROR - File not found',
            '2024-10-23 08:31:12 10.0.0.2 INFO - User logged out',
            '2024-10-23 08:31:15 10.0.0.3 ERROR - Disk space low',
            '2024-10-23 08:31:20 10.0.0.1 ERROR - Unable to connect to server',
            '2024-10-23 08:31:25 10.0.0.4 ERROR - Permission denied',
            '2024-10-23 08:32:00 10.0.0.1 ERROR - File not found',
            '2024-10-23 08:32:10 10.0.0.2 ERROR - Permission denied'
        ]
        for entry in log_entries:
            file.write(entry + '\n')

def extract_error_info(logfile):
    """Extract unique error entries from the log file."""
    error_pattern = r'(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\s+([0-9.]+)\s+ERROR\s+-\s+(.*)'
    error_info = []

    try:
        with open(logfile, 'r') as file:
            for line in file:
                line = line.strip()
                match = re.search(error_pattern, line)
                if match:
                    timestamp = match.group(1)
                    ip_address = match.group(2)
                    error_message = match.group(3)
                    error_info.append((timestamp, ip_address, error_message))

        return error_info

    except FileNotFoundError:
        print(f"Error: The file '{logfile}' was not found.")
        return []

def count_unique_ips(errors):
    """Count occurrences of unique IP addresses from error logs."""
    ip_count = {}
    for _, ip_address, _ in errors:
        if ip_address in ip_count:
            ip_count[ip_address] += 1
        else:
            ip_count[ip_address] = 1
    return ip_count

def plot_ip_counts(ip_counts):
    """Visualize the count of unique IP addresses."""
    ips = list(ip_counts.keys())
    counts = list(ip_counts.values())

    plt.bar(ips, counts, color='skyblue')
    plt.xlabel('IP Addresses')
    plt.ylabel('Count of Errors')
    plt.title('Error Counts by IP Address')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

def visualize_errors(errors):
    """Visualize errors in a pie chart based on unique error messages."""
    error_messages = [error[2] for error in errors]
    error_counts = defaultdict(int)

    for message in error_messages:
        error_counts[message] += 1

    plt.figure(figsize=(10, 6))
    plt.pie(error_counts.values(), labels=error_counts.keys(), autopct='%1.1f%%', startangle=140)
    plt.title('Error Message Distribution')
    plt.axis('equal')  # Equal aspect ratio ensures that pie is drawn as a circle.
    plt.show()

def visualize_error_trends(errors):
    """Visualize error trends over time."""
    time_counts = defaultdict(int)

    for timestamp, _, _ in errors:
        date_time = datetime.strptime(timestamp, '%Y-%m-%d %H:%M:%S')
        hour = date_time.strftime('%Y-%m-%d %H')  # Group by hour
        time_counts[hour] += 1

    hours = list(time_counts.keys())
    counts = list(time_counts.values())

    plt.plot(hours, counts, marker='o')
    plt.xlabel('Time (Hour)')
    plt.ylabel('Number of Errors')
    plt.title('Error Trends Over Time')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.show()

def main():
    # Create the log file
    #create_log_file()

    # Extract error information
    logfile = 'logfile-autogen.txt'
    errors = extract_error_info(logfile)

    # Count unique IP addresses
    ip_counts = count_unique_ips(errors)

    # Visualize the results
    plot_ip_counts(ip_counts)

    # Visualize error distribution
    visualize_errors(errors)

    # Visualize error trends over time
    visualize_error_trends(errors)

if __name__ == '__main__':
    main()
