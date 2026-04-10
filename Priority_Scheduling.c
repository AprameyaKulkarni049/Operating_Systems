#include<stdio.h>
typedef struct process
{
    int at,bt,ct,tat,wt,pr,pid,rt,comp;
}p;
void calculateAverages(p s[], int n) {
    float total_tat = 0, total_wt = 0;
    printf("\nPID\tPri\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        total_tat += s[i].tat;
        total_wt += s[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               s[i].pid, s[i].pr, s[i].at, s[i].bt, s[i].ct, s[i].tat, s[i].wt);
    }
    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
}
int main()
{
    int n,choice;
    printf("\nEnter the number of processes: ");
    scanf("%d",&n);
    printf("Enter choice:\n 1.Non-Preemptive 2.Preemptive\n");
    scanf("%d",&choice);
    p s[n];
    for(int i=0;i<n;i++)
    {
        s[i].pid=i+1;
        printf("\nEnter arrival time , burst time and Priority: ");
        scanf("%d %d %d",&s[i].at,&s[i].bt,&s[i].pr);
        s[i].rt=s[i].bt;
        s[i].comp=0;
    }
    int curr_time=0,comp_count=0;
    switch(choice)
    {
    case 1:
        {
            while(comp_count<n)
            {
                int idx=-1;
                int highest_priority=1e9;
                for(int i=0;i<n;i++)
                {
                    if(s[i].at<=curr_time && s[i].comp==0)
                    {
                        if(s[i].pr<highest_priority)
                        {
                            highest_priority=s[i].pr;
                            idx=i;
                        }
                    }
                }
                if(idx!=-1)
                {
                    curr_time+=s[idx].bt;
                    s[idx].ct=curr_time;
                    s[idx].tat=s[idx].ct-s[idx].at;
                    s[idx].wt=s[idx].tat-s[idx].bt;
                    s[idx].comp=1;
                    comp_count++;
                }
                else
                {
                    curr_time++;
                }
            }
            break;
        }
    case 2:
        {
            while(comp_count<n)
            {
                int idx=-1;
                int highest_priority=1e9;
                for(int i=0;i<n;i++)
                {
                    if(s[i].at<=curr_time && s[i].comp==0)
                    {
                        if(s[i].pr<highest_priority)
                        {
                            highest_priority=s[i].pr;
                            idx=i;
                        }
                    }
                }
                if(idx!=-1)
                {
                    s[idx].rt--;
                    curr_time++;
                    if (s[idx].rt == 0)
                    {
                        s[idx].ct =curr_time;
                        s[idx].tat = s[idx].ct - s[idx].at;
                        s[idx].wt = s[idx].tat - s[idx].bt;
                        s[idx].comp= 1;
                        comp_count++;
                    }
                }
                else
                {
                    curr_time++;
                }
            }
            break;
        }
    default:
        {
            printf("Invalid choice");
            return 1;
        }
    }
    calculateAverages(s,n);
    return 0;
}
