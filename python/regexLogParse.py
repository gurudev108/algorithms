import re
"""
re.search(pattern, string)
Searches for the first occurrence of the pattern in the string.
Returns a match object if the pattern is found; otherwise, returns None.

    match = re.search(r'\d+', 'My number is 12345')
    if match:
        print(match.group())  # Output: 12345

re.match(pattern, string)
Tries to match the pattern from the start of the string.
Returns a match object if the pattern matches from the beginning of the string; otherwise, returns None.

    match = re.match(r'\d+', '12345 is my number')
    if match:
        print(match.group())  # Output: 12345

re.findall(pattern, string)
Finds all occurrences of the pattern in the string.
Returns a list of matches.

    matches = re.findall(r'\d+', 'My numbers are 12345 and 67890')
    print(matches)  # Output: ['12345', '67890']

re.split(pattern, string)
Splits the string by occurrences of the pattern and returns a list of substrings.

    result = re.split(r'\s+', 'This is a test')  # Split by any whitespace
    print(result)  # Output: ['This', 'is', 'a', 'test']

re.sub(pattern, repl, string)
Replaces all occurrences of the pattern in the string with repl.
Returns a new string with the replacements.

    result = re.sub(r'\d+', 'NUMBER', 'I have 2 apples and 3 bananas')
    print(result)  # Output: 'I have NUMBER apples and NUMBER bananas'

re.fullmatch(pattern, string)
Checks if the entire string matches the pattern.
Returns a match object if the pattern completely matches the string; otherwise, returns None.
    match = re.fullmatch(r'\d+', '12345')
    if match:
        print("Full match")  # Output: Full match

re.compile(pattern)
Compiles a regular expression pattern into a regex object, which can be reused for multiple operations.
Useful for performance when you’re running the same pattern repeatedly.

    pattern = re.compile(r'\d+')
    print(pattern.findall('My numbers are 123 and 456'))  # Output: ['123', '456']

"""

# Function to parse log using regex
def regex_log_parse(logfile, pattern):
    matches = []
    with open(logfile, 'r') as file:
        for line in file:
            match = re.search(pattern, line)
            if match:
                matches.append(match.group(0))  # Extract matching string
    return matches

def regex_log_parse_unique_ip(logfile, ip_pattern):
    try:
        with open(logfile, 'r') as file:
            data = file.read()
        
        # Find all IP addresses in the log data
        all_ips = re.findall(ip_pattern, data)
        
        # Convert list of IPs to a set to get only unique IPs
        unique_ips = set(all_ips)

        # Use dict.fromkeys() to maintain order and remove duplicates
        # unique_ips = list(dict.fromkeys(all_ips))

        # Replace all IP addresses with '***.***.***.***'
        anonymized_log = re.sub(ip_pattern, '***.***.***.***', data)
        print("Anonymized log:")
        print(anonymized_log)
        
        return unique_ips
        
    except FileNotFoundError:
        print(f"Error: File {logfile} not found")
        return None

# Example: Match an IP address in the log file
logfile = 'tcp.csv'
ip_pattern = r'\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b'

# Extract all IP addresses
#ip_addresses = regex_log_parse(logfile, ip_pattern)

# Extract unique IP addresses
ip_addresses = regex_log_parse_unique_ip(logfile, ip_pattern)

print(f"Found IP addresses: {ip_addresses}")

"""
Popular Regular Expression Patterns

Digit Matching:
\d: Matches any digit (equivalent to [0-9]).

pattern = r'\d+'  # Matches one or more digits

Word Matching:
\w: Matches any word character (alphanumeric and underscore).

pattern = r'\w+'  # Matches one or more word characters

Whitespace Matching:
\s: Matches any whitespace character (spaces, tabs, newlines).

pattern = r'\s+'  # Matches one or more whitespace characters


Email Validation:

pattern = r'[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}'

Regex Pattern for IPv4:

ip_pattern = r'\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b'

ip_pattern = r'\b(?:[0-9]{1,3}\.){3}[0-9]{1,3}\b'
Explanation of the IP Address Regex:
\b: Asserts a word boundary (ensures no partial matches, such as "123.456.789.01234").
(?: ... ): A non-capturing group that allows us to repeat the pattern for each segment of the IP.
[0-9]{1,3}: Matches any number between 0 and 999 (although real IPs will only go up to 255).
\.: Matches the dot (.) between the octets.
{3}: Ensures that there are exactly 3 repetitions of the first part (i.e., matching 3 octets).
[0-9]{1,3}: Matches the final octet (the 4th part of the IP address).


"""