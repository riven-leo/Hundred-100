'''可运行'''

import random
import math

# Sigmoid 函数
def sigmoid(v):
    return 1.0 / (1.0 + math.exp(-v))

# 目标函数：例如最大化二进制串中 1 的个数（可替换为实际问题）
def fitness(x):
    return sum(x)

# BPSO 参数设置
num_p = 10
dim = 10
max_it = 10 # 最大迭代次数
w = 0.7    # 惯性权重
c1 = 1.5   # 个体学习因子
c2 = 1.5   # 社会学习因子

# random create partcles x and v
X = [[random.randint(0, 1) for _ in range(dim)] for _ in range(num_p)]
V = [[random.uniform(-4, 4) for _ in range(dim)] for _ in range(num_p)]

# initial pbest and gbest
pbest_pos = list(X) # 浅拷贝？pbest_pos = [list(x) for x in X]?
pbest_val = [fitness(x) for x in X]
gbest_pos = list(X[pbest_val.index(max(pbest_val))]) 
gbest_val = max(pbest_val)

# iteration
for iteration in range(max_it):
    for i in range(num_p):
        for d in range(dim):
            # update v
            r1, r2 = random.random(), random.random()
            V[i][d] = (w * V[i][d] +
                       c1 * r1 * (pbest_pos[i][d] - X[i][d]) + 
                       c2 * r2 * (gbest_pos[d] - X[i][d]))

            V[i][d] = max(-6.0, min(6.0, V[i][d]))

            # update x by sigmoid
            if random.random() < sigmoid(V[i][d]):
                X[i][d] = 1
            else:
                X[i][d] = 0 

        # update pbest and gbest
        cur_val = fitness(X[i])
        if cur_val > pbest_val[i]:
            pbest_val[i] = cur_val
            pbest_pos[i] = list(X[i])

        if cur_val > gbest_val:
            gbest_val = cur_val
            gbest_pos = list(X[i])

print("最优解：", gbest_pos)
print("最优适应度：", gbest_val)



