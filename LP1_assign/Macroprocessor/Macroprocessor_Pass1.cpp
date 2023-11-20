#include <bits/stdc++.h>
using namespace std;

void processMacroPass1(const string &inputFile)
{
    ifstream file(inputFile);
    if (!file)
    {
        cerr << "Failed to open input file: " << inputFile << endl;
        return;
    }

    ofstream mnt("mnt.txt");
    ofstream mdt("mdt.txt");
    ofstream kpdt("kpdt.txt");
    ofstream pnt("pntab.txt");

    map<string, int> pntab;

    string line;
    string macroName = "";
    int noofmacro = 0 , mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(file, line))
    {
        istringstream iss(line);
        string word;

        while (iss >> word)
        {
            if (word == "MACRO")
            {
                getline(file, line);
                istringstream iss(line);

                pp = kp = 0;flag = 1;paramNo = 1;
                pntab.clear();

                while (iss >> word)
                {
                    if (word.find('=') != string::npos)
                    {
                        kp++;
                        word.erase(remove(word.begin(), word.end(), '&'), word.end());
                        word.erase(remove(word.begin(), word.end(), ','), word.end());

                        istringstream keywordParam(word);
                        string key, value;
                        getline(keywordParam, key, '=');
                        getline(keywordParam, value);

                        pntab[key] = paramNo++;
                        kpdt << key << "\t" << value << "\n";
                    }
                    else if(word.find('&') != string::npos)
                    {
                        word.erase(remove(word.begin(), word.end(), '&'), word.end());
                        word.erase(remove(word.begin(), word.end(), ','), word.end());

                        pntab[word] = paramNo++;
                        pp++;
                    }
                    else
                        macroName = word;
                }
                mnt << ++noofmacro << "\t"<< macroName << "\t" << pp << "\t" << kp << "\t" << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << endl;
                kpdtp += kp;
            }
            else if (word == "MEND")
            {
                mdt << "MEND";
                flag = kp = pp = 0;
                paramNo = 1;

                // pnt << macroName << ":\n";
                map<int, string> mp;


                for (const auto &entry : pntab)
                {
                    mp[entry.second] = entry.first;
                    // pnt << entry.first << "\n";
                }
                for (const auto &entry : mp)
                {
                    // mp[entry.second] = entry.first;
                    pnt << entry.second << " " <<entry.first << "\n";
                }
                pnt << -1 << "\n";
                pntab.clear();
            }
            else if (flag == 1)
            {
                if (word.find('&') != string::npos)
                {
                    word.erase(remove(word.begin(), word.end(), '&'), word.end());
                    word.erase(remove(word.begin(), word.end(), ','), word.end());
                    mdt << "(P," << to_string(pntab[word]) << ")\t";
                }
                else
                    mdt << word << "\t";
            }
        }
        if(flag)
        {
            mdtp++;
            mdt << "\n";
        }
    }

    file.close();
    mdt.close();
    mnt.close();
    pnt.close();
    kpdt.close();
    cout << "Macro Pass 1 processing done. :)\n";
}

int main()
{
    processMacroPass1("Input.asm");
    return 0;
}