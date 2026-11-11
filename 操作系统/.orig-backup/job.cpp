#include  "stdio.h"
#include  "string.h"
#include  "stdlib.h"
typedef  struct  jcb  
{  
char name[4];  /*作业名*/  
int length;  /*作业长度，所需主存大小*/  
int printer ; /*作业执行所需打印机的数量*/  
int tape ; /*作业执行所需磁带机的数量*/  
int runtime ; /*作业估计的执行时间*/  
int waittime ; /*作业在输入井中的等待时间*/  
struct jcb *next ;/*指向下一个作业控制块的指针*/  
}JCB ; /*作业控制块类型定义*/
JCB *head ;  /*作业队列头指针定义*/  
int tape,printer;   
long memory;
shedule( )  /*作业调度函数*/  
{  
float xk,k;   
JCB *p,*q,*s,*t  ; 
//do 
//  {  
p=head ;  
s=NULL;   
q=NULL ;  
k=0 ;  
while(p!=NULL)  
{  
if(p->length<=memory&&p->tape<=tape&&p->printer<=printer) 
 /*系统可用资源是否满足作业需求*/
{  
xk=(float)(p->waittime)/p->runtime ;  
if(q==NULL||xk>k)
/*满足条件的第一个作业或者作业q的响应比小于作业p的响应比*/ 
{  
k=xk ;/*记录响应比*/  
q=p ; /*记录满足条件的p的位置*/  
t=s ;  /*记录p的前一个指针*/  
}/*if*/  
}/*if*/  
s=p ;  
p=p->next; /*指针p后移*/ 
}/*while*/  
if(q!=NULL)  
{  
if(t==NULL)/*满足条件的作业是作业队列的第一个*/  
head=head->next;   
else  
t->next=q->next ;  
/* 为作业q分配资源：分配主存空间；分配磁带机 分配打印机 */  memory=memory-q->length ;
tape=tape-q->tape ;  
printer=printer-q->printer ;  
printf("选中作业的作业名：%s\n",q->name)  ;
printf("作业大小、磁带机数、打印机数、等待时间、估计执行时间\n" );   
printf ("%5d%5d%5d%5d%5d",q->length,q->tape,q->printer,q->waittime,q->runtime);
   }  
//}while(q!=NULL);   
}/*作业调度函数结束*/ 
main( ) 
{  
int i;   
char name[4];   
int size,tcount,pcount,wtime,rtime ;  
JCB *p;   /*系统数据初始化*/  
memory=65536 ;  
tape=40 ; 
  printer=20  ;
  head=NULL;   
printf("输入作业相关数据(以作业大小为负数停止输入)：\n" ) ; 
 /*输入数据，建立作业队列*/  
printf("输入作业名、作业大小、磁带机数、打印机数、等待时间、估计执行时间\n" );   scanf("%s%d%d %d %d %d",name,&size,&tcount,&pcount,&wtime,&rtime);  
  while(size!=-1) 
  { 
 /*创建JCB*/  
p=(JCB*)malloc(sizeof(JCB)) ;  /*填写该作业相关内容*/  
strcpy(p-> name,name) ; 
    p-> length=size;  
    p-> printer=pcount ; 
p-> tape=tcount ; 
    p-> runtime=rtime ;  
p-> waittime=wtime ;  
/*挂入作业队列队首：*/ 
    p-> next=head;   
head=p;   /*输入一个作业数据*/  
printf(" 输入作业名、作业大小、磁带机数、打印机数、等待时间、估计执行时间\n" ) ;  
scanf(" %s%d%d%d%d%d" ,name,&size,&tcount,&pcount,&wtime,&rtime);   
}/*while*/  
shedule( ); /*进行作业调度*/  
}/*main( )结束*/