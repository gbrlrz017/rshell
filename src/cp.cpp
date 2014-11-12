#include <iostream>
#include "Timer.h"
#include <cstdio>
#include <fstream> 
#include <istream>
#include <unistd.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std; 


#include <sys/types.h>
#include <sys/stat.h>

void is_dir( const char* pathname)
{
	struct stat info;

	if( stat( pathname, &info ) != 0 )
	{
	    printf( "cannot access %s\n", pathname );
		perror("stat"); 
		exit(1);
	}
	else if( info.st_mode & S_IFDIR )  
	{
	    printf( "%s is a directory\n", pathname );
		exit(1);  
	}
	else
	{
	    //printf( "%s is no directory\n", pathname );
	}
}

bool file_exists ( const char *fname  )
{
	if( access( fname, F_OK ) != -1 ) {
		//file exists
		return 1; 
	} 
	
	 return 0; 
	 // file doesn't exist
	
}

void rem( const char* filename ) //removes file
{
	if ( !file_exists( filename ) )
	{
		return; //file does not exist 
	}
	
	if ( remove(filename) != 0 ){
		perror("Error removing file."); 
	}
} 


void copy1 ( ifstream &infile, ofstream & outfile, char** argv)
{
	char tmp; 
	infile.get( tmp ); 
	while ( infile.good() ) //checks whether we have reached end of file
	{
		outfile.put( tmp ); 
		infile.get(tmp); 
	}
	chmod(argv[2], S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IWGRP|S_IWOTH|S_IXOTH);	
	
} 



void copy2 ( char ** argv )
{
	int fdi=open(argv[1], O_RDONLY);
	int fdo=open(argv[2],  O_RDWR | O_CREAT , O_RDWR );
	chmod(argv[2], S_IRWXU); //|S_IRGRP|S_IXGRP|S_IROTH);	
	if ((fdi == -1) || (fdo == -1)) 
	{
		cout << "ERROR." << endl;
		cout << "fdo: " << fdo << " fdi: " << fdi << endl;
		perror("open");
		exit(1);
	}

	char buf[1];
	memset(buf,0,sizeof(buf));
	while (read(fdi, buf, 1))
	{
		//cout << "reading, writing.." << endl;
		write(fdo, buf, 1);
		//cout << "sizeof(buf): " << sizeof(buf) << endl;
	}
	close(fdi);
	close(fdo);
	return ;	
}






void copy3 ( char ** argv)
{
	int fdi=open(argv[1], O_RDONLY);
	int fdo=open(argv[2], O_RDWR | O_CREAT , O_RDWR);
	//int num;

	chmod(argv[2], S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH);	
	if ((fdi == -1) || (fdo == -1)) 
	{
		perror("open");
		exit(1);
	}

	char buf[sizeof(BUFSIZ)];
	memset(buf, 0, sizeof(buf));
	while ( read(fdi, buf, sizeof(buf)) != 0)
	{
		write(fdo, buf, sizeof(buf));
		//cout << "sizeof(buf): " << sizeof(buf) << endl;
	}
	
	close(fdi);
	close(fdo);
}





int main(int argc, char** argv)
{
	ifstream infile; 
	ofstream outfile; 
	
	//cout << "argc: " << argc << endl; 
	if( argc != 3 && argc != 4 )
	{
		cerr << "Error: Invalid number of arguments \n"; 
		cerr << "Expecting the name of two files, and the optional flag, \"-all\".\n"; 
		return 1; 
	}	
	is_dir(argv[1]); //checks if first file is directory
	//is_dir(argv[2]); //checks if second file is directory
	//prints out contents in argv	
	//for (unsigned i = 0; argv[i] != NULL; ++i )
	//{
	//	printf( argv[i] ); 
	//	cout << " "; 
	//}
	//cout << endl; 

	string inp_file = argv[1]; 
	infile.open( inp_file.c_str() ); 

	if( infile.fail() )
	{
		cout << "Error opening " << inp_file << endl; 
		return 1; 
	}	

	string out_file = argv[2]; 

	if ( file_exists ( out_file.c_str() ) )
	{
		cout << "Error: " << out_file << " already exists." << endl; 
		cerr << "Enter a differnt file to copy into...\n"; 
		return 1; 
	}

	
	outfile.open ( out_file.c_str() ); 
	if( outfile.fail() )
	{
		cout << "Error opening " << out_file << endl; 
		return 1; 
	}

	string flag = "-all"; 	
	if( argc == 4 ) // && argv[3] == flag.c_str() )
	{
		double wc_time, usr_time, sys_time; //record three types of time
		//cp1's time
		Timer cp1; //will keep tabs on copy1's time. 
		cp1.start(); 	
		copy1 (infile, outfile , argv); 
		cp1.elapsedTime( wc_time, usr_time, sys_time ); //will record times on these variables appropriately	
		cout << ".get/.put (one char at a time) method: \n" << "Wall Clock: " << wc_time << endl
			<< "User Time: " << usr_time << endl 
			<< "System Time: " << sys_time << endl; 
		//system("rm -rf out.txt"); 
		rem(argv[2]); //removing file b/c will create again
		cout << endl; 

		//cp2's time
		Timer cp2; //will keep tabs on copy1's time. 
		cp2.start(); 	
		copy2 ( argv ); 
		cp2.elapsedTime( wc_time, usr_time, sys_time ); //will record times on these variables appropriately	
		cout << "read()/write() (one character at a time): " << endl; 
		cout << "Wall Clock: " << wc_time << endl
			<< "User Time: " << usr_time << endl 
			<< "System Time: " << sys_time << endl; 
		rem(argv[2]); //removing file b/c will create again 
		cout << endl; 
	
		//cp3's time
		Timer cp3; //will keep tabs on copy1's time. 
		cp3.start(); 	
		copy3 ( argv ); 
		cp3.elapsedTime( wc_time, usr_time, sys_time ); //will record times on these variables appropriately	
		cout << "read()/write() (one buffer at a time): " << endl; 
		cout << "Wall Clock: " << wc_time << endl
			<< "User Time: " << usr_time << endl 
			<< "System Time: " << sys_time << endl; 
	}

	if( argc == 3 ) // no flag
	{
		copy1 (infile, outfile , argv); 
		//this is the fstest method 
	}	

	infile.close(); 
	outfile.close(); 


	/*
	Timer t;
	double eTime;
	t.start();
	for (int i=0, j; i<1000000000; i++)
	 j++;
	t.elapsedUserTime(eTime);
	cout << eTime << endl;	 
	*/

	return 0; 

}
