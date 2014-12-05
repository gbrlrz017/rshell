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
#include <signal.h>

//modifies input to remove comments
void rm_comment(string & input)
{
	unsigned i = 0;
	for(; i < input.size(); i++ )
	{
		if (input.at(i) == '#' ){
			break; //get out of the for loop
		}
	}
	
	for(; i < input.size(); i++ )
	{
		input.at(i) = ' ';	
	}
	 
}



//returns true if 1 '&&' is found
const bool is_and (const string & input )
{
	if ( input.find( "&&", 0 ) != string::npos )
	{
		return true; 
	}
	return false; 
}

const bool is_or (const string & input )
{
	if ( input.find( "||", 0 ) != string::npos )
	{
		return true; 
	}
	return false; 
}


//Counts number of arguments 
unsigned count_args( const string & input ) {
	if (input.size() == 0 )
	{
		return 0; 
	}

	unsigned count = 1; 
	
	for(unsigned i = 0; i < input.size(); ++i)
	{
		if ( input.at(i) == '&' || input.at(i) == '|' )
		{
			i+=1; // first '&' or '|' will be followed by another
			count +=1; 
		}

		if ( input.at(i) == ';' && i+1 != input.size() )//can have command: pwd;  
		{
			count +=1; 
		}
	}
	return count; 
}

unsigned count_args_space( const char input[] ) {
	if ( strlen(input) == 0 ||  strlen(input) == 1 )
	{
		return 3; 
	}

	unsigned count = 1; 
	
	for(unsigned i = 0; input[i] != '\0';  ++i)
	{
		if ( input[i] == ' '  )
		{
			i+=1; 
			count +=1; 
			//can have multiple whitespaes: ~ "       "
			while( input[i] != '\0' && input[i] == ' ' )
			{
				i+=1; 
			}
		}

	}
	return count; 
}

//vector<string> 
vector <char*> path()
{
	char *p = getenv("PATH");	
	//cout << "PATHS(s): " << p << endl;
	if(p == NULL)
	{
		cerr << "error: PATH is null\n";
		cerr << "exiting program....\n";
		exit(1);
	}
	
	//tokenizing PATH at ':'
	//using paths vector to store paths
	//vector <string> 
	vector <char*> paths;
	paths.resize(paths.size()+1); 
	paths.at(0) = new char[strlen(".") +1]; 
	strcpy( paths.at(0) , "."); 

	char * tmp;
	tmp = strtok(p,":");
	if(tmp != NULL)
	{
		paths.resize(paths.size()+1); 
		paths.at(1) = new char[strlen(tmp) +1]; 
		strcpy( paths.at(1) , tmp ); //copying first token 
		//paths.push_back( string(tmp) );
	}

	//further parses with connectors as delims
	while (tmp != NULL)
	{
		//argc +=1; // argument count increases. 
		tmp = strtok (NULL,":");  
		if(tmp != NULL){
			paths.resize(paths.size()+1); 
			paths.at(paths.size()-1) = new char[strlen(tmp) +1];
			strcpy(paths.at(paths.size()-1), tmp);
			//paths.at(paths.size()-1) = tmp; 
			// copying tokens into argv one at a time 
			//paths.push_back( string(tmp) );
		}
	}
/*
	for(unsigned i = 0; i < paths.size(); ++i)
	{
		cout << paths.at(i) << "   ";
	}
	cout << endl;
*/
	return paths;
}

//change directory
void cd(char ** argv)
{
	unsigned argc = 0;
	for(; argv[argc]!= NULL; argc++);//counts args
	if(argc <= unsigned(1))
	{
		cerr << "error: too few arguments: expecting \"cd directory_name\"\n";
		//exit(1);	
	}
	else if(argc > unsigned(2))
	{
		cerr << "error: too many arguments: expecting \"\
			cd directory_name\"\n";
		//exit(1);	
	}
	if( chdir(argv[1])==-1)
	{
		cerr << "bash: cd: " << argv[1] << \
		": No such file or derectory\n";
		perror("chdir");
		exit(1);
	}
	//at this point, chdir changed directory successfully.
}

enum par_child{neither, parent, child}; 
par_child p_c; 

void sig_handler(int signum)
{
    	//printf("Received signal %d\n", signum);
        if(signum == SIGINT)
        {
		//if(p_c ==neither) cerr << "neither\n";
		//if( p_c == parent)
		//{
			//cout << "parent" << endl;
			//kill(0, SIGINT);
		return;
		//}
                //cout << "child" << endl; 
		//exit(1); 
                //cout << "c\n";
        //SIGINT SIGQUIT(\) SIGTSTP(Z)  
        }
        else if(signum == SIGQUIT)
        {
                cout << "c\n";
        //SIGINT SIGQUIT(\) SIGTSTP(Z)  
        }
        else if(signum == SIGTSTP)
        {
                cout << "c\n";
        //SIGINT SIGQUIT(\) SIGTSTP(Z)  
        }
}

//needs to be in child scope 
//need to store paths each time
//b/c what if change directories (former dir paths stored ow) 


vector<char*> paths = path();

