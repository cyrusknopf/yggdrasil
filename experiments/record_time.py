import subprocess
import csv
import argparse
import time

def run_program(command):
    start_time = time.process_time()
    result = subprocess.run(command, stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    end_time = time.process_time()
    elapsed_time = end_time - start_time
    return elapsed_time

def write_to_csv(filename, tag, time_data):
    with open(filename, 'a', newline='') as csvfile:
        fieldnames = ['tag', 'cpu_time']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        
        # Write header if file is empty
        if csvfile.tell() == 0:
            writer.writeheader()
        
        row = {'tag': tag, 'cpu_time': time_data}
        writer.writerow(row)

def main():
    parser = argparse.ArgumentParser(description='Run a program and record the CPU time into a CSV file.')
    parser.add_argument('tag', type=str, help='Tag for the CSV entry')
    parser.add_argument('command', type=str, help='The command to run')
    parser.add_argument('csvfile', type=str, help='CSV file to write the timing data')
    parser.add_argument('runs', type=int, help='Number of times to run the command')
    
    args = parser.parse_args()

    command = args.command.split()  # Split the command into a list for subprocess
    for i in range(args.runs):
        elapsed_time = run_program(command)
        print(f"Run {i+1}/{args.runs}: CPU time = {elapsed_time:.6f} seconds")
        write_to_csv(args.csvfile, args.tag, elapsed_time)

if __name__ == '__main__':
    main()
