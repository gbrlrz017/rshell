
all: 	
	@if [ ! -d bin ]; then mkdir bin; fi
	g++ -g -Werror -ansi -pedantic -Wall src/hw3.cpp -o ./bin/rshell 	
	#g++ -g -Werror -ansi -pedantic -Wall src/rschell.cpp -o rshell 
	#mv rshell ./bin
	g++ -g -Werror -ansi -pedantic -Wall src/ls.cpp src/Status.h -o ls
	mv ls ./bin
	g++ -g -Werror -ansi -pedantic -Wall src/cp.cpp -o cp
	mv cp ./bin


rshell:
	@if [ ! -d bin ]; then mkdir bin; fi
	g++ -g -Werror -ansi -pedantic -Wall src/rschell.cpp -o rshell 
	mv rshell ./bin
	./bin/rshell		

ls: 
	@if [ ! -d bin ]; then mkdir bin; fi
	g++ -g -Werror -ansi -pedantic -Wall src/ls.cpp src/Status.h -o ls
	mv ls ./bin
	
cp: 
	g++ -g -Werror -ansi -pedantic -Wall src/cp.cpp -o cp
	mv cp ./bin

hw3:
	g++ -g -Werror -ansi -pedantic -Wall src/hw3.cpp -o ./bin/rshell

clean: 
	rm -r ./bin 





