import os
import sys

from matplotlib import pyplot as plt

def main():
    data = [float(line) for line in sys.stdin]

    plt.hist(data)

    if os.isatty(sys.stdout.fileno()):
        plt.show()
    else:
        plt.savefig(sys.stdout, format='png')

if __name__ == '__main__':
    main()
