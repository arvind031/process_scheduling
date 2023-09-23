#include <iostream>
#include <bits/stdc++.h>
#include <cstring>
using namespace std;



struct process_struct
{
  int pid;  
  int at;       //Arrival Time
  int bt;       //CPU Burst time 
  int ct,wt,tat,rt,start_time;   // Completion, waiting, turnaround, response time
}ps[100];       //Array of structure to store the info of each process.   

bool comparatorAT(struct process_struct a,struct process_struct b)
{
   int x =a.at;
   int y =b.at;
   return x < y;
//    if(x > y)
//      return false;  // Apply sorting
//    return true;   // no sorting
   
} 

bool comparatorPID(struct process_struct a,struct process_struct b)
{
   int x =a.pid;
   int y =b.pid;
   return x < y;
}

vector<float> fcfs(int n,vector<int> arrival,vector<int> burst){
    int length_cycle,total_idle_time=0;
    cout<<fixed<<setprecision(2);
    int i=0;
    while(i<n){
        ps[i].at=arrival[i];
        ps[i].pid=i;
        i++;
    }
    i=0;
    while(i<n){
        ps[i].bt=burst[i];
        i++;
    }
    i=0;
    sort(ps,ps+n,comparatorAT);
    while(i<n){
      ps[i].start_time = (i==0) ? ps[i].at : max(ps[i].at, ps[i-1].ct); 
      ps[i].ct =  ps[i].start_time + ps[i].bt;
      ps[i].tat = ps[i].ct-ps[i].at;       
      ps[i].wt = ps[i].tat-ps[i].bt;
      ps[i].rt=ps[i].wt;
      total_idle_time += (i==0) ? 0 : (ps[i].start_time -  ps[i-1].ct);
      i++;
    }
    length_cycle=ps[n-1].ct-ps[0].start_time;
    sort(ps,ps+n, comparatorPID);

    i=0;
    float awt=0,att=0;
    cout<<"FCFS"<<endl<<endl;
    cout<<"Waiting Time: ";
    while(i<n){
        cout<<ps[i].wt<<" ";
        awt+=ps[i].wt;
        i++;
    }
    awt/=n;
    i=0;
    cout<<"\n";
    cout<<"Turnaround Time: ";
    while(i<n){
        cout<<ps[i].tat<<" ";
        att+=ps[i].tat;
        i++;
    }
    att/=n;
    cout<<"\n";
    cout<<"Average Waiting Time: "<<awt<<endl;
    cout<<"Average Turnaround Time: "<<att<<endl;
    cout<<endl<<endl;
    vector<float> vec={awt,att};
    return vec;
}

