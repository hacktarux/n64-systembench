
#include "rdp_lowlevel.h"

#define CMD_SYNC_FULL       0x29LL
#define CMD_SET_SCISSOR     0x2dLL
#define CMD_SET_OTHER_MODES 0x2fLL
#define CMD_FILL_RECTANGLE  0x36LL
#define CMD_SET_FILL_COLOR  0x37LL
#define CMD_SET_COLOR_IMAGE 0x3fLL

void rdp_asm_sync_full(uint64_t** ptr) {
   **ptr = CMD_SYNC_FULL << 56;
   *ptr += sizeof(uint64_t);
}

void rdp_asm_set_scissor(uint64_t** ptr, Point upper_left, Point lower_right, InterlacedMode mode, Field field) {
   **ptr = (CMD_SET_SCISSOR << 56) |
     (((int64_t)(upper_left.x * 4.0) & 0xFFF) << 44) |
     (((int64_t)(upper_left.y * 4.0) & 0xFFF) << 32) |
     ((mode.value & 1) << 25) |
     ((field.value & 1) << 24) |
     (((int64_t)(lower_right.x * 4.0) & 0xFFF) << 12) |
     ((int64_t)(lower_right.y * 4.0) & 0xFFF);
   *ptr += sizeof(uint64_t);
}

void rdp_asm_set_cycle_type(OtherModes* other_modes, CycleType cycle_type) {
   other_modes->value |= (cycle_type.value & 3) << 52;
}

void rdp_asm_set_other_modes(uint64_t** ptr, OtherModes other_modes) {
   **ptr = (CMD_SET_OTHER_MODES << 56) |
     (other_modes.value & 0xFFFFFFFFFFFFFFLL);
   *ptr += sizeof(uint64_t);
}

void rdp_asm_fill_rectangle(uint64_t** ptr, Point upper_left, Point lower_right) {
   **ptr = (CMD_FILL_RECTANGLE << 56) |
     (((int64_t)(lower_right.x * 4.0) & 0xFFF) << 44) |
     (((int64_t)(lower_right.y * 4.0) & 0xFFF) << 32) |
     (((int64_t)(upper_left.x * 4.0) & 0xFFF) << 12) |
     ((int64_t)(upper_left.y * 4.0) & 0xFFF);
   *ptr += sizeof(uint64_t);
}

void rdp_asm_set_fill_color(uint64_t** ptr, Color color) {
   **ptr = (CMD_SET_FILL_COLOR << 56) |
     (uint64_t)color.value;
   *ptr += sizeof(uint64_t);
}

void rdp_asm_set_color_image(uint64_t** ptr, Format format, PixelSize size, int width, uint8_t* address) {
   **ptr = (CMD_SET_COLOR_IMAGE << 56) |
     ((format.value & 7) << 53) |
     ((size.value & 3) << 51) |
     (((uint64_t)width & 0x3FF) << 32) |
     ((uint32_t)address & 0xFFFFFF);
   *ptr += sizeof(uint64_t);
}
