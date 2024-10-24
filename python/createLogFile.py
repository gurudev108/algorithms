"""
Create logfile-autogen.txt for extract_error_info() in extractErrorInfo.py
"""
import random
from datetime import datetime

# Function to generate a random IP address
def generate_ip():
    return f"{random.randint(1, 255)}.{random.randint(1, 255)}.{random.randint(1, 255)}.{random.randint(1, 255)}"

# Sample log levels and messages
log_levels = ["INFO", "WARNING", "ERROR", "DEBUG"]
error_messages = [
    "ERROR: File not found",
    "ERROR: Network timeout",
    "ERROR: Access denied",
    "ERROR: Disk space low",
    "ERROR: Permission denied",
    "ERROR: Connection reset by peer"
]

# Create and write to logfile.txt
with open('logfile-autogen.txt', 'w') as logfile:
    for _ in range(100):  # Write 100 log entries
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        ip_address = generate_ip()
        log_level = random.choice(log_levels)
        message = random.choice(error_messages) if log_level == "ERROR" else "Operation successful"
        
        log_entry = f"{timestamp} {ip_address} {log_level} - {message}\n"
        logfile.write(log_entry)

print("logfile-autogen.txt created successfully!")
