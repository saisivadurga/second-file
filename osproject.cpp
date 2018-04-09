#include<stdio.h>
#include<stdlib.h>

struct Process{
	int p;
	int burstTime;
	int priority;
};

struct P{
	int p;
	int start;
	int end;
};

//This is helping function for displaying queue
void printQueue(struct Process queue[],int size){

	for(int i=0 ; i<size ; i++){
		printf("(Process:%d, Priority:%d, BurstTime:%d) ",queue[i].p,queue[i].priority,queue[i].burstTime);
	}

	printf("\n");

}

//This is helping function for printing final ans.
void printFinalAns(struct P finalAns[],int size){

	for(int i=0 ; i<size ; i++){
		printf("Process:%d \t Start:%d \t End:%d\n",finalAns[i].p,finalAns[i].start,finalAns[i].end);
	}

	printf("\n");

}

int ansFinal(struct P finalAns1[],struct P finalAns2[],struct P finalAns3[],struct P finalAns[],int s1,int s2,int s3,int totalBurstTime){

	int t=0,fs=0;
	int q1p=0,q2p=0,q3p=0;

	while(t != totalBurstTime){

		for(int i=0 ; i<3 ; i++){

			if(i == 0){

				int qt = 10;

				for(int i=q1p; i<s1 ;i++){

					struct P temp;

					if(finalAns1[i].end-finalAns1[i].start < qt){
						temp.p = finalAns1[i].p;
						temp.start = t;
						t += finalAns1[i].end-finalAns1[i].start;
						temp.end = t;
						qt -= finalAns1[i].end-finalAns1[i].start;
						q1p++;
					}
					else{
						temp.p = finalAns1[i].p;
						temp.start = t;
						t += qt;
						temp.end = t;
						finalAns1[i].start += qt;
						finalAns[fs++] = temp;
						break;
					}

					finalAns[fs++] = temp;
				}

			}
			else if(i == 1){
				
				int qt = 10;

				for(int i=q2p; i<s2 ;i++){

					struct P temp;

					if(finalAns2[i].end-finalAns2[i].start < qt){
						temp.p = finalAns2[i].p;
						temp.start = t;
						t += finalAns2[i].end-finalAns2[i].start;
						temp.end = t;
						qt -= finalAns2[i].end-finalAns2[i].start;
						q2p++;
					}
					else{
						temp.p = finalAns2[i].p;
						temp.start = t;
						t += qt;
						temp.end = t;
						finalAns2[i].start += qt;
						finalAns[fs++] = temp;
						break;
					}

					finalAns[fs++] = temp;
				}

			}
			else{
				
				int qt = 10;

				for(int i=q3p; i<s3 ;i++){

					struct P temp;

					if(finalAns3[i].end-finalAns3[i].start < qt){
						temp.p = finalAns3[i].p;
						temp.start = t;
						t += finalAns3[i].end-finalAns3[i].start;
						temp.end = t;
						qt -= finalAns3[i].end-finalAns3[i].start;
						q3p++;
					}
					else{
						temp.p = finalAns3[i].p;
						temp.start = t;
						t += qt;
						temp.end = t;
						finalAns3[i].start += qt;
						finalAns[fs++] = temp;
						break;
					}

					finalAns[fs++] = temp;
				}

			}

		}

	}

	return fs;

}

//Implemented Round Robin For First Queue
int RR(struct Process queue[],int qs,struct P finalAns[],int totalBurstTime){

	int t = 0,fas = 0,qt = 4;


	while(t != totalBurstTime){

		for(int i=0 ; i<qs ; i++){

			if(queue[i].burstTime == 0)
				continue;
			
			struct P temp;

			if(queue[i].burstTime >= qt){
				temp.p = queue[i].p;
				temp.start = t;
				temp.end = t+qt;
				queue[i].burstTime -= qt;
				t += qt;
			}
			else{
				temp.p = queue[i].p;
				temp.start = t;
				temp.end = t+queue[i].burstTime;
				t += queue[i].burstTime;
				queue[i].burstTime = 0;
			}
		
			finalAns[fas++] = temp; 
		}

	}

	return fas;

}


//Implemented Priority Scheduling
int FCFS(struct Process queue[],int qs,struct P finalAns[]){

	int t=0,fas=0;

	for(int i=0 ; i<qs ; i++){
		struct P temp;
		temp.p = queue[i].p;
		temp.start = t;
		temp.end = t+queue[i].burstTime;
		t += queue[i].burstTime;
		finalAns[fas++] = temp;
	}

	return fas;

}


//Comparator function for sorting prcoess in second queue
int comp(const void *p1,const void *p2){
	struct Process p = *(struct Process *)p1;
	struct Process q = *(struct Process *)p2;

	return p.priority-q.priority;
}

int main(){

	struct Process queue1[100]; //This queue follows round robin with quantum time of 4.
	struct Process queue2[100]; //This queue follows priority queue scheduling.
	struct Process queue3[100]; //This queue follows FCFS(First Come First Serve Scheduling).

	int n,sizeq1,sizeq2,sizeq3,q1BT,q2BT,q3BT;
	sizeq1 = sizeq2 = sizeq3 = 0;
	q1BT = q2BT = q3BT = 0;

	printf("Enter the number of process you want to enter: \n");
	scanf("%d",&n);

	printf("Enter Process with their Priority and Burst Time\n");
	for(int i=0 ; i<n ; i++){
		struct Process temp;
		temp.p = i+1;
		scanf("%d%d",&temp.priority,&temp.burstTime);

		if(temp.priority >=1 && temp.priority < 10){
			queue1[sizeq1++] = temp;
			q1BT += temp.burstTime;
		}

		if(temp.priority >= 10 && temp.priority < 20){
			queue2[sizeq2++] = temp;
			q2BT += temp.burstTime;
		}

		if(temp.priority >= 20){
			queue3[sizeq3++] = temp;
			q3BT += temp.burstTime;
		}

	}

	struct P finalAnsQ1[300];
	struct P finalAnsQ2[300];
	struct P finalAnsQ3[300];
	int faq1s = 0,faq2s = 0,faq3s = 0;

	faq1s = RR(queue1,sizeq1,finalAnsQ1,q1BT);

	qsort(queue2,sizeq3,sizeof(struct Process),comp);
	faq2s = FCFS(queue2,sizeq2,finalAnsQ2);

	faq3s =  FCFS(queue3,sizeq3,finalAnsQ3);

	// printFinalAns(finalAnsQ1,faq1s);
	// printFinalAns(finalAnsQ2,faq2s);
	// printFinalAns(finalAnsQ3,faq3s);

	int totalBurstTime = q1BT + q2BT + q3BT;

	struct P finalAns[600];

	int fs = ansFinal(finalAnsQ1,finalAnsQ2,finalAnsQ3,finalAns,faq1s,faq2s,faq3s,totalBurstTime);

	printFinalAns(finalAns,fs);

	// printQueue(queue1,sizeq1);
	// printQueue(queue2,sizeq2);
	// printQueue(queue3,sizeq3);
	// int totalTime;

	return 0;
}
