// #include <bits/stdc++.h>
// using namespace std;

// class Process {
// public:
//     int id;
//     int burst;
//     int arrival;
// };

// void FCFS (Process processes[], int n, int wt[], int ct[], int tat[]) 
// {
//     int i = 0;
//     ct[i] = processes[i].arrival + processes[i].burst;
//     tat[i] = ct[i] - processes[i].arrival;
//     wt[i] = tat[i] - processes[i].burst;
//     i++;
//     for(;i<n;i++) 
//     {
//         if(processes[i].arrival < ct[i-1])
//             ct[i] = ct[i-1] + processes[i].burst;
//         else
//             ct[i] = processes[i].arrival + processes[i].burst;
//         tat[i] = ct[i] - processes[i].arrival;
//         wt[i] = tat[i] - processes[i].burst;
//     }
// }
// int main() {
//     Process proc[] = { {1, 6, 2 }, {2, 2, 5}, {3, 8, 1 }, {4, 3, 0}, {5, 4, 4} };
//     // Process proc[] = { {1, 2, 0 }, {2, 2, 1}, {3, 3, 5 }, {4, 4, 6}};
//     int n = sizeof(proc) / sizeof(proc[0]);
//     int wt[n], ct[n], tat[n];

//     for(int i=0;i<n-1;i++) {
//         for(int j=0;j<n-i-1;j++) {
//             if(proc[j].arrival > proc[j+1].arrival) {
//                 Process temp = proc[j];
//                 proc[j] = proc[j+1];
//                 proc[j+1] = temp;
//             }
//         }
//     }

//     FCFS(proc, n, wt, ct, tat);

//     cout.width(5);
//     cout<<"ID";
//     cout.width(5);
//     cout<<"AT";
//     cout.width(5);
//     cout<<"BT";
//     cout.width(5);
//     cout<<"CT";
//     cout.width(5);
//     cout<<"TAT";
//     cout.width(5);
//     cout<<"WT"<<endl;

//     for(int i=0;i<n;i++) {
//         cout.width(5);
//         cout<<proc[i].id;
//         cout.width(5);
//         cout<<proc[i].arrival;
//         cout.width(5);
//         cout<<proc[i].burst;
//         cout.width(5);
//         cout<<ct[i];
//         cout.width(5);
//         cout<<tat[i]; 
//         cout.width(5);
//         cout<<wt[i]<<endl;
//     }     
    
//     return 0;
// }


// #include <bits/stdc++.h>
// using namespace std;

// class Process
// {
// public:
//     int id;
//     int burst;
//     int arrival;
// };

// void npSJF (Process processes[], int n, int wt[], int ct[], int tat[]) {
//     int currentTime = 0, completedTasks = 0, shortestTask = 0, minBurst = INT_MAX;
//     int remainingTime[n];
//     for(int i=0;i<n;i++)
//         remainingTime[i] = processes[i].burst;

//     while(completedTasks != n) {
//         bool taskIP = false;
//         for(int j=0;j<n;j++) {
//             if(processes[j].arrival <= currentTime && remainingTime[i] < minBurst && remainingTime[j] > 0) {
//                 shortestTask = j;
//                 minBurst =remainingTime[i];
//                 taskIP = true;
//             }
//         }

//         if(!taskIP) {
//             currentTime++;
//             continue;
//         }

//         currentTime += processes[shortestTask].burst;
//         remainingTime[shortestTask] = 0;
//         minBurst = INT_MAX;
//         completedTasks++;
//         taskIP = false;
//         wt[shortestTask] =  currentTime - processes[shortestTask].arrival - processes[shortestTask].burst;
//         ct[shortestTask] = currentTime;
//         tat[shortestTask] = ct[shortestTask] - processes[shortestTask].arrival;
//     }    
// }

// int main() {
//     Process proc[] = { {1, 5, 0 }, {2, 3, 1}, {3, 4, 2 }, {4, 1, 4} };
//     int n = sizeof(proc) / sizeof(proc[0]);
//     int wt[n], ct[n], tat[n];

//     npSJF(proc, n, wt, ct, tat);

//     cout.width(5);
//     cout<<"ID";
//     cout.width(5);
//     cout<<"AT";
//     cout.width(5);
//     cout<<"BT";
//     cout.width(5);
//     cout<<"CT";
//     cout.width(5);
//     cout<<"TAT";
//     cout.width(5);
//     cout<<"WT"<<endl;

