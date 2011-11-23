import argparse

def gen():
    import npx.bitarray as ba

    parser = argparse.ArgumentParser(description='Generate random bitarrays')
    parser.add_argument('num', type=int, help='Number of bitarrays')
    parser.add_argument('len', type=int, help='Length of each bitarray')

    args = parser.parse_args()

    for _ in xrange(args.num):
        print ba.random_bitarray(args.len).to01()


def nkeval():
    raise NotImplementedError()
