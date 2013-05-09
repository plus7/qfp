#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* 手抜き */
void print_qfp(unsigned char val)
{
  unsigned char sign = val >> 7;
  unsigned char exponent = (val & 0x70) >> 4;
  unsigned char fraction = val & 0x0f;

  if(exponent == 0x07){
    if(fraction == 0){
      if(sign) printf("-");
      puts("Inf");
    }else{
      puts("NaN");
    }
  }else if(exponent == 0x00){ /* Denormal number */
    if(sign) printf("-");
    printf("%f\n", pow(2, -2) * (0.5    * ((fraction & 0x08) >> 3) + 
				 0.25   * ((fraction & 0x04) >> 2) +
				 0.125  * ((fraction & 0x02) >> 1) +
				 0.0625 * (fraction & 0x01)));
  }else{
    if(sign) printf("-");
    printf("%f\n", pow(2, exponent - 3) * (1.0                               +
					   0.5    * ((fraction & 0x08) >> 3) + 
					   0.25   * ((fraction & 0x04) >> 2) +
					   0.125  * ((fraction & 0x02) >> 1) +
					   0.0625 * (fraction & 0x01)));
  }
}

int main(void)
{
  int i;
  for(i = 0; i < 256; i++){
    printf("%02x = ", i);
    print_qfp(i);
  }
  return 0;
}
