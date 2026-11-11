#include<stdio.h>
#include<iostream>
using namespace std;

unsigned int cnt=0;	//原来的名字 count 会和 std::count 重名（using namespace std），编译报二义性
typedef struct
{
	unsigned int A;
	unsigned int B;
	unsigned int C;
}resource;//系统中共3类资源
typedef struct
{
	resource max;
	resource allacation;
	resource need;
	resource work;
	bool     finish;
}process;
resource request(process &p)
{
	unsigned int x1,x2,x3;
	resource re;
	printf("please input the number of the requesting resource of the process:\n");
	printf("resource A:");
	cin>>x1;
	printf("resource B:");
	cin>>x2;
	printf("resource C:");
	cin>>x3;

	re.A=x1;
	re.B=x2;
	re.C=x3;
	return re;
}
void needResource(process &p)
{
	p.need.A=p.max.A-p.allacation.A;
	p.need.B=p.max.B-p.allacation.B;
	p.need.C=p.max.C-p.allacation.C;
}

resource availableresource(process *p)
{
	resource a;
	a.A=10-p[0].allacation.A-p[1].allacation.A-p[2].allacation.A-p[3].allacation.A-p[4].allacation.A;
	a.B=5-p[0].allacation.B-p[1].allacation.B-p[2].allacation.B-p[3].allacation.B-p[4].allacation.B;
	a.C=7-p[0].allacation.C-p[1].allacation.C-p[2].allacation.C-p[3].allacation.C-p[4].allacation.C;

	return a;
}
void printtable(process *p,resource available)
{
	printf("     max   ");
	printf("    allacation");
	printf("   need  ");
	printf("     available\n");

	for(unsigned int xx=0;xx<5;xx++)
	{

		printf("p%d   %d %d %d",xx,p[xx].max.A,p[xx].max.B,p[xx].max.C);
		printf("	 %d %d %d",p[xx].allacation.A,p[xx].allacation.B,p[xx].allacation.C);
		printf("	    %d %d %d",p[xx].need.A,p[xx].need.B,p[xx].need.C);
		if(xx==0)
			printf("	 %d %d %d\n",available.A,available.B,available.C);
		else
			printf("\n");
	}
}

void printTableByLine(process  &p,int xx,resource &available)
{
	cnt++;
	if(cnt==1)
	{
		printf("     work   ");
		printf("    allacation");
		printf("   need  ");
		printf("    work+allacation");
		printf("          finish\n");
	}
	

	printf("p%d   %d %d %d",xx,p.work.A,p.work.B,p.work.C);
	printf("	 %d %d %d",p.allacation.A,p.allacation.B,p.allacation.C);
	printf("	    %d %d %d",p.need.A,p.need.B,p.need.C);
	printf("	    %d %d %d",available.A,available.B,available.C);
	printf("	       %s   \n",p.finish?"true":"false");
	
}



int main()
{

	process p[5];
	unsigned int buffer[5];
	unsigned int b=0,j=0,temp=0;

		
	resource available;

	p[0].max.A=7;
	p[0].max.B=5;
	p[0].max.C=3;
	
	p[1].max.A=3;
	p[1].max.B=2;
	p[1].max.C=2;
	
	p[2].max.A=9;
	p[2].max.B=0;
	p[2].max.C=2;

	p[3].max.A=2;
	p[3].max.B=2;
	p[3].max.C=2;

	p[4].max.A=4;
	p[4].max.B=3;
	p[4].max.C=3;

	p[0].allacation.A=0;
	p[0].allacation.B=1;
	p[0].allacation.C=0;

	p[1].allacation.A=2;
	p[1].allacation.B=0;
	p[1].allacation.C=0;

	p[2].allacation.A=3;
	p[2].allacation.B=0;
	p[2].allacation.C=2;

	p[3].allacation.A=2;
	p[3].allacation.B=1;
	p[3].allacation.C=1;

	p[4].allacation.A=0;
	p[4].allacation.B=0;
	p[4].allacation.C=2;
	
	for(unsigned int h=0;h<5;h++)
	{
		
		needResource(p[h]);
		p[h].finish=false;
	}

	available=availableresource(p);
	

loop:
	while(true)
	{

		unsigned int nprocess;
		resource req;
		

		available=availableresource(p);	//每轮重新算一次可用资源（上面的安全性检查会改动 available）
		printtable(p,available);

		printf("please input the number of the process requesting the resources:");
		cin>>nprocess;
		if(nprocess>4)
		{
			printf("the %dth process doesn't exist!\n",nprocess);
			return 0;
		}
		printf("this is the %dth process's request.\n",nprocess);
		req=request(p[nprocess]);

		//available=availableresource(p);
		if((req.A>p[nprocess].need.A)||(req.B>p[nprocess].need.B)||(req.C>p[nprocess].need.C))
		{
			printf("illegal request! please input again!\n");
			goto loop;
			
		}

		available=availableresource(p);



		if((req.A>available.A)||(req.B>available.B)||(req.C>available.C))
		{
			printf("there isn't enough resource!\n");			
			cout<<"wait please........."<<endl;
				
			goto loop;
		}

		p[nprocess].allacation.A=p[nprocess].allacation.A+req.A;
		p[nprocess].allacation.B=p[nprocess].allacation.B+req.B;
		p[nprocess].allacation.C=p[nprocess].allacation.C+req.C;


		printf("this is the resource table that has been modified\n");
		needResource(p[nprocess]);
		available=availableresource(p);
		printtable(p,available);
	
		j=0;		//每轮都从头记录安全序列，否则第二轮的 buffer 会越界
		cnt=0;		//每轮重新打印一次表头
		for(unsigned int t=0;t<5;t++)
			{
				p[t].work.A=available.A;
				p[t].work.B=available.B;
				p[t].work.C=available.C;
				p[t].finish=false;	//每轮安全性检查前必须清空 finish，否则第二轮起全部为 true
			}

		
		for(unsigned int k=0;k<15;k++)
		{
			temp=(k%5);

			if(p[temp].finish==false)
			{
				
				if((p[temp].work.A>=p[temp].need.A)&&(p[temp].work.B>=p[temp].need.B)&&(p[temp].work.C>=p[temp].need.C))
					{				


							resource temp0;

							available.A=p[temp].work.A+p[temp].allacation.A;
							available.B=p[temp].work.B+p[temp].allacation.B;
							available.C=p[temp].work.C+p[temp].allacation.C;

						for(unsigned int t=0;t<5;t++)
						{
							if(t!=temp)
							{
								p[t].work.A=available.A;
								p[t].work.B=available.B;
								p[t].work.C=available.C;
							}
							
						}
						p[temp].finish=true;
						printTableByLine(p[temp],temp,available);
						buffer[j]=temp;
						j++;					
					}

			}
	
		}
		
		
		if(p[0].finish&&p[1].finish&&p[2].finish&&p[3].finish&&p[4].finish)
		{
			cout<<"the safe sequence has been found,as follows:"<<endl;
			for(unsigned int j=0;j<5;j++ )
			{
				printf("p[%d]",buffer[j]);
			}
			printf("\n");
		}
		
		else
		{
			cout<<"the scheme is not safe! the system will is restoring the resource........ "<<endl;

			p[nprocess].allacation.A-=req.A;
			p[nprocess].allacation.B-=req.B;
			p[nprocess].allacation.C-=req.C;

			p[nprocess].need.A+=req.A;
			p[nprocess].need.B+=req.B;
			p[nprocess].need.C+=req.C;

		}
	}
	
}
