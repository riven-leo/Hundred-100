#include <stdio.h>
#include <stdlib.h>
#include <windows.h>        // 用于设置控制台代码页，解决中文乱码

#if defined(_MSC_VER)
#pragma execution_character_set("utf-8")
#endif

// 定义进程控制块 PCB
struct pcb {
    char name[10];      // 进程名
    char state;         // 进程状态
    int super;          // 优先级
    int ntime;          // 需要运行的时间
    int rtime;          // 已经运行的时间
    struct pcb* link;   // 指向下一个进程
};

typedef struct pcb PCB;

// 就绪队列头指针、当前进程指针
PCB* ready = NULL;
PCB* p = NULL;


// 按优先级从高到低排列进程
void sort() {
    PCB* first;
    PCB* second;
    int insert = 0;

    // 就绪队列为空，或者当前进程优先级最高
    if (ready == NULL || p->super > ready->super) {
        p->link = ready;
        ready = p;
    }
    else {
        first = ready;
        second = first->link;

        while (second != NULL) {
            if (p->super > second->super) {
                p->link = second;
                first->link = p;
                insert = 1;
                break;
            }
            else {
                first = first->link;
                second = second->link;
            }
        }

        // 插入队尾
        if (insert == 0) {
            first->link = p;
            p->link = NULL;
        }
    }
}


// 建立进程控制块
void input() {
    int i, num;

    printf("\n请输入进程数量:");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        printf("\n进程号 No.%d:\n", i);

        p = (PCB*)malloc(sizeof(PCB));

        if (p == NULL) {
            printf("内存分配失败！\n");
            exit(1);
        }

        printf("\n输入进程名:");
        scanf("%9s", p->name);

        printf("\n输入进程优先数:");
        scanf("%d", &p->super);

        printf("\n输入进程运行时间:");
        scanf("%d", &p->ntime);

        p->rtime = 0;
        p->state = 'w';
        p->link = NULL;

        sort();
    }
}


// 显示进程信息
void disp(PCB* pr) {
    printf("\nqname\tstate\tsuper\tndtime\truntime\n");

    printf("|%s\t", pr->name);
    printf("|%c\t", pr->state);
    printf("|%d\t", pr->super);
    printf("|%d\t", pr->ntime);
    printf("|%d\t", pr->rtime);

    printf("\n");
}


// 查看当前运行进程和就绪队列
void check() {
    PCB* pr;

    printf("\n**** 当前正在运行的进程是:%s\n", p->name);
    disp(p);

    pr = ready;

    printf("\n**** 当前就绪队列状态为:\n");

    while (pr != NULL) {
        disp(pr);
        pr = pr->link;
    }
}


// 撤销已经运行结束的进程
void destroy() {
    printf("\n进程 [%s] 已完成.\n", p->name);

    free(p);
    p = NULL;
}


// 当前进程运行一个时间片
void running() {
    (p->rtime)++;

    // 判断进程是否运行结束
    if (p->rtime >= p->ntime) {
        destroy();
    }
    else {
        // 未完成：优先级降低，重新进入就绪队列
        (p->super)--;
        p->state = 'w';

        sort();
    }
}


// 主函数
int main() {
    char ch;

    SetConsoleOutputCP(65001);   // 控制台改用 UTF-8，中文不再乱码

    input();

    // 清除输入进程信息时留下的换行符
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    int h = 0;

    while (ready != NULL) {
        printf("\nThe execute number:%d\n", ++h);

        // 从就绪队列取出队首进程
        p = ready;
        ready = p->link;
        p->link = NULL;

        // 设置为运行状态
        p->state = 'R';

        // 显示当前进程和就绪队列
        check();

        // 执行一个时间片
        running();

        if (ready != NULL) {
            printf("\n按回车键继续......");
            getchar();
        }
    }

    printf("\n\n所有进程已经完成.\n");

    return 0;
}