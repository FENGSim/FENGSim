import numpy as np
import os
import glob
import re

files = glob.glob(os.path.join("./", "dump_p.*.LAMMPS"))
files_sorted = sorted(files, key=lambda x: int(re.search(r'dump_p\.(\d+)\.LAMMPS', x).group(1)))

i = 0
while i < len(files_sorted) :
    data = np.loadtxt(files_sorted[i], skiprows=9)

    if data.ndim == 1:
        data = data.reshape(1, -1)
    id = data[:, 2]
    x = data[:, 3]
    y = data[:, 4]
    z = data[:, 5]

    f = open('./dump_p_'+str(i)+'.vtk', 'w')
    
    f.write("# vtk DataFile Version 2.0\n")
    f.write("mpm example\n")
    f.write("ASCII\n")
    f.write("DATASET POLYDATA\n")
    f.write("POINTS "+str(len(x))+" float\n")

    j = 0
    while j < len(x) :
        f.write(str(x[j]) + " " + str(y[j]) + " " + str(z[j]) + "\n")
        j = j+1
        
    f.write("VERTICES " + str(len(x)) + " " + str(2*len(x)) + "\n")
    j = 0
    while j < len(x) :
        f.write("1 " + str(j) + "\n")
        j = j+1

    i = i+1
    
files = glob.glob(os.path.join("./", "dump_g.*.LAMMPS"))
files_sorted = sorted(files, key=lambda x: int(re.search(r'dump_g\.(\d+)\.LAMMPS', x).group(1)))

i = 0
while i < len(files_sorted) :
    data = np.loadtxt(files_sorted[i], skiprows=9)

    if data.ndim == 1:
        data = data.reshape(1, -1)
    id = data[:, 2]
    x = data[:, 3]
    y = data[:, 4]
    z = data[:, 5]

    f = open('./dump_g_'+str(i)+'.vtk', 'w')

    f.write("# vtk DataFile Version 2.0\n")
    f.write("mpm example\n")
    f.write("ASCII\n")
    f.write("DATASET POLYDATA\n")
    f.write("POINTS "+str(len(x))+" float\n")

    j = 0
    while j < len(x) :
        f.write(str(x[j]) + " " + str(y[j]) + " " + str(z[j]) + "\n")
        j = j+1
        
    f.write("VERTICES " + str(len(x)) + " " + str(2*len(x)) + "\n")
    j = 0
    while j < len(x) :
        f.write("1 " + str(j) + "\n")
        j = j+1
            
    i = i+1
