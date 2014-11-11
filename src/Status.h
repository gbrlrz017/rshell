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
	// directory or symbolic link 
	if ((mode & S_IFDIR) == S_IFDIR &&
	(mode & S_IFLNK)== S_IFLNK){
		local_buff[i] = 'l';
	}
	else if ((mode & S_IFDIR) == S_IFDIR) local_buff[i] = 'd';
	else if ((mode & S_IFLNK) == S_IFLNK){
		local_buff[i] = 'l';
	}
	else local_buff[i] = '-';
	i++;
	// user permissions
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
void status(char* path, 
	char* par_dir = const_cast<char*>("./"))
{
	string p = "./" + static_cast<string>(par_dir)
	+ "/" + static_cast<string>(path);  
	char* p2 = const_cast<char*>(p.c_str());
 
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
	if ( lstat( p2, &statbuf ) == -1 )
	{
		perror ("lstat"); 
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
    //strftime(datestring, sizeof(datestring), nl_langinfo(D_T_FMT), tm);
    strftime(datestring, sizeof(datestring), "%b %d %R", tm);

	if ((statbuf.st_mode & S_IFLNK) == S_IFLNK){

    char *linkname;
    ssize_t r;

      linkname = new char [statbuf.st_size +12];//malloc(statbuf.st_size + 12);
    if (linkname == NULL) {
        fprintf(stderr, "insufficient memory\n");
        exit(1);
    }

   r = readlink(p2, linkname, statbuf.st_size + 1);

   if (r < 0) {
        perror("lstat");
        exit(1);
    }

   if (r > statbuf.st_size) {
        fprintf(stderr, "symlink increased in size "
                        "between lstat() and readlink()\n");
        exit(1);
    }

   linkname[statbuf.st_size] = '\0';
		printf(" %s %s -> %s\n", datestring, path, linkname);
		delete [] linkname;
		return; 
	}
	printf(" %s %s\n", datestring, path);
	return ; 
}

//checks whether path is directory
bool is_dir(char *par_dir ,const char* pathname)
{
	string p = static_cast<string>(par_dir)
	+ "/" + static_cast<string>(pathname);  
	char* p2 = const_cast<char*>(p.c_str());
        struct stat info;
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

enum path_other {file, directory, other};
//checks whether path is file
path_other is_file(const char* pathname)
{
        struct stat info;
        if( stat( pathname, &info ) != 0 )
        {
            printf( "ls: cannot access %s -- ", pathname );
                perror("stat");
		return other;
                
                //exit(1);
        }
        else if( info.st_mode & S_IFREG )
        {
            //printf( "%s is a directory\n", pathname );
                return file;
                //exit(1);
        }
	//cout << pathname << " is not a directory." << endl; 
        return directory;
}

//function to print out files passed into 
//ls as arguments
void file_alone( char* path, const bool& lflag )
{
	if ( !lflag )
	{
		cout <<  path << "  ";
	}
	else if( lflag )
	{
		status( path );
	}
}



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
		if(Rflag && is_dir( path, direntp->d_name ))
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
                        status(direntp->d_name, path );
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
         //closedir(dirp);
}
 

#endif
