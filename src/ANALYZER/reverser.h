#ifndef REVERSER_H
#define REVERSER_H

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

string UndoFFunctionPermutation(string ciphertext);
void StoreBinary(int binary[], int length);
void GenerateAllBinaries(int binary[], int length, int temp);
void GenerateAttackKeys(int length);
string GetSbox(string str, int val);
string findCommonSolution(vector<vector<string>> keys);
string findKey(vector<vector<vector<string>>> solutions);
string GetCandidate(int i, vector<string> binaries, string k64);
string UndoPc2(string k48);
string UndoPc1(string k56);
int countSetBits(int n);

#endif // REVERSER_H 

