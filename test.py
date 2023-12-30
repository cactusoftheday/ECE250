import sys
import math
import os
import subprocess

in_files = [x for x in os.listdir() if x.endswith(".in")]

def check_print(command, output, comparator):
    out_sort = output.split().sort()
    comp_sort = output.split().sort()
    return out_sort == comp_sort

# valid forwards and reverse
def check_path(command, output, comparator):
    out_list = output.split()
    comp_list = comparator.split()
    return (out_list == comp_list) or (out_list[::-1] == comp_list)

def check_lowest(command, output, comparator):
    if (output == comparator == "failure"):
        return True
    # remove lowest is prefix
    out_num = float(output[10:])
    comp_num = float(output[10:])
    return math.isclose(out_num, comp_num)


def print_diff(line, cmd_arg, out, comp):
    print(f"---------Line: {line}---------")
    print(f"Command: {cmd_arg}")
    print(f"Output: {out}")
    print(f"Expected: {comp}")

for infile in in_files:
    outfile_name = infile[:-3] + ".out"
    outfile_path = os.path.join(os.getcwd(), outfile_name)
    if (not os.path.isfile(outfile_path)):
        continue
    command_file_name = os.path.join(os.getcwd(), infile)
    output_file_name = os.path.join(os.getcwd(), infile[:-3] + "_SCRIPT.out")
    comparator_file_name = outfile_path

    command_file = []
    output_file = []
    comparator_file = []
    with open(command_file_name, 'r') as f_in, open(output_file_name, 'w') as f_out:
        subprocess.run(['./a.out', '-v'], stdin=f_in, stdout=f_out)


    with open(command_file_name) as file:
        for line in file: 
            line = line.strip()
            command_file.append(line)

    with open(output_file_name) as file:
        for line in file: 
            line = line.strip()
            output_file.append(line)

    with open(comparator_file_name) as file:
        for line in file: 
            line = line.strip()
            comparator_file.append(line)

# assert(len(command_file) == len(output_file)+1)

    errors = 0
    for line, cmd_arg in enumerate(command_file):
        cmd = cmd_arg.split()[0]
        if (cmd == "END"):
            break
        out = output_file[line]
        comp = comparator_file[line]
        if (cmd == "PRINT"):
            if not check_print(cmd_arg, out, comp):
                errors += 1
                print_diff(line, cmd_arg, out, comp)
        elif (cmd == "PATH"):
            if not check_path(cmd_arg, out, comp):
                errors += 1
                print_diff(line, cmd_arg, out, comp)
        elif (cmd == "LOWEST"):
            if not check_lowest(cmd_arg, out, comp):
                errors += 1
                print_diff(line, cmd_arg, out, comp)
        elif (out != comp):
            errors += 1
            print_diff(line, cmd_arg, out, comp)

    print("==============")
    print(infile)
    if (errors > 0):
        print(f"Failed with {errors} errors")
    else:
        print(f"All tests passed")

