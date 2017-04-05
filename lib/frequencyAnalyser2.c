/*
 *  Lucas & Jordan | All Rights Reserved (R)
 *  29/03/2017
 *  Frequency analyser 2....analyusing a files characterrs for interesting 
 *  trends, v2 includes capital letters
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define WHITESPACE_ASCII 32
#define LF_CHAR 10

int main(int argc, char **argv) {

   int letterFrequency[26] = {0};

   // statistical data
   int totalCapitalLetters = 0;
   int totalLowerCaseLetters = 0;
   int totalWhiteSpace = 0;
   int totalLineFeedCharacters = 0;
   int vowelTotal = 0;

   char letter = getchar();

   int frequencyTotal = 0;
   int counter = 0;

   while (letter != EOF) {

      if (letter == WHITESPACE_ASCII) {
         totalWhiteSpace++;
      }

      if (letter == LF_CHAR) {
         totalLineFeedCharacters++;
      }

      // C's automatic <char> to <int> conversion
      if (letter >= 'a' && letter <= 'z') {

         letterFrequency[letter - 'a']++;
         totalLowerCaseLetters++;

         if ((letter == 'a') || 
             (letter == 'e') ||
             (letter == 'i') ||
             (letter == 'o') ||
             (letter == 'u')) {

            vowelTotal++;

         }

      }

      if (letter >= 'A' && letter <= 'Z') {

         letterFrequency[letter - 'A']++;
         totalCapitalLetters++;

         if ((letter == 'A') || 
             (letter == 'E') ||
             (letter == 'I') ||
             (letter == 'O') ||
             (letter == 'U')) {

            vowelTotal++;

         }

      }

      letter = getchar();
      frequencyTotal++;

  }

   float percentage = 0.0;
   printf("%-10s %-13s %-10s \n", "Letter", "Frequency", "Percentage (%)");

   while (counter < 26) {

      percentage = 0.0;
      char currentLetter = counter + 'a';
      int letterFrequencyAsInt = letterFrequency[counter];

      percentage = (float)letterFrequencyAsInt;
      percentage /= (float)frequencyTotal;
      percentage *= 100;
      // Rounding towards ceiling (up ^)
      percentage = ceilf(percentage * 100) / 100;

      printf("%-10c %-13d %-10.2f \n", currentLetter, 
           letterFrequencyAsInt, percentage);

      counter++;
  }

  float totalVowelPercentage = (float)vowelTotal;
  totalVowelPercentage /= (float)frequencyTotal;
  totalVowelPercentage *= 100;

  printf("Total characters             : [%d] \n", frequencyTotal);
  printf("Total Lower Case characters  : [%d] \n", totalLowerCaseLetters);
  printf("Total Capitalised characters : [%d] \n", totalCapitalLetters);
  printf("Total Percentage of vowels   : [%f] \n", totalVowelPercentage);
  printf("Total White Space characters : [%d] \n", totalWhiteSpace);
  printf("Total Line Feed characters   : [%d] \n", totalLineFeedCharacters);

  /*
  
  Sample output

  cat hamlet.txt | ./main.o

   Letter     Frequency     Percentage (%) 
   a          9863          5.52       
   b          1891          1.06       
   c          2748          1.54       
   d          5014          2.81       
   e          17900         10.01      
   f          2779          1.56       
   g          2485          1.39       
   h          8692          4.87       
   i          8816          4.93       
   j          45            0.03       
   k          1285          0.72       
   l          5908          3.31       
   m          4259          2.39       
   n          8377          4.69       
   o          11459         6.41       
   p          2130          1.20       
   q          207           0.12       
   r          7976          4.46       
   s          8299          4.65       
   t          12098         6.77       
   u          4960          2.78       
   v          623           0.35       
   w          3049          1.71       
   x          247           0.14       
   y          3245          1.82       
   z          56            0.04       
   Total characters             : [178843] 
   Total Lower Case characters  : [124487] 
   Total Capitalised characters : [9924] 
   Total Percentage of vowels   : [29.633814] 
   Total White Space characters : [31173] 
   Total Line Feed characters   : [5302] 

  */

  return EXIT_SUCCESS;

}