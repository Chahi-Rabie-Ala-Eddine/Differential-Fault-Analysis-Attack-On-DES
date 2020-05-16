#include "analyzer.h"
#include "../UTILS/converter.h"
#include "../UTILS/utils.h"
#include "../UTILS/constants.h"
#include "../UTILS/colors.h"

#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

using namespace std;

vector<vector<int>> undo =
                            {
                                {
                                    8,16,24,56,52,44,
                                    36,0,7,15,23,55,
                                    51,43,35,0,6,14,
                                    22,54,50,42,34,0,
                                    5,13,21,53,49,41,
                                    33,0,4,12,20,28,
                                    48,40,32,0,3,11,
                                    19,27,47,39,31,0,
                                    2,10,18,26,46,38,
                                    30,0,1,9,17,25,
                                    45,37,29,0
                                },
                                {
                                    5,24,7,16,6,10,
                                    20,18,0,12,3,15,
                                    23,1,9,19,2,0,
                                    14,22,11,0,13,4,
                                    0,17,21,8,47,31,
                                    27,48,35,41,0,46,
                                    28,0,39,32,25,44,
                                    0,37,34,43,29,36,
                                    38,45,33,26,42,0,
                                    30,40
                                },
                                {
                                    9, 18, 22, 25, 
                                    35, 38, 43, 54
                                },
                                {
                                    7, 15, 23, 31, 
                                    39, 47, 55, 63
                                },
                                {
                                    13, 14, 18, 19,
                                    50, 53, 57, 59
                                }

                            };


string* XorCorrectAndIncorrectR16(string correct, string incorrect)
{
    string xorResult = XorStrings(correct,incorrect);

    string* parts = new string[8]{
                                    xorResult.substr(0,4),
                                    xorResult.substr(4,4),
                                    xorResult.substr(8,4),
                                    xorResult.substr(12,4),
                                    xorResult.substr(16,4),
                                    xorResult.substr(20,4),
                                    xorResult.substr(24,4),
                                    xorResult.substr(28,4),
                                  };
    return parts;
}

int CountDifferences(string correctCiphertext, string incorrectCiphertext)
{
    string xored = XorStrings(FromHexadecimalToBinary(correctCiphertext),FromHexadecimalToBinary(incorrectCiphertext));
    cout << xored << endl;
    cout << "Number of bit 1 = [" << count(xored.begin(), xored.end(), '1') << "]" << endl << endl;

    return count(xored.begin(), xored.end(), '1');
}

string IsDfaBitOrByteSpread(string correctCiphertext, string incorrectCiphertexts[32])
{
    int max = 0, min = CountDifferences(incorrectCiphertexts[0],correctCiphertext);
    for(int i = 0; i < 32; i++)
    {
        if(CountDifferences(incorrectCiphertexts[i],correctCiphertext) > max)
            max = CountDifferences(incorrectCiphertexts[i],correctCiphertext);

        if(min > CountDifferences(incorrectCiphertexts[i],correctCiphertext))
            min = CountDifferences(incorrectCiphertexts[i],correctCiphertext);
    }

    if(max == 13)
        return "BYTE-DFA";

    else if(max == 9)
        return "BIT-DFA";

    /*cout << "max = " << max << endl;
    cout << "min = " << min << endl;*/

    return "ERROR";
}

string* GetCorruptedBits(string ciphers[32])
{
    string* xoredCorrectRightAndIncorrectRight = new string[32];
    for(int i = 0; i < 32; i++)
        xoredCorrectRightAndIncorrectRight[i] = XorStrings(SplitTwoParts(Permutation(FromHexadecimalToBinary("CE3B17D676D5F63B"), sixtyFourBits, initialPermutation))[1], SplitTwoParts(Permutation(FromHexadecimalToBinary(ciphers[i]), sixtyFourBits, initialPermutation))[1]);

    return (string*) xoredCorrectRightAndIncorrectRight;

}

array<array<int, 6>, 8> GetConsideredSbox()
{
    array<array<int, 6>, 8> infected;
    int val = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            infected[i][j] = expansionIndex[val];
            ++val;
        }
    }

    reverse(infected.begin(),infected.end());
    
    cout << endl;

    return infected;
}
