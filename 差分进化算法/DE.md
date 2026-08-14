鲁棒性——系统在异常条件下还能保持正常性能
Opfunu（全称为 Optimization benchmark Functions in Numpy）是一个用于数值优化问题的开源 Python 库。它专门为研究人员和学生提供丰富且全面的基准测试函数（Benchmark Functions），用于测试和评估各种全局优化算法和元启发式算法的性能
PyPI（Python Package Index）是 Python 编程语言的官方第三方软件仓库和分发平台    

对于每个个体population[i],生成一个mutant，通过crossover两者选一成为trial，
比较trial和population[i],更新population[i]为两者中更好的一个 —— 异步更新


① DE结构理解             ✅
② DE/rand/1 mutation     ✅
③ bin crossover          ✅
④ greedy selection       ✅
⑤ 同步代际更新            ✅
⑥ 接入CEC2017             ✅
⑦ FEs管理 / fitness缓存 
⑧ 多函数、多次独立运行、统计结果
