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
	//char *cvalue = NULL;
	//int index;
	int c;
	opterr = 0;

	while( (c = getopt (argc, argv, "a::l::R::")) != -1 )
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
				  fprintf (stderr, "ls: invalid option -- '%c'.\nTry 'a', 'l', 'R'\n", optopt);
				else
				  fprintf (stderr,
					   "Unknown option character `\\x%x'.\n", optopt);
				//exit(1);//FIXME need to deal with this case a better way 
			default:
				abort ();
		}
	}

	// may have to replace cflag = %d ..cvalue = %s\n", */
	printf ("aflag = %d, lflag = %d, Rflag = %d\n", aflag, lflag, Rflag); 
	//cvalue);
	
	//for (index = optind; index < argc; index++)
	//printf ("Non-option argument %s\n", argv[index]);
}



/*
 *  * This is a BARE BONES example of how to use opendir/readdir/closedir.  Notice
 *   * that there is no error checking on these functions.  You MUST add error 
 *    * checking yourself.
 *     */

int main( int argc, char** argv )
{
	//int index ; //index where flags begin
	vector<char*> files; 
	vector<char*> dirs; 
	vector<char*> others; 
	//loop checks if folders or files are passed in
	for(int i = 1; i < argc && argv[i] != NULL; ++i)
	{
		if( argv[i][0] != '-')
		{
			cout << argv[i] << " is not an option!" << endl; 
			path_other what = is_file(argv[i]); 
			if( what == file )
			{
				files.push_back( argv[i] ); 
				cout << argv[i] << " is a file!" <<endl; 
			}	
			else if (what == directory){
				dirs.push_back(argv[i]); 
				cout << argv[i] << " is a directory! (maybe)" << endl;
			}
			else
			{
				others.push_back(argv[i]); 
				cout << "other." << endl;
			}
		}	
	}
	
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
	if( others.size() != 0 || dirs.size() != 0
		 || files.size() != 0)
	{
		for(unsigned i = 0; i<files.size(); ++i)
		{
			file_alone( files.at(i), lflag ); 	
		}
		if(files.size() != 0)
		{
			//only want newline if
			//outputted files
			cout << endl; 
		}
		for(unsigned i = 0; i<dirs.size(); ++i)
		{
			if(!Rflag && files.size() > 0){
				cout << dirs.at(i) << ":" << endl; 
			}
			print_dir(dirs.at(i), aflag, lflag, Rflag); 	
		}

	}


	else
	{
		print_dir( const_cast<char*>("."), aflag, lflag, Rflag);
	}
	return 0; 
}
