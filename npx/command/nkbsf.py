import argparse
import sys

from IPython.parallel import Client

def print_bsfs(bsfs):
    print ("{:10.4g}" * len(bsfs)).format(*bsfs)
    sys.stdout.flush()

def main():
    parser = argparse.ArgumentParser(description='Run multiple simultaneous GAs and print their best-so-far statistics')
    parser.add_argument('-p', '--profile', help='IPython parallel profile to use', default='default')
    parser.add_argument('npops', type=int, help='Number of populations')
    parser.add_argument('ngens', type=int, help='Number of generations')
    parser.add_argument('popsize', type=int, help='Population size')
    parser.add_argument('n', type=int, help='N')
    parser.add_argument('k', type=int, help='K')

    args = parser.parse_args()

    rc = Client(profile=args.profile)

    dv = rc[:]
    dv.block = True

    from npx import nk
    from npx import parallel

    dv.execute('from npx import parallel')

    landscape = nk.Landscape(args.n, args.k, 651196428)
    dv['landscape'] = landscape
    dv.execute('parallel.landscape = landscape')

    print >>sys.stderr, "# NK ID = %s" % landscape.id
    print >>sys.stderr, "# Running on %s processes" % len(rc)

    tick = 0
    dv.apply(parallel.make_populations, args.npops, args.popsize, args.n)
    dv.apply(parallel.ga_init)

    while tick < args.popsize * args.ngens:
        dv.apply(parallel.ga_tick)

        if tick % args.popsize == 0:
            dv.execute('bsfs = [p.best_so_far for p in parallel.populations]')
            bsfs = dv.gather('bsfs')
            print_bsfs(bsfs)

        tick += 1

if __name__ == '__main__':
    main()
