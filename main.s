	.cpu cortex-m0
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 0
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Booting up...\000"
	.align	2
.LC2:
	.ascii	"EEPROM: RAR\000"
	.align	2
.LC4:
	.ascii	"EEPROM: RAR pass\000"
	.align	2
.LC6:
	.ascii	"EEPROM: RAR fail\000"
	.align	2
.LC8:
	.ascii	"EEPROM: SR\000"
	.align	2
.LC10:
	.ascii	"EEPROM: SR pass\000"
	.align	2
.LC12:
	.ascii	"Hello world: %d\000"
	.align	2
.LC14:
	.ascii	"EEPROM: SR fail\000"
	.text
	.align	1
	.global	reset_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	reset_handler, %function
reset_handler:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r4, r5, r6, r7, lr}
	sub	sp, sp, #20
	add	r7, sp, #0
	bl	cpu_get_partno
	movs	r3, r0
	movs	r2, r3
	movs	r3, #194
	lsls	r3, r3, #4
	cmp	r2, r3
	beq	.LCB13
	b	.L13	@long jump
.LCB13:
	bl	cpu_get_arch
	movs	r3, r0
	cmp	r3, #12
	beq	.LCB17
	b	.L14	@long jump
.LCB17:
	movs	r0, #2
	bl	enable_gpio
	movs	r2, #1
	movs	r1, #11
	movs	r0, #2
	bl	set_gpio_mode
	movs	r2, #1
	movs	r1, #12
	movs	r0, #2
	bl	set_gpio_mode
	movs	r2, #1
	movs	r1, #11
	movs	r0, #2
	bl	set_gpio_output
	movs	r2, #1
	movs	r1, #12
	movs	r0, #2
	bl	set_gpio_output
	ldr	r3, .L15
	movs	r0, r3
	bl	enable_stk
	bl	oled_init
	ldr	r3, .L15+4
	movs	r0, r3
	bl	oled_display1
	movs	r0, #0
	bl	eeprom_init
	movs	r5, #11
	adds	r3, r7, r5
	movs	r2, #238
	strb	r2, [r3]
	movs	r4, #10
	adds	r3, r7, r4
	movs	r2, #87
	strb	r2, [r3]
	movs	r6, #8
	adds	r3, r7, r6
	movs	r2, #0
	strh	r2, [r3]
	bl	oled_clear_display2
	ldr	r3, .L15+8
	movs	r0, r3
	bl	oled_display2
	adds	r3, r7, r5
	ldrb	r2, [r3]
	adds	r3, r7, r6
	ldrh	r1, [r3]
	movs	r6, r4
	adds	r3, r7, r4
	ldrb	r3, [r3]
	movs	r0, r3
	bl	eeprom_flash_write
	adds	r4, r7, #7
	movs	r3, #8
	adds	r3, r7, r3
	ldrh	r2, [r3]
	adds	r3, r7, r6
	ldrb	r3, [r3]
	movs	r1, r2
	movs	r0, r3
	bl	eeprom_flash_read
	movs	r3, r0
	strb	r3, [r4]
	adds	r2, r7, #7
	adds	r3, r7, r5
	ldrb	r2, [r2]
	ldrb	r3, [r3]
	cmp	r2, r3
	bne	.L5
	ldr	r3, .L15+12
	movs	r0, r3
	bl	oled_display2
	bl	oled_clear_display2
	ldr	r3, .L15+16
	movs	r0, r3
	bl	oled_display2
	movs	r4, #8
	adds	r3, r7, r4
	ldrh	r1, [r3]
	movs	r5, #10
	adds	r3, r7, r5
	ldrb	r3, [r3]
	movs	r2, #170
	movs	r0, r3
	bl	eeprom_flash_write
	adds	r3, r7, r4
	ldrh	r3, [r3]
	adds	r3, r3, #1
	uxth	r1, r3
	adds	r3, r7, r5
	ldrb	r3, [r3]
	movs	r2, #187
	movs	r0, r3
	bl	eeprom_flash_write
	adds	r3, r7, r4
	ldrh	r3, [r3]
	adds	r3, r3, #2
	uxth	r1, r3
	adds	r3, r7, r5
	ldrb	r3, [r3]
	movs	r2, #204
	movs	r0, r3
	bl	eeprom_flash_write
	adds	r3, r7, r4
	ldrh	r3, [r3]
	adds	r3, r3, #3
	uxth	r1, r3
	adds	r3, r7, r5
	ldrb	r3, [r3]
	movs	r2, #221
	movs	r0, r3
	bl	eeprom_flash_write
	movs	r3, r7
	movs	r2, #0
	str	r2, [r3]
	movs	r2, r7
	adds	r3, r7, r4
	ldrh	r1, [r3]
	adds	r3, r7, r5
	ldrb	r0, [r3]
	movs	r3, #4
	bl	eeprom_flash_read_sequential
	movs	r3, r7
	ldrb	r3, [r3]
	cmp	r3, #170
	bne	.L7
	b	.L12
