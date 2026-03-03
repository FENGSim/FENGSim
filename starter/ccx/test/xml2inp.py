import xml.etree.ElementTree as E
import sys
import json
import re

xml_file_name = input("input .xml file: ");
xml_file_name = xml_file_name + ".xml"
print (".xml file is", xml_file_name)

mesh_file_name = input("input .inp file: ");
mesh_file_name = mesh_file_name + ".inp"
print (".inp file is", mesh_file_name)

f = open('modal2.inp', 'w')
f2 = open(mesh_file_name, 'r')

tree = E.parse(xml_file_name)
root = tree.getroot()

ELSET = []
MATERIAL = []
ELASTIC = []
DENSITY = []
frequency = 1

for child in root:
    if child.tag == "Materials" :
        for child1 in child:
            ELSET.append(child1.tag)
            for child2 in child1:
                if child2.tag == "MATERIAL" :
                    MATERIAL.append(child2.text)
                if child2.tag == "ELASTIC" :
                    values = re.split(',',child2.text)
                    ELASTIC.append(float(values[0]))
                    ELASTIC.append(float(values[1]))
                if child2.tag == "DENSITY" :
                    DENSITY.append(float(child2.text))
    if child.tag == "Frequency" :
        frequency = int(child.text)

print(ELSET)
print(MATERIAL)
print(ELASTIC)
print(DENSITY)
print(frequency)

#    *include, input=all2.msh
#    *MATERIAL, NAME=Aluminium
#    *ELASTIC
#    70000, 0.34
#    *DENSITY
#    2.7e-9
#    *SOLID SECTION, ELSET=Eall,MATERIAL=Aluminium
#    1
#    *STEP
#    *frequency
#    12
#    *NODE FILE
#    U
#    *END STEP

#f.write("*include, input=all2.msh" + "\n")

var = 0
for line in f2:
    line = line[:-1]
    values_point = re.split(', ',line)
    if (values_point[0]=="*NODE") :
        var = 1
    if (values_point[0]=="*ELEMENT") :
        var = 1
    if (values_point[0]=="*NSET") :
        var = 1
    if (values_point[0]=="*ELSET") :
        var = 1
    if var == 1 :
        f.write(line+"\n")

i = 0
while i < len(MATERIAL):
    j = 0
    same = 0
    while j < i:
        if (MATERIAL[i]==MATERIAL[j]) :
            same = 1
        j += 1
    if (same==0) :
        f.write("*MATERIAL, NAME=" + MATERIAL[i] + "\n")
        f.write("*ELASTIC"+"\n")
        f.write(str(ELASTIC[0+i*2]) + ", " + str(ELASTIC[1+i*2]) +"\n")
        f.write("*DENSITY"+"\n")
        f.write(str(DENSITY[i])+"\n")
    i += 1

i = 0
while i < len(MATERIAL):    
    f.write("*SOLID SECTION, ELSET="+ELSET[i]+",MATERIAL="+MATERIAL[i]+"\n")
    f.write("1"+"\n")
    i += 1

f.write("*STEP"+"\n")
f.write("*frequency"+"\n")
f.write(str(frequency)+"\n")
f.write("*NODE FILE"+"\n")
f.write("U"+"\n")
f.write("*END STEP"+"\n")
