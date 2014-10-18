#include <iostream>
#include <cstring>

using namespace std; 





int main(int argc, char** argv)
{
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
