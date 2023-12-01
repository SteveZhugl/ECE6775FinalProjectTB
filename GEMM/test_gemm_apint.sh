#!/bin/bash

file="typedefs.h"
data_file="data/draft_c.txt"
output_ifle="output.txt"

# Define arrays of new values for dtype_in and dtype_out
new_dtype_in_values=(4 6 8)
new_dtype_out_values=(20 12 8)

# Check if the file exists
if [ -e "$file" ]; then
    for new_dtype_in in "${new_dtype_in_values[@]}"; do
        for new_dtype_out in "${new_dtype_out_values[@]}"; do
            # Change the values in the specified lines
            sed -i "s/typedef ap_int<[^>]*> dtype_in;/typedef ap_int<$new_dtype_in> dtype_in;/" "$file"
            sed -i "s/typedef ap_int<[^>]*> dtype_out;/typedef ap_int<$new_dtype_out> dtype_out;/" "$file"

            echo "Values in $file have been updated:"
            grep "typedef ap_int" "$file"

            # Run make command
            make

            # Collect data from the last line of data/draft_c.txt
            last_line_data=$(tail -n 1 "$data_file")
            echo "Data from the last line of $data_file: $last_line_data" >> "$output_file"

            # Add a newline for better readability
            echo
        done
    done
else
    echo "File $file not found."
fi
