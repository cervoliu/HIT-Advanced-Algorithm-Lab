import numpy as np
import matplotlib.pyplot as plt

file = open("CMM.out", "r")

lines = file.readlines()

Max = 0
Total = 0

for i in range(0, len(lines), 2):
    ip, max_size, total = lines[i].strip().split(", ")
    ip = ip.split(" = ")[1]
    max_size = int(max_size.split(" = ")[1])
    total = int(total.split(" = ")[1])
    # print(ip, max_size, total)
    Max = max(Max, max_size)
    Total += total

threshold = 100

# width = Max // 20
# ranges = []
# num = 0
# for i in range(1, Max + 1, width):
#     num += 1
#     j = min(Max, i + width - 1)
#     ranges.append((i, j))
# ranges_str = [str(x) for x in ranges]
# # print(ranges)

# for i in range(0, len(lines), 2):
#     ip, max_size, total = lines[i].strip().split(", ")
#     ip = ip.split(" = ")[1]
#     max_size = int(max_size.split(" = ")[1])
#     total = int(total.split(" = ")[1])

#     arr = list(map(int, lines[i+1].strip().split()))
#     arr.extend([0] * (Max - len(arr)))

#     sums = []
    
#     for (l, r) in ranges:
#         sum = 0
#         for j in range(l - 1, r): # 0-based indexing
#             sum += arr[j]
#         sums.append(sum)
    
#     plt.plot(sums, ranges_str, label=ip)

num = 30  # 设置分段数量
ranges = np.logspace(1, np.log10(Max), num+1, dtype=int)  # 生成对数刻度
ranges_str = [f"{ranges[i]}-{ranges[i+1]}" for i in range(len(ranges)-1)]

for i in range(0, len(lines), 2):
    ip, max_size, total = lines[i].strip().split(", ")
    ip = ip.split(" = ")[1]
    max_size = int(max_size.split(" = ")[1])
    total = int(total.split(" = ")[1])

    arr = list(map(int, lines[i+1].strip().split()))
    arr.extend([0] * (Max - len(arr)))

    sums = []
    
    for i in range(len(ranges)-1):
        l, r = ranges[i], ranges[i+1]
        sum = 0
        for j in range(l - 1, r): # 0-based indexing
            sum += arr[j]
        sums.append(sum)
    
    if total > threshold: plt.plot(sums, ranges_str, label=ip)
    else: plt.plot(sums, ranges_str)

# plt.xticks(range(len(ranges_str)), ranges_str, rotation=30)
# plt.xscale('log')
plt.xlabel('Number of packets')

plt.ylabel('Packet size')

#plt.legend(loc='upper right')
plt.legend(loc='lower right')
plt.title('Estimated Packet size distribution for different IP addresses')
plt.show()
