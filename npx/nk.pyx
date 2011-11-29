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

EPISTASIS_TYPES = {
    'nearneighbour': 1,
    'random': 2
}

cdef class Landscape:
    cdef public ulong n, k, id
    cdef int epistasis_type

    def __init__(self, ulong n=0, ulong k=0, id=None, epistasis='nearneighbour'):
        self.n = n
        self.k = k
        self.id = id or random.getrandbits(32)

        self.epistasis_type = EPISTASIS_TYPES.get(epistasis) or 1

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
    cpdef double evaluate_position(self, ulong length, char* obj, ulong i):
        cdef ulong j = 0
        cdef double s = 0.0

        # Generate a seed
        cdef ulong seed = self.id ^ i

        # The neighbours are all taken from the immediate "right" of the
        # bit position i. So, with K = 2, the hash is updated with the values
        # at i, i + 1, i + 2.
        #
        # If we overrun the end of the genome, we wrap to the beginning.

        if self.epistasis_type == 1: # near-neighbour epistasis
            seed = _hash_combine(seed, obj[i])

            for j in xrange(self.k):
                seed = _hash_combine(seed, obj[(i + j + 1UL) % length])

        elif self.epistasis_type == 2: # random epistasis
            c_libc_srandom(seed)
            seed = _hash_combine(seed, obj[i])

            for j in xrange(self.k):
                # the gibberish on the right has to be a little complicated so as to avoid selecting
                # *this gene* as one of the epistatic neighbours: it will return an index randomly
                # chosen from all the positions *except* i.
                seed = _hash_combine(seed, obj[(i + 1UL + (c_libc_random() % length - 1)) % length])

        c_libc_srandom(seed)

        return c_libc_random() / (1.0 * RAND_MAX)

    def __reduce__(self):
        return (Landscape, (self.n, self.k, self.id))

