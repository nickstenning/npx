#!/usr/bin/env python

from __future__ import print_function

from os import path
from sys import argv, stdin, stderr
from subprocess import check_call, check_output

_, file, ext, out = argv

file_parts = file.split('/')

if file_parts[-1][0] != '_':
    raise Exception("Don't know how to build a .so that doesn't start with '_'!")

file_parts[-1] = file_parts[-1][1:] + '.swig.o'

swig_file = path.join('..', 'build', *file_parts)

# redo-ifchange ../build/foo/bar.swig.o
check_call(['redo-ifchange', swig_file])

# ODEPS=$(odeps ../build/foo/bar.swig.o)
odeps = check_output([path.join('..', 'tools', 'odeps'), swig_file]).split('\n')
odeps = [f for f in odeps if f]

# redo-ifchange ${ODEPS}
cmd = ['redo-ifchange']
cmd.extend(odeps)
check_call(cmd)

# link -o out ${ODEPS}
cmd = ['clang++']
cmd.extend(['-lc++', '-bundle', '-undefined', 'dynamic_lookup'])
cmd.extend(['-o', out, swig_file])
cmd.extend(odeps)
check_call(cmd)
