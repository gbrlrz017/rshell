#include <iostream>
#include <string.h>
#include <istream>   
#include <cstring>

using namespace std; 

#include <stdio.h>
#include <string.h>

/*
int main ()
{
      char str[] ="- This, a sample string.";
        char * pch;
          printf ("Splitting string \"%s\" into tokens:\n",str);
            pch = strtok (str," ,.-");
              while (pch != NULL)
                    {
                            printf ("%s\n",pch);
                                pch = strtok (NULL, " ,.-");
                                  }
                                    return 0;
}
*/

//need to figure out how to parse!!
//see boost library's TOKENIZER !!!!!
int main()
{
    string input; 
   
    //taking input as a c++ string; will convert to c_str later
    cout << "$: "; //command prompt
    getline (cin,input);
    cout << endl << "outputting input: " << endl << input << endl; 
    
    //these will be the arguments to my shell after parsing
    int argc;
    char** argv;

    char * tmp; //cstring to not deal with memory management for now
    char delims[] = " &&||;.-";
    char input2[9999]; 
    strcpy(input2, input.c_str() );
    tmp = strtok(input2,delims); 
    while (tmp != NULL)
    {
        printf ("%s\n",tmp);
        tmp = strtok (NULL,delims);  
    }
                      


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
