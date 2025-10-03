
#ifndef RDP_LOWLEVEL_H
#define RDP_LOWLEVEL_H

#include <stdint.h>

typedef struct DP_regs_s
{
   uint32_t start;
   uint32_t end;
   uint32_t current;
   uint32_t status;
   uint32_t clock;
   uint32_t cmd_busy;
   uint32_t pipe_busy;
   uint32_t tmem_busy;
} DP_regs_t;

#define DP_STATUS_XBUS          0x001
#define DP_STATUS_FREEZE        0x002
#define DP_STATUS_FLUSH         0x004
#define DP_STATUS_GCLK          0x008
#define DP_STATUS_TMEM_BUSY     0x010
#define DP_STATUS_PIPE_BUSY     0x020
#define DP_STATUS_CMD_BUSY      0x040
#define DP_STATUS_CBUF_READY    0x080
#define DP_STATUS_DMA_BUSY      0x100
#define DP_STATUS_END_PENDING   0x200
#define DP_STATUS_START_PENDING 0x400

#define DP_STATUS_CLR_XBUS        0x001
#define DP_STATUS_SET_XBUS        0x002
#define DP_STATUS_CLR_FREEZE      0x004
#define DP_STATUS_SET_FREEZE      0x008
#define DP_STATUS_CLR_FLUSH       0x010
#define DP_STATUS_SET_FLUSH       0x020
#define DP_STATUS_CLR_TMEM_BUSY   0x040
#define DP_STATUS_CLR_PIPE_BUSY   0x080
#define DP_STATUS_CLR_BUFFER_BUSY 0x100
#define DP_STATUS_CLR_CLOCK       0x200

#define FORMAT_RGBA 0
#define FORMAT_YUB  1
#define FORMAT_CI   2
#define FORMAT_IA   3
#define FORMAT_I    4

#define SIZE_4BPP  0
#define SIZE_8BPP  1
#define SIZE_16BPP 2
#define SIZE_32BPP 3

void rdp_asm_set_color_image(uint64_t** ptr, int format, int size, int width, uint8_t* address);

#endif // RDP_LOWLEVEL_H
