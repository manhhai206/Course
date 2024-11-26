#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_flash.h"            // Keil::Device:StdPeriph Drivers:Flash

#define PAGE4 0x08001000

void Flash_Erase(uint32_t pageAddress) {
    FLASH_Unlock(); 
    while (FLASH_GetFlagStatus(FLASH_FLAG_BSY)) {} 
    
    FLASH->CR |= FLASH_CR_PER;          
    FLASH->AR = pageAddress;           
    FLASH->CR |= FLASH_CR_STRT;         

    while (FLASH->SR & FLASH_SR_BSY) {} 
    FLASH->CR &= ~FLASH_CR_PER;        
    FLASH_Lock(); 
}

void Flash_Write(uint32_t address, uint16_t data) {
    FLASH_Unlock(); 
    while (FLASH->SR & FLASH_SR_BSY) {} 

    FLASH->CR |= FLASH_CR_PG; 
    *(volatile uint16_t*)address = data;

    while (FLASH->SR & FLASH_SR_BSY) {} 
    FLASH->CR &= ~FLASH_CR_PG; 
    FLASH_Lock(); 
}

int Flash_WriteNumByte(uint32_t address, uint8_t *data, int num) {
    
    FLASH_Unlock();
    while (FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);

    uint16_t *ptr = (uint16_t*)data;
    for (int i = 0; i < (num / 2); i++) { 
        FLASH_ProgramHalfWord(address + 2 * i, *ptr);
        while (FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
        ptr++;
    }
    
    if (num % 2 != 0) { 
        uint16_t lastHalfWord = data[num - 1];
        FLASH_ProgramHalfWord(address + num - 1, lastHalfWord);
        while (FLASH_GetFlagStatus(FLASH_FLAG_BSY) == 1);
    }

    FLASH_Lock();
    return 0; // Ghi thành công
}

uint8_t data[] = {0x12, 0x34, 0x56};

int main() {
	
    Flash_Erase(PAGE4);          
		Flash_WriteNumByte(PAGE4, data, sizeof(data));
		
    while (1) {
        
    }
}
