#include <bits/stdc++.h>
using namespace std;

class job
{
public:
    int id;
    string name;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int priority;

    job()
    {
        id = 0;
        name = "";
        at = 0;
        bt = 0;
        ct = 0;
        tat = 0;
        wt = 0;
        priority = 0;
    }
    job(int id, string name, int at, int bt)
    {
        this->id = id;
        this->name = name;
        this->at = at;
        this->bt = bt;
        ct = 0;
        tat = 0;
        wt = 0;
        priority = 0;
    }

    void operator=(const job &j)
    {
        this->id = j.id;
        this->name = j.name;
        this->at = j.at;
        this->bt = j.bt;
        ct = 0;
        tat = 0;
        wt = 0;
    }
};

bool comp(job &a, job &b)
    {
        if (a.at == b.at)
        {
            return a.priority < b.priority;
        }
        else
        {
            return a.at < b.at;
        }
    }

class schedular
{
public:
    int n;
    job *processes;
    vector<job> readyqueue;

    schedular()
    {
    }
    schedular(int n)
    {
        this->n = n;
        processes = new job[n];
    }

    void input()
    {
        int a, b;
        for (int i = 0; i < n; i++)
        {
            cout << "ENTER THE ARRIVIAL TIME AND BURST TIME OF THE PROCESS P" << (i + 1) << endl;
            cin >> a >> b;
            job j(i + 1, "P" + to_string(i + 1), a, b);
            processes[i] = j;
        }
    }

    

    void display()
    {

        cout << "ID\tAT\tBT\tCT\tTAT\tWT\tpriority" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << processes[i].id << "\t" << processes[i].at << "\t" << processes[i].bt << "\t" << processes[i].ct << "\t" << processes[i].tat << "\t" << processes[i].wt <<"\t"<<processes[i].priority<< endl;
        }

        float sumTat = 0, sumWt = 0;

        for (int i = 0; i < n; i++)
        {
            sumTat += processes[i].tat;
            sumWt += processes[i].wt;
        }

        cout << "the average turn around time is : " << sumTat / n << endl;
        cout << "the waiting turn around time is : " << sumWt / n << endl;
    }

    void displayGantt(vector<job> readyQueue, int currentTime)
    {
        cout << "Ready queue at current time " << currentTime << " sec : " << endl;
        for (int i = 0; i < readyQueue.size(); i++)
        {
            cout << readyQueue[i].name << "(" << readyQueue[i].bt << " sec)"
                 << " ";
        }
        cout << endl;
    }

    void fcfs()
    {
        int totaltime = 0;
        int currenttime = 0;
        int proccessCompleted = 0;

        sort(processes, processes + n, [](const job &j1, const job &j2)
             { return j1.at < j2.at; });

        for (int i = 0; i < n; i++)
        {
            totaltime += processes[i].bt;
        }

        while (currenttime <= totaltime)
        {
            if (proccessCompleted < n && processes[proccessCompleted].at <= currenttime)
            {
                readyqueue.push_back(processes[proccessCompleted]);
                proccessCompleted++;
            }
            if (readyqueue.size() > 0)
            {
                readyqueue[0].bt--;
                if (readyqueue[0].bt == 0)
                {
                    for (int i = 0; i < n; i++)
                    {
                        if (readyqueue[0].id == processes[i].id)
                        {
                            processes[i].ct = currenttime + 1;
                            processes[i].tat = processes[i].ct - processes[i].at;
                            processes[i].wt = processes[i].tat - processes[i].bt;
                            break;
                        }
                    }

                    readyqueue.erase(readyqueue.begin());
                }
            }
            currenttime++;
        }

        display();
    }
    void sjf()
    {
        int currenttime = 0;
        int totaltime = 0;
        int processCompleted = 0;

        sort(processes, processes + n, [](const job &j1, const job &j2)
             { return j1.at < j2.at; });

        for (int i = 0; i < n; i++)
        {
            totaltime += processes[i].bt;
        }

        while (currenttime <= totaltime)
        {
            if (processCompleted < n && processes[processCompleted].at <= currenttime)
            {
                readyqueue.push_back(processes[processCompleted]);
                processCompleted++;
            }
            sort(readyqueue.begin(), readyqueue.end(), [](const job &j1, const job &j2)
                 { return j1.bt < j2.bt; });

            if (readyqueue.size() > 0)
            {
                readyqueue[0].bt--;
                if (readyqueue[0].bt == 0)
                {
                    for (int i = 0; i < n; i++)
                    {
                        if (readyqueue[0].id == processes[i].id)
                        {
                            processes[i].ct = currenttime + 1;
                            processes[i].tat = processes[i].ct - processes[i].at;
                            processes[i].wt = processes[i].tat - processes[i].bt;
                            break;
                        }
                    }

                    readyqueue.erase(readyqueue.begin());
                }
            }
            currenttime++;
        }

        display();
    }

    void priority()
    {
        int currenttime = 0;
        int totaltime = 0;
        int processCompleted = 0;
        sort(processes, processes + n, [](const job &j1, const job &j2)
             { return j1.id < j2.id; });
        for (int i = 0; i < n; i++)
        {
            cout << "enter the priority for P" << (i + 1) << endl;
            cin >> processes[i].priority;
        }

        sort(processes, processes + n, comp);

        for (int i = 0; i < n; i++)
        {
            totaltime += processes[i].bt;
        }

        while (currenttime <= totaltime)
        {
            if(processCompleted < n && processes[processCompleted].at <= currenttime)
            {
                readyqueue.push_back(processes[processCompleted]);
                processCompleted++;
            }
            if (readyqueue.size() > 0)
            {
                readyqueue[0].bt--;
                if (readyqueue[0].bt == 0)
                {
                    for (int i = 0; i < n; i++)
                    {
                        if (readyqueue[0].id == processes[i].id)
                        {
                            processes[i].ct = currenttime + 1;
                            processes[i].tat = processes[i].ct - processes[i].at;
                            processes[i].wt = processes[i].tat - processes[i].bt;
                        }
                    }

                    readyqueue.erase(readyqueue.begin());
                }
            }

            currenttime++;
        }

        display();
    }

    void rr()
    {

        
    }
};

int main()
{

    int n;
    cout << "enter the number of processes ";
    cin >> n;
    schedular s(n);
    s.input();
    // s.fcfs();
    // s.sjf();
    s.priority();
    return 0;
}

// fcfs 5 4 5 6 4 0  3 6 2 5 4
// avgtat = 8   avgwt = 4

// sjf 4 0 8 1 4 2 9 3 5
//  avgtat = 8   avgwt = 6.5
//  ID      AT      BT      CT      TAT     WT
//  1       0       8       17      17      9
//  2       1       4       5       4       0
//  3       2       9       26      24      15
//  4       3       5       10      7       2

//
// 7 0 8 1 2 3 4 4 1 5 6 6 5 10 1 3 4 4 5 2 6 1
// 3 4 4 5 2 6 1
// ID   AT      BT      CT      TAT     WT
// 1       0       5       12      12      7
// 2       1       4       8       7       3
// 3       2       2       7       5       3
// 4       4       1       5       1       0
// the average turn around time is : 6.25
// the average turn around time is : 3.25

// 0 10 0 1 0 2 0 1 0 5 3 1 4 5 2