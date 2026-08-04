粒子群优化算法 PSO(Particle Swarm Optimization)

BPSO
Xi​=(xi1​,xi2​,…,xin​)T, 0/1
Vi​=(vi1​,vi2​,…,vin​)T, 实数
Pbesti​
Gbest

eg: x2 = x1 + v1, x1 = 1, v1 = 0.37; then x2 = 1.37, but BPSO don't allow, only 0/1 

用sigmoid函数把速度转换成概率(0,1)

粒子的速度决定了其位置向量中每个比特翻转的概率。速度越高，该比特翻转的可能性就越大。
速度解释为“该位取 1 的倾向”

https://algorithmafternoon.com/particle/binary_particle_swarm_optimization/
GPT聊天搜索：BPSO讲讲

0/1背包
https://oi-wiki.org/dp/knapsack/

Algorithm   算法#
1. Initialize the swarm:  初始化集群：

    1. For each particle in the swarm:
    对于粒子群中的每个粒子：
        1. Initialize the position with random binary values.
        使用随机二进制值初始化该位置。
        2. Initialize the velocity with random real values.
        用随机实数值初始化速度。
        3. Set the personal best position to the initial position.
        将个人最佳位置设置为初始位置。
        4. Set the global best position to the best personal best position among all particles.
        将全局最佳位置设置为所有粒子中最佳的个人最佳位置。
2. For each iteration:  每次迭代：

    1. For each particle in the swarm:
    对于粒子群中的每个粒子：
        1. Evaluate the fitness of the particle’s current position.
        评估粒子当前位置的适应度。
        2. If the current position is better than the personal best position, update the personal best position.
        如果当前位置优于个人最佳位置，则更新个人最佳位置。
        3. If the current position is better than the global best position, update the global best position.
        如果当前位置优于全局最佳位置，则更新全局最佳位置。
3. For each particle in the swarm:
对于粒子群中的每个粒子：
    1. Update the velocity using the personal best and global best positions, inertia weight, cognitive coefficient, and social coefficient.
    使用个人最佳位置和全球最佳位置、惯性权重、认知系数和社会系数来更新速度。
    2. Update the position by applying the sigmoid function to the velocity and comparing it with a random threshold.
    将 sigmoid 函数应用于速度，并将其与随机阈值进行比较，从而更新位置。
    3. If the termination criterion is met, stop the algorithm and return the global best position.
    如果满足终止条件，则停止算法并返回全局最优位置。
4. Return the global best position as the optimal solution.
返回全局最优位置作为最优解。