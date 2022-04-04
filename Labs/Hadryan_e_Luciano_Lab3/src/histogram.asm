
//uint16_t EightBitHistogram(uint16_t width, uint16_t height, const uint8_t * p_image, uint16_t * p_hist);
#define VALUE_64K 0X10000
#define HIST_SIZE 256
	.syntax unified
	.text
	.align 2
	.global EightBitHistogram
	.thumb_func

EightBitHistogram:
	push {lr}
	push {R4}
	push {R5}
	push {R6}
	push {R7}

	mul R0, R0, R1
	cmp R0, 64000
	bge fimInvalido

	mov R4, 0
	mov R5, 0
loopClear:
	strh R5, [R3, R4]
	add R4, #2
	cmp R4, 512
	blt loopClear

	mov R4, 0
	mov R7, 2
loopFill:
	ldrb R5, [R2, R4]
	mul R5, R7
	ldrh R6, [R3, R5]
	add R6, 1
	strh R6, [R3, R5]

	add R4, 1
	cmp R4, R0
	blt loopFill

	pop {R7}
	pop {R6}
	pop {R5}
	pop {R4}
	pop {lr}
	BX lr

fimInvalido:
	mov R0, 0

	pop {R7}
	pop {R6}
	pop {R5}
	pop {R4}
	pop {lr}
	pop {lr}
	BX lr
