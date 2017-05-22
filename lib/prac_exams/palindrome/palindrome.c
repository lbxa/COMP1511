//palindrome.c
//Unofficial Practice Practical Exam
//Created by Michael Simarta
//Your Name Here
     
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
     
#define FALSE 0
#define TRUE 1
    
void testCase(void);
     
int palindrome (char *string);
     
int main (int argc, char *argv[]) {
  testCase();
  return EXIT_SUCCESS;
}
     
int palindrome (char *string) {
  int length  = sizeof(string);
  char reverseString[length + 1];  // 1 for the NULLBYTE
  int counter = 0;
  int index   = length;
  int returnStatus = 0;

  if ((string == NULL) || (string[0] == ' ')) {
    return TRUE;
  }

  while (index >= 0) {

    if ((reverseString[index] >= 'a') && (reverseString[index] <= 'z')){
      reverseString[counter] = string[index];
    }
    
    index--;
    counter++;
  }
 
  if (reverseString == string) {
    return TRUE;
  } else {
    return FALSE;
  }
   
} 

     
void testCase(void) {
  assert (palindrome("kayak.") == TRUE);
  assert (palindrome("puzzlequest") == FALSE);
  assert (palindrome("is addo odd as i?") == TRUE);
  assert (palindrome("canoe") == FALSE);
  assert (palindrome("eevee") == TRUE);
  assert (palindrome("awesome") == FALSE);
  //ADD MORE TESTS
  assert (palindrome(" ") == TRUE);
     
  printf ("All tests passed, you are Awesome!\n");
}
