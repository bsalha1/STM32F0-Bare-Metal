#include "compile.h"
#include "bool.h"
#include "rcc.h"
#include "gpio.h"
#include "i2c.h"
#include "eeprom_aa32af.h"
#include "oled_1602a.h"
#include "time.h"
#include "stk.h"
#include "nvic.h"

void reset_handler(void)
{
    enable_gpio(GPIO_PORT_C);
    set_gpio_mode(GPIO_PORT_C, 11, MODE_OUTPUT);
    set_gpio_output(GPIO_PORT_C, 11, 1);

    // Enable SysTick interrupt
    enable_stk(10000000);

    oled_init();
    oled_display1("Booting up...");
    
    // TEST: EEPROM //
    eeprom_init(I2C_PORT_1);
    
    uint8_t write = 0xee;
    uint8_t dev_address = 0x57;
    uint16_t address = 0x0;
    
    oled_clear_display2();
    oled_display2("EEPROM: RAR");

    // TEST: Random-Access Read
    eeprom_flash_write(dev_address, address, write);
    uint8_t read = eeprom_flash_read(dev_address, address);
    if(read == write)
    {
        oled_display2("EEPROM: RAR pass");
    }
    else
    {
        oled_display2("EEPROM: RAR fail");
        return;
    }

    oled_clear_display2();
    oled_display2("EEPROM: SR");

    // TEST: Sequential Read
    eeprom_flash_write(dev_address, address + 0, 0xaa);
    eeprom_flash_write(dev_address, address + 1, 0xbb);
    eeprom_flash_write(dev_address, address + 2, 0xcc);
    eeprom_flash_write(dev_address, address + 3, 0xdd);
    uint8_t data[4] = {0};
    eeprom_flash_read_sequential(dev_address, address, data, sizeof(data));
    if(data[0] == 0xaa && data[1] == 0xbb && data[2] == 0xcc && data[3] == 0xdd)
    {
        oled_display2("EEPROM: SR pass");
    }
    else
    {
        oled_display2("EEPROM: SR fail");
        return;
    }

}

__WEAK__ void nmi_handler(void) { }
__WEAK__ void hard_fault_handler(void) {}
__WEAK__ void svcall_handler(void) { }
__WEAK__ void pendsv_handler(void) { }

__WEAK__ void systick_handler(void)
{
    set_gpio_output(GPIO_PORT_C, 11, 1 ^ get_gpio_output(GPIO_PORT_C, 11));
}

__WEAK__ void wwdg_handler(void) { }
__WEAK__ void pvd_vddio_2_handler(void) { }
__WEAK__ void rtc_handler(void) { }
__WEAK__ void flash_handler(void) { }
__WEAK__ void rcc_crs_handler(void) { }
__WEAK__ void exti0_1_handler(void) { }
__WEAK__ void exti2_3_handler(void) { }
__WEAK__ void exti4_15_handler(void) { }
__WEAK__ void tsc_handler(void) { }
__WEAK__ void dma_ch1_handler(void) { }
__WEAK__ void dma_ch2_3_dma2_ch1_2_handler(void) { }
__WEAK__ void dma_ch4_7_dma2_ch3_5_handler(void) { }
__WEAK__ void adc_comp_handler(void) { }
__WEAK__ void tim1_brk_up_trg_com_handler(void) { }
__WEAK__ void tim1_cc_handlerm(void) { }
__WEAK__ void tim2_handler(void) { }
__WEAK__ void tim3_handler(void) { }
__WEAK__ void tim6_dac_handler(void) { }
__WEAK__ void tim7_handler(void) { }
__WEAK__ void tim14_handler(void) { }
__WEAK__ void tim15_handler(void) { }
__WEAK__ void tim16_handler(void) { }
__WEAK__ void tim17_handler(void) { }
__WEAK__ void i2c1_handler(void) { }
__WEAK__ void i2c2_handler(void) { }
__WEAK__ void spi1_handler(void) { }
__WEAK__ void spi2_handler(void) { }
__WEAK__ void usart1_handler(void) { }
__WEAK__ void usart2_handler(void) { }
__WEAK__ void usart3_8_handler(void) { }
__WEAK__ void cec_can_handler(void) { }
__WEAK__ void usb_handler(void) { }

int STACK[256];

__VECTOR__ const void* vectors[] = {
    STACK + sizeof(STACK) / sizeof(*STACK),
    reset_handler,       // Reset
    nmi_handler,         // Non maskable interrupt
    hard_fault_handler,  // All class of fault
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    svcall_handler,      // System service call via SWI instruction
    0,
    0,
    pendsv_handler,      // Pendable request for system service
    systick_handler,     // System tick timer
    wwdg_handler,        // Window watchdog interrupt
    pvd_vddio_2_handler, // PVD and VDDIO2 supply comparator interrupt
    rtc_handler,         // RTC interrupts
    flash_handler,       // Flash global interrupt
    rcc_crs_handler,     // RCC and CRS global interrupts
    exti0_1_handler,     // EXTI Line[1:0] interrupts
    exti2_3_handler,     // EXTI Line[3:2] interrupts
    exti4_15_handler,    // EXTI Line[15:4] interrupts
    tsc_handler,         // Touch sensing interrupt
    dma_ch1_handler,     // DMA channel 1 interrupt
    dma_ch2_3_dma2_ch1_2_handler, // DMA channel 2 and 3, DMA2 channel 1 and 2 interrupt
    dma_ch4_7_dma2_ch3_5_handler, // DMA channel 4-7 and DMA2 channel 3-5 interrupts
    adc_comp_handler,             // ADC and COMP interrupts
    tim1_brk_up_trg_com_handler,  // TIM1 break, update, trigger and commutation interrupt
    tim1_cc_handlerm,  // TIM1 capture compare interrupt
    tim2_handler,      // TIM2 global interrupt
    tim3_handler,      // TIM3 global interrupt
    tim6_dac_handler,  // TIM6 global interrupt and DAC underrun interrupt
    tim7_handler,  // TIM7 global interrupt
    tim14_handler, // TIM14 global interrupt
    tim15_handler, // TIM15 global interrupt
    tim16_handler, // TIM16 global interrupt
    tim17_handler, // TIM17 global interrupt
    i2c1_handler,  // I2C1 global interrupt
    i2c2_handler,  // I2C2 global interrupt
    spi1_handler,  // SPI1 global interrupt
    spi2_handler,  // SPI2 global interrupt
    usart1_handler,   // USART1 global interrupt
    usart2_handler,   // USART2 global interrupt
    usart3_8_handler, // USART3-8 global interrupt
    cec_can_handler,  // CEC and CAN global interrupts
    usb_handler,      // USB global interrupt
};