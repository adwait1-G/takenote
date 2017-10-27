#include <stdio.h>
#include <stdlib.h>

//newfile returns a pointer to a new file opened in write mode
FILE *newfile(char *filename)
{
	FILE *ret;
	ret = fopen(filename, "w");
	if (ret == NULL)
		return (FILE*)-1;
	else
		return ret;
}

void closefile(FILE *fp)
{
	fclose(fp);
}

//simple cat like functionality
int writetofile(FILE *fp)
{
	char c;
	while((c = getchar()) != EOF)
		putc(c, fp);
}

int writenote(char *name)
{
	FILE *fp = newfile(name);
	if(fp == (FILE*)-1) {
		fprintf(stderr, "file couldn't be opened\n");
		exit(1);
	}
	fprintf(stdout, "----File '%s' opened for output----\n", name);
	writetofile(fp);
	closefile(fp);
	fprintf(stdout, "---File '%s' closed---\n", name);
}
