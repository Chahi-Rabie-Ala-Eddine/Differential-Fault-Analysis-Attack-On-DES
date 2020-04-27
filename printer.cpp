#include "converter.h"
#include "utils.h"
#include "constants.h"
#include "colors.h"
#include "analyzer.h"
#include "reverser.h"
#include "attack.h"
#include "key.h"

#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <unistd.h>
 
using namespace std;

void PrintSboxOutputs(string* sbox)
{
    cout << "S-box outputs : "
         << sbox[0] << " "
         << sbox[1] << " "
         << sbox[2] << " "
         << sbox[3] << " "
         << sbox[4] << " "
         << sbox[5] << " "
         << sbox[6] << " "
         << sbox[7] << " "
         << endl << endl;
}

void PrintColored(string colored, int value)
{
    cout << "                                                   ";
    for(int i = 0; i < (int)colored.size(); i++)
    {
        if(colored[i] == '0')
            cout << CYAN << colored[i] << RESET;

        else
            cout << RED << colored[i] << RESET;
    }

    cout << YELLOW << " Injected fault position : [" << value << "]" << RESET << " "<< endl;
}

void PrintCorruptedBits(string ciphers[32])
{
    for(int i = 0; i < 32; i++)
        PrintColored(GetCorruptedBits(ciphers)[i],i);
}

void PrintBinaries(vector<string> bins)
{
    int incrementer = 0;
    for (auto const& key : bins)
    {
        if(incrementer == 8 || incrementer == 0)
        {
            incrementer = 0;
            cout << "\n                                                   ";
        }
        
        ++incrementer;
    
        cout << BOLDGREEN << key << RESET << " ";
    }
        
}

void PrintCommonSolution()
{
    for(int i = 0; i < 8 ; i++)
    {
        cout << "\n\n" << BOLDCYAN <<"                                                                  TREATEMENT OF 📦  SBOX-" << i+1 << " ..." << RESET << endl << endl;
        sleep(1.5);
        for(int j = 0; j < 6 ; j++)
        {
            sleep(0.75);
            cout << BOLDRED << "                            CIPHER " <<  consideredSbox[i][j] << RESET << " ";
            cout << " [ "; 
            for(int k = 0; k < (int)solutions[i][j].size(); k++)
            {
                sleep(0.5);
                cout << solutions[i][j][k] << " ";
            }
            
            cout << "]\n";
        }
        sleep(4);
    }
}

void PrintColoredSolution()
{
    sleep(0);
    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                                   DETRERMINATION OF THE SOLUTIONS " << RESET << BOLDWHITE << "COMMON " << RESET << BOLDYELLOW << "TO EACH S-BOX ...\n\n" <<  RESET;

    sleep(7);

    string key[8];

    for(int i = 0; i < (int)solutions.size(); i++)
        key[i] = findCommonSolution(solutions[i]);

    for(int i = 0; i < 8 ; i++)
    {
        sleep(1.5);
        cout << "\n\n" << BOLDCYAN << "                                                            COMMON SOLUTION OF 📦  SBOX-" << i+1 << " ..." << RESET << endl << endl;
        for(int j = 0; j < 6 ; j++)
        {
            sleep(0.75);
            cout << BOLDYELLOW << "                            CIPHER " << consideredSbox[i][j] << RESET << " [ "; 
            for(int k = 0; k < (int)solutions[i][j].size(); k++)
            {
                sleep(0.5);

                if(solutions[i][j][k] == key[i])
                    cout << BOLDGREEN << solutions[i][j][k] << " " << RESET;

                cout << solutions[i][j][k] << " ";
            }

            cout << "]\n";
        }

        cout << "\n";
    }
}

void PrintHexaBinSolutions()
{
    cout << BOLDYELLOW << "\n\n\n\n                                       ‼️  EXAUSTIVE RESEARCH THEREFORE GIVES THE FOLLOWING COMMON SOLUTIONS ...\n\n" << RESET;
    sleep(5);

    for(int i = 0; i < (int)solutions.size(); i++)
    {
        string temp = findCommonSolution(solutions[i]);
        cout << "                                                               S-BOX " << i+1 << RESET << " [ " << YELLOW << temp << RESET << " | " 
        << CYAN << FromBinaryToHexadecimal(temp) << RESET << " ]" << endl;
    }
    sleep(7);
}

