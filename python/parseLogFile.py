"""
line.strip()
The .strip() method is used to remove any leading and trailing whitespace characters from the string. 
This includes spaces, tabs, and newlines (\n).

"""

# Parse log file line by line
def parse_log_file(logfile, search_string):
    count = 0
    with open(logfile, 'r') as file:
        for line in file:
            if search_string in line:
                count += 1
                print(line.strip())  # Print matching lines
    return count

logfile = 'logfile.txt'
search_string = 'CALL_DROP'
occurrences = parse_log_file(logfile, search_string)
print(f"Found '{search_string}' {occurrences} times.")