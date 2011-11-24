import argparse

def bagen():
    from npx import bitarray

    parser = argparse.ArgumentParser(description='Generate random bitarrays')
    parser.add_argument('num', type=int, help='Number of bitarrays')
    parser.add_argument('len', type=int, help='Length of each bitarray')

    args = parser.parse_args()

    for _ in xrange(args.num):
        print bitarray.random_bitarray(args.len).bin

def bamtest():
    from npx import bitarray

    all_zeros = bitarray.BitArray(32)
    all_ones = all_zeros[:]
    all_ones.invert()

    print "all zeros:", all_zeros.bin
    print "all ones: ", all_ones.bin

    print "mutate_single(all_zeros): "
    for i in xrange(3):
        print " ", bitarray.mutate_single(all_zeros).bin

    print "mutate_uniform(all_zeros): "
    for i in xrange(3):
        print " ", bitarray.mutate_uniform(all_zeros).bin

    print "crossover_binary_1point(all_zeros, all_ones): "
    for i in xrange(3):
        print " ", bitarray.crossover_binary_1point(all_zeros, all_ones).bin

    print "crossover_binary_mpoint(all_zeros, all_ones, 3): "
    for i in xrange(3):
        print " ", bitarray.crossover_binary_mpoint(all_zeros, all_ones, 3).bin

    print "crossover_binary_uniform(all_zeros, all_ones): "
    for i in xrange(3):
        print " ", bitarray.crossover_binary_uniform(all_zeros, all_ones).bin

    print "crossover_binary_uniform(all_zeros, all_ones, 0.2): "
    for i in xrange(3):
        print " ", bitarray.crossover_binary_uniform(all_zeros, all_ones, 0.2).bin


def nkeval():
    import sys

    from npx import nk
    from npx import bitarray

    parser = argparse.ArgumentParser(description='Evaluate input bitarrays on a random NK landscape')
    parser.add_argument('n', type=int, help='N')
    parser.add_argument('k', type=int, help='K')

    args = parser.parse_args()

    landscape = nk.Landscape(**vars(args))

    for line in sys.stdin:
        genome = bitarray.BitArray(bin=line)
        print landscape.evaluate(genome.bin)

def nkneighbours():
    import sys

    from npx import nk
    from npx import bitarray

    parser = argparse.ArgumentParser(description='Evaluate input bitarrays on a random NK landscape')
    parser.add_argument('n', type=int, help='N')
    parser.add_argument('k', type=int, help='K')

    args = parser.parse_args()

    landscape = nk.Landscape(**vars(args))
    genome = bitarray.BitArray(bin=sys.stdin.read())

    print landscape.evaluate(genome.bin)

    for i, _ in enumerate(genome):
        neighbour = genome[:]
        neighbour[i] = not neighbour[i]
        print landscape.evaluate(neighbour.bin)