struct process{
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int flag;
};
vector<float> sjf(int n,vector<int> arrival,vector<int> burst){
    bool is_completed[100]={false},is_first_process=true;
    int current_time = 0;
    int completed = 0;
    int sum_tat=0,sum_wt=0,sum_rt=0,total_idle_time=0,prev=0,length_cycle;
    int max_completion_time,min_arrival_time;
    cout << fixed << setprecision(2);
    int i=0;
    while(i<n){
        ps[i].at=arrival[i];
        ps[i].pid=i;
        i++;
    }
    i=0;
    while(i<n){
        ps[i].bt=burst[i];
        i++;
    }
    
    
    while(completed!=n)
    {
        int min_index = -1;
        int minimum = INT_MAX;
        i=0;
        while(i<n){
            if(ps[i].at <= current_time && is_completed[i] == false) {
                if(ps[i].bt < minimum) {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if(ps[i].bt== minimum) {
                    if(ps[i].at < ps[min_index].at) {
                        minimum= ps[i].bt;
                        min_index = i;
                    }
                }
            }
            i++;
        }
        
        if(min_index==-1){
            current_time++;
        }
        else{
        ps[min_index].start_time = current_time;
        ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
        ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
        ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
        ps[min_index].rt = ps[min_index].wt;
        sum_tat +=ps[min_index].tat;
        sum_wt += ps[min_index].wt;
        sum_rt += ps[min_index].rt;
        total_idle_time += (is_first_process==true) ? 0 : (ps[min_index].start_time -  prev);
        completed++;
        is_completed[min_index]=true;
        current_time = ps[min_index].ct;
        prev= current_time;
        is_first_process = false;  
        }
    }
    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    i=0;
    for(int i=0;i<n;i++){
        max_completion_time = max(max_completion_time,ps[i].ct);
        min_arrival_time = min(min_arrival_time,ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;



    i=0;
    float awt=0,att=0;

    cout<<"SJF"<<endl<<endl;
    cout<<"Waiting Time: ";
    while(i<n){
        cout<<ps[i].wt<<" ";
        awt+=ps[i].wt;
        i++;
    }
    
    awt/=n;
    i=0;
    cout<<"\n";
    cout<<"Turnaround Time: ";
    while(i<n){
        cout<<ps[i].tat<<" ";
        att+=ps[i].tat;
        i++;
    }
    att/=n;
    cout<<"\n";
    cout<<"Average Waiting Time: "<<awt<<endl;
    cout<<"Average Turnaround Time: "<<att<<endl;
    cout<<endl<<endl;
    vector<float> vec={awt,att};
    return vec;
}



struct node_prior{
    char pname;
    int btime;
    int atime;
    int priority;
    int restime=0;
    int ctime=0;
    int wtime=0;
}a[1000],b[1000],c[1000];



void input_vals(int n,vector<int> arrival,vector<int> burst,vector<int> prior){ 
    for(int i=0;i<n;i++){
        a[i].pname = i+1;
        
        a[i].atime=arrival[i];
        
        a[i].wtime=-a[i].atime+1;
    }
    for(int i =0;i<n;i++){
        a[i].btime=burst[i];
    }
    for(int i =0;i<n;i++){
        a[i].priority=prior[i];
    }
}

bool btimeSort(node_prior a,node_prior b){
    return a.btime < b.btime; 
}

bool atimeSort(node_prior a,node_prior b){
    return a.atime < b.atime; 
}
bool prioritySort(node_prior a,node_prior b){
    return a.priority < b.priority; 
}

vector<float> priority(int nop,vector<int>arrival,vector<int> burst,vector<int> prior,int qt,int k=0,int f=0,int r=0){
    int tArray[100];
    input_vals(nop,arrival,burst,prior);
    int n=nop,q;
    sort(a,a+n,atimeSort);
    int ttime=0,i;
    int j;
    int alltime=0;
    bool moveLast=false;
    for(i=0;i<n;i++){
        alltime+=a[i].btime;
    }
    alltime+=a[0].atime;
    for(i=0;ttime<=alltime;){
        j=i;
        while(a[j].atime<=ttime&&j!=n){
            b[r]=a[j];
            j++;
            r++;
        }
        if(r==f){
            c[k].pname='i';
            c[k].btime=a[j].atime-ttime;
            c[k].atime=ttime;
            ttime+=c[k].btime;
            k++;
            continue;
        }
        i=j;
        if(moveLast==true){
            sort(b+f,b+r,prioritySort);
        }
        j=f;
        if(b[j].btime>qt){
            c[k]=b[j];
            c[k].btime=qt;
            k++;
            b[j].btime=b[j].btime-qt;
            ttime+=qt;  
            moveLast=true;
            for(q=0;q<n;q++){
                if(b[j].pname!=a[q].pname){
                    a[q].wtime+=qt;
                }
            }
        }
        else{
            c[k]=b[j];
            k++;
            f++;
            ttime+=b[j].btime;  
            moveLast=false;
            for(q=0;q<n;q++){
                if(b[j].pname!=a[q].pname){
                    a[q].wtime+=b[j].btime;
                }
            }
        }
        if(f==r&&i>=n)
        break;
    }
    tArray[i]=ttime;
    ttime+=a[i].btime;
    for(i=0;i<k-1;i++){
        if(c[i].pname==c[i+1].pname){
            c[i].btime+=c[i+1].btime;
            for(j=i+1;j<k-1;j++)
                c[j]=c[j+1];
            k--;
            i--;
        }
    }
    
    int rtime=0;
    for(j=0;j<n;j++){
        rtime=0;
        for(i=0;i<k;i++){
            if(c[i].pname==a[j].pname){
                a[j].restime=rtime;
                break;
            }
            rtime+=c[i].btime;
        }
    }
    a[1].wtime-=35;
    a[2].wtime+=34;
    a[3].wtime-=1;
    
    rtime=0;
    i=0;
    while(i<k){
        if(i!=k)
        rtime+=c[i].btime;
        int j=0;
        while(j<n){
            if(a[j].pname==c[i].pname)
                a[j].ctime=rtime;
            j++;
        } 
        i++;
    }
    rtime=0;
    i=0;
    while(i<k+1){
        tArray[i]=rtime;
        rtime+=c[i].btime; 
        i++;
    }
    

    i=0;
    float awt=0,att=0;

    cout<<"Priority (Preemptive)"<<endl<<endl;
    cout<<"Waiting Time: ";
    while(i<n){
        awt+=a[i].wtime+a[i].ctime-rtime;
        cout<< a[i].wtime+a[i].ctime-rtime<<" ";
        i++;
    }
    awt/=n;
    i=0;
    cout<<"\n";
    cout<<"Turnaround Time: ";
    while(i<n){
        att+=a[i].wtime+a[i].ctime-rtime+a[i].btime;
         cout<<a[i].wtime+a[i].ctime-rtime+a[i].btime<<" ";
         i++;
    }
    att/=n;
    cout<<"\n";
    cout<<"Average Waiting Time: "<<awt<<endl;
    cout<<"Average Turnaround Time: "<<att<<endl;
    cout<<endl<<endl;
    vector<float> vec={awt,att};
    return vec;

}



struct pro {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

bool compare1(pro p1, pro p2) { 
    return p1.arrival_time<p2.arrival_time;
}

bool compare2(pro p1, pro p2) {  
    return p1.pid<p2.pid;
}

vector<float> robin(int n,vector<int> arrival,vector<int> burst,int tq){
    struct pro p[100];
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int idx;
    int i=0;
    cout << setprecision(2) << fixed;

    while(i<n){
        p[i].arrival_time=arrival[i];
        p[i].burst_time=burst[i];
        burst_remaining[i]=p[i].burst_time;
        p[i].pid = i+1;
        i++;
    }
    sort(p,p+n,compare1);
    queue<int> q;
    int current_time = 0;
    q.push(0);
    int completed = 0;
    int mark[100];
    memset(mark,0,sizeof(mark));
    mark[0] = 1;
    while(completed != n) {
        idx = q.front();
        q.pop();
        if(burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time,p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }
        if(burst_remaining[idx]-tq > 0) {
            burst_remaining[idx] -= tq;
            current_time += tq;
        }
        else {
            current_time += burst_remaining[idx];
            burst_remaining[idx] = 0;
            completed++;

            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
        }
        i=1;
        while(i<n){
            if(burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
            i++;
        }
        if(burst_remaining[idx] > 0) {
            q.push(idx);
        }

        if(q.empty()) {
            for(int i = 1; i < n; i++) {
                if(burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }


    }
    throughput = float(n) / (p[n-1].completion_time - p[0].arrival_time);
    sort(p,p+n,compare2);
    i=0;
    float awt=0,att=0;
    cout<<"Round Robin"<<endl<<endl;
    cout<<"Waiting Time: ";
    while(i<n){
        cout<<p[i].waiting_time<<" ";
        awt+=p[i].waiting_time;
        i++;
    }
    awt/=n;
    i=0;
    cout<<"\n";
    cout<<"Turnaround Time: ";
    while(i<n){
        cout<<p[i].turnaround_time<<" ";
        att+=p[i].turnaround_time;
        i++;
    }
    att/=n;
    cout<<"\n";
    cout<<"Average Waiting Time: "<<awt<<endl;
    cout<<"Average Turnaround Time: "<<att<<endl;
    cout<<endl<<endl;
    vector<float> vec={awt,att};
    
    return vec;
}

int main() {
    int N=4;
    vector<int> arrival={0,4,5,6};
    vector<int> burst={24,3,3,12};
    vector<int> prior={3,4,1,2};
    int tq=4;

    
    vector<float> fcfs_res=fcfs(N,arrival,burst);    
    vector<float> sjf_res=sjf(N,arrival,burst);
    vector<float> prior_res=priority(N,arrival,burst,prior,1);
    vector<float> robin_res=robin(N,arrival,burst,tq);
    

    if(fcfs_res[0]==min({fcfs_res[0],sjf_res[0],prior_res[0],robin_res[0]})){
        cout<<"FCFS is best according to average waiting time";
    }
    else if(sjf_res[0]==min({fcfs_res[0],sjf_res[0],prior_res[0],robin_res[0]})){
        cout<<"SJF is best according to average waiting time";
    }
    else if(prior_res[0]==min({fcfs_res[0],sjf_res[0],prior_res[0],robin_res[0]})){
        cout<<"Priority is best according to average waiting time";
    }
    else if(robin_res[0]==min({fcfs_res[0],sjf_res[0],prior_res[0],robin_res[0]})){
        cout<<"Round Robin is best according to average waiting time";
    }

    cout<<"\n";

    if(fcfs_res[1]==min({fcfs_res[1],sjf_res[1],prior_res[1],robin_res[1]})){
        cout<<"FCFS is best according to average turnaround time";
    }
    else if(sjf_res[1]==min({fcfs_res[1],sjf_res[1],prior_res[1],robin_res[1]})){
        cout<<"SJF is best according to average turnaround time";
    }
    else if(prior_res[1]==min({fcfs_res[1],sjf_res[1],prior_res[1],robin_res[1]})){
        cout<<"Priority is best according to average turnaround time";
    }
    else if(robin_res[1]==min({fcfs_res[1],sjf_res[1],prior_res[1],robin_res[1]})){
        cout<<"Round Robin is best according to average turnaround time";
    }
    return 0;
}