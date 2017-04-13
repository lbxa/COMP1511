#include <stdio.h>
int main() {   
   FILE *q = fopen("quine.c", "r");
   char fq[72];
   while(!feof(q)){
      fgets(fq, 72, q);
      puts(fq);
   }
   fclose(q);
   
   return 0;
}