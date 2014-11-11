#ifndef STATUS_H
#define STATUS_H
#include <iostream>
using namespace std; 
#include <cstdlib>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

char const * sperm( __mode_t mode) {
	static char local_buff[16] = {0};
	int i = 0;
	// user permissions
	if ((mode & S_IFDIR) == S_IFDIR) local_buff[i] = 'd';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IRUSR) == S_IRUSR) local_buff[i] = 'r';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IWUSR) == S_IWUSR) local_buff[i] = 'w';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IXUSR) == S_IXUSR) local_buff[i] = 'x';
	else local_buff[i] = '-';
	i++;
	// group permissions
	if ((mode & S_IRGRP) == S_IRGRP) local_buff[i] = 'r';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IWGRP) == S_IWGRP) local_buff[i] = 'w';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IXGRP) == S_IXGRP) local_buff[i] = 'x';
	else local_buff[i] = '-';
	i++;
	// other permissions
	if ((mode & S_IROTH) == S_IROTH) local_buff[i] = 'r';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IWOTH) == S_IWOTH) local_buff[i] = 'w';
	else local_buff[i] = '-';
	i++;
	if ((mode & S_IXOTH) == S_IXOTH) local_buff[i] = 'x';
	else local_buff[i] = '-';
	return local_buff;
}

//prints out info necessary when -l flag called
void status(char * path)
{
	//struct dirent  *dp;
	struct stat     statbuf;
	struct passwd  *pwd;
	struct group   *grp;
	struct tm      *tm;
	char            datestring[256];
	//char *dirName = const_cast<char*>(".");
        //DIR *dir = opendir(dirName);

	//...
	/* Loop through directory entries. */
	//while ((dp = readdir(dir)) != NULL) {


    /* Get entry's information. */
	//need to do error checking here! FIXME
	if ( stat( path, &statbuf ) == -1 )
	{
		perror ("stat"); 
	}
	  //stat(dp->d_name, &statbuf) == -1)
	//continue;


    /* Print out type, permissions, and number of links. */
    printf("%10.10s", sperm (statbuf.st_mode));
    cout << " " << statbuf.st_nlink; 
    //printf("%2d", reinterpret_cast<long unsigned int>(statbuf.st_nlink) );


    /* Print out owner's name if it is found using getpwuid(). */
    if ((pwd = getpwuid(statbuf.st_uid)) != NULL)
	printf(" %-8.8s", pwd->pw_name);
    else
	printf(" %-8d", statbuf.st_uid);


    /* Print out group name if it is found using getgrgid(). */
    if ((grp = getgrgid(statbuf.st_gid)) != NULL)
	printf(" %-8.8s", grp->gr_name);
    else
	printf(" %-8d", statbuf.st_gid);


    /* Print size of file. */
    //printf(" %9jd", (intmax_t)statbuf.st_size);
	printf(" %9d", static_cast<int>((intmax_t)statbuf.st_size) );
	//FIXME removed j, may need fix later

    tm = localtime(&statbuf.st_mtime);


    /* Get localized date string. */
    strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);


    printf(" %s %s\n", datestring, path);
	//}


	return ; 
}

//checks whether path is directory
bool is_dir(char *par_dir ,const char* pathname)
{
	string p = static_cast<string>(par_dir)
	+ "/" + static_cast<string>(pathname);  
	char* p2 = const_cast<char*>(p.c_str());
        struct stat info;
	//cout << endl << endl << p << endl; 
        if( stat( p2, &info ) != 0 )
        {
            printf( "cannot access %s\n", pathname );
                perror("stat");
                exit(1);
        }
        else if( info.st_mode & S_IFDIR )
        {
            //printf( "%s is a directory\n", pathname );
                return true;
                //exit(1);
        }
	//cout << pathname << " is not a directory." << endl; 
        return false;
}

bool is_file ( const char *fname  )
{
        if( access( fname, F_OK ) != -1 ) {
                //file exists
                return 1;
        }
        return 0;
        // file doesn't exist
}
/*
void file_alone( char* path, const bool& lflag )
{
	if(aflag && (static_cast<string>(direntp->d_name) ==  "." 
		|| static_cast<string>(direntp->d_name) ==  ".."))  
	{
		continue; //don't want to go in these
	}
	if( !aflag && direntp->d_name[0] == '.' )
	{
		continue; //direntp->d_name starts with '.'
	}
	if(Rflag && //!is_file(direntp->d_name) && 
		 is_dir( path, direntp->d_name ))
	{
		string dir = static_cast<string>(path)
		+"/" + static_cast
		<string>(direntp->d_name); 
		sub_dirs.push_back(dir); 
		//sub_dirs.push_back(
		//const_cast<char*> (dir.c_str()) );
		//cout << dir << endl;
		//sub_dirs.push_back(direntp->d_name);
	}
	if ( !lflag )
	{
		cout << direntp->d_name << "  ";
		continue;
	}
	else if( lflag )
	{
		status( direntp->d_name );
	}
}

*/


//this function deals with printing out contents in current
//directory. If Rflag == true, then does same recursively 
//through subdirectories
void print_dir ( char* path, const bool& aflag, 
	const bool& lflag, const bool& Rflag)
{
	//will record names of subdirectories 
	//in curr directoroy. Will call print_dir
	//on these later.
	vector <string> sub_dirs;
	char *dirName = path; //const_cast<char*>(".");
        DIR *dirp = opendir(dirName);
        dirent *direntp;
	if( Rflag )
	{
		cout << path << ":"  << endl;
	}
        while ((direntp = readdir(dirp)))
        {

		if(aflag && (static_cast<string>(direntp->d_name) ==  "." 
		|| static_cast<string>(direntp->d_name) ==  ".."))  
		{
			continue; //don't want to go in these
		}
                if( !aflag && direntp->d_name[0] == '.' )
                {
                        continue; //direntp->d_name starts with '.'
                }
		if(Rflag && //!is_file(direntp->d_name) && 
			 is_dir( path, direntp->d_name ))
		{
			string dir = static_cast<string>(path)
			+"/" + static_cast
			<string>(direntp->d_name); 
			sub_dirs.push_back(dir); 
			//sub_dirs.push_back(
			//const_cast<char*> (dir.c_str()) );
			//cout << dir << endl;
			//sub_dirs.push_back(direntp->d_name);
		}
                if ( !lflag )
                {
                        cout << direntp->d_name << "  ";
                        continue;
                }
                else if( lflag )
                {
                        status( direntp->d_name );
                }
         }
         cout << endl;
	closedir(dirp);
	for (unsigned i = 0; i < sub_dirs.size(); ++i )
	{
		//cout << sub_dirs.at(i) << " "; 
		print_dir ( 
		const_cast<char*>(sub_dirs.at(i).c_str())
		, aflag, lflag, Rflag);

	} 	
	cout << endl; 
         //closedir(dirp);
}
 

#endif
