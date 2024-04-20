import matplotlib.pyplot as plt
import numpy as np
import statistics
import platform
import os
import subprocess
import sys

def clear_cache():
    system_os = platform.system()
    if system_os == 'Windows':
        ...
    elif system_os == 'Darwin':
        subprocess.run(['sudo', 'purge'])
    elif system_os == 'Linux':
        subprocess.run(['sudo', 'sync'])
        subprocess.run(['sudo', 'sh', '-c', 'echo 3 > /proc/sys/vm/drop_caches'])
    else: return 'Unknown OS'

def draw_histogram(stats_data):
    writing_stats = stats_data["writing"]
    total_stats = stats_data["total"]

    categories = ["Writing", "Total"]
    metrics = ["Minimum", "Average", "Standard Deviation"]
    x = np.arange(len(categories))
    width = 0.35

    fig, ax = plt.subplots(figsize=(10, 6))

    for i, metric in enumerate(metrics):
        values = [writing_stats[i], total_stats[i]]
        ax.bar(x + (i - 1) * width, values, width, label=metric)

    ax.set_xlabel('Categories')
    ax.set_ylabel('Values')
    ax.set_title('Statistics Comparison')
    ax.set_xticks(x)
    ax.set_xticklabels(categories)
    ax.legend()

    save_dir = "histograms"
    if not os.path.exists(save_dir): os.makedirs(save_dir)

    filename = os.path.join(save_dir, 'combined_histogram.png')
    plt.savefig(filename)
    plt.close()

def execute_program(iterations, enable_cache):
    cpp_exec = "bin/countwords_seq"
    all_times = []
    stats_data = dict()
    min_total, avg_total, std_total, min_writing, avg_writing, std_writing = 0, 0, 0, 0, 0, 0
    config_file = 'data/data.txt'
    for int_method in range(int(iterations)):
        if enable_cache: clear_cache() # if u write 1 in second arg
        command = [cpp_exec, config_file]
        one_try = subprocess.run(command, stdout=subprocess.PIPE, text=True)
        total, writing = one_try.stdout.strip().split("\n")
        total = int(total.split("=")[1])
        writing = int(writing.split("=")[1])
        all_times.append([total, writing])

    min_total = min(all_times, key=lambda x: x[0])[0]
    print(f"Total:\nMinimum word count time:\t\t{min_total}")
    avg_total = statistics.mean([x[0] for x in all_times])
    print(f"Average counting time: \t\t\t{avg_total:0.5f}")
    try: std_total = statistics.stdev([x[0] for x in all_times], xbar=avg_total)
    except statistics.StatisticsError as e: std_total = 0
    print(f"Corrected sample standard deviation:\t{std_total:0.5f}\n")

    min_writing = min(all_times, key=lambda x: x[1])[1]
    print(f"Writing:\nMinimum word count time:\t\t{min_writing}")
    avg_writing = statistics.mean([x[1] for x in all_times])
    print(f"Average counting time: \t\t\t{avg_writing:0.5f}")
    try: std_writing = statistics.stdev([x[1] for x in all_times], xbar=avg_writing)
    except statistics.StatisticsError as e: std_writing = 0
    print(f"Corrected sample standard deviation:\t{std_writing:0.5f}\n")

    stats_data["total"] = (min_total, avg_total, std_total)
    stats_data["writing"] = (min_writing, avg_writing, std_writing)

    return stats_data

if __name__ == "__main__":
    if len(sys.argv) != 3: sys.exit(1) #error code 1
    iterations = sys.argv[1]
    cache_flag = sys.argv[2]
    histograms_data = execute_program(iterations, cache_flag)
    draw_histogram(histograms_data)
    sys.exit(0) #error code 0 (no errors)
