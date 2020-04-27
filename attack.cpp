#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>

#include "attack.h"
#include "converter.h"
#include "utils.h"
#include "constants.h"
#include "colors.h"
#include "analyzer.h"
#include "reverser.h"
#include "printer.h"

using namespace std;

// All binaries
vector<string> binaries;

vector<vector<vector<string>>> solutions;

array<array<int, 6>, 8> consideredSbox;

string incorrectCiphers[32] = {
                                    "CC3E179276D4F62F",
                                    "CE29179676D5F63B",
                                    "CE2B159276D4F63B",
                                    "CF6B179076D5F63B",
                                    "CF7B179264D5F63B",
                                    "CE7B13D676D7F63B",
                                    "CF7B17D676D5F43B",
                                    "CE3B13D726C5F639",
                                    "C77B17D626C1F63B",
                                    "CE3317D736C1F63B",
                                    "CE3B1FD776D1F63B",
                                    "8E3B07DF7681F63B",
                                    "CE3B17D63E81F63A",
                                    "CE3B07D676DDF63A",
                                    "8E3B07D676D5FE3B",
                                    "8E3B07D676D5E732",
                                    "AE3B17D67695E73B",
                                    "CE1B17D676D5E77B",
                                    "CE3B37D672D5E73B",
                                    "DA3B56F672D5E77B",
                                    "DA3B56D652D5E73B",
                                    "DA3B57D676F5F63B",
                                    "CA3B56D676D5D63B",
                                    "DE3B57C676D5F21B",
                                    "5A3B16C677D5F23B",
                                    "CEBB17C677D5F63B",
                                    "CE3B97C677D5B23B",
                                    "CE3A174676D5B22B",
                                    "CE3B17C6F7D5F22F",
                                    "CE3F17D67655F63F",
                                    "CE3E17D676D5763B",
                                    "CE2F17D276D5F6AB"
                                };
                                
string correctCipher = "CE3B17D676D5F63B";

attack::attack()
{
    key k;
    k.SetContent(FromHexadecimalToBinary("0000000000000000"));
    this->d = new des("0000000000000000",k.GetContent());
}

string attack::attack48(string correct, string incorrect[32])
{
    
    /*
     * MANIPULATION DU CHIFFRÉ JUSTE :
    */

    //permutation IP sur le chiffré juste
    string correctPermuted = Permutation(FromHexadecimalToBinary(correct),64,initialPermutation);

    //découpage du message obtenu en 2 parties L16 et R16
    string L16 = SplitTwoParts(correctPermuted)[0];
    string R16 = SplitTwoParts(correctPermuted)[1];

    swap(L16,R16);
    
    //stocker L16 dans R15
    string R15 = L16;

    //calculer l'expansion de R15
    string exansedR15 = Permutation(R15,48,expansionIndex);

    consideredSbox = GetConsideredSbox();

    /*
     * ATTAQUE PAR FORCE BRUT :
    */

    //générer les 64 clés possibles ( 6 bits de clé donc 2⁶ = 64 clés possibles)
    GenerateAttackKeys(6);

    int step = 0, step2 = 0;

    string possibleKeys[8][6][64];

    int val = 0;

    for(int i = 0; i < 8; i++)
    {
        vector<vector<string>> sub_solutions;

        for(int j = 0; j < 6; j++)
        {

            vector<string> keys;

            //permutation IP sur le chiffré faux
            string incorrectPermuted = Permutation((string)FromHexadecimalToBinary(incorrect[consideredSbox[i][j]-1]),64,initialPermutation);

            //découpage du message obtenu en 2 parties L16* et R16*
            string L16F = SplitTwoParts(incorrectPermuted)[0];
            string R16F = SplitTwoParts(incorrectPermuted)[1];

            swap(L16F,R16F);

            //stocker R16* dans R15*
            string R15F = L16F;

            //calculer R16 ⊕ R16*
            string R16xorR16F = XorStrings(R16,R16F);

            //calculer la valeur attendue des 4bits à chaque sortie d’une SBOX avec la permutation [P−1(R16 ⊕ R16*)]
            string unpermuted = UndoFFunctionPermutation(R16xorR16F);

            //calcul de l’expansion de R15*
            string exansedR15F = Permutation(R15F,48,expansionIndex);

            //appliquer un XOR entre l’expansion et les 64 possibilités de clé K16 pour l’entrée des 8 SBOX avec E(R15*) et E(R15*).
            for(int k = 0; k < 64; k++)
            {
                val++;
                //calcul de l'entrée de la sbox lié au chiffré correct
                string sboxInput = XorStrings(exansedR15.substr(step,6),(string)binaries[k]);

                //calcul de l'entrée de la sbox lié au chiffré incorrect
                string sboxInputF = XorStrings(exansedR15F.substr(step,6),(string)binaries[k]);

                //calul de la sortie de la sbox lié au chiffré correct
                string sboxOutput = GetSbox(sboxInput,i);

                //calul de la sortie de la sbox lié au chiffré incorrect
                string sboxOutputF = GetSbox(sboxInputF,i);

                if(sboxOutput == sboxOutputF)
                    continue;

                //calcul de S(E(R15)⊕K16))⊕S((E(R15*)⊕K16))
                string supposed = XorStrings(sboxOutput,sboxOutputF);

                //comparer le résultat et la valeur de vérification sur 4bits de chaque SBOX.
                if(supposed == unpermuted.substr(step2,4))
                    //stocker la possible solution de K16 48bits dans un tableau.
                    keys.push_back(binaries[k]);
            }

            sub_solutions.push_back(keys);

        }
        step+= 6;
        step2+= 4;

        solutions.push_back(sub_solutions);
    }

    return FromBinaryToHexadecimal(findKey(solutions));
}

string attack::attack56(string k48, string plaintext, string ciphertext)
{
    //cout << "K16 : " << k48 << endl;
    binaries.clear();
    GenerateAttackKeys(8);

    string k56 = UndoPc2(FromHexadecimalToBinary(k48));
    //cout << "K48 : " << FromBinaryToHexadecimal(k56) << endl;

    //PC-1(K56)
    string k64 = UndoPc1(k56);
    //cout << "K56 : " << FromBinaryToHexadecimal(k64) << endl;

    key k;

    for(int i = 0; i < 256; i++)
    {
        string temp = GetCandidate(i, binaries, k64);

        k.SetContent(temp);   
        d->SetKey(k);
        d->SetText(plaintext);

        if(d->DesEncryption() == ciphertext)
        {
            k64 = temp;
            break;
        }

      }

    //cout << "KXX : " << FromBinaryToHexadecimal(k64) << endl;

    return FromBinaryToHexadecimal(k64);
}

string attack::attack64(string k64)
{
      string key = "";

      for(int i = 0; i < 64 ; i+=8)
      {
          if(countSetBits(FrombinaryToDecimal(FromHexadecimalToBinary(k64).substr(i,8)))%2 == 0)
              key+= FromHexadecimalToBinary(k64).substr(i,7) + "1";

          else
               key+= FromHexadecimalToBinary(k64).substr(i,7) + "0";
      }

      return FromBinaryToHexadecimal(key);
}

string attack::FaultAnalysisAttack(string plaintext, string correct, string incorrect[32])
{
    string broken = attack64(attack56(attack48(correct,incorrect), plaintext, correct));
    key k;
    k.SetContent(FromHexadecimalToBinary(broken));
    des* DES = new des(myPlaintext,k.GetContent());
    string cipher = DES->DesEncryption();

    if(cipher == correct)
        return broken;

    return "Error !";
}
