
import os.path
import time

print("Abaqus status update started successfully")
file_path = 'abaqus.rpy'
while not os.path.exists(file_path):
    time.sleep(1)

if os.path.isfile(file_path):
    with open(file_path,'r') as gp:
        for line in gp.readlines():
            print(line.rstrip())
else:
    raise ValueError("%s isn't a file!" % file_path) 