
#ifndef RDP_LOWLEVEL_H
#define RDP_LOWLEVEL_H

#include <stdint.h>

typedef struct DP_regs_s {
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

#define MI_MODE_CLEAR_DP 0x800

#define MI_INTERRUPT_DP 0x20

#define DEFINE_VALUE_HOLDER(type, name) \
   typedef struct { \
      type value; \
   } name;

DEFINE_VALUE_HOLDER(uint64_t, Format);
#define FORMAT(v) ((Format){ (v) })
#define FORMAT_RGBA FORMAT(0)
#define FORMAT_YUB  FORMAT(1)
#define FORMAT_CI   FORMAT(2)
#define FORMAT_IA   FORMAT(3)
#define FORMAT_I    FORMAT(4)

DEFINE_VALUE_HOLDER(uint64_t, PixelSize);
#define PIXELSIZE(v) ((PixelSize){ (v) })
#define PIXELSIZE_4BPP  PIXELSIZE(0)
#define PIXELSIZE_8BPP  PIXELSIZE(1)
#define PIXELSIZE_16BPP PIXELSIZE(2)
#define PIXELSIZE_32BPP PIXELSIZE(3)

DEFINE_VALUE_HOLDER(uint64_t, InterlacedMode);
#define INTERLACED_MODE(v) ((InterlacedMode){ (v) })
#define INTERLACED_MODE_OFF INTERLACED_MODE(0)
#define INTERLACED_MODE_ON  INTERLACED_MODE(1)

DEFINE_VALUE_HOLDER(uint64_t, Field);
#define FIELD(v) ((Field){ (v) })
#define FIELD_EVEN FIELD(0)
#define FIELD_ODD  FIELD(1)

DEFINE_VALUE_HOLDER(uint64_t, CycleType);
#define CYCLE_TYPE(v) ((CycleType){ (v) })
#define CYCLE_TYPE_1CYCLE CYCLE_TYPE(0)
#define CYCLE_TYPE_2CYCLE CYCLE_TYPE(1)
#define CYCLE_TYPE_COPY   CYCLE_TYPE(2)
#define CYCLE_TYPE_FILL   CYCLE_TYPE(3)

DEFINE_VALUE_HOLDER(uint64_t, OtherModes);

typedef struct {
   float x;
   float y;
} Point;

#pragma pack(push,1)
typedef union {
   struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
   } rgba32;
   struct 
     {
	uint16_t value;
     } rgba16[2];
   struct
     {
	uint8_t value;
     } i;
   uint32_t value;
} Color;
#pragma pack(pop)

#define toRGBA16(r,g,b,a) ((((r) & 0x1F) << 11) | (((g) & 0x1F) << 6) | (((b) & 0x1F) << 1) | ((a) & 0x1))

void rdp_asm_sync_full(uint64_t** ptr);
void rdp_asm_set_scissor(uint64_t** ptr, Point upper_left, Point lower_right, InterlacedMode mode, Field field);
void rdp_asm_set_cycle_type(OtherModes* other_modes, CycleType cycle_type);
void rdp_asm_set_other_modes(uint64_t** ptr, OtherModes other_modes);
void rdp_asm_fill_rectangle(uint64_t** ptr, Point upper_left, Point lower_right);
void rdp_asm_set_fill_color(uint64_t** ptr, Color color);
void rdp_asm_set_color_image(uint64_t** ptr, Format format, PixelSize size, int width, uint8_t* address);

#endif // RDP_LOWLEVEL_H