void PrintSubKey16()
{
    cout << BOLDYELLOW << "\n\n\n\n                                    🔗 CONCATENATE THE" << RESET << BOLDWHITE << " 8 WORDS" << RESET << BOLDYELLOW " OF " << RESET << BOLDWHITE << "6 BITS " << RESET << BOLDYELLOW <<"TO FORM THE FOLLOWING " << RESET << BOLDWHITE << "48 BITS WORD...\n\n\n" << RESET;
    sleep(7);

    string key = "";

    cout << "                                              [";
    for(int i = 0; i < (int)solutions.size(); i++)
    {
        if(i == 0)
        {
            cout << RED << findCommonSolution(solutions[i]) << " " << RESET;
            key+= findCommonSolution(solutions[i]);
        }

        if(i == 1)
        {     
            cout << WHITE << findCommonSolution(solutions[i]) << " " << RESET;
            key+= findCommonSolution(solutions[i]);
        }

        if(i == 2)
        {           
            cout << BLUE << findCommonSolution(solutions[i]) << " " << RESET;
            key+= findCommonSolution(solutions[i]);
        }

        if(i == 3)
        {            
            cout << GREEN << findCommonSolution(solutions[i]) << " " << RESET;
            key+= findCommonSolution(solutions[i]);
        }

        if(i == 4)
        {
            cout << MAGENTA << findCommonSolution(solutions[i]) << " " << RESET;
            key+= findCommonSolution(solutions[i]);
        }

        if(i == 5)
        {      
            cout << YELLOW << findCommonSolution(solutions[i]) << " " << RESET;
            key+= findCommonSolution(solutions[i]);
        }

        if(i == 6)
        {
            key+= findCommonSolution(solutions[i]);
            cout << CYAN << findCommonSolution(solutions[i]) << " " << RESET;
        }
            

        if(i == 7)
        {
            cout << WHITE << findCommonSolution(solutions[i]) << RESET << "]";
            key+= findCommonSolution(solutions[i]);
        }

    }

    cout << "\n\n                                                🗝️  " << BOLDWHITE << key << RESET;

    cout << "\n\n\n";

    sleep(7);

    cout << BOLDYELLOW << "\n\n\n\n                                                             FINALLY IN HEXADECIMAL\n\n";
    
    sleep(3); 
    
    cout << BOLDWHITE 
    << "                                                             🔑 K16 [" << BOLDGREEN << FromBinaryToHexadecimal(key) << BOLDWHITE << "]" << RESET << endl << endl;
    sleep(7);
}

void PrintInfectedSbox()
{
    array<array<int, 6>, 8> infected = GetConsideredSbox();

    for(int i = 0; i < 8; i++)
    {
        cout << BOLDGREEN << "                                                                  📦  SBOX[" << RESET << BOLDCYAN << (i+1) << RESET <<BOLDGREEN << "] " << RESET;

        for(int j = 0; j < 6; j++)
            cout << infected[i][j] << " ";

        cout <<  endl;
    }

    cout << endl;
}

