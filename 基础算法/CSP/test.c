#include <stdio.h>
#include <stdlib.h>
int main() {
    int n = 10;
    // malloc return void pointer default, 自动强转成对应类型in c
    // sizeof()里写*ptr，而不写int类型名，可以自适应ptr指针的类型
    // 给ptr指针分配10个int大小的内存空间，即40字节，可以存放10个int类型数据
    int* ptr = malloc(10 * sizeof(*ptr));

    // 分配内存失败
    if (ptr == NULL) return -1;

    // 使用内存
    for (int i = 0; i < n; i++) {
        ptr[i] = i + 1;
        printf("%d ", ptr[i]);
    }
    printf("\n");
    
    // 养成好习惯，释放内存后置NULL, 防止野指针
    free(ptr);
    ptr = NULL;
    return 0;
}