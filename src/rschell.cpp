#include <iostream>
#include <string.h>
#include <istream>   
#include <cstring>
#include <unistd.h>
using namespace std; 
#include <cstdio>
#include <stdio.h>
#include <string.h>



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
    char delims[] = " &&||;-"; // connectors we are looking out for.
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

    if (argv[1]=='\0'){
        cout << "Null man. " << endl; 
    }
    
    //execvp(argv);
    
    cout << "||" << endl;
    

	return 0; 
}
