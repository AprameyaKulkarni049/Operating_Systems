#include<stdio.h>
struct process
{
    int p_id;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
};
void main()
{
    int n;
    printf("\nEnter number of processes: ");
    scanf("%d",&n);
    struct process p[n];

    for(int i=0;i<n;i++)
    {
        p[i].p_id=i+1;
        printf("\nEnter Arrival time: ");
        scanf("%d",&p[i].at);
        printf("\nEnter Burst time: ");
        scanf("%d",&p[i].bt);
    }

    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            struct process temp;
            if(p[i].at>p[j].at)
            {
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
    int curr_time=0;
    float total_tat=0,total_wt=0;

    for(int i=0;i<n;i++)
    {
        if(curr_time<p[i].at)
        {
            curr_time=p[i].at;
        }
        p[i].ct= curr_time + p[i].bt;
        p[i].tat= p[i].ct - p[i].at;
        p[i].wt= p[i].tat - p[i].bt;
        curr_time=p[i].ct;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    for(int i=0;i<n;i++)
    {
        printf("\nProcess id: %d",p[i].p_id);
        printf("\nArrival time: %d",p[i].at);
        printf("\nBurst time: %d",p[i].bt);
        printf("\nCompletion time: %d",p[i].ct);
        printf("\nWaiting time: %d",p[i].wt);
        printf("\nTurnaround time: %d",p[i].tat);
        printf("\n");
    }
    printf("\nAverage waiting time: %.2f",(total_wt/n));
    printf("\nAverage turnaround time: %.2f",(total_tat/n));

}
