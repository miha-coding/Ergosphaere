import matplotlib.pyplot as plt
import sys

fName = sys.argv[1]

f = open(fName)
x = []
y = []
for line in f:
    txt = line.split(",")
    x.append(float(txt[0]))
    y.append(float(txt[2]))
    #print(x[-1], " ", y[-1])
plt.plot(x, y);

plt.savefig(fName +".png")

