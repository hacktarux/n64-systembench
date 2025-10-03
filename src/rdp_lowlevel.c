
#include "rdp_lowlevel.h"

#define CMD_SET_COLOR_IMAGE 0x3fLL

void rdp_asm_set_color_image(uint64_t** ptr, int format, int size, int width, uint8_t* address) 
{
   **ptr = (CMD_SET_COLOR_IMAGE << 56) |
     (((uint64_t)format & 7) << 53) |
     (((uint64_t)size & 3) << 51) |
     (((uint64_t)width & 0x3FF) << 32) |
     ((uint32_t)address & 0xFFFFFF);
   *ptr += sizeof(uint64_t);
}
