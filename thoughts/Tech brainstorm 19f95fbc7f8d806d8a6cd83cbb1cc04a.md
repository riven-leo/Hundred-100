# Tech brainstorm



[赞美空我！真正的神作无惧时间检验！《假面骑士空我》观后感漫谈【第九放映室】_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV19f9tYyExc/?spm_id_from=333.1007.tianma.2-2-4.click&vd_source=4f8462d96ba22f7e95b8f0eb7c908f0e)

# 3.11

- 处理极限情况，首先思考当输入一个数据时能否处理
- 有不少构造函数 例 `std::string(size_t count, char ch);`
- 处理字符串时，按位处理，进行分类讨论，分出字符有几种情况，分别处理，这个思路很清晰
- 优化思路，将重复出现的代码进行整合

- 回文链表
    - 逆序可以用考虑栈思想
    - 判断回文 反转结构比分奇偶讨论要好
    - 双指针可以用一个for循环写
    
    ```cpp
    for (int i = 0, j = (int)vals.size() - 1; i < j; ++i, --j)
    		if (vals[i] != vals[j]) 
    				return false;
    ```
    
    - 链表遍历时 while(head) ······head → next; 非常简洁好用
    - 栈问题，要bool返回值时，如果是判断是否栈为空结束，直接return st. empty（）；即可，空则返回true 非空则返回false，不用单独自己写
- emplace or emplace_back 和 push or push_back的使用场景
    
    
    | 场景 | 适合 `push` | 适合 `emplace` |
    | --- | --- | --- |
    | 插入已存在的对象 | ✅ | ❌ |
    | 需要构造新对象 | ❌ | ✅ |
    | 可能涉及拷贝/移动 | ✅ | ❌（更高效） |
    | 代码可读性优先 | ✅ | ❌（可能不直观） |
- INT_MAX 、 INT_MIN 宏常量 表示int型的最大数和最小数
    - c中`<limits.h>` 里有，c++则是`<climits>`
        
        [宏定义](Tech%20brainstorm/%E5%AE%8F%E5%AE%9A%E4%B9%89%201b495fbc7f8d80bdb930fd3679558f37.md)
        