int main()
{
	if(signal(SIGINT, sig_handler)==SIG_ERR)
	{
		perror("signal");
	}
	//signal(SIGQUIT, sig_parent);
	//signal(SIGTSTP, sig_parent);


    string input; 
	    //taking input as a c++ string; will convert to c_str later

char * cwd = get_current_dir_name();
	if(cwd == NULL){ perror("get_current_dir_name"); }
    cout << cwd << " $ "; //command prompt
    getline (cin,input);

while ( input != "exit" ) //bug if enters: "     exit" ->anything with exit and spaces
{

	//cout << "getenv (while loop): " << getenv("PATH") << endl;
	//print_paths();
	//removing comments
	rm_comment (input); 


    //these will be the arguments to my shell after parsing
    	unsigned arg_count = count_args(input);  	
	vector <char**> argv; 
	argv.resize( arg_count ); 

    	char * tmp; //cstring to not deal with memory management for now
	int inp_sz = input.size()+1;
    	char* input2 = new char[inp_sz]; //will take copy of input from std::string input
    	strcpy(input2, input.c_str() );
	
	//stores strings of diff command/argument groups . Parses with connectors as delims	
	vector <char*> inp;
	inp.resize(arg_count+1); 
	
	//loop to get substrings of input with "&&||;" as delimiters
	int argc = 0 ; // no arguments (yet) 
	tmp = strtok(input2,"&&||;"); 
	
	if(tmp != NULL)
	{
		inp.at(0) = new char[strlen(tmp) +1]; 
		strcpy( inp.at(0) , tmp ); //copying first token 
	}

	//further parses with connectors as delims
	while (tmp != NULL)
	{
		argc +=1; // argument count increases. 
		tmp = strtok (NULL,"&&||;");  
		if(tmp != NULL){
			inp.at(argc) = new char[strlen(tmp) +1]; 
			inp.at(argc) = tmp; // copying tokens into argv one at a time 
		}
	}

	//here we have a vector of char** with each element of argv (the vector)
	//containing one commands with parameters for execvp
	for(unsigned i = 0; i < arg_count; ++i)
	{
		int argc = 0 ; // no arguments (yet) 
		tmp = strtok(inp.at(i)," ") ; 
		if(tmp != NULL){
			argv.at(i) = new char* [ count_args_space(inp.at(i) ) + 3 ];
			argv.at(i)[argc] = new char[strlen(tmp) +4]; 
			strcpy( (argv.at(i)[argc] ) , tmp ); //copying first token 
		}
		while (tmp != NULL)
		{
			if(tmp != NULL){
				argc +=1; // argument count increases. 
				tmp = strtok (NULL," ");  
				argv.at(i)[argc] = tmp; // copying tokens into argv one at a time 
			} 

		}
	}



    //beginning fork, execpv processes
    //may need to creat multiple forks to run input with connectors

	//tells us if have && or ||
	const bool AND = is_and(input); 
	const bool OR = is_or(input); 
	
	//execute multiple commands through for loop (similar to lab02)
	for(unsigned i = 0; i < argv.size(); ++i )
	{ 
		if( strcmp(argv.at(i)[0], "cd") == 0)
		{
			cd(argv.at(i));
			continue;
		} 
		int status; 
		int pid=vfork(); //stores child's pid .. will use for connector cases in parent!
		if(pid == -1)
		{
			perror("There was an error with fork(). Go back and check. " ); 
			exit(1); 
		}
		//child process
		if (pid==0) {
			p_c = child;
			 
			//*
  			if (kill(0, SIGINT) == -1)
			{
				perror("kill");
			}
		//	*/
			//signal(SIGINT, sig_child);
			//signal(SIGQUIT, sig_child);
			//signal(SIGTSTP, sig_parent);
		
			//if(-1 == execvp(argv.at(i)[0] ,  argv.at(i) )  )
			//
			
			for(unsigned j=0; j<paths.size(); ++j)
			{
				string p = string(paths.at(j))+"/"+string(argv.at(i)[0]);
				char *p2 = const_cast<char*>(p.c_str());
				execv(p2, argv.at(i)); 
			}
			
			perror("execv");
			exit(1); //avoid zombies    
		}
		
		//pid now > 0 so we are in parent process. 
		else{
			//vector<char*> paths = path(); 
			p_c = parent;
			if( wait(&status) == -1 )
			{
				perror("Error: wait() did not wait!! Not good: Check Code in parent process...");
			}

			if (status == 0 ) //OR, and first command did not fail so do not execute next cmd
			{
				if ( OR ) 
				{
					//must only execute once so exit(1)
					exit(1); // no more looping!!
				}
			}

			if ( status != 0) //means child process failed 
			{
				if ( AND ) 
				{
					exit(1); // c1 in "c1 && ..." failed so done
				}	
			}			
			//no exit so continue loop as necesary. 
		}
	
	}
	
	char * cwd = get_current_dir_name();
	if(cwd == NULL){ perror("get_current_dir_name"); }
    cout << cwd  << " $ "; //command prompt
    getline (cin,input);



}





	return 0; 
}







