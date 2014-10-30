#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4

#include <cstring>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

//parses input with " " as delim
//returns vector of cstring tokens
vector<char*> parse_inp (string & input)
{
	char * tmp; //cstring will be used in parsing later
	int inp_sz = input.size()+1; //character size of inputted string
	char * input2 = new char[inp_sz]; //will take compy of input
	strcpy(input2, input.c_str() ); 


	vector <char*> inp; 
	int argc = 0; //no args yet
	tmp = strtok(input2, " "); //parsing with whitespace as delims
	
	if (tmp != NULL)
	{
		inp.at(0) = new char[strlen(tmp) +1]; 
		strcpy( inp.at(0), tmp); //copying token (1st one)
	}

	//further parses with whitespace as delims. 
	while (tmp != NULL)
	{   
		argc +=1; // argument count increases. 
		tmp = strtok (NULL," ");  
		if(tmp != NULL){ 
			inp.at(argc) = new char[strlen(tmp) +1];
			inp.at(argc) = tmp; // copying tokens into argv one at a time                
		}
	}
	
	delete tmp; 
	delete input2; 
	return inp; 

}



/*
 *  * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
 *   * that there is no error checking on these functions.  You MUST add error 
 *    * checking yourself.
 *     */

int main()
{
	//will tell me whether or not flags passed in
	//need to combine later: to binary number? 
	//bool flag_a, flag_l, flag_R; 
	
	string input; 
	//taking input as a c++ string; 

	cout << "$ "; //command prompt
	getline (cin,input);
	
	while( input != "exit" )
	{
				//will take in parsed input
		vector <char*> inp = parse_inp(input); 
				
				
		//point to same memory, so have to be careful later.
		char ** argv = &inp[0]; 


		cout << "$ "; //command prompt
		getline (cin,input);
	}


	/*
	    char *dirName = ".";
	    DIR *dirp = opendir(dirName);
	    dirent *direntp;
	    while ((direntp = readdir(dirp)))
		
		cout << direntp->d_name << endl;  // use stat here to find attributes of file
	    closedir(dirp);
	*/
	return 0; 
}
