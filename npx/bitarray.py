from __future__ import absolute_import

import random

from bitarray import bitarray

def random_bitarray(length):
    s = bin(random.getrandbits(length))[2:].zfill(length)
    return bitarray(s)
