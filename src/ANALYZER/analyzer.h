#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

string* XorCorrectAndIncorrectR16(string correct, string incorrect);
int CountDifferences(string correctCiphertext, string incorrectCiphertext);
string IsDfaBitOrByteSpread(string correctCiphertext, string incorrectCiphertexts[32]);
string* GetCorruptedBits(string ciphers[32]);
array<array<int, 6>, 8> GetConsideredSbox();

#endif // #define ANALYZER_H
 
