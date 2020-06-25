#include <cstdlib>
//helpers.h (c) 2020 max goren
//functions to make life easier in c/c++
//returns smaller number
int min(int a, int b)
{
  if (a < b) {
     return a;
  } else{
     return b;
  }
}

//returns bigger number
int max(int a, int b)
{
  if (a > b) {
    return a;
  } else {
    return b;
  }
}


//random number in range.
int getrand(int min, int max)
{
  return (rand() % (max - min + 1)) + min;
}