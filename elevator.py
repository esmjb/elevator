import sys
import re

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
    
if len(sys.argv) != 3:
    print "Elevator usage: elevator <inputFile> <mode>"
    exit()
    
inputFile = sys.argv[1]

with open(inputFile) as fh:
    for line in fh:        
        delimiters = [':', '-', '\n']
        for char in delimiters:
            line = line.replace(char, ',')
        line = line.split(',')
        line = line[0:-1]               #chop of newline
        line = [int(x) for x in line]
        # current = line[0]
        # line = line[1:]                 #pop off starting position of elevator
        # begin = []
        # end = []
        # for i in range(len(line)):
            # if i % 2 == 0:
                # begin.append(line[i])
            # else:
                # end.append(line[i])
        
        # total = 0;
        # stops = []
        # stops.append(current)
        # for i in range(len(begin)):            
            # if begin[i] != current:
                # stops.append(begin[i])
            # total += abs(current - begin[i])
            # total += abs(begin[i] - end[i])
            # stops.append(end[i])
            # current = end[i]
            
        if sys.argv[2] == "A":
            modeA(line)
        else:
            print "what the fuck"
            
        # stops = [str(x) for x in stops]
        # total = str(total)
        # total = "(" + total + ")"
        # stops.append(total)
        # print " ".join(stops)
        

    