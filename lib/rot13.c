// Lucas Barbosa
// 24/03/17
// Basic rotate 13 cypher

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char encode (char letter);
void testEncode(void);
char* rot13_encoder(char *sentence, int sizeOfString);

int main (int argc, char **argv) {
 
   testEncode();
   
   return EXIT_SUCCESS;
 
}

char encode(char letter) {
   
   char outputLetter   = '\0';
   char inputKeys[52]  = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
   char outputKeys[52] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
   int inputKeyArraySize = sizeof(inputKeys)/sizeof(inputKeys[0]);
   int asciiKey = (int)letter;
   
   if (((asciiKey >= 65) && (asciiKey <= 90)) || ((asciiKey >= 97) && (asciiKey <= 122))) { 
      for (int i = 0; i < inputKeyArraySize; i++) {
         int CURRLETTER = i;
         if (letter == inputKeys[CURRLETTER]) {
            outputLetter = outputKeys[CURRLETTER];
         }   
      }
   } else {
      outputLetter = letter;
   }
   
   return outputLetter;
   
}

char* rot13_encoder(char *sentence, int sizeOfString) {
   char *encodedString = (char *)malloc(sizeof(encodedString + 1));
   for (int i = 0; i < sizeOfString; i++) {
      int CURRLETTER = i;
      encodedString[CURRLETTER] = encode(sentence[CURRLETTER]);
   }
   return encodedString;
}

void testEncode(void) {
   char A = 'A'; char B = 'B'; char C = 'C';
   char D = 'D'; char z = 'z'; char w = 'w';
   
   assert(encode(A) == 'N');
   assert(encode(B) == 'O');
   assert(encode(C) == 'P');
   assert(encode(D) == 'Q');
   assert(encode(z) == 'm');
   assert(encode(w) == 'j');
   /// Special case
   assert(encode('[') == '[');
   
   printf("All unit tests were successful.\n");
   
}
   