/*
 *  Lucas & Jordan | All Rights Reserved (R)
 *  29/03/2017
 *  Frequency analysis....analyusing a files characterrs for interesting trends
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

int main(int argc, char **argv) {

  int letterFrequency[26] = {0};

  char letter = getchar();

  int frequencyTotal = 0;
  int counter = 0;

  while (letter != EOF) {
    // C's automatic <char> to <int> conversion
    if (letter >= 'a' && letter <= 'z') {
      letterFrequency[letter - 'a']++;
    }
    letter = getchar();
    frequencyTotal++;
  }

  float percentage = 0.0;
  printf("Total characters: %d \n", frequencyTotal);
  printf("%-10s %-13s %-10s \n", "Letter", "Frequency", "Percentage (%)");

  while (counter < 26) {
    percentage = 0.0;
    char currentLetter = counter + 'a';
    int letterFrequencyAsInt = letterFrequency[counter];

    percentage = (float)letterFrequency[counter];
    percentage /= (float)frequencyTotal;
    percentage *= 100;
    // Rounding towards ceiling (up ^)
    percentage = ceilf(percentage * 100) / 100;
    
    printf("%-10c %-13d %-10.2f \n", currentLetter, letterFrequencyAsInt, percentage);
    
    counter++;
  }

  /*
  
  Sample output

  cat file.txt | ./main.o

  Letter    Frequency    Percentage (%)
  a         972          5.99
  b         208          1.28
  c         356          2.20
  d         457          2.82
  e         1583         9.76
  f         267          1.65
  g         277          1.71
  h         608          3.75
  i         1146         7.07
  j         4            0.02
  k         40           0.25
  l         546          3.37
  m         311          1.92
  n         919          5.67
  o         830          5.12
  p         220          1.36
  q         5            0.03
  r         788          4.86
  s         894          5.51
  t         1012         6.24
  u         311          1.92
  v         139          0.86
  w         167          1.03
  x         31           0.19
  y         159          0.98
  z         1            0.01

  */

  return EXIT_SUCCESS;

}