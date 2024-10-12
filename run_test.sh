#!/bin/bash

# Create or clear the output file
output_file="test_results.txt"
echo "" > "$output_file"

# Function to compile and run each test
run_test() {
    test_number=$1
    test_file="test${test_number}.c"
    executable="test${test_number}"

    echo "Running Test ${test_number}" | tee -a "$output_file"
    echo "----------------------------" | tee -a "$output_file"

    # Compile the test program
    gcc -o "$executable" "$test_file"
    if [ $? -ne 0 ]; then
        echo "Compilation of $test_file failed." | tee -a "$output_file"
        echo "" | tee -a "$output_file"
        return
    fi

    # Run the test without custom malloc
    echo "Without custom malloc:" | tee -a "$output_file"
    /usr/bin/time -l ./"$executable" 2>&1 | tee -a "$output_file"
    echo "" | tee -a "$output_file"

    # Run the test with custom malloc
    echo "With custom malloc:" | tee -a "$output_file"
    ./run.sh /usr/bin/time -l ./"$executable" 2>&1 | tee -a "$output_file"
    echo "" | tee -a "$output_file"

    echo "" | tee -a "$output_file"
}

# Run tests from test0 to test5
for i in {0..5}; do
    run_test "$i"
done

echo "All tests completed. Results are in $output_file."
