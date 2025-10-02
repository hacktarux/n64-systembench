
#ifndef RDP_LOWLEVEL_H
#define RDP_LOWLEVEL_H

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

#endif // RDP_LOWLEVEL_H
