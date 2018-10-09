#include "stm32f10x.h"
#include "flash.h"



void FLASH_WriteMoreData(uint32_t startAddress,uint16_t *data,uint16_t count)
{
	uint32_t	offsetAddress;
	uint32_t	sectorPosition;
	uint32_t	sectorStartAddress;
	uint16_t	i;
	
	if(startAddress < FLASH_BASE||((startAddress+count*2)>=(FLASH_BASE+1024*FLASH_SIZE))){
		return;
	}
	FLASH_Unlock(); 
	offsetAddress = startAddress - FLASH_BASE; 
	sectorPosition = offsetAddress / SECTOR_SIZE; 

	sectorStartAddress = sectorPosition*SECTOR_SIZE + FLASH_BASE; 

	FLASH_ErasePage(sectorStartAddress);

	for(i=0;i<count;i++){
		FLASH_ProgramHalfWord(startAddress+i*2,data[i]);
	}

	FLASH_Lock();
}

void FLASH_ReadMoreData(uint32_t startAddress,uint16_t *data,uint16_t count)
{
	uint16_t	i;
	
	if(startAddress<FLASH_BASE||((startAddress+count*2)>=(FLASH_BASE+1024*FLASH_SIZE))){
		return;
	}
	//FLASH_Unlock(); 

	for(i=0;i<count;i++){
		//FLASH_ProgramHalfWord(startAddress+i*2,data[i]);
		data[i] =*((__IO uint16_t*)(startAddress+i*2));
	}

	//FLASH_Lock();
}

int flash_write_pages(uint32_t idx,uint8_t *data,uint32_t count)
{
	uint32_t	page_start_addr;
	uint32_t	i;
	uint32_t	*pwrite;
	uint32_t	tmp;
	
	if(idx < FLASH_PAGE_MIN||((idx + count/SECTOR_SIZE) >FLASH_PAGE_MAX)){
		return -1;
	}
	FLASH_Unlock(); 
	if(count % 4) {
		count = count / 4 + 1;
	} else {
		count = count / 4;
	}
	pwrite = (uint32_t *)data;
	
	tmp = SECTOR_SIZE / 4;
	if(count % tmp) {
		tmp = count / tmp + 1;
	} else {
		tmp = count / tmp;
	}
	
	
	for(i = 0; i < tmp; i++) {
		page_start_addr = (i+idx) * SECTOR_SIZE + FLASH_BASE; 
		
		FLASH_ErasePage(page_start_addr);
		
	}
	//FLASH_ProgramWord(page_start_addr, idx);
	//FLASH_ProgramWord(page_start_addr+4, count);
	page_start_addr = idx * SECTOR_SIZE + FLASH_BASE;
	for(i = 0; i < count; i++) {
		FLASH_ProgramWord(page_start_addr+i*4,pwrite[i]);
	}

	FLASH_Lock();
	return (count*4);
}

int flash_read_pages(uint32_t idx, uint8_t *data,uint32_t count)
{
	uint32_t	page_start_addr;
	uint32_t	*pread;
	uint16_t	i;
	
	if(idx < FLASH_PAGE_MIN||((idx + count/SECTOR_SIZE) >FLASH_PAGE_MAX)){
		return -1;
	}
	if(count % 4) {
		count = count / 4 + 1;
	} else {
		count = count / 4;
	}
	pread = (uint32_t *)data;
	
	page_start_addr = idx*SECTOR_SIZE + FLASH_BASE; 
	/*
	tmp = *((__IO uint32_t*)(page_start_addr));
	if(tmp != idx) {
		return -1;
	}
	tmp = *((__IO uint32_t*)(page_start_addr+4));
	if(tmp != count) {
		return -1;
	}*/
	for(i = 0; i < count; i++){
		pread[i] = *((__IO uint32_t*)(page_start_addr + i*4));
	}
	return (count*4);

}

