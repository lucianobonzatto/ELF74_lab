
//uint16_t EightBitHistogram(uint16_t width, uint16_t height, const uint8_t * p_image, uint16_t * p_hist);
#define VALUE_64K 0X10000
#define HIST_SIZE 256
	.syntax unified
	.text
	.align 2
	.global EightBitHistogram
	.thumb_func

EightBitHistogram:
	add R0, R0, #01
