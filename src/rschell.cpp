#include <iostream>
#include <string.h>
#include <cstring>

using namespace std; 





int main()
{
    //declaring argc and argv as local variables (as arguments to main too complicated)
    int argc = 0;
    char** argv;

    //reading in arguments and keeping count
    unsigned i = 0; //keep track of index
    while (cin >> argv[i])
    {
        
    }


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