//     for(int i=0;i<n;i++) {
//         cout.width(5);
//         cout<<proc[i].id;
//         cout.width(5);
//         cout<<proc[i].arrival;
//         cout.width(5);
//         cout<<proc[i].burst;
//         cout.width(5);
//         cout<<ct[i];
//         cout.width(5);
//         cout<<tat[i]; 
//         cout.width(5);
//         cout<<wt[i]<<endl;
//     }     
//     return 0;
// }

// #include <bits/stdc++.h> 
// using namespace std; 

// struct Process { 
// 	int pid; 
// 	int bt;
// 	int art; 
// }; 


// void findWaitingTime(Process proc[], int n, int wt[] , int ct[]) 
// { 
// 	int rt[n]; 

// 	for (int i = 0; i < n; i++) 
// 		rt[i] = proc[i].bt; 

// 	int complete = 0, t = 0, minm = INT_MAX; 
// 	int shortest = 0, finish_time; 
// 	bool check = false; 

// 	while (complete != n) 
//     { 
// 		for (int j = 0; j < n; j++) 
//         { 
// 			if ((proc[j].art <= t) && (rt[j] < minm) && rt[j] > 0) 
//             { 
// 				minm = rt[j]; 
// 				shortest = j; 
// 				check = true; 
// 			} 
// 		} 

// 		if (check == false) 
//         { 
// 			t++; 
// 			continue; 
// 		} 

// 		rt[shortest]--; 
// 		minm = rt[shortest]; 
// 		if (minm == 0) 
//         {
// 			minm = INT_MAX; 
//         }

// 		if (rt[shortest] == 0) 
//         { 
// 			complete++; 
// 			check = false; 
// 			finish_time = t + 1; 
//             ct[shortest] = finish_time;
// 			wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].art; 

// 			if (wt[shortest] < 0) 
// 				wt[shortest] = 0; 
// 		} 
// 		t++; 
// 	} 
// } 

// void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) 
// { 
// 	for (int i = 0; i < n; i++) 
// 		tat[i] = proc[i].bt + wt[i]; 
// } 

// void findavgTime(Process proc[], int n) 
// { 
// 	int wt[n], tat[n], ct[n] , total_wt = 0, 
// 					total_tat = 0; 

// 	findWaitingTime(proc, n, wt , ct ); 
// 	findTurnAroundTime(proc, n, wt, tat); 

// 	cout << " P\t\t"
//         << "AT \t\t"
// 		<< "BT\t\t"
//         << "CT\t\t"
// 		<< "TAT\t\t" 
// 		<< "WT\t\t"
//         << "Rt\t\t\n";

// 	for (int i = 0; i < n; i++) { 
// 		total_wt = total_wt + wt[i]; 
// 		total_tat = total_tat + tat[i]; 
// 		cout << " " << proc[i].pid << "\t\t" 
//                     << proc[i].art << "\t\t"
// 			        << proc[i].bt << "\t\t" 
//                     << ct[i] << "\t\t"
//                     << tat[i] << ct[i]-proc[i].art<< "\t\t"
//                     << wt[i] <<  "\t\t"
//                     << endl;
// 	} 

// 	cout << "\nAverage waiting time = "
// 		<< (float)total_wt / (float)n; 
// 	cout << "\nAverage turn around time = "
// 		<< (float)total_tat / (float)n; 
// } 

// int main() 
// { 
// 	// Process proc[] = { { 1, 6, 2 }, { 2, 2, 5 }, 
// 					// { 3, 8, 1 }, { 4, 3, 0}, {5, 4, 4} }; 
// 	Process proc[] = { {1, 5, 0 }, {2, 3, 1}, {3, 4, 2 }, {4, 1, 4} };
// 	// Process proc[] = { {1, 7, 0 }, {2, 4, 1}, {3, 8, 2 } };
// 	// Process proc[] = { {1, 300, 0 }, {2, 125, 0}, {3, 400 ,  0} , { 4 , 150 , 0} , {5, 100 , 0} , {6 , 50 , 150} };
// 	int n = sizeof(proc) / sizeof(proc[0]); 

// 	findavgTime(proc, n); 
// 	return 0; 
// } 



#include <iostream>
#include <climits>
using namespace std;

