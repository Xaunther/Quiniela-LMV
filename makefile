#Este makefile está pensado para ser usado en Linux.
#En Windows recomiendo usar Dev-C++ o algún otro software para programar en C++

#Variables
GCC = g++
Scripts = Quiniela.out PostQuiniela.out


#Custom options
.PHONY: all clean

all: $(Scripts) #Compila todos los códigos	

clean: #Borra compilaciones
	rm *.o *.so *.exe *.out

Quiniela.out: Quiniela.cpp
	$(GCC) Quiniela.cpp -o Quiniela.out

PostQuiniela.out: PostQuiniela.cpp
	$(GCC) PostQuiniela.cpp -o PostQuiniela.out
