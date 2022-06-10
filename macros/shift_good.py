#!/opt/star/sl73_gcc485/bin/python
from glob import glob
import os

good_list = set()
with open('sums_statuses.txt','r') as f_in:
    while True:
        line = f_in.readline()
        if not line:
            break
        if line[:24] == ' files with status good:':
            print line
            break
    while True:
        line = f_in.readline()
        if not line:
            break
        good_list.add(int(line.split()[0].split('_')[1]))

for good in good_list:
    name = '_output/C5069F692AF1CFD4F85D60D341744E36_%i.root'%good
    if not os.path.isfile(name):
        print('Missing: ',good)
    else:
        os.rename(name,'_output/complete/C5069F692AF1CFD4F85D60D341744E36_%i.root'%good)

# print good_list
# os.rename('junka','junkb')

# move all completed
# for f in glob('_output/*.root'):
    # print f
