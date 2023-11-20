#include <bits/stdc++.h>
using namespace std;

// **************print frame ************
void printFrame(int pageFrame[] , int Framesize )
{
    cout <<"Frame --->  ";
    for(int i = 0 ; i < Framesize ; i++) 
        cout << pageFrame[i] <<" ";
    cout<< endl;
}

// **************FIFO Page replacement************
bool isPresent(int pageFrame[] , int page , int Framesize )
{
    for(int i = 0 ; i < Framesize ; i++)
    {
        if(pageFrame[i] == page)
            return 1;
        if(pageFrame[i] == -1)
            break;
    }
    return 0;
}

void FIFO(int pages[] , int pageFrame[] , int no_pages , int Framesize)
{
    int pageFault = 0;
    int end = 0;
    for(int i = 0 ; i < no_pages ; i++)
    {
        cout << "for Page " << pages[i] <<"----> ";

        if(isPresent(pageFrame ,  pages[i] , Framesize))
        {
            printFrame(pageFrame , Framesize) ;
        }
        else
        {
            pageFrame[end] = pages[i];
            pageFault++;
            end++;
            end = end%Framesize;
            printFrame(pageFrame , Framesize);
        }
    }
    cout <<"Page Faults :-- > " << pageFault << endl;
}

// ************Optimal Page replacement**************
int getindex(int pages[] , int pageFrame[] , int no_pages , int Framesize , int insertpage , int sindex)
{
    int mostrecent[Framesize];

    for(int i = 0 ; i < Framesize ; i++)
        mostrecent[i] = -1;
        
    for(int i = 0 ; i < Framesize ; i++)
    {
        for(int j = sindex ; j < no_pages ; j++)
        {
            if(pageFrame[i] == pages[j])
            {
                mostrecent[i] =  j;
                break;
            }
        }
    }

    if(insertpage == 3)
    {
        cout << endl;
        for(int i = 0 ; i < Framesize ; i++)
            cout << mostrecent[i] << " ";
        cout << endl;
    }
    int index = -1;
    for(int i = 0 ; i < Framesize ; i++)
    {
        if(mostrecent[i] == -1)
            return pageFrame[i];
        if(mostrecent[i] != -1)
        {
            index = max(index , mostrecent[i]);
        }
    }

    return pages[index];
}
void optimalpr(int pages[] , int pageFrame[] , int no_pages , int Framesize)
{
    int pageFault = 0;
    int end = 0;
    bool flag = 0;
    for(int i = 0 ; i < no_pages ; i++)
    {
        cout << "for Page " << pages[i] <<"----> ";

        if(isPresent(pageFrame , pages[i] , Framesize ))
        {
            printFrame(pageFrame , Framesize) ;
        }
        else 
        {
            if(flag)
            {
                int index_inpage = getindex(pages , pageFrame, no_pages ,Framesize , pages[i] ,i + 1);
                int index_inframe = -1;
                
                for(int i = 0 ; i < Framesize ; i++)
                    if(pageFrame[i] == index_inpage)
                        index_inframe = i;

                pageFault++;
                pageFrame[index_inframe] = pages[i];
            }
            else
            {
                pageFrame[end] = pages[i];
                pageFault++;
                end++;
                if(end == Framesize)
                    flag = 1;
            }
            
            printFrame(pageFrame , Framesize);
        }
    }
    cout <<"Page Faults :-- > " << pageFault << endl;
}


// **************least recent *************


void LRU(int pages[], int no_pages, int Framesize)
{
	set<int> st;
	map<int, int> indexes;

	int pageFault = 0;
	for (int i=0; i < no_pages; i++)
	{
        cout << "for Page " << pages[i] <<"----> ";
		if (st.size() < Framesize)
		{
			if (st.find(pages[i])==st.end())
			{
				st.insert(pages[i]);
				pageFault++;
			}
			indexes[pages[i]] = i;
		}
		else
		{
			if (st.find(pages[i]) == st.end())
			{
				int least_recent = INT_MAX, val;
				for (auto it : st)
				{
					if (indexes[it] < least_recent)
					{
						least_recent = indexes[it];
						val = it;
					}
				}
				st.erase(val);
				st.insert(pages[i]);
				pageFault++;
			}
			indexes[pages[i]] = i;
		}

        cout << "Frame --->";
        for(auto it : st)
            cout << it <<" ";
        cout << endl;
	}

	cout <<"Page Faults :-- > " << pageFault << endl;
}



// **************most recent *************


void MRU(int pages[], int no_pages, int Framesize)
{
	set<int> st;
	map<int, int> indexes;

	int pageFault = 0;
	for (int i=0; i < no_pages; i++)
	{
        cout << "for Page " << pages[i] <<"----> ";
		if (st.size() < Framesize)
		{
			if (st.find(pages[i])==st.end())
			{
				st.insert(pages[i]);
				pageFault++;
			}
			indexes[pages[i]] = i;
		}
		else
		{
			if (st.find(pages[i]) == st.end())
			{
				int least_recent = INT_MIN, val;
				for (auto it : st)
				{
					if (indexes[it] > least_recent)
					{
						least_recent = indexes[it];
						val = it;
					}
				}
				st.erase(val);
				st.insert(pages[i]);
				pageFault++;
			}
			indexes[pages[i]] = i;
		}

        cout << "Frame --->";
        for(auto it : st)
            cout << it <<" ";
        cout << endl;
	}

	cout <<"Page Faults :-- > " << pageFault << endl;
}



int main()
{
    // int pages[8] = {3, 1, 2, 1, 6, 5, 1, 3};
	// int pages[15] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3,1 ,  2 , 0};
	// int pages[12] = {1,2,3,4,1,2,5,1,2,3,4,5};
    // int pages[7] = {1, 3, 0, 3, 5, 6, 3};
    // int no_pages = 15;
    // int pageFrame[3];
    // int Framsize = 3;
    // for(int i = 0;i < Framsize ; i++)
        // pageFrame[i] = -1;


    // cout <<"FIFO"<< endl;
    // FIFO(pages , pageFrame , no_pages , Framsize );
    // for(int i = 0;i < Framsize ; i++)
    //     pageFrame[i] = -1;

    // cout << endl;
    //  int pages[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    // int no_pages = 20;
    // int pageFrame[4];
    // int Framsize = 4;
    // for(int i = 0;i < Framsize ; i++)
    //     pageFrame[i] = -1;
    // cout <<"Optimal"<< endl;
    // optimalpr(pages , pageFrame , no_pages , Framsize );

    cout << endl;
    int pages[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int no_pages = 20;
    int pageFrame[4];
    int Framsize = 4;
    for(int i = 0;i < Framsize ; i++)
    pageFrame[i] = -1;
    cout <<"LRU"<< endl;
    LRU(pages, no_pages, Framsize);

    cout << endl;
    // int pages[20] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    // int no_pages = 20;
    // int pageFrame[4];
    // int Framsize = 4;
    for(int i = 0;i < Framsize ; i++)
    pageFrame[i] = -1;
    cout <<"MRU"<< endl;
    MRU(pages, no_pages, Framsize);
}