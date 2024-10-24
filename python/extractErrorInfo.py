"""
Advanced Regex matching - You can also use regex groups to extract specific parts of a string. 
For example, to extract a date and error level from a log line.

Output:
Found 21 errors:
Timestamp: 2024-10-23 19:54:50, IP: 164.160.15.235, Error: ERROR: Network timeout
Timestamp: 2024-10-23 19:54:50, IP: 29.65.151.125, Error: ERROR: Permission denied
Timestamp: 2024-10-23 19:54:50, IP: 180.181.218.150, Error: ERROR: Permission denied
Timestamp: 2024-10-23 19:54:50, IP: 197.239.147.144, Error: ERROR: Permission denied
Timestamp: 2024-10-23 19:54:50, IP: 36.134.69.43, Error: ERROR: Connection reset by peer
Timestamp: 2024-10-23 19:54:50, IP: 121.65.145.231, Error: ERROR: Permission denied
Timestamp: 2024-10-23 19:54:50, IP: 156.183.251.59, Error: ERROR: Connection reset by peer
Timestamp: 2024-10-23 19:54:50, IP: 209.140.145.6, Error: ERROR: Access denied
Timestamp: 2024-10-23 19:54:50, IP: 149.255.36.52, Error: ERROR: Connection reset by peer
Timestamp: 2024-10-23 19:54:50, IP: 207.65.49.90, Error: ERROR: Network timeout
Timestamp: 2024-10-23 19:54:50, IP: 169.32.111.71, Error: ERROR: Access denied
Timestamp: 2024-10-23 19:54:50, IP: 213.153.173.202, Error: ERROR: Permission denied
Timestamp: 2024-10-23 19:54:50, IP: 50.220.70.124, Error: ERROR: Network timeout
Timestamp: 2024-10-23 19:54:50, IP: 157.212.60.42, Error: ERROR: Network timeout
Timestamp: 2024-10-23 19:54:50, IP: 211.236.116.20, Error: ERROR: Access denied
Timestamp: 2024-10-23 19:54:50, IP: 88.137.11.215, Error: ERROR: Connection reset by peer
Timestamp: 2024-10-23 19:54:50, IP: 90.89.56.32, Error: ERROR: File not found
Timestamp: 2024-10-23 19:54:50, IP: 130.148.67.143, Error: ERROR: File not found
Timestamp: 2024-10-23 19:54:50, IP: 62.51.138.5, Error: ERROR: Network timeout
Timestamp: 2024-10-23 19:54:50, IP: 74.77.164.9, Error: ERROR: Connection reset by peer
Timestamp: 2024-10-23 19:54:50, IP: 41.112.184.114, Error: ERROR: File not found
"""

import re

def extract_error_info(logfile):
    # Regular expression pattern to match log entries with ERROR level
    error_pattern = r'(\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2})\s+([0-9.]+)\s+ERROR\s+-\s+(.*)'

    error_info = []

    try:
        with open(logfile, 'r') as file:
            for line in file:
                line = line.strip()  # Remove leading and trailing whitespace
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

# Example usage
logfile = 'logfile-autogen.txt'
errors = extract_error_info(logfile)

if errors:
    print(f"Found {len(errors)} errors:")
    for error in errors:
        print(f"Timestamp: {error[0]}, IP: {error[1]}, Error: {error[2]}")
else:
    print("No errors found.")


"""
Explanation of Changes:
Regular Expression:
The pattern now matches the exact format of the log entries:
Timestamp: Matches YYYY-MM-DD HH:MM:SS.
IP address: Matches standard IPv4 addresses.
ERROR log level: Matches the string ERROR followed by - and the error message.
Parsing Each Line:
The re.search() function looks for lines that match the error pattern.
It extracts the timestamp, IP address, and error message, and stores them as a tuple in the error_info list.
"""