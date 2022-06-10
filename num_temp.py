#!/usr/bin/python3

skip = []
for L in open('temp','r').readlines():
    skip.append(int(L.strip()))
print(skip)

line = ''
with open('temp2','r') as in_file:
    line = in_file.readline()
each = line.split(',')
print(each)

keep = []
for entry in each:
    E = int(entry.strip())
    if E not in skip:
        keep.append(f"{E}")
    else:
        print('skip',E)

redo = ','.join(keep)
print(redo)

with open('sums_res.csh','w') as fout:
    fout.write(f'star-submit -r {redo} schedBA485DDE195DC967489E7B082C154220.session.xml')
