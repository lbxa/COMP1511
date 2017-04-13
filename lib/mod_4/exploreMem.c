// Lucas Barbosa
// 22.03.17
// Memory exploration

#include <stdio.h>
#include <stdlib.h>
 
long add (int x, int y);
 
int main(int argc, const char * argv[]) {
 
   int x;
   int y;
   long total;
 
   x = 40;
   y = 2;
 
   total = add (x, y);
 
   printf("the sum of %d and %d is %ld\n", x, y, total);
   printf("\n\n\n\n");
 
   char c ='a';
 
   unsigned long ul       = 0;
   unsigned int ui        = 1;
   unsigned long long ull = 2;
   unsigned short us      = 3;
   
   // printf() table formating with "%-[CELLWIDTH]"
   
   printf("The Stack\n\n");
   
   printf("%-20s%-20s%-20s\n", "[Unsigned Type]", "Memory (bytes)", 
   "Stack location");
   printf("%-20s%-20ld0x%-20p\n", "Long", sizeof(ul), &ul);
   printf("%-20s%-20ld0x%-20p\n", "Int", sizeof(ui), &ui);
   printf("%-20s%-20ld0x%-20p\n", "Long Long", sizeof(ull), &ull);
   printf("%-20s%-20ld0x%-20p\n", "Short", sizeof(us), & us);
   printf("\n");
   
   signed long sl       = 4;
   signed int si        = 5;
   signed long long sll = 6;
   signed short ss      = 7;
   
   printf("%-20s%-20s%-20s\n", "[Signed Type]", "Memory (bytes)", 
   "Stack location");
   printf("%-20s%-20ld0x%-20p\n", "Long", sizeof(sl), &sl);
   printf("%-20s%-20ld0x%-20p\n", "Int", sizeof(si), &si);
   printf("%-20s%-20ld0x%-20p\n", "Long Long", sizeof(sll), &sll);
   printf("%-20s%-20ld0x%-20p\n", "Short", sizeof(ss), & ss);
   printf("\n");
 
   long l       = 8;
   int i        = 9;
   long long ll = 10;
   short s      = 11;
   
   printf("%-20s%-20s%-20s\n", "[Generic Types]", "Memory (bytes)", 
   "Stack location");
   printf("%-20s%-20ld0x%-20p\n", "Long", sizeof(l), &l);
   printf("%-20s%-20ld0x%-20p\n", "Int", sizeof(i), &i);
   printf("%-20s%-20ld0x%-20p\n", "Long Long", sizeof(ll), &ll);
   printf("%-20s%-20ld0x%-20p\n", "Short", sizeof(s), & s);
   printf("\n");
 
   float f = 3.1;
   double d = 3.14;
 
   // add them all together just to make use of them so the compiler
   // doesn't grumble that they are unused in the program
 
   double grandTotal;
   grandTotal =  c +
                 ul + ui + ull + us +
                 sl + si + sll + ss +
                  l +  i +  ll +  s +
                  f + d;
 
   
   printf("\n\n\n\n");
   printf ("all these things added together make %f\n", grandTotal);
 
   return EXIT_SUCCESS;
}
 
long add (int x, int y) {
   long answer;
   answer = x + y;
 
   return answer;
}