import re

file_path = "obras.csv"

ex = r"(.+?);.+?;\d+;(.+?);(.+?);\d+:\d+:\d+;O\d+"

data = []


with open(file_path,'r') as file:
    file.readline()
    line = file.readline()

    while file:

        full_line = line

        if(not re.match(ex, line)):
            line = file.readline()
            while(re.match(r"^\W+", line)):
                full_line += line
                line = file.readline()
            
            full_line = re.sub(r"\s\s+", "", full_line)

        else:
            line = file.readline()

        match = re.findall(ex, full_line)
       
        if match:
            data.append(match[0])
        else:
            break


# 1. Lista ordenada alfabeticamente dos compositores musicais
composers = []
for i in data:
    comp = i[2]

    if re.match(r".+?,.+", comp):
        comp = re.sub(r"(.+?),(.+)", r"\2 \1", comp)
    composers.append(comp)
        
composers_sorted = list(set(composers))
composers_sorted.sort()

# Print composers
print("Compositores Musicais por ordem alfabética:")
for i in composers_sorted:
    print(i)

# 2. Distribuição das obras por período: quantas obras catalogadas em cada período
periods = {}

for i in data:
    period = i[1]
    if period in periods:
        periods[period] += 1
    else:
        periods[period] = 1

# Print periods
print("\nDistribuição das obras por período:")
for i in periods:
    print(f"{i}: {periods[i]}")

# 3. Dicionário em que a cada período está a associada uma lista alfabética dos títulos das obras desse período
dic_obras = {}

for i in data:
    if i[1] not in dic_obras:
        dic_obras[i[1]] = []
    dic_obras[i[1]].append(i[0])

for value in dic_obras.values():
    value.sort()

# Print dic_obras
print("\nDicionário de obras por período:")
for key, value in dic_obras.items():
    print(f"{key}: {value}")






