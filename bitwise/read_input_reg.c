/* 
Read input by using read_input_reg from API.
1st byte has the count of info
2-4th byte has data
Reassemble the data

* |31....... .24|23.........16|15....    ..8|7.    ......0|
* | Valid bytes | FIFO byte 3 | FIFO byte 2 | FIFO byte 1 |
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> //for exit()

uint32_t read_input_reg(void);

int main()
{

  uint32_t buffer;
  uint8_t data[16];
  uint8_t index = 0;
  while(buffer = read_input_reg())
  {
    uint8_t count = buffer>>24;
    printf("\nValid byte = %d", count);
    for (int i=count; i>0; i--)
    {
      data[index] = buffer>>((i-1)*8) & 0xFF;
      printf("\n i=%d, %c", i, data[index]);
      index++;
    }
  }
  printf("\n%s", data);
  return 0;

}
uint32_t read_input_reg(void)
{
  const uint32_t input_values[] = {
    0x01000048,
    0x0200656c,
    0x036c6f20,
    0x03776f72,
    0x0100006c,
    0x02006421,
    0x00000000
};

  static unsigned idx = 0;

  if (idx >= (sizeof(input_values)/sizeof(input_values[0]))) {
    printf("Error: read_input_reg() called after full input received\n");
    exit(-1);
  }

  return input_values[idx++];
}
