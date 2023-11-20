// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <map>
// #include <algorithm>
// #include <sstream>
#include<bits/stdc++.h>

using namespace std;

map<string, string> OPTAB = {
    {"STOP", "(IS,00)"},
    {"ADD", "(IS,01)"},
    {"SUB", "(IS,02)"},
    {"MUL", "(IS,03)"},
    {"MOVER", "(IS,04)"},
    {"MOVEM", "(IS,05)"},
    {"COMP", "(IS,06)"},
    {"BC", "(IS,07)"},
    {"DIV", "(IS,08)"},
    {"READ", "(IS,09)"},
    {"PRINT", "(IS,10)"},
};

map<string, string> REG = {
    {"AREG", "(1)"},
    {"BREG", "(2)"},
    {"CREG", "(3)"},
    {"DREG", "(4)"},
};

map<string, string> CC = {
    {"LT", "(1)"},
    {"LE", "(2)"},
    {"EQ", "(3)"},
    {"GT", "(4)"},
    {"GE", "(5)"},
    {"ANY", "(6)"},
};

class AssemblerPass2
{
private:
    vector<string> icLines;
    map<int, string> symtab;
    map<int, string> littab;
    vector<int> pooltab;

    string generateMachineCode(const string &opcode, const vector<string> &operands)
    {
        string machineCode = opcode;
        for (const auto &operand : operands)
        {
            machineCode += " " + operand;
        }
        return machineCode;
    }

public:
    AssemblerPass2(const string &icFileName)
    {
        ifstream icFile(icFileName);
        if (!icFile.is_open())
        {
            cerr << "Error opening IC file." << endl;
            return;
        }

        string line;
        while (getline(icFile, line))
        {
            icLines.push_back(line);
        }
        icFile.close();

        ifstream symtabFile("Pass1_SYMTAB.txt");
        if (!symtabFile.is_open())
        {
            cerr << "Error opening SYMTAB file." << endl;
            return;
        }

        int index = 0;
        while (getline(symtabFile, line))
        {
            stringstream ss(line);
            string symbol, value;
            ss >> symbol >> value;
            symtab[index] = value;
            ++index;
        }
        symtabFile.close();

        ifstream littabFile("Pass1_LITTAB.txt");
        if (!littabFile.is_open())
        {
            cerr << "Error opening LITTAB file." << endl;
            return;
        }

        index = 0;
        while (getline(littabFile, line))
        {
            stringstream ss(line);
            string literal , value ;
            ss >> literal >> value;
            littab[index] = value;
            ++index;
        }
        littabFile.close();

        ifstream pooltabFile("Pass1_POOLTAB.txt");
        if (!pooltabFile.is_open())
        {
            cerr << "Error opening POOLTAB file." << endl;
            return;
        }

        while (getline(pooltabFile, line))
        {
            pooltab.push_back(stoi(line));
        }
        pooltabFile.close();
    }

    void process()
    {
        ofstream outputFile("Pass2_MachineCode.txt");
        if (!outputFile.is_open())
        {
            cerr << "Error opening output file." << endl;
            return;
        }

        int poolIndex = 0;
        for (const auto &icLine : icLines)
        {
            stringstream ss(icLine);
            string token, opcode;
            ss >> token; // First token

            
            // cout << token << " " ;

            if (token == "(AD,01)")
            {
                // outputFile << "*\t(AD,01)" << endl;
                outputFile << endl;

                continue;
            }
            else if (token == "(AD,02)")
            {
                // outputFile << "*\t(AD,02)" << endl;
                outputFile << endl;
                ++poolIndex;
                continue;
            }

            opcode = token[4]; 
            opcode +=  token[5]; // OPCODE

            vector<string> operands;
            while (ss >> token)
            {
                // cout << token << endl;
                if (token[1] == 'C')
                {
                    operands.push_back(token.substr(3, token.length() - 4) );
                    // cout << "token " << token.substr(3, token.length() - 4) << endl;
                }
                else if (token[1] == 'S' || token[1] == 'L')
                {
                    int index = stoi(token.substr(3, token.length() - 3));
                    // cout << "index" << index << endl;
                    if (token[1] == 'S')
                    {
                        operands.push_back(symtab[index]);
                    }
                    else
                    {
                        operands.push_back(littab[index]);
                    }
                }
                else
                {
                    string temp = "";
                    temp += token[1];
                    operands.push_back(temp);
                }
            }

            for(auto it : operands)
            {
                cout << it << " " ;
            }
            cout << endl; 
            outputFile << generateMachineCode(opcode, operands) << endl;
        }

        outputFile.close();
    }
};

int main()
{
    AssemblerPass2 pass2("Pass1_IC.txt");
    pass2.process();
    return 0;
}
