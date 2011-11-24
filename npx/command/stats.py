import sys
import numpy as np

def main():
    data = np.loadtxt(sys.stdin, ndmin=2, unpack=True)

    for i, d in enumerate(data):
        print "# col %d" % i
        print "mean = %s" % np.mean(d)
        print "min = %s" % np.min(d)
        print "max = %s" % np.max(d)
        print "stddev = %s" % np.std(d)
        print ""

if __name__ == '__main__':
    main()
