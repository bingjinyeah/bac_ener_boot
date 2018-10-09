#include "stm32f10x.h"
#include <string.h>
#include "linux_list.h"
#include "eth_app.h"
#include "w5500.h"
#include "flash.h"
#include "led.h"


typedef enum {
	CFG_STATE_IDLE,
	CFG_STATE_DOWNLOAD,
	CFG_STATE_UPLOAD,
	CFG_STATE_SET_IP,
	CFG_STATE_UPDATE
}cfg_state_t;

cfg_state_t			cfg_state = CFG_STATE_IDLE;

uint8_t eth_rxd_buff[1536];
uint8_t eth_txd_buff[1536];

#define FW_FLASH_LENGTH		2048
extern uint8_t gw_update_completed;
extern uint8_t W5500_Interrupt;
uint32_t 	fw_length = 0;
uint32_t	fw_comp_size = 0;
uint8_t  	fw_flash[FW_FLASH_LENGTH];
uint32_t	fw_idx = 0;
uint32_t	fw_pages = 0;


void process_pc_msg(SOCKET s)
{
	uint32_t size;
	uint32_t tmp;
	
	uint8_t  *p;

	size = Read_SOCK_Data_Buffer(s, eth_rxd_buff);
	if(S0_Mode==UDP_MODE){
		UDP_DIPR[0] = eth_rxd_buff[0];
		UDP_DIPR[1] = eth_rxd_buff[1];
		UDP_DIPR[2] = eth_rxd_buff[2];
		UDP_DIPR[3] = eth_rxd_buff[3];

		UDP_DPORT[0] = eth_rxd_buff[4];
		UDP_DPORT[1] = eth_rxd_buff[5];
	}
	
	tmp = (eth_rxd_buff[1] << 8) | eth_rxd_buff[0];
	switch(cfg_state) {
		case CFG_STATE_IDLE:
			if(tmp==PC_UPDATE_START) {
				if(size == 10) {
					if((eth_rxd_buff[6]==0x12)&&(eth_rxd_buff[7]==0x34)&&
						(eth_rxd_buff[8]==0x56)&&(eth_rxd_buff[9]==0x78)){
						flash_write_pages(CFG_UPDATE_PAGE, (uint8_t*)&eth_rxd_buff[6], 4);
						NVIC_SystemReset();
					}
				}
			} else if(tmp==PC_UPDATE_TRANS) {
				p = (uint8_t*)&fw_length;
				*p = eth_rxd_buff[2];
				*(p+1) = eth_rxd_buff[3];
				*(p+2) = eth_rxd_buff[4];
				*(p+3) = eth_rxd_buff[5];
				fw_idx = size - 6;
				memcpy(fw_flash, &eth_rxd_buff[6], fw_idx);
				fw_comp_size = fw_idx;
				cfg_state = CFG_STATE_UPDATE;
			} else if(tmp==PC_REBOOT) {
				NVIC_SystemReset();
			} else if(tmp==PC_SET_IP) {
				if(size == 10) {
					IP_Addr[0] = eth_rxd_buff[6];
					IP_Addr[1] = eth_rxd_buff[7];
					IP_Addr[2] = eth_rxd_buff[8];
					IP_Addr[3] = eth_rxd_buff[9];
					IP_Addr[6] = 0xaa;
					IP_Addr[7] = 0x55;
					flash_write_pages(CFG_NET_PAGE, (uint8_t*)IP_Addr, 8);
					NVIC_SystemReset();
				}
			}
			break;
		case CFG_STATE_UPDATE:
			if((fw_idx + size) > FW_FLASH_LENGTH) {
				memcpy(&fw_flash[fw_idx], eth_rxd_buff, FW_FLASH_LENGTH - fw_idx);
				flash_write_pages(APP_FLASH_PAGE+fw_pages, fw_flash, FW_FLASH_LENGTH);
				memcpy(&fw_flash[0], &eth_rxd_buff[FW_FLASH_LENGTH - fw_idx], size + fw_idx - FW_FLASH_LENGTH);
				fw_idx = size + fw_idx - FW_FLASH_LENGTH;
				fw_pages++;
				fw_comp_size += size;
				if(fw_comp_size >= fw_length) {
					flash_write_pages(APP_FLASH_PAGE+fw_pages, fw_flash, fw_idx);
					gw_update_completed = 1;
					cfg_state = CFG_STATE_IDLE;
					
				}
			} else {
				memcpy(&fw_flash[fw_idx], eth_rxd_buff, size);
				fw_idx += size;
				fw_comp_size += size;
				if(fw_comp_size >= fw_length) {
					flash_write_pages(APP_FLASH_PAGE+fw_pages, fw_flash, fw_idx);
					gw_update_completed = 1;
					cfg_state = CFG_STATE_IDLE;
					
				}
			}
			break;
		default:break;
		
		
	}
}

void eth_app_task(void )
{

	W5500_Socket_Set();//W5500端口初始化配置

	if(W5500_Interrupt)//处理W5500中断		
	{
		W5500_Interrupt_Process();//W5500中断处理程序框架
	}
	if((S0_Data & S_RECEIVE) == S_RECEIVE)
	{
		S0_Data&=~S_RECEIVE;
		process_pc_msg(0);
		LED_WIFI_BLINK;
	}
			
}


