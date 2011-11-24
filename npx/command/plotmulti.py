import os
import sys

from matplotlib import pyplot as plt
import numpy as np

def main():
    data = np.loadtxt(sys.stdin, unpack=True)
    x = np.arange(len(data[0]))

    for i, d in enumerate(data):
        plt.plot(x, d, label="col %d" % i)

    plt.legend()

    if os.isatty(sys.stdout.fileno()):
        plt.show()
    else:
        plt.savefig(sys.stdout, format='png')

if __name__ == '__main__':
    main()
