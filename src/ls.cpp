#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4                                                                                                                                              
#define INPUT cout << "$ "; /*command prompt */\ 
	getline (cin,input)


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
	int inp_sz = input.size()+3; //character size of inputted string
	char * input2 = new char[inp_sz]; //will take copy of input
	strcpy(input2, input.c_str() ); 


	vector <char*> inp; 
	int argc = 0; //no args yet
	tmp = strtok(input2, " "); //parsing with whitespace as delims
	
	if (tmp != NULL)
	{
		inp.resize( 2 ); 
		inp.at(0) = new char[strlen(tmp) +2]; 
		strcpy( inp.at(0), tmp); //copying token (1st one)
	}

	//further parses with whitespace as delims. 
	while (tmp != NULL)
	{   
		argc +=1; // argument count increases. 
		tmp = strtok (NULL," ");  
		if(tmp != NULL){ 
			inp.resize( inp.size() + 1 );
			inp.at(argc) = new char[strlen(tmp) +2];
			inp.at(argc) = tmp; // copying tokens into argv one at a time                
		}
	}
	//watchout later for memory leaks
	//may need to have different return type: vector <string>	
	//delete tmp; 
	//delete input2; 
	return inp; 

}

void print ( char ** argv ) 
{
	if( argv == NULL )
	{
		return; 
	}
	cerr << "entering loop \n"; 
	for (unsigned i = 0; argv[i] != '\0'; ++i )
	{
		cout << "None yet." << endl; 
		printf( argv[i]); 
		cout << " "; 
		cout << "Not yet." << endl; 
	}
	cout << endl; 
}


vector <bool> what_flags (int argc, char **argv)
{
	vector <bool> flags (3, 0); 
	if ( argv == NULL )
	{
		return flags; //empty case
	}

	int aflag = 0;
	int lflag = 0;
	int Rflag = 0; 
	//char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;
	cerr << "nothing yet \n" << endl; 
	for (unsigned i = 1; argv[i] != '\0' && (c = getopt (argc, argv, "alR")) != -1; ++i)
	{
		switch (c)
		{
			case 'a':
				aflag = 1;
				flags.at(0) = 1; 	
				break;
			case 'l':
				lflag = 1;
				flags.at(1) = 1; 
				break;
			case 'R':
				Rflag = 1; 
				flags.at(2) = 1; 
				//cvalue = optarg;
				break;
			case '?':
				//if (optopt == 'c')
				//  fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				if (isprint (optopt))
				  fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
				  fprintf (stderr,
					   "Unknown option character `\\x%x'.\n",
					   optopt);
				exit(1);//FIXME need to deal with this case a better way 
			default:
				abort ();
		}
	}

	// may have to replace cflag = %d ..cvalue = %s\n", */
	printf ("aflag = %d, lflag = %d, Rflag = %d\n", aflag, lflag, Rflag); 
	//cvalue);
	
	for (index = optind; index < argc; index++)
	printf ("Non-option argument %s\n", argv[index]);
	return flags; 
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
	
	string input; // = "ls -l -a -R"; 
	//taking input as a c++ string; 

	INPUT;  //command prompt
	
	while( input != "exit" )
	{
				//will take in parsed input
		vector <char*> inp = parse_inp(input); 
		//potential memory leak...FIXME	
				
		//point to same memory, so have to be careful later.
		char ** argv = &inp[0]; 
		unsigned argc = inp.size() -1;//argument count 
		cout << "Printing." << endl; 
		cout << "argc: " << argc << "\n" ; 
		print(argv); 	
		

		cerr << "flags: " << endl; 
		//this function checks whether/which flags passed in
		vector <bool> flags = what_flags(argc, argv); 
		
		input = "";	
		INPUT;//macro for command prompt 	
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