struct Process {
	int AT, BT, ST[20], WT, FT, TAT, pos;
};

int quant;

int main() {
	int n, i, j;

	cout << "Enter the no. of processes: ";
	cin >> n;
	Process p[n];

	cout << "Enter the quantum: " << endl;
	cin >> quant;

	cout << "Enter the process numbers: " << endl;
	for (i = 0; i < n; i++)
		cin >> p[i].pos;

	cout << "Enter the Arrival time of processes: " << endl;
	for (i = 0; i < n; i++)
		cin >> p[i].AT;

	cout << "Enter the Burst time of processes: " << endl;
	for (i = 0; i < n; i++)
		cin >> p[i].BT;

	int c = n, s[n][20];
	float time = 0, mini = INT_MAX, b[n], a[n];

	int index = -1;
	for (i = 0; i < n; i++) {
		b[i] = p[i].BT;
		a[i] = p[i].AT;
		for (j = 0; j < 20; j++) {
			s[i][j] = -1;
		}
	}

	int tot_wt, tot_tat;
	tot_wt = 0;
	tot_tat = 0;
	bool flag = false;

	while (c != 0) {
		mini = INT_MAX;
		flag = false;

		for (i = 0; i < n; i++) {
			float p = time + 0.1;
			if (a[i] <= p && mini > a[i] && b[i] > 0) {
				index = i;
				mini = a[i];
				flag = true;
			}
		}

		if (!flag) {
			time++;
			continue;
		}

		j = 0;
		while (s[index][j] != -1) {
			j++;
		}

		if (s[index][j] == -1) {
			s[index][j] = time;
			p[index].ST[j] = time;
		}

		if (b[index] <= quant) {
			time += b[index];
			b[index] = 0;
		} else {
			time += quant;
			b[index] -= quant;
		}

		if (b[index] > 0) {
			a[index] = time + 0.1;
		}


		if (b[index] == 0) {
			c--;
			p[index].FT = time;
			p[index].WT = p[index].FT - p[index].AT - p[index].BT;
			tot_wt += p[index].WT;
			p[index].TAT = p[index].BT + p[index].WT;
			tot_tat += p[index].TAT;
		}
	} 

	// Printing output
	cout << "Process number ";
	cout << "Arrival time ";
	cout << "Burst time ";
	cout << "\tStart time";
	j = 0;
	while (j != 10) {
		j += 1;
		cout << " ";
	}
	cout << "\t\tFinal time";
	cout << "\tWait Time ";
	cout << "\tTurnAround Time" << endl;

	for (i = 0; i < n; i++) {
		cout << p[i].pos << "\t\t";
		cout << p[i].AT << "\t\t";
		cout << p[i].BT << "\t";
		j = 0;
		int v = 0;
		while (s[i][j] != -1) {
			cout << p[i].ST[j] << " ";
			j++;
			v += 3;
		}
		while (v != 40) {
			cout << " ";
			v += 1;
		}
		cout << p[i].FT << "\t\t";
		cout << p[i].WT << "\t\t";
		cout << p[i].TAT << endl;
	}

	double avg_wt, avg_tat;
	avg_wt = tot_wt / static_cast<double>(n);
	avg_tat = tot_tat / static_cast<double>(n);

	cout << "The average wait time is: " << avg_wt << endl;
	cout << "The average TurnAround time is: " << avg_tat << endl;

	return 0;
}

// #include<bits/stdc++.h>
// using namespace std;
    
    
// void priority()
//     {
//         int totalTime = 0;
//         int currentTime = 0;
//         int processCompleted = 0;
//         int priority[n];

//         cout << "Enter priorities : " << endl;
//         for (int i = 0; i < n; i++)
//         {
//             cin >> priority[i];
//         }

//         for (int i = 0; i < n - 1; i++)
//         {
//             for (int j = 0; j < n - i - 1; j++)
//             {
//                 if (priority[j] > priority[j + 1])
//                 {
//                     swap(priority[j], priority[j + 1]);
//                     swap(processes[j], processes[j + 1]);
//                 }
//             }
//         }

//         for (int i = 0; i < n; i++)
//         {
//             totalTime += processes[i].bt;
//         }

//         while (currentTime <= totalTime)
//         {
//             if (processCompleted < n)
//             {
//                 readyQueue.push_back(processes[processCompleted]);
//                 processCompleted++;
//             }

