import argparse
import random
import sys
from collections import namedtuple
import numpy as np
from IPython.parallel import Client

from npx import nk
from npx import bitarray

class Individual(object):
    def __init__(self, obj=None, fitness=0.0):
        self.obj = obj
        self.fitness = fitness

class Population(list):
    def __init__(self, *args, **kwargs):
        super(Population, self).__init__(*args, **kwargs)
        self.best_so_far = -1.0

    def update_best_so_far(self):
        fitnesses = np.array(map(lambda x: x.fitness, self))
        max_ = fitnesses.max()
        if not self.best_so_far or max_ > self.best_so_far:
            self.best_so_far = max_

def make_populations(npops, popsize, n):
    return [make_population(popsize, n) for _ in xrange(npops)]

def make_population(popsize, n):
    return Population([Individual(bitarray.random_bitarray(n), 0.0) for _ in xrange(popsize)])

def ga_init(populations, landscape):
    # Initialize fitnesses
    for pop in populations:
        for ind in pop:
            ind.fitness = landscape.evaluate(ind.obj.bin)

def ga_tick(tick, populations, landscape):
    for pop in populations:
        pop.update_best_so_far()

        cand_idx = random.randrange(len(pop))
        other_idx = random.randrange(len(pop))

        cand = Individual()
        cand.obj = bitarray.mutate_single(pop[cand_idx].obj)
        cand.obj = bitarray.crossover_binary_mpoint(cand.obj, random.choice(pop).obj, 4)
        # cand.obj = bitarray.crossover_binary_uniform(cand.obj, random.choice(pop).obj, 0.2)

        cand.fitness = landscape.evaluate(cand.obj.bin)

        if cand.fitness > pop[other_idx].fitness:
            pop[other_idx] = cand


def print_bsfs(bsfs):
    print ("{:10.4g}" * len(bsfs)).format(*bsfs)

def main():
    parser = argparse.ArgumentParser(description='Run multiple simultaneous GAs and print their best-so-far statistics')
    parser.add_argument('-p', '--profile', help='IPython parallel profile to use', default='default')
    parser.add_argument('npops', type=int, help='Number of populations')
    parser.add_argument('ngens', type=int, help='Number of generations')
    parser.add_argument('popsize', type=int, help='Population size')
    parser.add_argument('n', type=int, help='N')
    parser.add_argument('k', type=int, help='K')

    args = parser.parse_args()

    landscape = nk.Landscape(args.n, args.k, 651196428)

    rc = Client(profile=args.profile)
    dview = rc[:]

    print >>sys.stderr, "# NK ID = %s" % landscape.id
    print >>sys.stderr, "# Running on %s processes" % len(rc)

    dview.block = True

    dview['landscape'] = landscape

    dview.scatter('populations', range(args.npops))

    dview['make_populations'] = make_populations
    dview['ga_init'] = ga_init
    dview['ga_tick'] = ga_tick

    dview.execute('populations = make_populations(len(populations), %d, %d)' % (args.popsize, args.n))
    dview.execute('ga_init(populations, landscape)')

    dview['tick'] = tick = 0

    while tick < args.popsize * args.ngens:
        dview.execute('ga_tick(tick, populations, landscape)')

        if tick % args.popsize == 0:
            dview.execute('bsfs = [p.best_so_far for p in populations]')
            bsfs = dview.gather('bsfs')
            print_bsfs(bsfs)

        tick += 1
        dview.execute('tick += 1')
