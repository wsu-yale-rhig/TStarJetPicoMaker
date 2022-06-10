#!/usr/bin/python3

'''
    Current:
    * Read output files in ./tmplogs/*.log and see if the file ran to completion.
    * See if the corresponding output file is in ./output/ (otherwise error with no-copy)
    * Write a sums-resub.csh file 

    Possible in the future:
    * If output is in ./output/ then get time to run, num calls, and events

'''

# look through the files in ./tmplogs/*.log and get statistics on what failed and what passed and why
from glob import glob
import os, subprocess
from sys import argv

# Count the 


err_files = glob("tmplogs/*.err")
n_total = len(err_files)
n_ping = 0
for file_name in err_files:
    try:
        file = open(file_name,'rb')
    except:
        continue

    file.seek(0, os.SEEK_END)
    last_line = ''
    # print('starting seek')
    try:
        while (file.read(1) != b'\n'):
            file.seek(-2,os.SEEK_CUR)
        last_line=str(file.readline())
    except:
        last_line = ''

    # print(f'this is last line: {last_line}')
    if 'For more details see ps(1)' in last_line:
        n_ping += 1

print(f'total: {n_total}   no_ping {n_ping}  ratio {1.*n_ping/n_total}')
