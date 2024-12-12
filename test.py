import subprocess
from rich.console import Console
from rich.table import Table

console = Console()

# Function to run a command and capture output and errors
def run_command(command):
    try:
        result = subprocess.run(command, shell=True, capture_output=True, text=True)
        return result.stdout, result.stderr, result.returncode
    except Exception as e:
        return "", str(e), 1

# Function to extract relevant performance metrics from the output
def extract_relevant_metrics(output):
    metrics = {}
    for line in output.split("\n"):
        if "Minor (reclaiming a frame) page faults" in line:
            metrics["Minor Page Faults"] = line.split(":")[-1].strip()
        elif "Major (requiring I/O) page faults" in line:
            metrics["Major Page Faults"] = line.split(":")[-1].strip()
        elif "Maximum resident set size" in line:
            metrics["Max Resident Size"] = line.split(":")[-1].strip()
    return metrics

# Function to compare performance of standard malloc vs custom malloc for tests 0,1,2
def compare_malloc(test_name, executable):
    output = []

    # Standard malloc test
    std_command = f"/usr/bin/time -v ./{executable}"
    std_out, std_err, std_ret = run_command(std_command)
    if std_ret != 0:
        return f"[red]{test_name} Standard malloc failed: {std_err.strip()}[/red]"
    std_metrics = extract_relevant_metrics(std_err)
    output.append(f"Standard malloc command: [cyan]{std_command}[/cyan]")
    output.append(f"Standard malloc metrics: {std_metrics}")

    # Custom malloc test
    custom_command = f"./run_linux.sh /usr/bin/time -v ./{executable}"
    custom_out, custom_err, custom_ret = run_command(custom_command)
    if custom_ret != 0:
        return f"[red]{test_name} Custom malloc failed: {custom_err.strip()}[/red]"
    custom_metrics = extract_relevant_metrics(custom_err)
    output.append(f"Custom malloc command: [cyan]{custom_command}[/cyan]")
    output.append(f"Custom malloc metrics: {custom_metrics}")

    # Comparison
    comparison = [
        f"Minor Page Faults: Standard={std_metrics.get('Minor Page Faults', 'N/A')}, Custom={custom_metrics.get('Minor Page Faults', 'N/A')}",
        f"Major Page Faults: Standard={std_metrics.get('Major Page Faults', 'N/A')}, Custom={custom_metrics.get('Major Page Faults', 'N/A')}",
        f"Max Resident Size: Standard={std_metrics.get('Max Resident Size', 'N/A')}, Custom={custom_metrics.get('Max Resident Size', 'N/A')}",
    ]
    output.append("Comparison:")
    output.extend(comparison)
    
    return "\n".join(output)

# Test scenarios
# Tests 0, 1, 2 will have memory details
part1_tests = [
    {"name": "Malloc Test", "source": "test0.c", "exec": "test0", "compile_cmd": "gcc -o test0 test0.c"},
    {"name": "Malloc Allocation Test", "source": "test1.c", "exec": "test1", "compile_cmd": "gcc -o test1 test1.c"},
    {"name": "Free Test", "source": "test2.c", "exec": "test2", "compile_cmd": "gcc -o test2 test2.c"},
]

# Tests 3, 4, 5 will show binary output only
part2_tests = [
    {"name": "Realloc Test", "source": "test3.c", "exec": "./run_linux.sh /usr/bin/time -v ./test3", "compile_cmd": "gcc -o test3 test3.c -L. -lft_malloc"},
    {"name": "Show Alloc Memory Test", "source": "test4.c", "exec": "./run_linux.sh /usr/bin/time -v ./test4", "compile_cmd": "gcc -o test4 test4.c -L. -lft_malloc"},
    {"name": "Alignment Test", "source": "test5.c", "exec": "./run_linux.sh /usr/bin/time -v ./test5", "compile_cmd": "gcc -o test5 test5.c -L. -lft_malloc"},
]

# Dashboard 1 for part1 tests (detailed memory comparison)
part1_table = Table(title="Part 1 Tests (Detailed Memory Comparison)")
part1_table.add_column("Test Name", justify="left")
part1_table.add_column("Compilation Status", justify="center")
part1_table.add_column("Performance Comparison", justify="left")

for test in part1_tests:
    # Compile the source code
    compile_command = test["compile_cmd"]
    compile_stdout, compile_stderr, compile_retcode = run_command(compile_command)
    
    if compile_retcode != 0:
        part1_table.add_row(test["name"], "[red]Failed[/red]", compile_stderr.strip())
    else:
        # Compare performance using compare_malloc
        comparison_result = compare_malloc(test["name"], test["exec"])
        part1_table.add_row(test["name"], "[green]Success[/green]", comparison_result)

# Dashboard 2 for part2 tests (binary output only, no memory details)
part2_table = Table(title="Part 2 Tests (Binary Output Only)")
part2_table.add_column("Test Name", justify="left")
part2_table.add_column("Compilation Status", justify="center")
part2_table.add_column("Execution Output", justify="left")

for test in part2_tests:
    # Compile the source code
    compile_command = test["compile_cmd"]
    compile_stdout, compile_stderr, compile_retcode = run_command(compile_command)
    
    if compile_retcode != 0:
        part2_table.add_row(test["name"], "[red]Failed[/red]", compile_stderr.strip())
        continue
    
    # Run the test (no memory extraction, just raw output)
    exec_command = test["exec"]
    exec_stdout, exec_stderr, exec_retcode = run_command(exec_command)
    if exec_retcode != 0:
        part2_table.add_row(test["name"], "[green]Success[/green]", f"[red]Execution failed: {exec_stderr.strip()}[/red]")
    else:
        # Show binary (raw) output only
        part2_table.add_row(test["name"], "[green]Success[/green]", exec_stdout.strip())

# Display both tables (two dashboards)
console.print(part1_table)
console.print(part2_table)
