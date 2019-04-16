# Plactor - Boat buoyancy simulation
import matplotlib.pyplot as plt

# Formula: Boat weight < water density * volume displaced
class Buoyancy:
    h = 0.5             # Total boat height (m)
    w = 1.0             # Total boat width (m)
    l = 1.5             # Total boat length (m)
    p = 997             # Water density (kg/m3)
    volume = []
    maxweight = []

    def __init__(self):
        print("Increasing size:")
        self.increaseSize(self.h, self.w, self.l)
        self.printArray()
        self.plotGraph("Max allowed weight with increasing size:", 0.5, 0.25*11, 300, 2000)
        self.resetArray()

        print("Decreasing size:")
        self.decreaseSize(self.h, self.w, self.l)
        self.printArray()
        self.plotGraph("Max allowed weight with decreasing size:", 0.8, 0, 0, 400)
        self.resetArray()

    def printArray(self):
        for i in range(len(self.volume)):
            print("Boat volume:", round(self.volume[i], 2), "m^3", "-", "Max allowed weight:", round(self.maxweight[i], 2), "kg")

    def resetArray(self):
        self.volume.clear()
        self.maxweight.clear()

    def increaseSize(self, h, w, l):
        for i in range(10):
            # Volume displaced:
            v1 = (h - 0.2) * (2/3)*l * w
            v2 = (1/2)*((h - 0.2) * (1/3)*l * w)
            
            # Max allowed weight:
            vd = (v1+v2) * self.p

            self.volume.append(h * w * l)
            self.maxweight.append(vd)
            h = h + 0.05
            w = w + 0.05
            l = l + 0.05

    def decreaseSize(self, h, w, l):
        for i in range(10):
            # Volume displaced:
            v1 = (h - 0.2) * (2/3)*l * w
            v2 = (1/2)*((h - 0.2) * (1/3)*l * w)
            
            # Max allowed weight:
            vd = (v1+v2) * self.p

            if(vd > 0):
                self.volume.append(h * w * l)
                self.maxweight.append(vd)
                h = h - 0.05
                w = w - 0.05
                l = l - 0.05

    def plotGraph(self, title, x1, x2, y1, y2):
        plt.title(title)
        plt.xlabel('Boat volume ($\mathregular{m^3}$)');
        plt.ylabel('Max allowed weight (kg)');
        plt.xlim(x1, x2)
        plt.ylim(y1, y2)
        plt.plot(self.volume, self.maxweight)
        plt.show()

Buoyancy()