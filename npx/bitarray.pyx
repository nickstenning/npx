from __future__ import division

import random
from bitstring import BitArray
import numpy as np

__all__ = ["BitArray", "random_bitarray", "mutate_single", "mutate_uniform",
           "crossover_binary_1point", "crossover_binary_uniform"]

ctypedef unsigned int uint

def random_bitarray(length):
    return BitArray(uint=random.getrandbits(length), length=length)

cdef char _flip(char c):
    if c == '0':
        return '1'
    else:
        return '0'

class ImpossibleCrossover(Exception):
    pass

def mutate_single(g):
    g = g[:]

    idx = random.randrange(len(g))
    g[idx] = not g[idx]

    return g

def mutate_uniform(g, rate=None):
    cdef uint i
    cdef uint l = len(g)
    cdef char* g_ary = g.bin
    cdef double r = 1.0 / l

    if rate is not None:
        r = rate

    for i in xrange(l):
        if random.random() < r:
            g_ary[i] = _flip(g_ary[i])

    return BitArray(bin=g_ary)

def crossover_binary_1point(a, b):
    return crossover_binary_mpoint(a, b)

def crossover_binary_mpoint(a, b, m=1):
    if len(a) != len(b):
        raise ImpossibleCrossover()

    a = a.bin[:]
    b = b.bin[:]

    cdef uint l = len(a)
    cdef char* c_ary = a
    cdef char* b_ary = b

    pivots = np.random.randint(0, l + 1, m)
    pivots.sort()

    cdef uint i, j = 0, nextpivot = pivots[0]
    for i in xrange(l):
        while nextpivot <= i and j < m:
            j += 1
            if not j < m:
                break
            nextpivot = pivots[j]

        if j % 2 == 1:
            c_ary[i] = b_ary[i]

    return BitArray(bin=c_ary)

def crossover_binary_uniform(a, b, weight=0.5):
    if len(a) != len(b):
        raise ImpossibleCrossover()

    a = a.bin[:]
    b = b.bin[:]

    cdef uint i
    cdef uint l = len(a)
    cdef char* c_ary = a
    cdef char* b_ary = b

    for i in xrange(l):
        if random.random() < weight:
            c_ary[i] = b_ary[i]

    return BitArray(bin=c_ary)
