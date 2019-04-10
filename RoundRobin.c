#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<malloc.h>

struct process
{
	int arrivalTime;
	int burstTime;
	int PID;
	
	int bstTime;
	int waitTime;
	int turnTime;
	float noWait;
};

/*
defined functions
*/

void showHeading();
void get_input(struct process*,int);
void gotoxy(int x,int y);
void schedule_processes(struct process*, int,int);
void show_process_info(struct process*,int);



int main()
{
	
/*
Display Heading
*/
showHeading();

/*
Input the process information 
*/
	int noProcess;
	printf("\n\nEnter number of processes : ");
	scanf("%d",&noProcess);
	
	int timeSlice;
	printf("\nEnter time quantum : ");
	scanf("%d",&timeSlice);
	
	//allocating memory dynamically
	struct process *p_array =  (struct process *)malloc(sizeof(struct process)*noProcess);
	if(p_array==NULL)
	{
		printf("\n...Memory Error...");
		return -1;
	}
	
	//function to get input
	get_input(p_array,noProcess);

	//schedule the processes and print the result
	printf("\nOrder of execution :\n");
	schedule_processes(p_array,noProcess,timeSlice);
	
	//showing result (waiting time, turnaround time)
	printf("\n\nProcess info : ");
	show_process_info(p_array,noProcess);
}


void schedule_processes(struct process *p, int noProcess,int timeSlice)
{
	int i=0;
	int time = 0;
	int flag=0;
	int remainProcess=noProcess;								//number of remaining process
	float avg_wait_time=0,avg_turnaround_time=0;
	
	while(remainProcess!=0) 
  { 
    if((p+i)->bstTime<=timeSlice && (p+i)->bstTime>0) 			//changing process parameters
    { 
      time+=(p+i)->bstTime; 
      (p+i)->bstTime = 0; 
      flag=1; 
    } 
    else if((p+i)->bstTime>0) 
    { 
      (p+i)->bstTime-=timeSlice; 
      time+=timeSlice; 
    } 
    if((p+i)->bstTime==0 && flag==1) 
    { 
      remainProcess--; 
      
      if(remainProcess!=0)
      	printf("P%d -> ",(p+i)->PID); 
      else
      	printf("P%d",(p+i)->PID);				// no need to print '->' after last process 
      
      
      avg_wait_time+=time-(p+i)->arrivalTime-(p+i)->burstTime;        
      (p+i)->waitTime += time-(p+i)->arrivalTime-(p+i)->burstTime;   //wait Time for each process
      
      
      avg_turnaround_time+=time-(p+i)->arrivalTime; 
      (p+i)->turnTime += time-(p+i)->arrivalTime; 					//turnaround time for each process
      
      flag=0; 
    } 
    if(i==noProcess-1) 
      i=0; 
    else if((p+i+1)->arrivalTime<=time) 
      i++; 
    else 
      i=0; 
  } 
  
  printf("\n\nAverage Waiting Time= %.2f\n",avg_wait_time/noProcess); 
  printf("Avg Turnaround Time = %.2f",avg_turnaround_time/noProcess); 
  
}

void show_process_info(struct process *p, int noProcess)
{
	int i = 0;
	float WaitSum = 0;
	for(i = 0;i<noProcess;i++)
	{
		printf("\n\n--------------------------------------------");
		printf("\nP%d",(p+i)->PID);
		
		printf("\nWaiting Time : \t%d",(p+i)->waitTime);
		printf("\nTurnaround Time : \t%d",(p+i)->turnTime);
	}
}

void get_input(struct process *p,int noProcess)
{
	
	
	printf("\nEnter Process information ");
	printf("\n\n\tProcessID\t\tArrival Time\t\tBurst Time\n");
	gotoxy(8,10);
	printf("---------------------------------------------------------");
	

	int depth = 11;					
	int i =0;
	for(i=0;i<noProcess;i++)
	{
		gotoxy(12,depth);
		
		printf("%d",i+1);
		(p+i)->PID = i+1;
		gotoxy(35,depth);
		scanf("%d",&(p+i)->arrivalTime);
		
		gotoxy(60,depth);
		scanf("%d",&(p+i)->burstTime);
		
		(p+i)->bstTime = (p+i)->burstTime;
		(p+i)->turnTime = 0;
		(p+i)->waitTime = 0;
		depth+=1;
	}
	
}


void showHeading()
{
	printf("\t\t R O U N D \t R O B I N \t A L G O R I T H M\n");
	printf("\t\t--------------------------------------------------- ");
}

//function to move cursor to a particular location given by (x,y)
void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(  GetStdHandle(STD_OUTPUT_HANDLE) , c);
}
