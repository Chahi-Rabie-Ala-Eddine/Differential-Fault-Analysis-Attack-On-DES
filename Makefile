CFLAGS = -g -Wall -c

# Edition de lien du programme principal
main: main.o converter.o utils.o analyzer.o reverser.o printer.o des.o key.o attack.o 
	g++ -o FaultAttackAnalysis main.o converter.o utils.o analyzer.o reverser.o printer.o des.o key.o attack.o

# Compilation du programme principal
main.o: main.cpp des.h attack.h
	g++ $*.cpp ${CFLAGS}
	
# Compilation du programme principal
des.o: des.h des.cpp utils.h utils.cpp converter.h key.h key.cpp
	g++ $*.cpp ${CFLAGS}

# Compilation du programme principal
key.o: utils.h utils.cpp converter.h converter.cpp key.h key.cpp
	g++ $*.cpp ${CFLAGS}
	
# Compilation du programme principal
attack.o: des.h des.cpp utils.h utils.cpp converter.h converter.cpp analyzer.h analyzer.cpp reverser.cpp reverser.h printer.h printer.cpp key.h key.cpp
	g++ $*.cpp ${CFLAGS}

# Le clean
clean:
	rm -f *.o
	rm -f main

# Pour faire un zip
LENOM=Chahi_Rabie_Ala_Eddine
zip:
	rm -rf ${LENOM}
	rm -rf ${LENOM}.zip
	mkdir ${LENOM}
	cp Makefile ${LENOM}
	cp *.h *.c ${LENOM}
	zip -r ${LENOM}.zip ${LENOM}
	rm -rf ${LENOM}
