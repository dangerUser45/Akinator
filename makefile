Compiler = g++
B = build_akinator/

#-----------------------------------------------------------------------

akin :           $(B)akinator.o $(B)Akinator_init.o $(B)Processing.o $(B)Print.o $(B)TXLib.o  
	$(Compiler)  $(B)akinator.o $(B)Akinator_init.o $(B)Processing.o $(B)Print.o $(B)TXLib.o -o akin.exe
#-----------------------------------------------------------------------

$(B)akinator.o : akinator.cpp \
				 akinator.h
	$(Compiler) -c akinator.cpp -o $(B)akinator.o

$(B)Akinator_init.o : akinator_init.cpp                                \
				      ..\Processor\Onegin_for_proc\Onegin_processing.h \
					  ..\Processor\Onegin_for_proc\Onegin_General.h    \
					  ..\Processor\Onegin_for_proc\Print.h             \
					  akinator.h
	$(Compiler) -c akinator_init.cpp -o $(B)Akinator_init.o

$(B)Print.o : ../Processor/Onegin_for_proc/Print.cpp                          \
		      ../Processor/Onegin_for_proc/Onegin_General.h                   \
			  ../Processor/Onegin_for_proc/Print.h
	$(Compiler) -c  ../Processor/Onegin_for_proc/print.cpp -o $(B)print.o

$(B)Processing.o : ../Processor/Onegin_for_proc/Processing.cpp      \
				   ../Processor/Onegin_for_proc/Onegin_General.h    \
				   ../Processor/Onegin_for_proc/Onegin_Processing.h \
				   ../Processor/Onegin_for_proc/Print.h
	$(Compiler) -c ../Processor/Onegin_for_proc/Processing.cpp -o $(B)Processing.o

$(B)TXLib.o : TXLib.cpp
	$(Compiler) -c TXLib.cpp -o $(B)TXLib.o

#---------------------------------------------------------------------------
clean :
	del build_akinator\*.o
