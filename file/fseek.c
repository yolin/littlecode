#include <stdio.h>
#include <unistd.h>
#include <string.h>

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
    pFile = fopen ("./data" , "r");
    if (pFile == NULL)
        perror ("Error opening file");
    else {

        int size=filesize("./data");
        printf("-->[Yolin:%s:%d:%s]size[%d]\n", __FILE__, __LINE__, __FUNCTION__,size);

        rewind(pFile);
        fseek(pFile,0,SEEK_SET);

        while(ftell(pFile)<size)
        {
            printf("position %ld\n",ftell(pFile));
            fgets(mystring,1000,pFile);

            printf("%s",mystring);
            printf("length[%ld]\n", strlen(mystring));

            // needn't do this
            /* fseek(pFile, strlen(mystring),SEEK_CUR); */
            printf("current - %ld\n",ftell(pFile));    

            /* fseek(pFile,0,SEEK_END); */
            /* printf("end - %ld\n",ftell(pFile)); */ 
        }

        fclose(pFile);
    }

    return 0;
}
