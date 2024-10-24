# Search and Count occurence of keyword in the data
def count_instances(logfile, logstring):
    try:
        with open(logfile, 'r') as file:
            data = file.read()
        
        # Count occurrences of the search string
        instances = data.count(logstring)
        return instances
        
    except FileNotFoundError:
        print(f"Error: File {logfile} not found")
        return None


# the code block under this condition will only run when the script is executed directly, 
# not when it's imported into another script.
if __name__ == "__main__":
    logfile = input("Enter log file name: ")
    logstring = input("Enter string to search: ")

    #count = count_instances(logfile, logstring)
    count = parse_log_file(logfile, logstring)
    if count is not None:
        print(f"{count} instances of {logstring} found in {logfile} ")