void PrintKey16Attack()
{
    cout << "\n\n\n\n\n\n" << endl;
    
    cout << "                                         "; printf("\033[%dm                                                                                  \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&&&&&&      &&&&&&&&       &&             &&&&&&&&&    &&&&&&&&  &&&&&&&&&&  \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&   &&&     &&&&&&&&      &&&&            &&&&   &&&   &&&&&&&&  &&&&&       \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&   &&&&    &&&&         &&&&&&           &&&&   &&&&  &&&&&     &&&&&       \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&   &&&&    &&&&&&&&    &&&  &&&   &&&&&  &&&&   &&&&  &&&&&&&&  &&&&&&&&&&  \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&   &&&&    &&&&&&&&   &&&&&&&&&&         &&&&   &&&&  &&&&&          &&&&&  \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&   &&&     &&&       &&&&    &&&&        &&&&   &&&   &&&&&          &&&&&  \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm  &&&&&&&&&      &&&      &&&&&    &&&&&       &&&&&&&&&    &&&&&&&&& &&&&&&&&&&  \033[m\n", 41);
    cout << "                                         "; printf("\033[%dm                                                                                  \033[m\n", 41);

    sleep(3);

    cout << BOLDCYAN << "\n\n\n\n\n\n\n                              WELCOME TO THIS TUTORIAL 🙋 , WE WILL SEE HOW TO BREAK THE DATA ENCRYPTION STANDARD USING A FAULT ATTACK !\n\n";
    
    sleep(7);

    cout << BOLDRED << "                                                            PLEASE TURN YOUR TERMINAL 🖥️  FULLSCREEN 🙏 !\n\n\n\n\n" << RESET << endl;
    
    sleep(5);

    cout<<BOLDYELLOW<< "                                                                   Are You Ready 👨‍💻  ? GO  ▶️   " << RESET << endl;

    sleep(3);

    cout << BOLDWHITE << "\n\n\n\n\n" 
         << "                                                              " << UNDERLINE << "STEP 1 [DETERMINE THE TYPE OF INJECTION]\n\n\n" << RESET << RESET;

    sleep(3);

    PrintCorruptedBits(incorrectCiphers);

    sleep(7);

    cout << "\n\n\n" << BOLDGREEN << "                               ‼️   AS WE CAN SEE EACH FALSE CIPHER HAS A SINGLE WRONG BIT, IT'S THEREFORE A SINGLE BIT FILP INJECTION\n\n\n" << RESET;

    sleep(8);
    
    cout << "\n\n\n\n\n" 
         << "                                                              " << UNDERLINE << "STEP 2  [DETERMINE SUBKEY K16]\n\n\n" << RESET << endl;

    sleep(4);

    cout << "\n\n" << BOLDYELLOW << "                                                  DETERMINE THE MESSAGES LINKED TO EACH OF THE 8 SBOXES 📦 ...\n\n" << RESET;

    sleep(4);

    PrintInfectedSbox();

    sleep(7);

    cout << "\n\n\n";

    string cipher = FromBinaryToHexadecimal(Permutation(FromHexadecimalToBinary(myCorrectCipher),64,initialPermutation));
    
    cout << "\n\n" << BOLDYELLOW 
    << "                                                  UNDO IP⁻¹(" << RESET << BOLDWHITE << "Ciphertext" << BOLDYELLOW << ") : SIMPLY COMPUTE IP(IP⁻¹(" << RESET << BOLDWHITE "Ciphertext" << RESET << BOLDYELLOW ")) ...\n\n" << RESET;

    sleep(5);
    cout << BOLDWHITE << "                                                               IP(" << BOLDGREEN << myCorrectCipher << BOLDWHITE << ") = " << BOLDGREEN << cipher << RESET << endl;
    
    sleep(3);

    cout << "\n\n\n\n\n\n" << BOLDYELLOW 
    << "                                              SPLIT ✂️  CIPHERTEXT INTO TWO PARTS AND STORE THEM INTO " << RESET << BOLDWHITE << "R16" << BOLDYELLOW" AND " << RESET << BOLDWHITE << "L16" << RESET << BOLDYELLOW " ...\n\n" << RESET;

    sleep(7);

    cout 
    << BOLDCYAN << "                                                                  CIPHER : " << RESET << BOLDGREEN << cipher << RESET "\n" <<
     BOLDCYAN <<   "                                                                  L16    : " << RESET << BOLDBLUE << SplitTwoParts(cipher)[0] << RESET << "\n" << 
     BOLDCYAN <<   "                                                                  R16    :         " << RESET << BOLDRED << SplitTwoParts(cipher)[1] << RESET << "\n\n";

    sleep(7);

    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                          SWAP " << RESET << BOLDWHITE << "R16" << BOLDYELLOW << " 🔛 " << RESET << BOLDWHITE "L16" << RESET << BOLDYELLOW " BECAUSE DURING THE LAST ROUND THE TWO PARTS ARE EXCHANGED ...\n\n" << RESET;

    sleep(7);

    cout 
    << BOLDCYAN << "                                                                  CIPHER : " << RESET << BOLDGREEN << cipher << RESET "\n" <<
     BOLDCYAN <<   "                                                                  L16    :         " << RESET << BOLDBLUE << SplitTwoParts(cipher)[1] << RESET << "\n" << 
     BOLDCYAN <<   "                                                                  R16    : " << RESET << BOLDRED << SplitTwoParts(cipher)[0] << RESET << "\n\n";
    
    sleep(7);

    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                                     STORE " << RESET << BOLDWHITE << "L16" << BOLDYELLOW << " IN " << RESET << BOLDWHITE "R15" << RESET << BOLDYELLOW " COMPUTE THE EXPANSION OF" << RESET << BOLDWHITE << " R15" << RESET << BOLDYELLOW << " ...\n\n" << RESET;

    sleep(7);

    cout << BOLDYELLOW << "                                                                   E(" << RESET << BOLDWHITE << "R15" << RESET << BOLDYELLOW << ") : " << RESET << BOLDRED << FromBinaryToHexadecimal(Permutation(FromHexadecimalToBinary(SplitTwoParts(cipher)[1]),48,expansionIndex)) << RESET << endl;

    sleep(5);

    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                                         DO THE SAME WITH THE " << RESET << BOLDWHITE << "32" << RESET << BOLDYELLOW << " FALSE CIPHERS ...\n\n" << RESET;

    sleep(7);

    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                              GENERATION OF THE " << RESET << BOLDWHITE << " 2⁶" << RESET << BOLDYELLOW << " POSSIBILITIES OF" <<  RESET << BOLDWHITE << " 6-bit" << RESET << BOLDYELLOW << " FORMED WORDS ...\n\n" << RESET;

    sleep(7);

    GenerateAttackKeys(6);
    PrintBinaries(binaries);
    binaries.clear();

    sleep(7);

    cout << "\n\n\n\n\n" << BOLDWHITE 
    << "                                                ⚠️  EXHAUSTIVE SEARCH " << RESET << BOLDYELLOW << "ON THE " << RESET << BOLDWHITE <<  "6 " << RESET << BOLDYELLOW << "INPUT BITS OF EACH SBOX 📦 ...\n\n" << RESET;

    sleep(7);
    
    attack a;
    a.attack48(myCorrectCipher,incorrectCiphers);
    
    PrintCommonSolution();

    PrintColoredSolution();
    
    PrintHexaBinSolutions();
    
    PrintSubKey16();
}

