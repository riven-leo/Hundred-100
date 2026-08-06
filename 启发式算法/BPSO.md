BPSO
 cd .\启发式算法 在当前文件夹里进入子文件夹启发式算法
 dir 显示当前文件夹里的子文件夹，cd .. 返回上一层文件夹


种子不变，生成的随机数序列相同，方便调试
random.seed(42)

pbest_pos = list(X) # 复制一个新列表内容和X相同
gbest_pos = list(X[pbest_val.index(max(pbest_val))]) # index()查找某个值第一次出现的位置
list(X[i]) 是复制当前位置。不能只写：
p_best_pos[i] = X[i]
**并不修改初始化时的新列表, 而是更换引用到X[i]**
否则后面继续修改 X[i] 时，保存的历史最好位置也可能跟着变化


random.random()生成一个 0 到 1 之间的随机浮点数
random.randint(0, 1)生成一个 0 到 1 之间的随机整数 
random.uniform(-4, 4)生成一个 -4 到 4 之间的随机浮点数


速度限制：防止 Sigmoid 饱和，让粒子不要过早“锁死”，
因为速度会累加，时间长了饱和了，会导致某个位置固定为1或0，让粒子丧失探索能力
V[i][d] = max(-6.0, min(6.0, V[i][d]))


用sigmoid函数把速度转换成概率(0,1)
速度解释为“该位X取 1 的倾向”

再取个随机数和速度概率比较，如果概率>随机数，x=1, 否则x=0;
保证随机性，防止陷入局部最优


资料：
https://algorithmafternoon.com/particle/binary_particle_swarm_optimization/
GPT：BPSO讲讲


