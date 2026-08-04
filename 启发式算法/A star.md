启发式底层算法：A、A*、IDA*
启发式算法应用：PSO算法解决基本0-1背包问题
技术要点，实现过程的要点

Search
这是考虑了“已探索集合”（Explored Set）以避免死循环的通用搜索框架。通过改变Frontier（边界）的数据结构，可以实现不同的搜索策略（如 DFS 或 BFS）
Start with a frontier that contains the initial state
Start with an empty explored set
Repeat:
    If the frontier is empty, then no solution
    Remove a node from the frontier
    If node contains goal state, return the solution
    Add the node to the explored set
    Expand the node (look at neighbors), and for each neighbor:
        Add the neighbor to the frontier only if it is not already in the frontier and not already in the explored set


A algorithm
1964年，尼尔逊提出一种算法以提高最短路径搜索的效率，被称为A1算法；1967年，拉斐尔改进了A1算法，称为A2算法（A算法）。A算法估价函数f(n)=h(n)+g(n)，对h(n)无限制，虽提高了算法效率，但不能保证找到最优解。另外，不合适的h (n)定义会导致算法不完备。

1968年，彼得·哈特对A算法进行了很小的修改，并证明了当估价函数满足一定的限制条件时，算法一定可以找到最优解。估价函数满足一定限制条件的算法称为A*算法，一般地，限制 g(n) 大于 0， h(n) 不大于n到目标的实际代价时，所得到的就是最优解。


A* f(n)=g(n)+h(n)
保持最优的前提条件
*可接纳性 (Admissibility)*：启发式函数绝不能高估到达目标的真实成本。它给出的估计值必须小于或等于实际所需的最小步数。
    例如：在迷宫中使用“曼哈顿距离”（忽略墙壁的直线步数）作为启发式，因为它总是比实际带墙壁的路径更短或相等，所以它是可接纳的
。
*一致性 (Consistency)*: 对于任何节点 n及其继任节点 n',从 n到目标的估计成本不应大于"从 n到 n'的实际成本"加上"从 n'到目标的估计成本"。
    用数学公式表示为：h(n)≤h(n')+cost(n,n')。这确保了随着算法的深入，路径的评价不会出现逻辑上的“倒退”

**总结**
当启发式函数满足可接纳性和一致性时，A* 算法在扩展节点时，总是优先处理那些最有希望（总估算成本最低）的节点。即使某条路径看起来很快就能到达目标，但如果它积累的实际成本 g(n) 太高，A* 最终会回过头去尝试那些实际成本更低、虽然估计距离稍远一点的路径，从而保证最终返回的方案是总成本最低的最优解

如果扩展节点很多的话，那最小堆就会非常的满，会占用非常多的空间，所以需要IDA*重复搜索一遍，限制进入的节点


Dijkstra 算法 仅根据已付出的路径代价 g(n) （从起点到当前节点的实际距离）来扩展节点 
无启发式搜索（Uninformed Search）
（在边权为正的情况下）确保找到最优解

扩展新节点的时候，就会判断是不是goal，不是goal就放到堆里，然后在出堆的时候标记已访问


贪婪最佳优先搜索 (Greedy Best-First Search) 仅依靠启发式函数 h(n)（即对剩余路程的估计值）来决定扩展哪个节点
知情搜索（Informed Search）
不一定能找到全局最短路径（最优解）


IDS 是 Iterative Deepening Search
迭代加深搜索，也常写作 IDDFS（Iterative Deepening Depth-First Search）
不断增加深度限制，重复执行 DFS，以求达到结合BFS和DFS，弥补两者的缺点
DFS 不保证找到最浅解，BFS按层扩展内存消耗大


IDA* 是A* 的变体，即结合了IDS
IDA* 将f(n)=g(n)+h(n)）作为搜索的阈值（Threshold），而不是像 IDDFS 那样使用固定的深度限制

1. 初始化：将初始阈值设置为起始节点的 f(n)=h(n);
2. DFS：从起始节点开始进行 DFS。如果某个节点的 f(n) 值超过了当前阈值，则该路径会被剪枝（Prune），不再进一步向下探索
3. 更新阈值：如果在当前阈值下未找到目标，算法会选择所有被剪枝节点中最小的 f(n) 值作为下一轮迭代的新阈值
4. 重复执行：算法带着新的阈值再次从起始节点重新开始搜索，直到找到目标节点为止

通过牺牲一部分时间（重复搜索）来换取极低的内存消耗，同时在合适的启发式函数引导下保持了寻找最优解的能力


MA* 是A* 的另一变体，Memory-bounded A* 记忆受限 A* 搜索，以及SMA*(simplified)
IDA* 的内存需求是线性的，非常小，这意味着即使你的计算机有充足的内存（例如 16GB），IDA* 也只会使用其中极小的一点，而无法通过利用剩余内存来加速搜索。SMA*利用硬件条件约束，优化搜索，尽可能填满这些空间以保留更多的搜索信息，从而减少重复搜索带来的时间消耗
SMA* 是 A* 和 IDA* 的平衡方案
SMA* 和 IDA*的主要代码差距在于frontier，后者只需要记录当前dfs的路径上的节点信息，前者则需要根据frontier大小来将f(n)较大的先删除


