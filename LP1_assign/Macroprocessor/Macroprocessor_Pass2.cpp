#include <bits/stdc++.h>
using namespace std;

vector<string> getWords(string line)
{
    istringstream iss(line);
    vector<string> allWords;
    string word;
    while (iss >> word)
    {
        allWords.push_back(word);
    }
    return allWords;
}

// void nestedCall(string line, string macroName, map<int, pair<string, string>> kpTabMap, map<string, bool> macroNameMap,fstream& mac)
// {
//     vector<string> allWords = getWords(line);
    
//     fstream mnt("mnt.txt");
//     fstream mdt("mdt.txt");
    
//     string buffer;
//     while (getline(mnt, buffer))
//     {
//         vector<string> mntLine = getWords(line);

//         if (mntLine[0] == macroName)
//         {
//             vector<string> aptab;
//             int tot_pp = stoi(mntLine[1]);
//             int tot_kp = stoi(mntLine[2]);
//             int mdtPtr = stoi(mntLine[3]);
//             int kpdPtr = stoi(mntLine[4]);
//             for (int i = 1; i < allWords.size(); i++)
//             {
//                 pair<string, string> p;
//                 bool isKeywordPara = false;
//                 int j;
//                 string para = "";
//                 for (j = 0; j < allWords[i].size(); j++)
//                 {
//                     if (allWords[i][j] == ',')
//                     {
//                         aptab.push_back(para);
//                         break;
//                     }
//                     if (allWords[i][j] == '=')
//                     {
//                         reverse(para.begin(), para.end());
//                         para.pop_back();
//                         reverse(para.begin(), para.end());
//                         p.first = para;
//                         para.clear();
//                         isKeywordPara = true;
//                         break;
//                     }
//                     para += allWords[i][j];
//                 }
//                 if (isKeywordPara)
//                 {
//                     j++;
//                     for (; j < allWords[i].size(); j++)
//                     {
//                         para += allWords[i][j];
//                     }
//                     p.second = para;
//                     aptab.push_back(para);
//                 }
//             }

//             for (int i = kpdPtr; i < kpdPtr + tot_kp; i++)
//             {
//                 if (aptab.size() != tot_kp + tot_pp)
//                 {
//                     aptab.push_back(kpTabMap[i].second);
//                 }
//             }

//             mdt.seekg(0, ios::beg);

//             for (int i = 0; i < mdtPtr - 1; ++i)
//             {
//                 if (!getline(mdt, buffer))
//                 {
//                     cerr << "Error: mdtPtr exceeds the number of lines in the file." << endl;
//                     return;
//                 }
//             }

//             while (getline(mdt, buffer))
//             {
//                 istringstream bufStream(buffer);
//                 string bufWord;
//                 if (bufStream >> bufWord)
//                 {
//                     if (bufWord != "MEND")
//                         mac << bufWord << "\t";
//                     if (bufWord == "MEND") break;
//                 }
//                 for (int i = 0; i < buffer.length(); i++)
//                 {
//                     if (buffer[i] >= '0' and buffer[i] <= '9')
//                     {
//                         mac << aptab[(buffer[i] - '0') - 1] << "\t";
//                     }
//                 }
//                 mac << endl;
//             }
//             cout << endl;
//         }
//     }
// }

