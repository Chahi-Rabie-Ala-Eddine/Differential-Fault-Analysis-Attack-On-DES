#ifndef ATTACK_H
#define ATTACK_H

#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

#include "des.h"

using namespace std;

class attack
{
    private:
    des* d;
   
    public:
    attack();
    string attack48(string correct, string incorrect[32]);
    string attack56(string k48, string plaintext, string ciphertext);
    string attack64(string k64);
    string FaultAnalysisAttack(string plaintext, string correct, string incorrect[32]);
};

#endif // DES_H 