.L5:
	ldr	r3, .L15+20
	movs	r0, r3
	bl	oled_display2
	b	.L1
.L12:
	movs	r3, r7
	ldrb	r3, [r3, #1]
	cmp	r3, #187
	bne	.L7
	movs	r3, r7
	ldrb	r3, [r3, #2]
	cmp	r3, #204
	bne	.L7
	movs	r3, r7
	ldrb	r3, [r3, #3]
	cmp	r3, #221
	bne	.L7
	ldr	r3, .L15+24
	movs	r0, r3
	bl	oled_display2
	ldr	r3, .L15+28
	movs	r1, #22
	movs	r0, r3
	bl	oled_printf
	b	.L8
.L7:
	ldr	r3, .L15+32
	movs	r0, r3
	bl	oled_display2
	b	.L1
.L8:
	movs	r3, #0
	str	r3, [r7, #12]
	b	.L9
.L10:
	ldr	r3, [r7, #12]
	adds	r3, r3, #1
	str	r3, [r7, #12]
.L9:
	ldr	r3, [r7, #12]
	ldr	r2, .L15+36
	cmp	r3, r2
	ble	.L10
	movs	r1, #12
	movs	r0, #2
	bl	get_gpio_output
	movs	r3, r0
	uxtb	r3, r3
	movs	r2, #1
	eors	r3, r2
	uxtb	r3, r3
	movs	r2, r3
	movs	r1, #12
	movs	r0, #2
	bl	set_gpio_output
	b	.L8
.L13:
	nop
	b	.L1
.L14:
	nop
.L1:
	mov	sp, r7
	add	sp, sp, #20
	@ sp needed
	pop	{r4, r5, r6, r7, pc}
.L16:
	.align	2
.L15:
	.word	10000000
	.word	.LC0
	.word	.LC2
	.word	.LC4
	.word	.LC8
	.word	.LC6
	.word	.LC10
	.word	.LC12
	.word	.LC14
	.word	499999
	.size	reset_handler, .-reset_handler
	.align	1
	.global	nmi_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	nmi_handler, %function
nmi_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	nmi_handler, .-nmi_handler
	.align	1
	.global	hard_fault_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	hard_fault_handler, %function
hard_fault_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	hard_fault_handler, .-hard_fault_handler
	.align	1
	.global	svcall_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	svcall_handler, %function
svcall_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	svcall_handler, .-svcall_handler
	.align	1
	.global	pendsv_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	pendsv_handler, %function
pendsv_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	pendsv_handler, .-pendsv_handler
	.align	1
	.global	systick_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	systick_handler, %function
systick_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	movs	r1, #11
	movs	r0, #2
	bl	get_gpio_output
	movs	r3, r0
	uxtb	r3, r3
	movs	r2, #1
	eors	r3, r2
	uxtb	r3, r3
	movs	r2, r3
	movs	r1, #11
	movs	r0, #2
	bl	set_gpio_output
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	systick_handler, .-systick_handler
	.align	1
	.global	wwdg_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	wwdg_handler, %function
wwdg_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	wwdg_handler, .-wwdg_handler
	.align	1
	.global	pvd_vddio_2_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	pvd_vddio_2_handler, %function
pvd_vddio_2_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	pvd_vddio_2_handler, .-pvd_vddio_2_handler
	.align	1
	.global	rtc_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	rtc_handler, %function
rtc_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	rtc_handler, .-rtc_handler
	.align	1
	.global	flash_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	flash_handler, %function
flash_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	flash_handler, .-flash_handler
	.align	1
	.global	rcc_crs_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	rcc_crs_handler, %function
rcc_crs_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	rcc_crs_handler, .-rcc_crs_handler
	.align	1
	.global	exti0_1_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	exti0_1_handler, %function
exti0_1_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	exti0_1_handler, .-exti0_1_handler
	.align	1
	.global	exti2_3_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	exti2_3_handler, %function
exti2_3_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	exti2_3_handler, .-exti2_3_handler
	.align	1
	.global	exti4_15_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	exti4_15_handler, %function
exti4_15_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	exti4_15_handler, .-exti4_15_handler
	.align	1
	.global	tsc_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tsc_handler, %function
tsc_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tsc_handler, .-tsc_handler
	.align	1
	.global	dma_ch1_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	dma_ch1_handler, %function
dma_ch1_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	dma_ch1_handler, .-dma_ch1_handler
	.align	1
	.global	dma_ch2_3_dma2_ch1_2_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	dma_ch2_3_dma2_ch1_2_handler, %function
dma_ch2_3_dma2_ch1_2_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	dma_ch2_3_dma2_ch1_2_handler, .-dma_ch2_3_dma2_ch1_2_handler
	.align	1
	.global	dma_ch4_7_dma2_ch3_5_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	dma_ch4_7_dma2_ch3_5_handler, %function
dma_ch4_7_dma2_ch3_5_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	dma_ch4_7_dma2_ch3_5_handler, .-dma_ch4_7_dma2_ch3_5_handler
	.align	1
	.global	adc_comp_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	adc_comp_handler, %function
adc_comp_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	adc_comp_handler, .-adc_comp_handler
	.align	1
	.global	tim1_brk_up_trg_com_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim1_brk_up_trg_com_handler, %function
tim1_brk_up_trg_com_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim1_brk_up_trg_com_handler, .-tim1_brk_up_trg_com_handler
	.align	1
	.global	tim1_cc_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim1_cc_handler, %function
tim1_cc_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim1_cc_handler, .-tim1_cc_handler
	.align	1
	.global	tim2_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim2_handler, %function
tim2_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim2_handler, .-tim2_handler
	.align	1
	.global	tim3_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim3_handler, %function
tim3_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim3_handler, .-tim3_handler
	.align	1
	.global	tim6_dac_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim6_dac_handler, %function
tim6_dac_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim6_dac_handler, .-tim6_dac_handler
	.align	1
	.global	tim7_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim7_handler, %function
tim7_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim7_handler, .-tim7_handler
	.align	1
	.global	tim14_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim14_handler, %function
tim14_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim14_handler, .-tim14_handler
	.align	1
	.global	tim15_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim15_handler, %function
tim15_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim15_handler, .-tim15_handler
	.align	1
	.global	tim16_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim16_handler, %function
tim16_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim16_handler, .-tim16_handler
	.align	1
	.global	tim17_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	tim17_handler, %function
tim17_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	tim17_handler, .-tim17_handler
	.align	1
	.global	i2c1_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	i2c1_handler, %function
i2c1_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	i2c1_handler, .-i2c1_handler
	.align	1
	.global	i2c2_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	i2c2_handler, %function
i2c2_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	i2c2_handler, .-i2c2_handler
	.align	1
	.global	spi1_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	spi1_handler, %function
spi1_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	spi1_handler, .-spi1_handler
	.align	1
	.global	spi2_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	spi2_handler, %function
spi2_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	spi2_handler, .-spi2_handler
	.align	1
	.global	usart1_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	usart1_handler, %function
usart1_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	usart1_handler, .-usart1_handler
	.align	1
	.global	usart2_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	usart2_handler, %function
usart2_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	usart2_handler, .-usart2_handler
	.align	1
	.global	usart3_8_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	usart3_8_handler, %function
usart3_8_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	usart3_8_handler, .-usart3_8_handler
	.align	1
	.global	cec_can_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	cec_can_handler, %function
cec_can_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	cec_can_handler, .-cec_can_handler
	.align	1
	.global	usb_handler
	.syntax unified
	.code	16
	.thumb_func
	.fpu softvfp
	.type	usb_handler, %function
usb_handler:
	@ Stack Align: May be called with mis-aligned SP.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	usb_handler, .-usb_handler
	.comm	stack,1024,4
	.global	vectors
	.section	.vectors,"aw",%progbits
	.align	2
	.type	vectors, %object
	.size	vectors, 192
vectors:
	.word	stack+1024
	.word	reset_handler
	.word	nmi_handler
	.word	hard_fault_handler
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	0
	.word	svcall_handler
	.word	0
	.word	0
	.word	pendsv_handler
	.word	systick_handler
	.word	wwdg_handler
	.word	pvd_vddio_2_handler
	.word	rtc_handler
	.word	flash_handler
	.word	rcc_crs_handler
	.word	exti0_1_handler
	.word	exti2_3_handler
	.word	exti4_15_handler
	.word	tsc_handler
	.word	dma_ch1_handler
	.word	dma_ch2_3_dma2_ch1_2_handler
	.word	dma_ch4_7_dma2_ch3_5_handler
	.word	adc_comp_handler
	.word	tim1_brk_up_trg_com_handler
	.word	tim1_cc_handler
	.word	tim2_handler
	.word	tim3_handler
	.word	tim6_dac_handler
	.word	tim7_handler
	.word	tim14_handler
	.word	tim15_handler
	.word	tim16_handler
	.word	tim17_handler
	.word	i2c1_handler
	.word	i2c2_handler
	.word	spi1_handler
	.word	spi2_handler
	.word	usart1_handler
	.word	usart2_handler
	.word	usart3_8_handler
	.word	cec_can_handler
	.word	usb_handler
	.ident	"GCC: (15:7-2018-q2-6) 7.3.1 20180622 (release) [ARM/embedded-7-branch revision 261907]"
