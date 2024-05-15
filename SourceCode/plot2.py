import matplotlib.pyplot as plt
import sys
from numpy import sin, cos, sqrt, pi

def r_event(a, M=1):
    ret = M + sqrt((M - a)*(M + a))
    print("Ereignishorizont bei ", ret)
    return ret
    
def r_unrot(a, M=1, theta=pi/2):
    ret = M + sqrt(pow(M, 2) - pow(a, 2)*pow(cos(theta), 2));
    print("Unendliche Rotverschiebung bei", ret)
    return ret

fName = sys.argv[1]

f = open(fName)
x = []
y = []
for line in f:
    txt = line.split(",")
    # t, r, phi
    t = float(txt[0])
    r = float(txt[2])
    p = float(txt[3])
    
    x.append(r*cos(p))
    y.append(r*sin(p))
    #print(x[-1], " ", y[-1])
plt.plot(x, y, color="blue");

if len(sys.argv)>2:
    a = float(sys.argv[2])
    c = plt.Circle((0, 0), r_unrot(a), color="yellow")
    plt.gcf().gca().add_patch(c)
    c = plt.Circle((0, 0), r_event(a), color="grey")
    plt.gcf().gca().add_patch(c)

plt.title(fName)
plt.gca().set_aspect("equal");
plt.savefig(fName +"_plot2.png")

