#include <stdio.h>

int remove_note(char *path)
{
	return remove(path);
}

int main(int argc, char **argv)
{
	remove_note(argv[1]);
	perror("Remove file: ");
}
