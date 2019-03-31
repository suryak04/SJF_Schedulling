#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<pthread.h>
//#include<semaphore.h>
void *ord1();
void *intro();
void *scan();
void *display();
void *sort();
void *ord();
void *wai();
char a[100];
int b[50],d[50];
int n,e,pri[20];
int samp[20],wait[20];

void *intro()
{
int fd1=open("Intro",O_CREAT|O_RDWR|O_APPEND,0777);
int m=read(fd1,a,100);
write(1,a,m);
}

void *scan()
{
scanf("%d",&n);
printf("\nEnter execution Time of Each Process\n");
for(int j=0;j<n;j++)
{
printf("\np[%d]--",j);
scanf("%d",&e);
samp[j]=e;
}
}

void *display()
{
printf("\nProcess 		Exec-Time	Wait-Time");
for(int i=0;i<n;i++)
{
printf("\np[%d] 			%d 		%d",i,samp[i],wait[i]);
}
}

int main()
{
pthread_t in,sc,di,so,or,wa,or1;
pthread_create(&in,NULL,intro,NULL);
pthread_create(&sc,NULL,scan,NULL);
//pthread_create(&di,NULL,display,NULL);
//pthread_create(&p,NULL,fun,NULL);
pthread_join(in,NULL);
pthread_join(sc,NULL);
//pthread_create(&di,NULL,display,NULL);
//pthread_join(di,NULL);
pthread_create(&so,NULL,sort,NULL);
pthread_join(so,NULL);
pthread_create(&or,NULL,ord,NULL);
pthread_join(or,NULL);
pthread_create(&wa,NULL,wai,NULL);
pthread_join(wa,NULL);
pthread_create(&di,NULL,display,NULL);
pthread_join(di,NULL);
pthread_create(&or1,NULL,ord1,NULL);
pthread_join(or1,NULL);
}

void *sort()
{
//printf("\n\nexecution part\n");
for(int k=0;k<n;k++)
{
d[k]=samp[k];
}
int c[50];
for(int i=0;i<n;i++)
{
  for(int j=0;j<n;j++)
     {
	if(samp[i]>samp[j]){}
	else{
	c[j]=samp[i];
	samp[i]=samp[j];
	samp[j]=c[j];
	}
     }
}
}

void *ord()
{
for(int i=0;i<n;i++)
{
 for(int j=0;j<n;j++)
    {
      if(samp[i]==d[j])
	{
	  b[i]=j;
	}
    }
}
}

void *wai()
{
int sum=0;
wait[0]=sum;
for(int j=1;j<n;j++)
{
sum=sum+samp[j-1];
wait[j]=sum;
}
int x;
for(int i=0;i<n;i++)
{
x=wait[i]/samp[i];
pri[i]=1+x;
}
}

void *ord1()
{
printf("\n\n		--Processing Schedule in Order of SJF AND PRIORITY\n");
printf("\nProcess		Exe-Time 	Wait-Time	Priority\n");
for(int i=0;i<n;i++)
{
printf("\np[%d]---		%d		%d		     %d",b[i],samp[i],wait[i],pri[i]);
}
printf("\n");
}

