
all: 	
	@if [ ! -d bin ]; then mkdir bin; fi
	g++ -Werror -ansi -pedantic -Wall src/rschell.cpp 
	mv a.out ./bin
	./bin/a.out		

rshell:
	@if [ ! -d bin ]; then mkdir bin; fi
	g++ -Werror -ansi -pedantic -Wall src/rschell.cpp 
	mv a.out ./bin
	./bin/a.out		









