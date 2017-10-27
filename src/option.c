#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern void create_nb(char *);
extern int remove_directory(char *);
extern int writenote(char *);

int
main (int argc, char **argv)
{
	int nflag = 0, dflag = 0, lflag = 0;
	char *nvalue = NULL;
	char *dvalue = NULL;
	char *lvalue = NULL;

	int index;

	int c;

	opterr = 0;
	
	char *home = getenv("HOME");
	char *dirname = "takenote";
	size_t homelen = strlen(home);
	size_t dirlen = strlen(dirname);
	dirlen += homelen;
	dirlen += 1;
	char *str = malloc(dirlen+1);
	snprintf(str, dirlen+1, "%s/%s", home, dirname);
	printf("%s\n", str);

	chdir(str);
	perror("ERROR: ");
	while((c = getopt (argc, argv, "n:d:l::")) != -1)
	{
		switch(c)
		{
			case 'n':
				nflag = 1;
				nvalue = optarg;
				break;
			case 'd':
				dflag = 1;
				dvalue = optarg;
				break;
			case 'l':
				lvalue = optarg;
				lflag = 1;
				break;
			case '?':
				if(optopt == 'n')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				return 1;
			default:
				abort ();
		}
	}
	
	printf("nflag = %d, nvalue = %s, dflag = %d, dvalue = %s, lflag = %d, lvalue = %s\n", nflag, nvalue, dflag, dvalue, lflag, lvalue);
	
	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	if(nflag == 1) {
		create_nb(nvalue);
	}
	if(nflag == 0 && dflag == 0 && lflag == 0)
	{
		writenote(argv[2]);
	}
	if(lflag == 1) {
		//if(nvalue == NULL)
		//	list notebooks
		//else
		//	list notes in notebook
	}
	if(dflag == 1) {
		remove_directory(dvalue);
	}
}
