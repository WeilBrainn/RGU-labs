#include "overprintf.h"

int main() {
  overprintf("Number in Roman: %Ro\n", 1987);
  overprintf("Zeckendorf: %Zr\n", 21);
  overprintf("Custom Base: %Cv\n", 255, 16);
  return 0;
}
