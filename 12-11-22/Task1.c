#include <stdio.h>

int main(void) {
  int length = 0, width = 0, area = 0;
  printf("Length: ");
  scanf("%d", &length);
  printf("Width: ");
  scanf("%d", &width);
  area = length * width;
  printf("Area: %d \n", area);
  return 0;
}