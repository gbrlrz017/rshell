#ifndef STATUS_H
#define STATUS_H
#include <iostream>
using namespace std; 
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
#endif
