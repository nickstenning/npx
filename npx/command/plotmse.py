import os
import sys

from matplotlib import pyplot as plt
import numpy as np

def main():
    data = np.loadtxt(sys.stdin, unpack=True)
    x = np.arange(len(data[0]))

    for i, d in enumerate(data):
        plt.plot(x, d, 'k', alpha=0.05)

    max_ = data.max(axis=0)
    min_ = data.min(axis=0)
    mean = data.mean(axis=0)
    # Std error in mean = sample stddev / sqrt(n)
    serr = data.std(axis=0, ddof=1) / np.sqrt(len(data[:,0]))

    plt.plot(x, mean)
    plt.plot(x, max_, '--k', alpha=0.4)
    plt.plot(x, min_, '--k', alpha=0.4)
    plt.fill_between(x, mean - serr, mean + serr, alpha=0.1)

    if "-l" in sys.argv:
        plt.semilogx()

    if os.isatty(sys.stdout.fileno()):
        plt.show()
    else:
        plt.savefig(sys.stdout, format='png')

if __name__ == '__main__':
    main()
