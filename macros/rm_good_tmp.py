#!/usr/bin/python3
import os 
from glob import glob

with open('sums_statuses.txt','r') as file:
    line = ''
    while ('files with status good') not in line:
        line = file.readline()

    i = 0
    while True:
        line = file.readline()
        if line == '': break
        line = line.split()[0]
        # print(f"os.remove(f'tmplogs/{line}.err')")
        # print(f"os.remove(f'tmplogs/{line}.log')")
        os.remove(f'tmplogs/{line}.err')
        os.remove(f'tmplogs/{line}.log')
