from __future__ import division

import random
cimport cython

class InvalidSize(Exception):
    pass

class InvalidPosition(Exception):
    pass

ctypedef unsigned long ulong

cdef import from "stdlib.h":
    ulong c_libc_random "random"()
    void c_libc_srandom "srandom"(ulong seed)
    ulong RAND_MAX "RAND_MAX"

cdef ulong _hash_combine(ulong seed, ulong v):
    return seed ^ (v + 0x9e3779b9UL + (seed << 6) + (seed >> 2))

cdef class Landscape:
    cdef public ulong n, k, id

    def __init__(self, ulong n=0, ulong k=0, id=None):
        self.n = n
        self.k = k
        self.id = id or random.getrandbits(32)

    @cython.cdivision(True)
    cpdef double evaluate(self, char obj[]) except -1:
        cdef ulong l = len(obj)
        cdef double s = 0.0

        if l != self.n:
            raise InvalidSize()

        if l == 0:
            return s

        for i in xrange(l):
            s += self.evaluate_position(l, obj, i)

        return s / l

    @cython.cdivision(True)
    cdef double evaluate_position(self, ulong length, char* obj, ulong i):
        cdef ulong j = 0
        cdef double s = 0.0

        # Generate a seed
        cdef ulong seed = self.id ^ i

        # The neighbours are all taken from the immediate "right" of the
        # bit position i. So, with K = 2, the hash is updated with the values
        # at i, i + 1, i + 2.
        #
        # If we overrun the end of the genome, we wrap to the beginning.
        seed = _hash_combine(seed, obj[i])

        for j in xrange(self.k):
            seed = _hash_combine(seed, obj[(i + j + 1UL) % length])

        c_libc_srandom(seed)

        return c_libc_random() / (1.0 * RAND_MAX)

    def __reduce__(self):
        return (Landscape, (self.n, self.k, self.id))

