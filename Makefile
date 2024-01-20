flags = -c -ggdb -Wall -Wextra

all:
	gcc $(flags) modules/String/stringClass.c -o Build/stringClass.o
	gcc $(flags) modules/Utils/utils.c -o Build/utils.o
	gcc $(flags) modules/LinearAlgebra/matrix.c -o Build/matrix.o
	ar cr bin/libCBase.a Build/matrix.o Build/utils.o Build/stringClass.o
	cp src/CBase.h bin/CBase.h
	
	# tests
	gcc tests/main.c -o tests/build/main.exe -I bin -L bin -lCBase