# 6数组和队列

Status: Not started

约瑟夫环用queue模拟循环出队

```cpp
int n, m; cin >> n >> m;
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    while (!q.empty()) {
        for (int i = 1; i < m; i++) {
            q.push(q.front());
            q.pop();
        }
        cout << q.front() << endl;
        q.pop();
    }
```

![image.png](6%E6%95%B0%E7%BB%84%E5%92%8C%E9%98%9F%E5%88%97/image.png)

# 高精度

```cpp
string add(string a, string b, string& ans) {
    //判断字符串长度
    int lena = a.size();
    int lenb = b.size();
    int lmax = max(lena, lenb);
    //倒置字符串，并转换成单个数字储存在数组中
    for (int i = 0; i < lena; i++) {
        na[lena - i - 1] = a[i] - '0';
    }
    for (int i = 0; i < lenb; i++) {
        nb[lenb - i - 1] = b[i] - '0';
    }
    //进位
    for (int i = 0; i < lmax; i++) {
        na[i] += nb[i];
        na[i + 1] += na[i] / 10;
        na[i] %= 10;
    }
    //长度判断
    if (na[lmax]) lmax++;
    //转ans字符串
    for (int i = lmax-1; i >= 0; i--) {
        ans += na[i] + '0';
    }
    return ans;
}
```