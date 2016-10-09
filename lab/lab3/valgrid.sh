#!/usr/bin/env bash

if [ $1 = "C" ]  
then  
    /usr/bin/clang -ggdb main.c -std=c99 -Wall -Werror -o program && /usr/local/bin/valgrind ./program
elif [ $1 = "Cpp" ]  
then  
    /usr/bin/clang++ -std=c++11 -stdlib=libc++ Main.cpp Rparser.cpp Rparser.h Node.cpp Node.h Resistor.cpp Resistor.h -Wall -Werror -o program && /usr/local/bin/valgrind ./program
fi
