#include<stdio.h>

#define MAX 1000
#define time 4

int queue[MAX];
int rear = - 1;
int front = - 1;
void push(int items)
{
    
       if (front == - 1) //if the front empty
          front = 0;
     
        rear = rear + 1;
        queue[rear] = items;
    
}  
void pop()
{
  front = front + 1;
}


int front1()
{
    return queue[front]; 	
}

int fl[MAX],arrivaltime[MAX],bursttime[MAX];
int priority[MAX],responsetime[MAX],completion_time[MAX];
int response[MAX], rflag[MAX],processid[MAX],tms,quatumtime[MAX];


void roundrobin()
{
      
      	if(responsetime[front1()]>0 && quatumtime[front1()]<4)
      	{
          		quatumtime[front1()]++;
          		responsetime[front1()]--;
          		if(responsetime[front1()]==0)
          		{
            	completion_time[front1()]=tms+1;
            	pop();
          		}
          		if(responsetime[front1()]!=0 && quatumtime[front1()]==4)
          		{
				quatumtime[front1()]=0;
				push(front1());
				pop();
          		}
        	}
      
}

int main()
{
    int i=0,n=0,small=0,last=-1,min,sum=0 ,large=0;
    printf("Enter The Number PROCESS(INTEGER):");
    scanf("%d",&n);
    printf("\n");
    for(i=0;i<n;i++) //O(N)
    { 
            printf("Enter The  Process ID(INTEGER):");
    		scanf("%d",&processid[i]);
    		printf("\n");
    		printf("Enter The ARRIVAL TIME(INTEGER):");
			scanf("%d",&arrivaltime[i]);
			printf("\n");
			printf("Enter The BURST TIME(INTEGER):");
			scanf("%d",&bursttime[i]);
			printf("\n");
			printf("Enter The PRIORITY(INTEGER):");
			scanf("%d",&priority[i]);
			printf("\n");
			printf("\n");
    		if(arrivaltime[i]>large)
    		  	large=arrivaltime[i];
    		sum+=bursttime[i];
    		responsetime[i]=bursttime[i];
    }
    min=MAX;
    for(tms=0; tms<=sum+large ;tms++)  
    {
      min=MAX;
      small=-1;   
      for(i=0;i<n;i++) //o(n)
      {
      	if(arrivaltime[i]<=tms && priority[i]<min && responsetime[i]>0 && !fl[i])
      	{
      		min=priority[i];
          		small=i;
        	}
      }
      
      if(small==-1)
      {
      	if(last !=-1 && responsetime[last]==0)
      	{
      		completion_time[last]=tms;
          		fl[last]=1;
        	}
        	last=-1;
        	roundrobin();
        	continue;
      }
      else if(small!=-1 &&  last==-1)
      {
      	
      	if(quatumtime[front1()]<=4 && quatumtime[front1()]>0)
      	{
      		push(front1());
      	     pop();
        	}
      }
      if(small!=-1 && ! rflag[small])
      {
      	response[small]=tms-arrivaltime[small];
      	 rflag[small]=1;
      }
      if( small!=last && last!=-1 && !fl[last])
      {
      	push(last);    //pushing the process into the last of the queue
      	fl[last]=1;
      }
      if(small !=-1)
      	responsetime[small]--;
      
      if((small !=-1) && ((responsetime[small]==0) ||(bursttime[small]-responsetime[small])==time))
      {
      	if((bursttime[small]-responsetime[small])==time && responsetime[small]!=0)
      	{
      		fl[small]=1;
      		push(small);
        	}
       	else if(small!=-1)
       	{
          		completion_time[small]=tms+1;
          		fl[small]=1;
        	}
      }
      last=small;
    }
    
    int waiting_time[n];
     for(int i=0;i<n;i++)
     {
     
     waiting_time[i]= ((completion_time[i]- arrivaltime[i])-bursttime[i]);
       if(waiting_time[i]<0)
       {
        waiting_time[i]=0;
       }
 }
printf("\nProcess Id\tResponse Time\tCompletion Time\tTurnaound Time\t\tWaiting Time");
   for(int i=0;i<n;i++)   //o(n)
      printf("\n%d \t\t%d\t\t%d\t\t%d\t\t%d\n",processid[i],response[i],completion_time[i],completion_time[i]-arrivaltime[i],waiting_time[i]);
    float waitingaverage=0.0,tatavg=0.0;
     for(int i=0;i<n;i++)
     {
         waitingaverage+=completion_time[i]-arrivaltime[i]-bursttime[i];	
	     tatavg +=completion_time[i] - arrivaltime[i]; 
	 }

	 printf("\nAVG WAITING TIME IS : %f\n",waitingaverage/n);
	 printf("\nAVG Turnaround is : %f",tatavg/n);
    
    return 0;
}
