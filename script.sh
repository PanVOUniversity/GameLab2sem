#!/bin/bash

# Check if an output file name is provided as an argument
if [ -z "$1" ]; then
  echo "Usage: $0 <output_file.txt> [directory]"
  echo "  - <output_file.txt>: The name of the file to save the combined text."
  echo "  - [directory]: (Optional) The directory to search for files. Defaults to the current directory."
  exit 1
fi

output_file="$1"
search_dir="${2:-.}" # Default to current directory if no directory is provided

# Find all regular files in the specified directory (excluding directories)
find "$search_dir" -maxdepth 1 -type f -print0 | while IFS= read -r -d $'\0' file; do
  # Get the base name of the file
  file_name=$(basename "$file")

  # Print the file name enclosed in quotes
  echo "\"$file_name\""

  # Print the content of the file
  cat "$file"

  # Print a newline to separate content from different files
  echo ""
done > "$output_file"

echo "Successfully extracted text from files in '$search_dir' (excluding subdirectories) to '$output_file'."

exit 0