#include <stdio.h>
#include "mymath.h"

int main()
{
  int a=14,b=2;
  printf("%d+%d=%d",a,b,add(a,b));
  printf("%d-%d=%d",a,b,sub(a,b));
  printf("%d/%d=%d",a,b,div1(a,b));
  printf("%d*%d=%d",a,b,muti(a,b));
  return 1;
}
