# -*- coding: utf-8 -*-

import os

# argvs = (10, 20, 30, 40, 50, 100)

# argvs = (4, 8, 15, 20, 30, 50)

argvs = (25, 35, 40, 45)

cmd = "./a -F {} -W {} -R 0.9 -H {}"

cmd_naive = "./a -F {} -W 1 -R 0.9"

cmd_lsh = "./a -F {} -W 4 -R 0.9 -H 50 -B {}"

filename = "data/AOL/AOL.txt"
# filename = "data/kosarak/kosarak.txt"
# filename = "data/Booking/Booking_10.txt"

# if os.system(cmd_naive.format(filename)):
#     print("ERROR")

# for i in argvs:
#     if os.system(cmd.format(filename, 2, i)):
#         print("ERROR")

# for i in argvs:
#     if os.system(cmd.format(filename, 3, i)):
#         print("ERROR")

for i in argvs:
    if os.system(cmd_lsh.format(filename, i)):
        print("ERROR")