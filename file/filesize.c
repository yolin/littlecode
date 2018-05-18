#include <stdio.h>
#include <unistd.h>

int filesize(const char *f)
{
	FILE *fp;
	int filesize=0;

	if(access(f, F_OK))
	{
        printf("file not found");
		return 0;
	}

	fp = fopen(f, "r");
	if(!fp)
	{
		return 0;
	}

	fseek(fp, 0, SEEK_END);
	filesize=ftell(fp);

	fclose(fp);

	return filesize;
}

int main()
{
    FILE * pFile;
    char mystring [1024];
    pFile = fopen ("/tmp/1" , "r");
    if (pFile == NULL)
        perror ("Error opening file");
    else {
            printf("----\n[");
        if ( fgets (mystring , 1025 , pFile) != NULL )
            printf("%s",mystring);
        printf("]----\n");
        fclose (pFile);
    }

    printf("size:%d\n", filesize("/tmp/x"));
    return 0;
}
