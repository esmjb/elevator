import sys
import re
from collections import deque

def main():    
    if len(sys.argv) != 3:
        print "Elevator usage: elevator <inputFile> <mode>"
        exit()
    if sys.argv[2] != "A":
        if sys.argv[2] != "B":
            print "Acceptable modes: A or B"
            exit()
        
    inputFile = sys.argv[1]    

    with open(inputFile) as fh:
        for line in fh:        
            delimiters = [':', '-', '\n']
            for char in delimiters:
                line = line.replace(char, ',')
            line = line.split(',')
            line = line[0:-1]               #chop off newline
            line = [int(x) for x in line]
                        
            if sys.argv[2] == "A":
                modeA(line)
            elif sys.argv[2] == "B":
                modeB(line)            
            
def modeA(line):
    total = 0
    stops = []
    
    for i in range(len(line)):
        if i > 0 and line[i] != line[i - 1]:
            total += abs(line[i] - line[i - 1])
            stops.append(str(line[i]))
        elif i == 0:
            stops.append(str(line[i]))
    
    total = str(total)
    total = "(" + total + ")"
    stops.append(total)
    print " ".join(stops)
    
def modeB(line):
    stops = []
    total = 0
    stops.append(line[0])
    current = line[0]
    
    q = deque()
    for i in range(1, len(line), 2):
        q.append((line[i], line[i + 1]))    
    
    while len(q) > 0:
        temp = []
        ride = q.popleft()
        start, end = ride
        temp.extend([start, end])
        
        if start < end:
            while len(q) > 0:
                ride = q.popleft()
                x, y = ride
                if x < y:
                    temp.extend([x, y])                    
                else:
                    q.appendleft(ride)
                    break
            temp.sort()
        else:
            while len(q) > 0:
                ride = q.popleft()
                x, y = ride
                if x > y:
                    temp.extend([x, y])                    
                else:
                    q.appendleft(ride)
                    break
            temp.sort(reverse=True)
        
        if current != temp[0]:
            stops.append(temp[0])
        
        for i in range(1, len(temp)):
            if temp[i] != temp[i - 1]:
                stops.append(temp[i])
        
        current = temp[-1]
    
    for i in range(1, len(stops)):
        total += abs(stops[i] - stops[i - 1])           
        
    stops = [str(x) for x in stops]
    total = str(total)
    total = "(" + total + ")"
    stops.append(total)
    print " ".join(stops)        
        
main()
    