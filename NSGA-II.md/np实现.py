import numpy as np
import matplotlib.pyplot as plt

# 定义参数
POP_SIZE = 100
MAX_GEN = 50
BOUNDS = [0, 10]
DIM = 3

# 初始化种群
def initialize_population(pop_size, dim, bounds):
    return np.random.uniform(bounds[0], bounds[1], (pop_size, dim))

# 评估目标函数
def evaluate(individual):
    x1, x2, x3 = individual
    f1 = 2 * x1 + 3 * x2 + 4 * x3
    f2 = x1**2 + x2**2 + x3**2
    f3 = 100 - (x1 - 5)**2 - (x2 - 5)**2 - (x3 - 5)**2
    return f1, f2, f3

# 非支配排序
def non_dominated_sorting(pop):
    pop_size = len(pop)
    domination_count = np.zeros(pop_size)
    dominated_solutions = [[] for _ in range(pop_size)]
    rank = np.zeros(pop_size)
    
    for i in range(pop_size):
        for j in range(pop_size):
            if i != j:
                if dominates(pop[i], pop[j]):
                    dominated_solutions[i].append(j)
                elif dominates(pop[j], pop[i]):
                    domination_count[i] += 1
        if domination_count[i] == 0:
            rank[i] = 0
    
    current_front = [i for i in range(pop_size) if domination_count[i] == 0]
    fronts = [current_front]
    
    while current_front:
        next_front = []
        for i in current_front:
            for j in dominated_solutions[i]:
                domination_count[j] -= 1
                if domination_count[j] == 0:
                    rank[j] = len(fronts)
                    next_front.append(j)
        fronts.append(next_front)
        current_front = next_front
    
    return fronts[:-1]

# 支配关系判断
def dominates(p, q):
    return all(p <= q) and any(p < q)

# 拥挤度计算
def calculate_crowding_distance(front, pop_values):
    distances = np.zeros(len(front))
    if len(front) > 0:
        for m in range(pop_values.shape[1]):
            values = pop_values[front, m]
            sorted_indices = np.argsort(values)
            distances[sorted_indices[0]] = np.inf
            distances[sorted_indices[-1]] = np.inf
            for i in range(1, len(front) - 1):
                distances[sorted_indices[i]] += (values[sorted_indices[i + 1]] - values[sorted_indices[i - 1]]) / (values[sorted_indices[-1]] - values[sorted_indices[0]])
    return distances

# 选择操作
def selection(pop, pop_values, fronts, crowding_distances):
    new_pop = []
    for front in fronts:
        if len(new_pop) + len(front) > POP_SIZE:
            front_distances = crowding_distances[front]
            sorted_indices = np.argsort(-front_distances)
            new_pop.extend([pop[i] for i in np.array(front)[sorted_indices[:POP_SIZE - len(new_pop)]]])
            break
        else:
            new_pop.extend([pop[i] for i in front])
    return np.array(new_pop)

# 交叉操作
def crossover(parent1, parent2, crossover_prob=0.9):
    if np.random.rand() < crossover_prob:
        point = np.random.randint(1, len(parent1) - 1)
        return np.concatenate((parent1[:point], parent2[point:])), np.concatenate((parent2[:point], parent1[point:]))
    return parent1, parent2

# 变异操作
def mutation(individual, mutation_prob=0.1):
    for i in range(len(individual)):
        if np.random.rand() < mutation_prob:
            individual[i] = np.random.uniform(BOUNDS[0], BOUNDS[1])
    return individual

# NSGA-II算法主流程
population = initialize_population(POP_SIZE, DIM, BOUNDS)
for gen in range(MAX_GEN):
    pop_values = np.array([evaluate(ind) for ind in population])
    fronts = non_dominated_sorting(pop_values)
    crowding_distances = [calculate_crowding_distance(front, pop_values) for front in fronts]
    
    offspring = []
    while len(offspring) < POP_SIZE:
        parents = population[np.random.choice(POP_SIZE, 2, replace=False)]
        child1, child2 = crossover(parents[0], parents[1])
        offspring.append(mutation(child1))
        if len(offspring) < POP_SIZE:
            offspring.append(mutation(child2))
    
    population = selection(np.vstack((population, offspring)), np.vstack((pop_values, np.array([evaluate(ind) for ind in offspring]))), fronts, np.hstack(crowding_distances))

# 绘制帕累托前沿
final_values = np.array([evaluate(ind) for ind in population])
plt.figure(figsize=(10, 7))
plt.scatter(final_values[:, 0], final_values[:, 1], c=final_values[:, 2], cmap='viridis', marker='o')
plt.colorbar(label='Quality (f3)')
plt.xlabel('Cost (f1)')
plt.ylabel('Time (f2)')
plt.title('Pareto Front')
plt.show()