void PrintKey56Attack()
{
    attack a;
    string k16 = a.attack48(myCorrectCipher,incorrectCiphers);

    cout << BOLDWHITE << "\n\n\n\n\n" 
         << "                                                   " << UNDERLINE << "STEP 3 [DETERMINE THE 56 BITS OF THE KEY : FIND THE 8 LOST BITS]\n\n\n" << RESET << RESET;

    sleep(3);

    binaries.clear();
    GenerateAttackKeys(8);

    cout << "\n\n" << BOLDYELLOW 
    << "                                                                            UNDO PC2(" << RESET << BOLDWHITE << "K16" << BOLDYELLOW ") ...\n\n" << RESET;

    sleep(5);

    cout << BOLDWHITE << "                                                                  PC⁻²(" << BOLDGREEN << k16 << BOLDWHITE << ") = " << BOLDGREEN << FromBinaryToHexadecimal(UndoPc2(FromHexadecimalToBinary(k16))) << RESET << endl;
    
    sleep(3);

    cout << "\n\n" << BOLDYELLOW 
    << "                                                                          UNDO PC1(" << RESET << BOLDWHITE << "PC⁻²(K16)" << BOLDYELLOW << ") ...\n\n" << RESET;

    sleep(5);

    cout << BOLDWHITE << "                                                                 PC⁻1(" << BOLDGREEN << FromBinaryToHexadecimal(UndoPc2(FromHexadecimalToBinary(k16))) << BOLDWHITE << ") = " << BOLDGREEN << FromBinaryToHexadecimal(UndoPc1(UndoPc2(FromHexadecimalToBinary(k16)))) << RESET << endl;
    
    sleep(5);

    cout << "\n\n\n" << BOLDGREEN << "                                               ‼️  NOTE THAT WE DON'T KNOW YET THE 8 MISSING BITS THEN THEY ARE SET TO 0\n\n\n" << RESET;

    sleep(8);

    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                                      GENERATION OF THE " << RESET << BOLDWHITE << " 2⁸" << RESET << BOLDYELLOW << " POSSIBILITIES OF" <<  RESET << BOLDWHITE << " 8-bit" << RESET << BOLDYELLOW << " FOR LOST BITS ...\n\n" << RESET;

    sleep(7);

    PrintBinaries(binaries);

    cout << "\n\n\n\n";

    sleep(7);

    cout << "\n\n\n\n\n" << BOLDWHITE 
    << "                                                             ⚠️  EXHAUSTIVE SEARCH " << RESET << BOLDYELLOW << "ON THE " << RESET << BOLDWHITE <<  "8 " << RESET << BOLDYELLOW << "LOST BITS USING" << BOLDBLUE << " DES " << BOLDYELLOW << "...\n\n" << RESET;

    sleep(7);
    
    cout << BOLDYELLOW << "\n\n\n\n                                               THE " << BOLDWHITE << "8 " << BOLDYELLOW << "BITS THAT CORRECTLY " << BOLDBLUE << "ENCRYPT" << BOLDYELLOW << " THE PLAINTEXT GIVE THE FOLLOWING" << BOLDWHITE << " 64-BIT" << BOLDYELLOW << " KEY...\n\n";

    sleep(7);

    cout << BOLDWHITE 
    << "                                                                             🔑 K64[" << BOLDGREEN << a.attack56(k16,myPlaintext,myCorrectCipher) << BOLDWHITE << "]" << RESET << endl << endl;
    sleep(7);

    cout << "\n\n\n" << BOLDGREEN << "                                                                      ‼️  NOTE THAT THE PARITY BITS ARE WRONG\n\n\n" << RESET;

    sleep(7);
}

