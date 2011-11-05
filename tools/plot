#!/Users/borior/code/venv/sci/bin/python

import os
import sys
import pylab

data = [float(line) for line in sys.stdin]

pylab.plot(data)

if os.isatty(sys.stdout.fileno()):
    pylab.show()
else:
    pylab.savefig(sys.stdout, format='png')
