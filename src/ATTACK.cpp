#include <iostream>

#include "./PRINTER/printer.h"
#include "./UTILS/colors.h"

int main(int argc, char** argv)
{
	PrintAttackProcess();
	
	/*
	 * Can also run it differently by :
	 * 1 - Modify makefile
	 * 2 - Make then ./FaultAttackAnalysis result
	 * OR - Make then ./FaultAttackAnalysis animation
	 * 
	 * */
	
	/*
    if(argc == 1)
        cout << BOLDRED << "\nError !" << BOLDWHITE << "you have to select a program\n" << endl;

    else
    {
        if((string)argv[1] == "result")
            PrintAttackResults();

        else if((string)argv[1] == "animation")
            PrintAttackProcess();
        
        else
            cout << BOLDRED << "\nError !" << BOLDWHITE << "Please select" << BOLDYELLOW << " ANIMATION" << BOLDWHITE << " OR" << BOLDYELLOW << " RESULT\n" << RESET << endl;
    }
	*/
}