- 设计题常规思路
    
    **1. 明确需求和接口**
    
    - **问题拆解**：仔细阅读题目描述，明确需要实现哪些功能（例如 `insert`, `get`, `delete` 等）。
    - **接口设计**：定义清晰的输入输出，例如方法的参数、返回值、异常处理等。
    - **示例验证**：通过题目给出的示例，验证自己的设计是否能覆盖基本场景。
    
    ---
    
    **2. 选择合适的数据结构与算法**
    
    - **时间复杂度**：根据操作频率选择最优结构（例如哈希表 O(1) 查询、堆 O(1) 取极值）。
    - **空间复杂度**：避免不必要的空间浪费，例如使用链表而非数组实现动态扩容。
    - **权衡取舍**：例如 LRU 缓存（[LeetCode 146](https://leetcode.com/problems/lru-cache/)）需要结合哈希表（快速查找）和双向链表（快速增删）。
    
    ---
    
    **3.  处理边界条件 （可迁移）**
    
    - **空值/无效输入**：例如插入空数据、删除不存在的元素。
    - **容量限制**：例如缓存满时的淘汰策略（LRU、LFU）。
    - **极端数据**：例如最小值、最大值、重复数据。
- 线程是什么
- 理解接口interface什么意思
    - 接口是定义对象间交互行为的抽象规范，通过约定“能做什么”而非“如何做”，实现代码解耦和多态，不依赖具体实现细节。
- 通常自定义类里会有个跟类同名的构造函数，用于当在构建这个自定义数据结构时进行初始化，便于后续方法的使用111111111
    
    ```cpp
    class MinStack {
        stack<int> x_stack;
        stack<int> min_stack;2222222封装，只在该数据结构内才能有
    public:
        /** initialize your data structure here. */
        MinStack() {
            min_stack.push(INT_MAX);
        }11111111，便于后面栈的使用防止出现未定义行为
        
        void push(int x) {
            x_stack.push(x);
            min_stack.push(min(min_stack.top(), x));
        }
        
        void pop() {
            x_stack.pop();
            min_stack.pop();
        }
        
        int top() {
            return x_stack.top();
        }
        
        int getMin() {
            return min_stack.top();
        }
    };
    
    /**
     * Your MinStack object will be instantiated and called as such:
     * MinStack* obj = new MinStack();
     * obj->push(x);
     * obj->pop();
     * int param_3 = obj->top();
     * int param_4 = obj->getMin();
     */
    ```
    
- 补充常规 `new` 的用法
    - **单个对象**：`new` 后直接跟类型，编译器会自动计算所需内存大小。
        
        ```cpp
        int* p = new int;      // 正确！自动分配 sizeof(int) 字节
        ```
        
        不需要手动计算 `sizeof(int)`，编译器隐式处理。
        
    - **对象数组**：通过 `[n]` 指定元素个数，编译器计算总大小
        
        ```cpp
        int* arr = new int[10]; // 正确！分配 sizeof(int)*10 字节
        ```
        
        同样无需手动计算总字节数。
        
    
    如果要创建包含 `n` 个 `MinStack` 对象的数组：
    
    ```
    int n = 5;                     // 假设需要 5 个对象
    MinStack* arr = new MinStack[n]; // 分配并构造数组
    ```
    
    - **底层行为**：
        - `new MinStack[n]` 会分配 `sizeof(MinStack) * n` 字节的内存。
        - 对每个元素自动调用 `MinStack` 的**默认构造函数**（无参构造函数）。
- 什么是预处理
    
    
- 别人代码里的::有什么用
    
    萨芬大厦佛啊法发阿发
    

# 3.12

- first → st; second → nd;

- 除法很多要考虑的——整数还是浮点数
    - int相除默认、向零取整== 向零截断、向下取整、向上取整
        
        5/2  2.5→2、2、2、3
        
        -5/2  -2.5→-2、
        
- 中缀表达式和后缀表达式
    - 逆波兰表达式是一种后缀表达式，所谓后缀就是指算符写在后面。
    - 平常使用的算式则是一种中缀表达式，如 `( 1 + 2 ) * ( 3 + 4 )` 。
    - 该算式的逆波兰表达式写法为 `( ( 1 2 + ) ( 3 4 + ) * )` 。
    
    逆波兰表达式主要有以下两个优点：
    
    - 去掉括号后表达式无歧义，上式即便写成 `1 2 + 3 4 + *` 也可以依据次序计算出正确结果。
    - 适合用栈操作运算：遇到数字则入栈；遇到算符则取出栈顶两个数字进行计算，并将结果压入栈中
- string 转 num
    
     **string c++函数**
    
    - `stoi`：将字符串转换为 `int`。
    - `stol`：将字符串转换为 `long`。
    - `stoll`：将字符串转换为 `long long`。
    - `stof`：将字符串转换为 `float`。
    - `stod`：将字符串转换为 `double`。
    - `stold`：将字符串转换为 `long double`
    
    **或使用 C 标准库函数**
    
    C++ 兼容 C 标准库，可以使用以下函数：
    
    - `atoi`：将字符串转换为 `int`。
    - `atol`：将字符串转换为 `long`。
    - `atoll`：将字符串转换为 `long long`。
    - `atof`：将字符串转换为 `double`。
    - 缺点：
        - 不支持异常处理，如果字符串无效，返回 `0` 或未定义行为。
        - 只能处理 C 风格字符串（`const char*`），不能直接处理 `std::string`。
    
    例：
    
    ```cpp
    std::string s = "45.67";
    double num = std::stod(s);  // 输出 45.67
    
    #include <cstdlib>
    const char* s = "12345";
    int i = std::atoi(s);       // int
    long l = std::atol(s);      // long
    double d = std::atof(s);    // double
    ```
    
- num 转 string
    
    **to_string 函数**  
    
    - 缺点：浮点数转换时会保留多余的小数位。
    
    ```cpp
    #include <string>
    
    int num = 12345;
    std::string s = std::to_string(num);  // 输出 "12345"
    
    double d = 67.89;
    std::string s2 = std::to_string(d);   // 输出 "67.890000"
    ```
    
    **或C++ 兼容 C 标准库，可以使用以下函数：**
    
    - `sprintf`：将数字格式化为 C 风格字符串。
    - `snprintf`：更安全的版本，避免缓冲区溢出。
    
    ```cpp
    #include <cstdio>
    #include <array>
    #include <string>
    
    int num = 12345;
    std::array<char, 10> buffer;
    std::snprintf(buffer.data(), buffer.size(), "%d", num);
    std::string s(buffer.data());  // 输出 "12345"
    
    double d = 67.89;
    std::snprintf(buffer.data(), buffer.size(), "%.2f", d);
    std::string s2(buffer.data());  // 输出 "67.89"
    ```
    
    - 优点：灵活，支持格式化。
    - 缺点：需要手动管理缓冲区，容易出错。
- 判断一段代码是o(n)还是o(logn)
    
    
- o(1) 和o(n)区别 前者指执行时间和输入规模n没关系，都执行固定次数的操作； 后者数据变2倍，执行时间也变成2倍
    
    
- for循环遍历 c++11形式
    
    ```cpp
    std::vector<std::string> vec = {"apple", "banana", "cherry"};
    
        for (const auto& str : vec) {
            std::cout << str << std::endl;
        }
    ```
    
    范围 `for` 循环（语法糖）（即 `for (auto& element : container)` 语法）可以用于**大多数 STL 容器**，但并非所有。具体是否支持取决于容器是否满足以下条件：
    
    ### 1. **支持的容器**
    
    所有提供 **`begin()` 和 `end()` 成员函数**的 STL 容器均支持范围 `for` 循环。这包括：
    
    - **序列容器**：`vector`、`deque`、`list`、`forward_list`、`array`、`string`。
    - **关联容器**：`set`、`map`、`multiset`、`multimap`。
    - **无序关联容器**：`unordered_set`、`unordered_map`、`unordered_multiset`、`unordered_multimap`。
    - **容器适配器以外的其他容器**：如 `valarray`（需 C++11 后兼容迭代器）。
    
    ### 2. **不支持的容器**
    
    以下 **容器适配器** 不支持范围 `for` 循环，因为它们**不提供迭代器接口**：
    
    - **`stack`**：基于 `deque`/`list`/`vector` 封装，仅支持 `push()`、`pop()`、`top()`。
    - **`queue`**：基于 `deque`/`list` 封装，仅支持 `push()`、`pop()`、`front()`、`back()`。
    - **`priority_queue`**：基于 `vector`/`deque` 封装，仅支持堆操作。
    
    此外，`bitset` 也不支持迭代器，因此无法直接使用范围 `for` 循环。
    
    **语法糖（Syntactic Sugar）** 是编程语言中的一个术语，指那些**对代码功能没有实质改变，但能让代码更简洁、易读或符合直觉的语法特性**。它本质上是一种语法上的“包装”，目的是让开发者写代码更轻松，但底层实现依然是原有的机制。
    
    **语法盐（Syntactic Salt）**与语法糖相反，**语法盐**指为了让代码更安全或避免错误而设计的**冗余语法**。
    
- 补充使用const的情形
    
    [const constant constance](Tech%20brainstorm/const%20constant%20constance%201b495fbc7f8d8016969cdbad3f908aa7.md)
    
- 判断算法超时的方法
- Unix路径什么意思

# 3.17

- 序号问题
    
    访问第n个数，写n-1 下标n-1 位置n-1
    
    问 1 和 k 中间有多少个数
    
    问从 1 到 k 有多少个数 k-1 +1
    
    问从 s 到 k 有多少个数 k-s +1
    

# 25.5.7

- CTRL+L 选中整行

# 25.5.8

- 英文单位快速转化为中文量感知：
    - 50k把k前的0一起看进去就是万了
    - 50M把M前面的0一起看进去就是千万了
    - 5.5k 5500 53.4M 五千万 567k 56万

[数据结构复习](Tech%20brainstorm/%E6%95%B0%E6%8D%AE%E7%BB%93%E6%9E%84%E5%A4%8D%E4%B9%A0%201f895fbc7f8d801fab58c92973a271b0.md)