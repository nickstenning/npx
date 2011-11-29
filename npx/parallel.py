import random

from npx import nk
from npx import bitarray

landscape = None
populations = None
crossover = None

class Individual(object):
    def __init__(self, obj=None, fitness=0.0):
        self.obj = obj
        self.fitness = fitness

class Population(list):
    def __init__(self, *args, **kwargs):
        super(Population, self).__init__(*args, **kwargs)
        self.best_so_far = -1.0

    def update_best_so_far(self):
        fitnesses = map(lambda x: x.fitness, self)
        max_ = max(fitnesses)
        if not self.best_so_far or max_ > self.best_so_far:
            self.best_so_far = max_

def make_population(popsize, n):
    return Population([Individual(bitarray.random_bitarray(n), 0.0) for _ in xrange(popsize)])

def make_populations(npops, popsize, n):
    global populations
    populations = [make_population(popsize, n) for _ in xrange(npops)]

def ga_init():
    # Initialize fitnesses
    for pop in populations:
        for ind in pop:
            ind.fitness = landscape.evaluate(ind.obj.bin)

def ga_tick():
    for pop in populations:
        pop.update_best_so_far()

        cand_idx = random.randrange(len(pop))
        other_idx = random.randrange(len(pop))

        cand = Individual()
        cand.fitness = landscape.evaluate(pop[cand_idx].obj.bin)

        if cand.fitness > pop[other_idx].fitness:
            cand.obj = bitarray.mutate_single(pop[cand_idx].obj)
            if random.random() < 0.6:
                if crossover == '1point':
                    cand.obj = bitarray.crossover_binary_1point(cand.obj, random.choice(pop).obj)
                elif crossover == '4point':
                    cand.obj = bitarray.crossover_binary_mpoint(cand.obj, random.choice(pop).obj, 4)
                elif crossover == 'uni0.2':
                    cand.obj = bitarray.crossover_binary_uniform(cand.obj, random.choice(pop).obj, 0.2)
                elif crossover == 'uni0.5':
                    cand.obj = bitarray.crossover_binary_uniform(cand.obj, random.choice(pop).obj, 0.2)
            pop[other_idx] = cand
