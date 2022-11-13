#include <stdio.h>

int main(){
    int side1 = 0, side2 = 0, side3 = 0;

    printf("Enter 3 sides of a triangle \n");
    printf("Side1: ");
    scanf("%d", &side1);
    printf("Side2: ");
    scanf("%d", &side2);
    printf("Side3: ");
    scanf("%d", &side3);


if (side1 == side2 + side3 || side2 == side1 + side3 || side3 == side1 + side2){
    printf("THe Entered Values are not valid \n");
}
else if (side1 != side2 && side2 != side3 && side1 != side3){
    printf("Scalene Triangle \n");
}
else if (side1 == side2 && side2 == side3){
    printf("Equilateral Triangle \n");
}
else{
    printf("Isosceles Triangle \n");
}

    return 0;
}