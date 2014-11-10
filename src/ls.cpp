#define FLAG_a 1
#define FLAG_l 2
#define FLAG_R 4                                                                                                                                              
#define INPUT cout << "$ "; /*command prompt */\ 
	getline (cin,input)
#include "Status.h"
#include <string>
#include <string.h>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string.h>
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
void flags (int argc, char *const* argv)
{
	if ( argc <= 1  )
	{
		return; //can't be any flags 
	}

	//char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;
	for (unsigned i = 1; argv[i] != '\0' && (c = getopt (argc, argv, ":alR")) != -1; ++i)
	{
		switch (c)
		{
			case 'a':
				aflag = true;
				break;
			case 'l':
				lflag = true;
				break;
			case 'R':
				Rflag = true;
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
}








/*
 *  * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
 *   * that there is no error checking on these functions.  You MUST add error 
 *    * checking yourself.
 *     */

int main( int argc, char** argv )
{
	//cout << "argc: " << argc << "\n" ; 
	//print(argv); 
	
	//checks what options passed in
	//sets Truthness of global indicator variables 
	flags(argc, argv); 	
	/*for (vector<char *>::iterator it = inp.begin(); it != inp.end(); it++) {
delete *it;
}

	inp.clear();			
*/


/*	
	char *dirName = const_cast<char*>(".");
	DIR *dirp = opendir(dirName);
	dirent *direntp;
	while ((direntp = readdir(dirp)))
	{

		if( !aflag && direntp->d_name[0] == '.' )
		{
			continue; //direntp->d_name starts with '.'
		}
		if ( !lflag && !Rflag )
		{
			cout << direntp->d_name << "  ";  
			continue; 
		}
		else if( lflag )
		{
			//need conditional for R flag
			status( direntp->d_name ); 
		}
	}
	cout << endl; 
	closedir(dirp);
*/
	print_dir( const_cast<char*>("."), aflag, lflag, Rflag);
	return 0; 
}
