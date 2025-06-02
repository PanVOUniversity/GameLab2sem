#!/bin/bash

# Check if folder path is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <folder_path>"
    exit 1
fi

folder_path="$1"
output_file="combined_files.txt"

# Check if folder exists
if [ ! -d "$folder_path" ]; then
    echo "Error: Folder '$folder_path' does not exist."
    exit 1
fi

# Clear or create the output file
> "$output_file"

# Find all files recursively and process them
find "$folder_path" -type f | while read -r file; do
    # Get the filename without path
    filename=$(basename "$file")
    
    # Add filename in quotes
    echo "\"$filename\"" >> "$output_file"
    
    # Add file content
    cat "$file" >> "$output_file"
    
    # Add a newline between files for better readability
    echo "" >> "$output_file"
done

echo "Makefile" >> "$output_file"

cat Makefile >> "$output_file"

echo "" >> "$output_file"

echo "All files have been combined into $output_file"