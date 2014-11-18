#include <iostream>
#include <string.h>
#include <istream>   
#include <cstring>
#include <unistd.h>
#include <cassert>
using namespace std; 
#include <cstdio>
#include <cstring>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <cstdlib>
#include <vector>
#include "hw2.h"

//modifies input to remove comments
void rm_comment(string & input)
{
	unsigned i = 0;
	for(; i < input.size(); i++ )
	{
		if (input.at(i) == '#' ){
			break; //get out of the for loop
		}
	}
	
	for(; i < input.size(); i++ )
	{
		input.at(i) = ' ';	
	}
	 
}



//returns true if 1 '&&' is found
const bool is_and (const string & input )
{
	if ( input.find( "&&", 0 ) != string::npos )
	{
		return true; 
	}
	return false; 
}

const bool is_or (const string & input )
{
	if ( input.find( "||", 0 ) != string::npos )
	{
		return true; 
	}
	return false; 
}

const bool is_pipe(const string & input)
{
	if ( input.find( "|", 0 ) != string::npos 
		&& is_or(input) == false)
	{
		return true; 
	}
	return false; 
	
}



//Counts number of arguments 
unsigned count_args( const string & input ) {
	if (input.size() == 0 )
	{
		return 0; 
	}

	unsigned count = 1; 
	
	for(unsigned i = 0; i < input.size(); ++i)
	{
		if ( input.at(i) == '&' || input.at(i) == '|' )
		{
			i+=1; // first '&' or '|' will be followed by another
			count +=1; 
		}

		if ( input.at(i) == ';' && i+1 != input.size() )//can have command: pwd;  
		{
			count +=1; 
		}
	}
	return count; 
}

unsigned count_args_space( const char input[] ) {
	if ( strlen(input) == 0 ||  strlen(input) == 1 )
	{
		return 3; 
	}

	unsigned count = 1; 
	
	for(unsigned i = 0; input[i] != '\0';  ++i)
	{
		if ( input[i] == ' '  )
		{
			i+=1; 
			count +=1; 
			//can have multiple whitespaes: ~ "       "
			while( input[i] != '\0' && input[i] == ' ' )
			{
				i+=1; 
			}
		}

	}
	return count; 
}

enum what {reg, piipe};

int main()
{
    string input; 
	    //taking input as a c++ string; will convert to c_str later

    cout << "$ "; //command prompt
    getline (cin,input);

while ( input != "exit" ) //bug if enters: "     exit" ->anything with exit and spaces
{

	//removing comments
	rm_comment (input); 


    //these will be the arguments to my shell after parsing
    	unsigned arg_count = count_args(input);  	
	vector <char**> argv; 
	argv.resize( arg_count ); 

    	char * tmp; //cstring to not deal with memory management for now
	int inp_sz = input.size()+1;
    	char* input2 = new char[inp_sz]; //will take copy of input from std::string input
    	strcpy(input2, input.c_str() );
	
	//stores strings of diff command/argument groups . Parses with connectors as delims	
	vector <char*> inp;
	//FIXME size could be segm fault problem later D:
	inp.resize(arg_count); 
	//inp.resize(arg_count+1); 
	
	//can only handle one of these cases at a time
	//loop to get substrings of input with "&&||;" as delimiters
	if(is_or(input) )
	{
		inp = parse(input, "||");
	}
	else if(is_and(input) )
	{
		inp = parse(input, "&&");
	}

	else//either have  ';' or nothing
	{
		int argc = 0 ; // no arguments (yet) 
		tmp = strtok(input2,";"); 
		
		if(tmp != NULL)
		{
			inp.at(0) = new char[strlen(tmp) +1]; 
			strcpy( inp.at(0) , tmp ); //copying first token 
		}

		//further parses with connectors as delims
		while (tmp != NULL)
		{
			argc +=1; // argument count increases. 
			tmp = strtok (NULL,"&&||;");  
			if(tmp != NULL){
				inp.at(argc) = new char[strlen(tmp) +1]; 
				inp.at(argc) = tmp; // copying tokens into argv one at a time 
			}
		}
	}
	vector<what> indicator;
	//here we have a vector of char** with each element of argv (the vector)
	//containing one commands with parameters for execvp
	for(unsigned i = 0; inp.size() > i && inp.at(i) != NULL; ++i) //FIXME
	//i < arg_count && inp.at(i) != NULL; ++i)
	{
		if(is_pipe( static_cast<std::string>(inp.at(i)) ))
		{
			indicator.push_back(piipe);//pipe input!
			char* tmp[2];// = {"random", "random"}; 
			tmp[0] = (char*)malloc(8);
			tmp[1] = (char*)malloc(8);
			strcpy(tmp[0], "random");
			strcpy(tmp[1], "random");
			//tmp[1] = "random\0";
			argv.push_back(tmp);
			continue; //won't modify :D
		}
		else{
			 indicator.push_back(reg);//non pipe
		}
		
		int argc = 0 ; // no arguments (yet) 
		tmp = strtok(inp.at(i)," ") ; 
		if(tmp != NULL){
			argv.at(i) = new char* [ count_args_space(inp.at(i) ) + 3 ];
			argv.at(i)[argc] = new char[strlen(tmp) +4]; 
			strcpy( (argv.at(i)[argc] ) , tmp ); //copying first token 
		}
		while (tmp != NULL)
		{
			if(tmp != NULL){
				argc +=1; // argument count increases. 
				tmp = strtok (NULL," ");  
				argv.at(i)[argc] = tmp; // copying tokens into argv one at a time 
			} 

		}
	}



    //beginning fork, execpv processes
    //may need to creat multiple forks to run input with connectors

	//tells us if have && or ||
	//can only be one or other or ';'
	const bool AND = is_and(input); 
	const bool OR = is_or(input); 
		
	//assert(argv.size() == indicator.size()); 
	cout << "inp: " << inp.size() << " argv: " << argv.size() << endl;
	//assert( argv.size() == inp.size() );
	//execute multiple commands through for loop (similar to lab02)
	for(unsigned i = 0; i < argv.size(); ++i )
	{ 
		if( indicator.at(i) == piipe)
		{
			string hw_2 = "./bin/hw2 " + static_cast<string>
			(inp.at(i)) + "\0"; 
			//pipe or inp redirection!
			system( const_cast<char*>(hw_2.c_str()));	
			//called appropriate things in seperate executable
			continue;
		}	
		int status; 
		int pid=fork(); //stores child's pid .. will use for connector cases in parent!
		if(pid == -1)
		{
			perror("There was an error with fork(). Go back and check. " ); 
			exit(1); 
		}
		//child process
		if (pid==0) {
		
			if(-1 == execvp(argv.at(i)[0] ,  argv.at(i) )  )
			{
				perror("Error: execvp didn't run as expected. Command may not exist.");
				exit(1); //avoid zombies    
			}
		}
		
		//pid now > 0 so we are in parent process. 
		else{
			if( wait(&status) == -1 ){
				perror("wait");
			}
			
			if (status == 0 ) //OR, and first command did not fail so do not execute next cmd
			{
				if ( OR ) 
				{
					//must only execute once so exit(1)
					exit(1); // no more looping!!
				}
			}

			if ( status != 0) //means child process failed 
			{
				if ( AND ) 
				{
					exit(1); // c1 in "c1 && ..." failed so done
				}	
			}			
			//no exit so continue loop as necesary. 
		}
	
	}

    cout << "$ "; //command prompt
    getline (cin,input);



}





	return 0; 
}







