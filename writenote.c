#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<fcntl.h>
#include<unistd.h>


//newfile returns a pointer to a new file opened in write mode
FILE *newnote(char *notename)
{
	FILE *ret;
	ret = fopen(notename, "w");
	if (ret == NULL)
		return (FILE*)-1;
	else
		return ret;
}

//closenote closes the file.
void closenote(FILE *fp)
{
	fclose(fp);
}

//writetonote writes into the file.
int writetonote(FILE *fp)
{
	char c;
	while((c = getchar()) != EOF)
		putc(c, fp);
}
//addtonote opens a file in append mode and returns that file pointer.
FILE  *addtonote(char *notename)
{
	FILE *fp;	
	fp = fopen(notename , "a");
	return fp;
}
//fileexists checks if a note with a given name exists or not.It returns 0 if file exists and returns -1 if file doesnt exist.
int noteexists(char *notename)
{
	int ret;
	ret = access(notename , F_OK);
	return ret;
}
//Where everything happens
int main(int argc, char **argv)
{
	int nflag = 0 , aflag = 0;
	char *nvalue = NULL;
	char *avalue = NULL;
	
	int index;
	int c;
		
	opterr = 0;
	while((c = getopt(argc , argv , "n:a:")) != -1)
	{
		switch(c) 
		{
			case 'n':
				nflag = 1;
				nvalue = optarg;
				break;
			case 'a':
				aflag = 1;
				avalue = optarg;
				break;
			case '?':
				if(optopt =='n')
					fprintf(stderr , "Option -%c requires an argument.\n",optopt);
				else if(isprint(optopt))
					fprintf(stderr , "Unknown option '-%c' .\n",optopt);
				else 
					 fprintf(stderr , "Unknown option character '\\x%x .\n",optopt);

		}
	}

//	for(index = optind; index < argc; index++ )
//		printf("Non-option argument %s\n",argv[index]);

	if(nflag == 1 && aflag == 1)		//If both the options are given in the cmdline , an error statement.
	{
		fprintf(stderr , "Can open only one note at a time on the terminal\n");
		exit(1);
	}
	else if(nflag == 0 && aflag == 0)	//When no options are given in the commandline .
	{
		fprintf(stderr , "Put in some options and required arguments\n");
		exit(1);
	}
	else if(nflag == 1 && aflag == 0)	// the '-n' option is given .
	{
		FILE *fp;
		fp = newnote(nvalue);
		fprintf(stdout , "---A new note '%s' opened for input---\n",nvalue);
		writetonote(fp);
		closenote(fp);
		fprintf(stdout , "---Note '%s' saved and closed---\n",nvalue);
	}
	else if(aflag == 1 && nflag == 0)	//The '-a' option is given.
	{
		int fe ; //fe is the return value of fileexists() routine.
		FILE *fp;
		fe = noteexists(avalue);
		if(fe == 0)			//If the note exists , the note is opened in append mode.
		{
			fp = addtonote(avalue);
		}
		else if(fe == -1)		//If the note doesn't exist , a new note with the given name is created .
		{
			fprintf(stdout , "Note with name  '%s' doesn't exist\n",avalue);
			fprintf(stdout , "Creating a new note with name :%s\n",avalue);
			fp = newnote(avalue);
		}
		fprintf(stdout , "-----Ready for appending or writing----\n");
		writetonote(fp);
		closenote(fp);
		fprintf(stdout , "----Note '%s' saved and closed----\n",avalue);
	}
	return 0;

}









