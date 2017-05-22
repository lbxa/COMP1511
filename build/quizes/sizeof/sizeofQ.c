    // quiz A
    // predict what will be printed by each line and then run the program to confirm

#include <stdio.h>
#include <stdlib.h>

void quizA (void);
     
     
int main (int argc, char *argv[]) {
  
   quizA ();
   
   printf ("quiz done!\n");
   return EXIT_SUCCESS;
}
     
void quizA (void) {
    
   printf ("size of quiz\n\n");
     
       char sequence = 'a';
     
       int x;
       long int y;
       long yy;
       unsigned int ux;
       long long z;
       unsigned long long zu;
       int *p;
       char c;
       char *message = "Rise like a pheonix";
     
       printf ("\nQuiz A\n");
       printf ("%c) %u   \t", sequence++, sizeof (x));
       printf ("%c) %u   \t", sequence++, sizeof (y));
       printf ("%c) %u   \t", sequence++, sizeof (yy));
       printf ("%c) %u\n"   , sequence++, sizeof (ux));
     
       printf ("%c) %u   \t", sequence++, sizeof (z));
       printf ("%c) %u   \t", sequence++, sizeof (zu));
       printf ("%c) %u   \t", sequence++, sizeof (p));
       printf ("%c) %u\n"   , sequence++, sizeof (c));
     
       printf ("%c) %u   \t", sequence++, sizeof (message));
       printf ("%c) %u   \t", sequence++, sizeof (*message));
       printf ("%c) %u   \t", sequence++, sizeof (*p));
       printf ("%c) %u\n"   , sequence++, sizeof (sequence));
     
       printf ("%c) %u   \t", sequence++, sizeof (&c));
       printf ("%c) %u   \t", sequence++, sizeof (&x));
       printf ("%c) %u   \t", sequence++, sizeof (&zu));
       printf ("%c) %u\n"   , sequence++, sizeof (&p));
}
