#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void print_nb();
//structure to store notebook info
typedef struct nb_t
{
	char *dir_name;
	char *start_date;
} nb_t;

//function to create a new notebook
nb_t *new_nb(char *name, char *date)
{
	FILE *outfile;
	nb_t *create;
	create = (nb_t *)malloc(sizeof(nb_t));
	create->dir_name = name;
	create->start_date = date;
	outfile = fopen("nb.log", "a");
	fwrite(&create, sizeof(nb_t), 1, outfile);
}

void create_nb(char *name)
{
	time_t curr_time = time(NULL);
	char *time_str = ctime(&curr_time);
	new_nb(name, time_str);
	mkdir(name, 0777);
	//print_nb();
}

void print_nb()
{
	char *name;
	FILE *fp;
	nb_t inp;
	fp = fopen("nb.log", "r");
	if(fp == NULL)
		fprintf(stderr, "Coudln't open file");
	else {
		fread(&inp, sizeof(nb_t), 1, fp);
		//printf(inp.dir_name);
	}
}
