#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
 
//https://read01.com/LdkEKJ.html
int main(void)
{
   int i;
   for(i=0; i<2; i++){
      fork();
      printf("-");
   }
 
   wait(NULL);
   wait(NULL);
 
   return 0;
}
