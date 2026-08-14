import random
from opfunu.cec_based import F292017

random.seed(42)


func = F292017(ndim=10)
def fitness(x):
    return func.evaluate(x)


class DE:
    def __init__(
        self,
        fitness,
        bounds,
        pop_size=30,
        max_it=1000,
        F=0.5,
        CR=0.9

    ):
        self.fitness = fitness
        self.bounds = bounds
        self.dim = len(self.bounds) # 有多少个变量范围，就有多少个维度
        self.pop_size = pop_size
        self.max_it = max_it
        self.F = F
        self.CR = CR

        self.population = []
        self.pop_fitness = []

        self.best_x = None
        self.best_val = float("inf")

    def initialize(self):
        self.population = [[random.uniform(low, high) for low, high in self.bounds] for _ in range(self.pop_size)]
        self.pop_fitness = [self.fitness(x) for x in self.population] 

    def mutation(self, i): # i是“当前正在为哪个目标个体生成变异向量”的索引

        idx = list(range(self.pop_size))
        idx.remove(i)
        r1, r2, r3 = random.sample(idx, 3)

        mutant = []
        for d in range(self.dim):
            # rand r1, 1 1个差分向量
            value = self.population[r1][d] + self.F * (self.population[r2][d] - self.population[r3][d])

            # 边界有不同的处理方式_1截断法
            low, high = self.bounds[d]
            if value < low:
                value = low
            if value > high:
                value = high

            mutant.append(value)

        return mutant
    
    def crossover(self, i, mutant):
        trial = []
        d_rand = random.randint(0, self.dim-1) # 指定一个固定维度强制继承 mutant

        for d in range(self.dim):
            # bin binomial crossover 二项式交叉
            if random.random() < self.CR or d == d_rand: # 概率机制 + 兜底机制
                trial.append(mutant[d])
            else:
                trial.append(self.population[i][d])

        return trial

    def selection(self, i, trial):
        trial_fitness = self.fitness(trial)
        if trial_fitness < self.pop_fitness[i]:
            return trial, trial_fitness
        else:
            return self.population[i], self.pop_fitness[i]

    def update_best(self):
        for i in range(len(self.population)):
            if self.pop_fitness[i] < self.best_val:
                self.best_val = self.pop_fitness[i]
                self.best_x = list(self.population[i])

    def run(self):
        self.initialize()

        for iteration in range(self.max_it):

            new_population = []
            new_pop_fitness = []
            for i in range(self.pop_size):
                mutant = self.mutation(i)

                trial = self.crossover(i, mutant)

                new_p, new_fitness = self.selection(i, trial)
                new_population.append(new_p);new_pop_fitness.append(new_fitness)
            # 所有粒子更新完后，旧族群更新为新族群, 旧评价值更新为新评价值
            self.population = new_population
            self.pop_fitness = new_pop_fitness

            self.update_best()

            print(
                "iteration:",
                iteration,
                "best:",
                self.best_val
            )

        return self.best_x, self.best_val

de = DE(
    fitness=fitness,
    bounds=[(-100, 100)] * 10
)

best_x, best_val = de.run()

print("最优解：", best_x, "最优值:", best_val)