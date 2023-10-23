#include <bits/stdc++.h>
using namespace std;


void print(int blockSize[], int s)
{
    for (int i = 0; i < s; i++)
        cout << blockSize[i] << " ";
    cout << endl << endl;
}
//  First - Fit algorithm
void firstFit(int blockSize[], int m, int processSize[], int n)
{
    cout << endl << "First fit " << endl;
    int allocation[n];
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t"
             << processSize[i] << "\t\t";
        if (allocation[i] != -1)
        {
            cout << allocation[i] + 1;
        }
        else
            cout << "Not Allocated";

        cout << endl;
    }
    print(blockSize, m);
}

void NextFit(int blockSize[], int m, int processSize[], int n)
{
    cout << "Nestfit " << endl;
    int allocation[n], j = 0, lastend = m - 1;
    memset(allocation, -1, sizeof(allocation));

    for (int i = 0; i < n; i++)
    {
        while (j < m)
        {
            if (blockSize[j] >= processSize[i])
            {

                allocation[i] = j;
                blockSize[j] -= processSize[i];

                lastend = (j - 1) % m;
                break;
            }
            if (lastend == j)
            {
                lastend = (j - 1) % m;
                break;
            }

            j = (j + 1) % m;
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << " " << i + 1 << "\t\t" << processSize[i]
             << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
    print(blockSize, m);
}

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    cout << "best fit " << endl;
	int allocation[n];
    memset(allocation, -1, sizeof(allocation));

	for (int i = 0; i < n; i++)
	{
		int bestIdx = -1;
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (bestIdx == -1)
					bestIdx = j;
				else if (blockSize[bestIdx] > blockSize[j])
					bestIdx = j;
			}
		}

		if (bestIdx != -1)
		{
			allocation[i] = bestIdx;
			blockSize[bestIdx] -= processSize[i];
		}
	}

	cout << "\nProcess No.\tProcess Size\tBlock no.\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
		if (allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << endl;
	}
    print(blockSize, m);
}
void worstFit(int blockSize[], int m, int processSize[],int n)
{
    cout << "worst fit " << endl;
	int allocation[n];
	memset(allocation, -1, sizeof(allocation));

	for (int i=0; i<n; i++)
	{
		int wstIdx = -1;
		for (int j=0; j<m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (wstIdx == -1)
					wstIdx = j;
				else if (blockSize[wstIdx] < blockSize[j])
					wstIdx = j;
			}
		}

		if (wstIdx != -1)
		{
			allocation[i] = wstIdx;
			blockSize[wstIdx] -= processSize[i];
		}
	}

	cout << "\nProcess No.\tProcess Size\tBlock no.\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
		if (allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << endl;
	}
    print(blockSize, m);
}

int main()
{
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};

    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    firstFit(blockSize, m, processSize, n);

    int blockSize1[] = {5, 10, 20};
    int processSize1[] = {10, 20, 5};

    NextFit(blockSize1, m, processSize1, n);

	int blockSize2[] = {100, 500, 200, 300, 600};
	int processSize2[] = {212, 417, 112, 426};

	bestFit(blockSize2, m, processSize2, n);

    int blockSize3[] = {100, 500, 200, 300, 600};
    int processSize3[] = {212, 417, 112, 426};
 
    worstFit(blockSize3, m, processSize3, n);
 
    return 0;
}

