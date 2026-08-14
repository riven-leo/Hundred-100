import random
import math

random.seed(1)

class BPSO:
    def __init__(
        self,
        values,
        weights,
        capacity,
        num_p=10,
        max_it=10,
        w=0.7, 
        c1=1.5,
        c2=1.5,
        penalty_factor=5
    ):
        # BPSO 参数设置
        self.values = values
        self.weights = weights
        self.capacity = capacity

        self.dim = len(values)

        self.num_p = num_p
        self.max_it = max_it # 最大迭代次数
        self.w = w           # 惯性权重
        self.c1 = c1         # 个体学习因子
        self.c2 = c2         # 社会学习因子

        self.X = []
        self.V = []

        self.pbest_pos = []
        self.pbest_val = []
        self.gbest_pos = []
        self.gbest_val = float("-inf") # float解析字符串

    # Sigmoid 函数
    def sigmoid(self, v):
        return 1.0 / (1.0 + math.exp(-v))

    # ΔΔΔ 评价函数：
    def fitness(self, x):
        value = 0
        weight = 0

        for i in range(len(x)):
            if x[i]:
                value += self.values[i]
                weight += self.weights[i]

        # version1：超重直接fitness=0
        if weight > self.capacity:
            return 0

        # version2: penalty超重惩罚
        penalty = self.penalty_factor * max(0, weight - self.capacity) # penalty_factor = 5
        value -= penalty

        #version3:  repair修复策略
        '''因为评价的时候默认是repair过的可行解,不存在超重情况
        value = 0
        for i in range(len(x)):
            if x[i]:
                value += self.values[i]
        return value
        '''

        return value

    # version3: repair function
    def repair(self, x):
        weight = 0
        selected = []

        for i in range(self.dim):
            if x[i]:
                weight += self.weights[i]
                selected.append(i)

        while weight > self.capacity:
            worst = min(selected, key=lambda i: self.values[i] / self.weights[i])

            x[worst] = 0
            weight -= self.weights[worst]
            selected.remove(worst)

    def initialize_particles(self):
        self.X = [[random.randint(0, 1) for _ in range(self.dim)] for _ in range(self.num_p)]
        self.V = [[random.uniform(-4, 4) for _ in range(self.dim)] for _ in range(self.num_p)]

        # 初始化粒子时可能就超重了，所以需要repair
        for x in self.X:
            self.repair(x)

    def initialize_best(self):
        self.pbest_pos = [list(x) for x in self.X] # 二维列表，使用浅拷贝不会修改引用,逐行创建新的列表。
        self.pbest_val = [self.fitness(x) for x in self.X]
        self.gbest_pos = list(self.X[self.pbest_val.index(max(self.pbest_val))])
        self.gbest_val = max(self.pbest_val)

    def update_partcles_each_dim(self):
        for i in range(self.num_p):
            for d in range(self.dim):
                r1, r2 = random.random(), random.random()
                self.V[i][d] = (self.w * self.V[i][d] + 
                                self.c1 * r1 * (self.pbest_pos[i][d] - self.X[i][d]) + 
                                self.c2 * r2 * (self.gbest_pos[d] - self.X[i][d]))

                self.V[i][d] = max(-5.0, min(self.V[i][d], 5.0))

                if random.random() < self.sigmoid(self.V[i][d]):
                    self.X[i][d] = 1
                else:
                    self.X[i][d] = 0

            # 更新完一个粒子后，修复该粒子为可行解
            self.repair(self.X[i])

    def update_best(self):
        for i in range(self.num_p):
            cur_val = self.fitness(self.X[i])
            if cur_val > self.pbest_val[i]:
                self.pbest_val[i] = cur_val
                self.pbest_pos[i] = list(self.X[i]) # 这里拷贝的是一维列表，修改里面的常数不影响引用

            if cur_val > self.gbest_val:
                self.gbest_val = cur_val
                self.gbest_pos = list(self.X[i])

    def run(self):
        self.initialize_particles()
        self.initialize_best()
        for iterator in range(self.max_it):
            self.update_partcles_each_dim()
            self.update_best()

            print(f"第{iterator + 1}轮, 最优适应度：{self.gbest_val}")

        return self.gbest_pos, self.gbest_val

    # 理论上penalty函数还是可能会出现非法解
    def get_weight(self):
        weight = 0

        for i in range(len(self.gbest_pos)):
            if self.gbest_pos[i]:
                weight += self.weights[i]

        return weight

values = [6, 10, 12, 7, 3, 8, 9, 4, 5, 11]
weights = [1, 2, 3, 2, 1, 4, 3, 2, 2, 5]
capacity = 10

bpso = BPSO(
    values=values,
    weights=weights,
    capacity=capacity,
    num_p=10,
    max_it=10
)

best_pos, best_val = bpso.run()

print("最优解：", best_pos)
print("最优适应度：", best_val)
print("总重量：", bpso.get_weight())


