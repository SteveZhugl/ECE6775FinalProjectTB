#!/bin/bash

file="typedefs.h"
data_file="data/draft_c.txt"
output_file="apint_analysis_output.txt"
csynth_report="softmax_proj.prj/solution1/syn/report/dut_csynth.rpt"

# Define arrays of new values for dtype_in and dtype_out
new_dtype_in_values=(16 24 32)
new_dtype_out_values=(32 24 16)

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
            echo "Input Data Size: $new_dtype_in Output Data Size: $new_dtype_out" >> "$output_file"
            echo "Accuracy Difference: $last_line_data" >> "$output_file"
            sed -n '64p;78p' "$csynth_report" >> "$output_file"

            echo "" >> "$output_file"

            # Add a newline for better readability
            echo
        done
    done
else
    echo "File $file not found."
fi
