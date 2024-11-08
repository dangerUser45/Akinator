Compiler = g++
B = build_akinator/

#-----------------------------------------------------------------------

akin : $(B)akinator.o   $(B)TXLib.o  
	$(Compiler)  $(B)akinator.o $(B)TXLib.o -o akin.exe

#-----------------------------------------------------------------------

$(B)akinator.o : akinator.cpp \
		akinator.h
	$(Compiler) -c akinator.cpp -o $(B)akinator.o

$(B)TXLib.o : TXLib.cpp
	$(Compiler) -c TXLib.cpp -o $(B)TXLib.o