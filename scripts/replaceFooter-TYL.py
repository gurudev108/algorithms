import sys
import os

def replace_second_last_section(file_name):
    # The new section to replace the second-to-last </section>
    replacement = '''</section><section class="display-7" style="padding: 0;align-items: center;justify-content: center;flex-wrap: wrap;    align-content: center;display: flex;position: relative;height: 4rem;"><a href="https://github.com/gurudev108/theyogiclens.org" style="flex: 1 1;height: 4rem;position: absolute;width: 100%;z-index: 1;"><img alt="" style="height: 4rem;" src="data:image/gif;base64,R0lGODlhAQABAIAAAP///wAAACH5BAEAAAAALAAAAAABAAEAAAICRAEAOw=="></a><p style="margin: 0;text-align: center;" class="display-7">&#8204;</p><a style="z-index:1" href="https://github.com/gurudev108/theyogiclens.org">♡ If you like the website I created for myself, feel free to copy it from here ♾️</a></section><script src="assets/bootstrap/js/bootstrap.bundle.min.js"></script>  <script src="assets/parallax/jarallax.js"></script>  <script src="assets/smoothscroll/smooth-scroll.js"></script>  <script src="assets/ytplayer/index.js"></script>  <script src="assets/dropdown/js/navbar-dropdown.js"></script>  <script src="assets/embla/embla.min.js"></script>  <script src="assets/embla/script.js"></script>  <script src="assets/mbr-switch-arrow/mbr-switch-arrow.js"></script>  <script src="assets/countdown/countdown.js"></script>  <script src="assets/theme/js/script.js"></script>  <script src="assets/formoid/formoid.min.js"></script> '''

    # Check if the file exists
    if not os.path.exists(file_name):
        print(f"Error: File '{file_name}' not found.")
        return

    try:
        # Open the file for reading
        with open(file_name, 'r') as file:
            content = file.read()

        # Find all occurrences of </section>
        sections = content.split('</section>')

        if len(sections) < 3:
            print(f"Error: Less than two </section> tags found in the file '{file_name}'.")
            return

        # Replace the second-to-last </section> with the replacement section
        new_content = '</section>'.join(sections[:-2]) + replacement + '</section>'.join(sections[-1:])

        # Write the modified content back to the file
        with open(file_name, 'w') as file:
            file.write(new_content)
        
        print(f"Successfully replaced the second-to-last </section> in '{file_name}'.")

    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    # Check for the correct number of command-line arguments
    if len(sys.argv) != 2:
        print("Usage: python replace_second_last_section.py <filename>")
    else:
        file_name = sys.argv[1]
        replace_second_last_section(file_name)
