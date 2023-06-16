import subprocess

methods = ["CM", "CU", "CMM", "Count", "naive"]

network_interface = "wlp0s20f3"

packet_number = 10000

commands = []

for method in methods:
    command = f"sudo time -v ./analyzer {method} {network_interface} {packet_number} > {method}.out"
    # print(command)
    commands.append(command)

processes = []
for command in commands:
    process = subprocess.Popen(command, shell=True)
    processes.append(process)

# Wait for all processes to complete
for process in processes:
    process.wait()
