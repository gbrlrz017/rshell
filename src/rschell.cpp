#include <iostream>
#include <string.h>
#include <istream>   
#include <cstring>
#include <unistd.h>
using namespace std; 
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <errno.h>
#include <cstdlib>
#include <vector>


//Counts number of arguments 
int count_args( const string & input ) {
	if (input.size() == 0 )
	{
		return 0; 
	}

	int count = 1; 
	
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
	//BUG: will give greater size than should be when have input: "ls ; pwd;   "
	//will count white space unfortunately.....
	//will say extra argument than there is..
		}
	}
	return count; 
}

vector<int> con_pos( const string & input ) {
	vector<int> x; 
	if (input.size() == 0 )
	{
		return x; 
	}

	//int count = 1; 
	
	for(unsigned i = 0; i < input.size(); ++i)
	{
		if ( input.at(i) == '&' || input.at(i) == '|' )
		{
			x.push_back(i); 
			x.push_back(i+1); 
			i+=1; // first '&' or '|' will be followed by another
			
			//count +=1; 
		}

		if ( input.at(i) == ';' && i+1 != input.size() )//can have command: pwd;  
		{
			x.push_back(i); 
	//BUG: will give greater size than should be when have input: "ls ; pwd;   "
	//will count white space unfortunately.....
	//will say extra argument than there is..
		}
	}
	return x; 
}




int main()
{
    string input; 
	    //taking input as a c++ string; will convert to c_str later

    cout << "$ "; //command prompt
    getline (cin,input);
    cout << endl << "outputting input: " << endl << input << endl; 
    cout << "input.size() (raw): " << input.size() << endl; 
	// trying to see if space adds size
	// Answer: IT DOES -_____- 	 

    //these will be the arguments to my shell after parsing
    	unsigned arg_count = count_args(input);  	
	vector <char**> argv; 
	argv.resize( arg_count ); 

    char * tmp; //cstring to not deal with memory management for now
    char delims[] = " "; // connectors we are looking out for.
                                //FIXME: may not be exactly what we want since may have 
                                //to be arguments too
	int inp_sz = input.size()+1;
    char* input2 = new char[inp_sz]; //will take copy of input from std::string input
    strcpy(input2, input.c_str() );
	cout << "input2 done. no seg fault here. " << endl; 	
	
	vector <int> pos = con_pos(  input ); //contains positions of delimiters 
	//printing elements in pos
	if(pos.size() != 0 ){
		for(unsigned i = 0; i < pos.size(); ++i){
			cout << pos.at(i) << " "; 
		}
		cout << endl; 
	}
//	
	for(unsigned i = 0; i < arg_count; ++i)
	{
		int argc = 0 ; // no arguments (yet) 
		tmp = strtok(input2,delims) ; 
		cout << "strtok, i = " << i << endl; 
		argv.at(i) = new char* [999];
		argv.at(i)[argc] = new char[strlen(tmp) +1]; 
    		strcpy( (argv.at(i)[argc] ) , tmp ); //copying first token 
   		cout << "strcpy, i = " << i << endl;  

		while (tmp != NULL)
		{
			argc +=1; // argument count increases. 
			printf ("%s\n",tmp) ;
			tmp = strtok (NULL,delims);  
			argv.at(i)[argc] = tmp; // copying tokens into argv one at a time 
			 

		}
		cout << "first while, i = " << i << endl; 
	}
	    /* cerr << "copying tmp into argv..." << endl; 
    strcpy(*argv,tmp );
    cout << "strcpy successful!! (maybe LOL)" << endl; 
    */

    //checking everything was read in 
    //cout << "argc: " << argc << "   " <<  endl;
    //cout << " argv:" << endl;

    for(unsigned i = 0; argv[i]!='\0'; ++i){
        cout << i << ": " << argv[i] << endl; 
    }
    
    //need to figure out a way to read in commands with ';' in between
    //and white space in between
    
    //checking how execvp works (dummy variables)
    char * aargv[4]; 
    aargv[0] = new char[4]; 
    aargv[1] = new char[4]; 
    aargv[2] = new char[4]; 
    strcpy( aargv[0] , "pwd"); //copying first token 
    cout << "first copy. \n" << endl; 
    strcpy( aargv[1] , " ; " ); 
    cout << "about tho start third..." << endl; 
    strcpy( aargv[2] , "ls"); 
    cout << "done copying... " << endl; 


    //beginning fork, execpv processes
    //may need to creat multiple forks to run input with connectors

	//will now make major changes
	//execute multiple commands through for loop (similar to lab02)

	int pid=fork();
	if(pid == -1)
	{
		perror("There was an error with fork(). " ); 
		exit(1); 

	}
	//child process
	if (pid==0) {
		cout << "i'm a child" << endl;
	
/*
		if(-1 == execvp(*argv.at(0)[0] ,  *argv.at(0) )
		{
			perror("Error: execvp didn't run as expected. Commands may not exist.");
		
			exit(1); //avoid zombies    

		}*/
	}
	//pid now > 0 so we are in parent process. 
	else{
		if( wait(NULL) == -1 ){
			perror("Error: wait() did not wait!! :o ");
		}

		cout << "I'm a parent." << endl; 
		exit(1); 
	}


	return 0; 
}