void PrintKey64Attack()
{
    attack DFA;
    string key = DFA.attack64(DFA.attack56(DFA.attack48(myCorrectCipher,incorrectCiphers),myPlaintext,myCorrectCipher));

    cout << BOLDWHITE << "\n\n\n\n\n" 
         << "                                                   " << UNDERLINE << "STEP 4 [DETERMINE THE 64 BITS OF THE KEY : FIND THE 8 PARITY BITS]\n\n\n" << RESET << RESET;

    sleep(5);

    cout << "\n\n\n" << BOLDGREEN << "      ‼️  THE PARITY BIT IS CALCULATED FROM THE PREVIOUS 7 BITS IF THEY ARE CONTAINING AN ODD NUMBER OF 1 THE 8TH BIT IS SET TO 0 OTHERWISE IT IS SET TO 1.\n\n\n" << RESET;

    sleep(7);


    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                                                       COMPUTATION OF" << BOLDWHITE << " PARITY" << BOLDYELLOW << " BITS ..." << RESET;

    sleep(7);

    cout << "\n\n\n\n";
    
    sleep(4);
    cout << BOLDWHITE 
    << "                                                                        🗝️  K64[" << BOLDGREEN << key << BOLDWHITE << "]" << RESET << endl << endl;
    sleep(7);
}

