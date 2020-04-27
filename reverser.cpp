#include "converter.h"
#include "utils.h"
#include "constants.h"
#include "colors.h"
#include "reverser.h"

#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

string UndoFFunctionPermutation(string ciphertext)
{
    string unpermuted = ciphertext;

    for(int i = 0; i < 32; i++)
        unpermuted[fFunctionPermutation[i]-1]= ciphertext[i];

    return unpermuted;
}

void StoreBinary(int binary[], int length)
{
    string str = "";

    for (int i = 0; i < length; i++)
        str+= to_string(binary[i]);

    binaries.push_back(str);
}

void GenerateAllBinaries(int binary[], int length, int temp)
{
    if (temp == length)
    {
        StoreBinary(binary, length);
        return;
    }

    binary[temp] = 0;
    GenerateAllBinaries(binary, length, (temp + 1));

    binary[temp] = 1;
    GenerateAllBinaries(binary, length, (temp + 1));
}

void GenerateAttackKeys(int length)
{
    int bins[length];
    GenerateAllBinaries(bins, length, 0);
}

string GetSbox(string str, int val)
{
    return bitset<4>(sbox[val][FrombinaryToDecimal(string() + str.substr(0,1) + str.substr(5,1))][FrombinaryToDecimal(str.substr(1,4))]).to_string();
}

string findCommonSolution(vector<vector<string>> keys)
{
    vector<string> list(keys[0].size() + keys[1].size());
    vector<string> commons;
    vector<string>::iterator iterator, st;
    iterator = set_intersection(keys[0].begin(),keys[0].end(),keys[1].begin(),keys[1].end(),list.begin());

    for (st = list.begin(); st != iterator; ++st)
        commons.push_back(*st);

    string solution = "";

    for(int i = 0; i < (int)commons.size(); i++)
    {
        int temp = 0;

        for(int j = 0; j < 4; j++)
            if (find(keys[j].begin(), keys[j].end(), commons[i]) != keys[j].end())
                temp++;

        if(temp == 4)
        {
            solution = commons[i];
            break;
        }

    }

    return solution;
}

string findKey(vector<vector<vector<string>>> solutions)
{
    string key = "";

    for(int i = 0; i < (int)solutions.size(); i++)
        key+= findCommonSolution(solutions[i]);

    return key;
}

string GetCandidate(int i, vector<string> binaries, string k64)
{
    string temp = "";
    int incrementer = 0;

    for(int j = 0; j < 64; j++)
        {
            if(find(begin(undo[4]), end(undo[4]), j) != end(undo[4]))
            {
                temp+= binaries[i][incrementer];
                ++incrementer;
            }

            else
                temp+= k64[j];
        }
    
    return temp;
}

string UndoPc2(string k48)
{
    string k56 = "";

    for(int i = 0; i < 56; i++)
    {
        if(find(begin(undo[2]), end(undo[2]), i+1) != end(undo[2]))
            k56+= "0";

        else
            k56+= k48[undo[1][i]-1];
    }

    return k56;
}

string UndoPc1(string k56)
{
    string k64 = "";

    for(int i = 0; i < 64; i++)
    {
        if(find(begin(undo[3]), end(undo[3]), i) != end(undo[3]))
            k64+= "0";

        else
            k64+= k56[undo[0][i]-1];
    }

    return k64;
}

int countSetBits(int n)
{
    if (n == 0)
        return 0;

    else
        return (n & 1) + countSetBits(n >> 1);
}