void processMacroPass2(const string &inputFile)
{
    ifstream infile(inputFile);
    ifstream mnt("mnt.txt");
    ifstream mdtf("mdt.txt");
    ifstream kpdt("kpdt.txt");
    ifstream pntf("pntab.txt");
    ofstream aptf("apt.txt");
    ofstream outputf("output.txt");



    string line;
    map<string, string> kpTab;
    set<string > macroname;
    vector<string> mdt;
    while(getline(mdtf , line))
    {
        mdt.push_back(line);
    }

    vector<map<string ,int>> pnt;
    map<string , int> mp;
    while(getline(pntf , line))
    {
        vector<string> temp = getWords(line);
        if(temp[0] == "-1")
        {
            pnt.push_back(mp);
            mp.clear();
            continue;
        }
        mp[temp[0]] = stoi(temp[1]);
    }

    
    while(getline(mnt , line))
    {
        istringstream ss(line);
        string first ; ss >> first;
        ss >> first;
        macroname.insert(first);
    }

    while (getline(kpdt, line))
    {
        vector<string> allWords = getWords(line);
        if (allWords.size() == 2)
            kpTab[allWords[0]] =  allWords[1];
        else if (allWords.size() == 1)
            kpTab[allWords[0]]  = "";
    }

    cout << "Sucessfully created data structure " << endl;
    bool isMacro = false;
    while (getline(infile, line))
    {
        vector<string> allWords = getWords(line);
        if (allWords[0] == "MACRO")
        {
            isMacro = true;
            continue;
        }

        if (allWords[0] == "MEND")
        {
            isMacro = false;
            continue;
        }

        if (isMacro)
            continue;


        mnt.clear(); 
        mnt.seekg(0, ios::beg);


        if (macroname.find(allWords[0]) != macroname.end())
        {
            string buffer ;
            vector<string> mntLine;
            while (getline(mnt, buffer))
            {
                mntLine = getWords(buffer);
                if(mntLine[1] == allWords[0])
                    break;
            }
            int noofmacro = stoi(mntLine[0]);
            int tot_pp = stoi(mntLine[2]);
            int tot_kp = stoi(mntLine[3]);
            int mdtPtr = stoi(mntLine[4]);
            int kpdPtr = stoi(mntLine[5]);

            vector<string> aptab(tot_pp + tot_kp , "NULL");
            int counter = 0;
            for (int i = 1; i < allWords.size(); i++)
            {
                    if (allWords[i].find('=') != string::npos)
                    {
                        string w = allWords[i].substr(0 , allWords[i].find('='));
                        w.erase(remove(w.begin(), w.end(), '&'), w.end());
                        allWords[i].erase(remove(allWords[i].begin(), allWords[i].end(), ','), allWords[i].end());
                        string para = allWords[i].substr(allWords[i].find('=') + 1 );
                        
                        aptab[pnt[noofmacro-1][w]-1] = para;
                    }
                    else 
                    {
                        allWords[i].erase(remove(allWords[i].begin(), allWords[i].end(), ','), allWords[i].end());
                        aptab[counter++] = allWords[i];
                    }
            }

           
            aptf.flush();
            for(int i = 0 ; i < aptab.size() ; i++)
            {
                if(aptab[i] == "NULL")
                {
                    for(auto it : pnt[noofmacro-1])
                    {
                        if(it.second == i + 1)
                        {
                            aptab[i] = kpTab[it.first];
                        }
                    }
                }
                aptf << aptab[i] << "\n";
                aptf.flush();
            }   
            aptf << "\n";

            mdtf.seekg(0, ios::beg);

            int i = mdtPtr;
            bool flag = 0;
            while (true)
            {
                string mdtline = mdt[i++]; 
                istringstream ss(mdtline);
                string word ;

                while(ss >> word)
                {
                    if (word == "MEND")
                    {
                        flag = 1;
                        break;
                    }
                    if(word.find("P") != string::npos)
                    {
                        word = word.substr(word.find(",") + 1);
                        word.erase(remove(word.begin(), word.end(), ')'), word.end());
                        outputf << aptab[stoi(word)-1] << " ";
                        outputf.flush();
                    }
                    else
                    {
                        outputf << word << " ";
                        outputf.flush();
                    }
                }
                outputf << "\n";
                if(flag)
                    break;
            }
        }
    }
    kpdt.close();
    mdtf.close();
    mnt.close();
    infile.close();
    aptf.close();
    outputf.close();
    pntf.close();
    cout << "M2 done check files "<<endl;
}

int main()
{
    processMacroPass2("Input.asm");
    return 0;
}