//             this->displayGantt(readyQueue, currentTime);

//             if (readyQueue.size() > 0)
//             {
//                 readyQueue[0].bt--;
//                 if (readyQueue[0].bt == 0)
//                 {
//                     for (int i = 0; i < n; i++)
//                     {
//                         if (readyQueue[0].id == processes[i].id)
//                         {
//                             processes[i].ct = currentTime + 1;
//                             processes[i].tat = (processes[i].ct - processes[i].at) > 0 ? processes[i].ct - processes[i].at : 0;
//                             processes[i].wt = (processes[i].tat - processes[i].bt) > 0 ? processes[i].tat - processes[i].bt : 0;
//                         }
//                     }
//                     readyQueue.erase(readyQueue.begin());
//                 }
//             }
//             currentTime++;
//         }

        
//     }


// int main()
// {
//      priority();
//     return 0;
// }
// #include<bits/stdc++.h>
// using namespace std;
    

// class Process
// {
// public:
//     int id;
//     int burst;
//     int arrival;
//     int priority;
// };
// void bubbleSort(vector<Process> &processes)
// {
//     int n = processes.size();
//     for (int i = 0; i < n - 1; i++)
//     {
//         for (int j = 0; j < n - i - 1; j++)
//         {
//             if (processes[j].arrival > processes[j + 1].arrival)
//             {
//                 Process temp = processes[j];
//                 processes[j] = processes[j + 1];
//                 processes[j + 1] = temp;
//             }
//         }
//     }
// }

// void display(vector<Process> &proc, int n, int wt[], int ct[], int tat[])
// {

//     cout.width(5);
//     cout << "ID";
//     cout.width(5);
//     cout << "AT";
//     cout.width(5);
//     cout << "BT";
//     cout.width(5);
//     cout << "CT";
//     cout.width(5);
//     cout << "TAT";
//     cout.width(5);
//     cout << "WT" << endl;

//     for (int i = 0; i < n; i++)
//     {
//         cout.width(5);
//         cout << proc[i].id;
//         cout.width(5);
//         cout << proc[i].arrival;
//         cout.width(5);
//         cout << proc[i].burst;
//         cout.width(5);
//         cout << ct[i];
//         cout.width(5);
//         cout << tat[i];
//         cout.width(5);
//         cout << wt[i] << endl;
//     }
// }

// void npPriority(vector<Process> processes, int n, int wt[], int ct[], int tat[])
// {
//     int remainingTime[n];

//     for (int i = 0; i < n; i++)
//         remainingTime[i] = processes[i].burst;

//     int currentTime = 0, completedTasks = 0, HPT = 0, maxPriority = INT_MIN;
//     bool taskActive = false;

//     while (completedTasks != n)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             if (processes[j].arrival <= currentTime && remainingTime[j] > 0 && processes[j].priority > maxPriority)
//             {
//                 HPT = j;
//                 maxPriority = processes[j].priority;
//                 taskActive = true;
//             }
//         }

//         if (!taskActive)
//         {
//             currentTime++;
//             continue;
//         }

//         currentTime += processes[HPT].burst;
//         remainingTime[HPT] = 0;
//         maxPriority = INT_MIN;
//         taskActive = false;
//         completedTasks++;
//         wt[HPT] = currentTime - processes[HPT].arrival - processes[HPT].burst;
//         ct[HPT] = currentTime;
//         tat[HPT] = ct[HPT] - processes[HPT].arrival;
//     }
// }

// int main()
// {
//     int n = 5;
//     // cin>>n;
//     vector<Process> proc = {{0 , 4, 0, 2}, {1 , 3, 1, 3}, {2 , 1, 2, 4}, {3 , 5, 3, 5}, { 4 ,2, 4, 5}};
//     // vector<Process> proc;
//     // for(int i=0;i<n;i++)
//     // {
//     //     Process temp;
//     //     cout<<"Process id ";
//     //     cin>>temp.id;
//     //     cout<<"Process burst time ";
//     //     cin>>temp.burst;
//     //     cout<<"Process arrival time ";
//     //     cin>>temp.arrival;
//     //     proc.push_back(temp);
//     // }
//      int wt[n], ct[n], tat[n];
//     bubbleSort(proc);
//     npPriority(proc, n, wt, ct, tat);
// display(proc, n, wt, ct, tat);
// }