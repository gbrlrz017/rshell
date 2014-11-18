#ifndef HW2_H
#define HW2_H

#include <iostream>
#include <string.h>
#include <istream>
#include <cstring>
#include <unistd.h>
using namespace std;
#include <cstdio>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <errno.h>
#include <cstdlib>
#include <vector>
#include <stdlib.h>
#include <string>

//REMEMBER to declare input2
//since alters it!!!
vector<char*> parse( string  x, string  delimiter)
{
	//std::string s = "scott>=tiger";
	//std::string delim = ">=";
	vector <char*> tok; 	
	size_t pos = 0;
	std::string token;
	while ((pos = x.find(delimiter)) != std::string::npos) {
    		token = x.substr(0, pos) + '\0';
		tok.resize(tok.size()+1);
		tok.at(tok.size()-1) = (char*)malloc(token.size()+1);
		strcpy(tok.at(tok.size()-1), const_cast<char*>(token.c_str()) );
    		x.erase(0, pos + delimiter.length());
	}
	x = x + '\0';
	tok.resize(tok.size()+1);
	tok.at(tok.size()-1) = (char*)malloc(token.size()+1);
	strcpy(tok.at(tok.size()-1), const_cast<char*>(x.c_str()) );

	//tok.push_back(const_cast<char*>(t.c_str())); 
	return tok; 
}



/*
int main()
{
	//char * pipe[20]; 
	//pipe[0] = "./a.out";
	//pipe[1] = "cat";
	//pipe[2] = "ls.cpp";
	//pipe[3] = "|";
	//pipe[4] =  "tr";
	//pipe[5] = "a-z";
	//pipe[6] =  "A-Z"; 
	vector<char*> tok = parse( "...||ha | z||zz |||| .", "||");
	for(int i =0; i< tok.size(); ++i)
	{
		cout << tok.at(i) << " "; 
	}
	cout << endl;
	//system("./a.out cat ls.cpp | tr a-z A-z" );
	//if(-1 == execvp(pipe[0], pipe)) perror("execvp") ;
	return 0;
}
*/
#endif
