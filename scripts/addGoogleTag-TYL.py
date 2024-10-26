import sys
import os

def insert_google_tag(file_name):
    # Define the Google Tag code to be inserted
    tag = """
    <!-- Google tag (gtag.js) -->
    <script async src="https://www.googletagmanager.com/gtag/js?id=G-2G4GYDL8RZ"></script>
    <script>
      window.dataLayer = window.dataLayer || [];
      function gtag(){dataLayer.push(arguments);}
      gtag('js', new Date());
      gtag('config', 'G-2G4GYDL8RZ');
    </script>"""
    
    # Check if the file exists
    if not os.path.exists(file_name):
        print(f"Error: File '{file_name}' not found.")
        return

    try:
        # Open the file for reading
        with open(file_name, 'r') as file:
            content = file.read()

        # Check if <head> tag is present
        if "<head>" not in content:
            print(f"Error: No <head> tag found in the file '{file_name}'.")
            return
        
        # Insert the Google tag after the first occurrence of <head>
        new_content = content.replace("<head>", "<head>\n" + tag, 1)

        # Write the modified content back to the file
        with open(file_name, 'w') as file:
            file.write(new_content)
        
        print(f"Google tag inserted successfully in '{file_name}'.")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Check for the correct number of command-line arguments
    if len(sys.argv) != 2:
        print("Usage: python insert_google_tag.py <filename>")
    else:
        file_name = sys.argv[1]
        insert_google_tag(file_name)
