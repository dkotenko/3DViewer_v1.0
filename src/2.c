#include <stdio.h>
int main(void)
{
char str[80];
double i = 2;
sscanf("hello 1.2 2 3 4 5", "%s%lf", str, &i);
printf("%s %f", str, i);
return 0;
}