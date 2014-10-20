#include <iostream>
#include <string.h>
#include <istream>   
#include <cstring>
#include <unistd.h>
using namespace std; 
#include <cstdio>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <errno.h>
#include <cstdlib>

int main()
{
    string input; 
    //taking input as a c++ string; will convert to c_str later

    cout << "$ "; //command prompt
    getline (cin,input);
    cout << endl << "outputting input: " << endl << input << endl; 
    
    //these will be the arguments to my shell after parsing
    int argc = 0; // no arguments (yet) 
    char* argv[99999];
    argv[0] = new char[9999];

    char * tmp; //cstring to not deal with memory management for now
    char delims[] = " "; // connectors we are looking out for.
                                //FIXME: may not be exactly what we want since may have 
                                //to be arguments too

    char input2[9999]; //will take copy of input from std::string input
    strcpy(input2, input.c_str() );

    cout << "about to run strtok 1st time" << endl; 
    tmp = strtok(input2,delims) ; 
    strcpy( argv[argc] , tmp ); //copying first token 
    
    cout << "about to run strtok In while loop." << endl; 
    while (tmp != NULL)
    {
        argc +=1; // argument count increases. 
        printf ("%s\n",tmp) ;
        tmp = strtok (NULL,delims);  
        argv[argc] = tmp; // copying tokens into argv one at a time 
         
        
    }
    /* cerr << "copying tmp into argv..." << endl; 
    strcpy(*argv,tmp );
    cout << "strcpy successful!! (maybe LOL)" << endl; 
    */

    //checking everything was read in 
    cout << "argc: " << argc << "   " <<  endl;
    cout << " argv:" << endl;

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
    int pid=fork();

    if(pid == -1)
    {
        perror("There was an error with fork(). " ); 
        exit(1); 

    }
    //child process
    if (pid==0) {
        cout << "i'm a child" << endl;

        cout <<" before" << endl;
        if(-1 == execvp(argv[0], argv))
        {
            perror("Error: execvp didn't run as expected. Commands may not exist.");
        }
        exit(1); //avoid zombies    

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
