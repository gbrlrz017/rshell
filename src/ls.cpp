#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4                                                                                                                                              
#define INPUT cout << "$ "; /*command prompt */\ 
	getline (cin,input)

#include <string>
#include <string.h>
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

//int debug_flag, compile_flag, size_in_bytes;
bool aflag, lflag, Rflag;

//prints elements in argv
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


//sets Truth values to boolean global flag indicator variables 
//will tell if a, l, or R flags passed into argv
//FIXME need to fix case(s) -alR,...
void <bool> flags (int argc, char *const* argv)
{
	vector <bool> flags (3, 0); 
	if ( argv == NULL )
	{
		return flags; //empty case
	}

	//char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;
	cerr << "nothing yet \n" << endl; 
	for (unsigned i = 1; argv[i] != '\0' && (c = getopt (argc, argv, ":alR")) != -1; ++i)
	{
		switch (c)
		{
			case 'a':
				aflag = true;
				flags.at(0) = 1; 	
				break;
			case 'l':
				lflag = true;
				flags.at(1) = 1; 
				break;
			case 'R':
				Rflag = true;
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

int main( int argc, char** argv )
{
	//cout << "Printing." << endl; 
	//cout << "argc: " << argc << "\n" ; 
	//print(reinterpret_cast<char* *> (argv));  	
	print(argv); 
	//cerr << "flags: " << endl; 
	//this function checks whether/which flags passed in
	//vector <bool> flags = what_flags(argc, argv); 
	
	/*for (vector<char *>::iterator it = inp.begin(); it != inp.end(); it++) {
delete *it;
}

	inp.clear();			
*/


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