void PrintVerification()
{
    attack DFA;
    string key64 = DFA.attack64(DFA.attack56(DFA.attack48(myCorrectCipher,incorrectCiphers),myPlaintext,myCorrectCipher));
    key k;
    k.SetContent(FromHexadecimalToBinary(key64));
    des* DES = new des(myPlaintext,k.GetContent());
    string cipher = DES->DesEncryption();

    cout << BOLDWHITE << "\n\n\n\n\n" 
         << "                                                                   " << UNDERLINE << "STEP 5 [CHECK THE OBTAINED KEY]\n\n\n" << RESET << RESET;
    
    sleep(4);

    cout << "\n\n\n\n\n" << BOLDYELLOW 
    << "                                       ENCRYPT THE " << BOLDWHITE << " PLAINTEXT" << BOLDYELLOW << " WITH THE " << BOLDWHITE << "OBTAINED KEY 🗝️  " << BOLDYELLOW << "AND COMPARE IT TO THE " << BOLDWHITE << "GIVEN CIPHERTEXT" << BOLDYELLOW << " ..." << RESET;

    cout << "\n\n\n\n";
    
    sleep(7);
    cout << BOLDWHITE 
    << "                                                    DES[" << BOLDRED << key64 << BOLDWHITE << "](" << BOLDGREEN << myPlaintext << BOLDWHITE << ") = {" << BOLDBLUE << cipher << BOLDWHITE << "}\n\n\n" << RESET << endl << endl;
    sleep(7);

    cout << BOLDWHITE 
    << "                                                               CIPHERTEXT = [" << BOLDRED << cipher << BOLDWHITE << "]  ✅\n\n\n" << RESET << endl;
    sleep(7);

    cout << BOLDWHITE 
    << "                                            🗝️  [" << BOLDYELLOW << key64 << BOLDWHITE << "] IS THEREFORE THE RIGHT KEY USED, THE ATTACK WORKED 🌟✨⭐💫\n\n\n\n\n\n\n" << RESET << endl;

    sleep(7);

    cout << BOLDWHITE 
    << "                                                              ®️  MADE BY " << BOLDYELLOW << "CHAHI RABIE ALA-EDDINE" << BOLDCYAN << " 2020\n\n\n" << RESET << endl;

    sleep(7);

    //system("clear");
}

void PrintAttackProcess()
{
    PrintKey16Attack();
    PrintKey56Attack();
    PrintKey64Attack();
    PrintVerification();

    return;
}

void PrintAttackResults()
{
    cout << BOLDWHITE << "\n\n          " << UNDERLINE << "                                                            " << RESET << "\n";
    cout << BOLDCYAN << "          " << UNDERLINE << "🛡️  DIFFRENTIAL FAULT ANALYSIS ON DATA ENCRYPTION STANDARD 🛡️\n\n" << RESET << RESET;
    cout << BOLDWHITE << "\n\n                                 GIVEN DATA 📜\n\n" << RESET;
    cout << WHITE << "                       🔵  Plaintext  : " <<  RESET << RED << myPlaintext << RESET << "\n\n";
    cout << WHITE << "                       🔴  Ciphertext : " << RESET <<GREEN <<myCorrectCipher << RESET << "\n\n";

    attack DFA;

    string str1 = DFA.attack48(myCorrectCipher,incorrectCiphers);
    string str2 = DFA.attack56(str1,myPlaintext,myCorrectCipher);
    string str3 = DFA.attack64(str2);
    cout << "K16 : " << BOLDYELLOW << str1  << RESET << "     (The last key of key schedule algorithm)" << endl; 
    cout << "K64 : " << BOLDBLUE << str2  << RESET << " (The 64 bits key with wrong parity bits)" << endl;
    cout << "K64 : " << BOLDGREEN << str3  << RESET << " (The 64 bits of the key used in the DES)" << endl;

    key k;
    k.SetContent(FromHexadecimalToBinary(str3));
    des* DES = new des(myPlaintext,k.GetContent());
    string cipher = DES->DesEncryption();

    if(cipher == myCorrectCipher)
        cout << BOLDBLUE << "\n\n                          🔑 WAS SUCCESFULLY BROKEN ✅\n\n\n" << RESET << MAGENTA 
        << "                         ®️   CHAHI RABIE ALA EDDINE 2020" << RESET << endl;

    else
        cout << RED << "ERROR ! " << RESET << endl;

    return;
}
