#ifndef	_FLASH_H
#define _FLASH_H

#include "stm32f10x.h"

#define FLASH_SIZE 512         

#if FLASH_SIZE<256
  #define SECTOR_SIZE           1024 
#else 
  #define SECTOR_SIZE           2048
#endif

#define APP_FLASH_PAGE				10
#define APP_ADDRESS					(FLASH_BASE+APP_FLASH_PAGE*SECTOR_SIZE)
#define	CFG_NET_PAGE				200
#define CFG_UPDATE_PAGE				201
#define CFG_STORE_START_PAGE		202

#define	GW_PARAM_PAGE				CFG_STORE_START_PAGE
#define	DRV_PARAM_PAGE				(CFG_STORE_START_PAGE+2)
#define	CHN_PARAM_PAGE				(CFG_STORE_START_PAGE+4)
#define	DEV_PARAM_PAGE				(CFG_STORE_START_PAGE+6)
#define	PNT_PARAM_PAGE				(CFG_STORE_START_PAGE+8)

#define	FLASH_PAGE_MIN				10
#define	FLASH_PAGE_MAX				250

typedef enum {
	MSG_GW,
	MSG_DRV,
	MSG_CHN,
	MSG_DEV,
	MSG_PNT
}pc_msg_type_t;

typedef enum{
    PC_UPLD         	= 1000,
    PC_DNLD             = 1001,
	PC_SET_IP			= 1002,
	PC_REBOOT			= 1005,
	PC_UPDATE_START		= 1006,
	PC_UPDATE_TRANS		= 1007,
	PC_DNLD_RSP			= 5000
}pc_msg_cmd_t;

#define MAX_CHARS_GATEWAY_NAME  30
#define MAX_CHARS_DRIVER_NAME  MAX_CHARS_GATEWAY_NAME
#define MAX_CHARS_CHANNEL_NAME  MAX_CHARS_GATEWAY_NAME
#define MAX_CHANNELS    4  //×î´óÍ¨µÀÊýÄ¿

#define MAX_POINTNAME  MAX_CHARS_GATEWAY_NAME
#define MAX_DEVICENAME MAX_CHARS_GATEWAY_NAME

#define MAX_POINTNUM	260
#define MAX_DEVICE_NUM  32



#pragma pack(1)

//lfa 201808  Íø¹ØÈ«¾ÖÅäÖÃ
typedef struct {
    char		gw_name[MAX_CHARS_GATEWAY_NAME];  //Íø¹ØÃû³Æ, 0½áÎ²µÄ×Ö·û´®
	uint8_t		gw_ip[4];       //Íø¹ØIP£¬ 0½áÎ²µÄ×Ö·û´®
    uint16_t    ip_port;         //Íø¹ØIP¶Ë¿ÚºÅ
    uint16_t    gw_id;       //BACnet Íø¹Ø Éè±¸ ID
    uint8_t		mstp_enable;        //0-²»ÆôÓÃ£¬¼´×÷ÎªBACNET IPÍø¹Ø£»1-ÆôÓÃMSTP£¬¼´×÷ÎªMSTPÍø¹Ø
    uint8_t		mac_addr;     //1~255
    uint8_t		com_id;       //1~255£¬¶ÔÓ¦COM1~COM255
    uint8_t		baud_rate;      // 0~4£¬ ·Ö±ð¶ÔÓ¦ {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    uint8_t    	data_bits;   //7,8
    uint8_t    	stop_bits;   //1,2
    //uint8_t   	parity; //Ð£ÑéÎ»  ÆæÅ¼Ð£Ñé
    uint8_t    	lc;          //Á÷¿Ø 0-ÎÞ; 1-Ó²¼þRTC/CTS
    uint8_t    	parity;         //0-ÎÞ£»1-ÆæODD£»2-Å¼EVEN
    uint16_t    timeout;    //ºÁÃë  MSTPÊ±£¬³¬Ê±Ê±¼ä
    uint8_t		encode_type;     //Íø¹Ø×Ö·û±àÂë 0-ANSCii; 1-UNICODE; 2-UTF8
	uint8_t		ai_num;       //Íø¹ØBACNETÖÐAIµÄ×ÜµãÊý
	uint8_t		ao_num;
	uint8_t		av_num;
	uint8_t		bi_num;
	uint8_t		bo_num;
	uint8_t		bv_num;
	uint8_t		msi_num;
	uint8_t		mso_num;
}gw_param_t;//56bytes

typedef struct {
	char		driver_name[MAX_CHARS_DRIVER_NAME];  //Çý¶¯Ãû³Æ, 0½áÎ²µÄ×Ö·û´®  È«¾ÖÎ¨Ò»
    char		driver_imp_name[MAX_CHARS_DRIVER_NAME];  //Çý¶¯ÊµÏÖµÄ(´úÂë)Ãû³Æ, 0½áÎ²µÄ×Ö·û´®.  Ä¿Ç°¹Ì¶¨Îª  ModbusRTUClient
    uint16_t	polling_time;   //ºÁÃë  ÂÖÑµÊ±¼ä£¬·ÃÎÊËùÓÐÉè±¸µÄÂÖÑ¯Ê±¼ä£¬Èç¹û·ÃÎÊÍêËùÓÐÉè±¸ËùÐèÒªÊ±¼äÐ¡ÓÚÉè¶¨Ê±¼ä£¬ÔòµÈ´ýµ½´ïÊ±¼äºó£¬ÔÙÂÖÑ¯¡£·ñÔòÂÖÑ¯Ê±¼äÎÞÐ§£¬ÒÑÊµ¼ÊÂÖÑ¯»°·ÑµÄÊ±¼äÎª×¼
}driver_param_t;//62bytes

//µ¥Í¨µÀÅäÖÃ
typedef struct {
    uint8_t    	valid;       //0-ÎÞÐ§£»1-ÓÐÐ§µÄÍ¨µÀÅäÖÃ
	char    	channel_name[MAX_CHARS_CHANNEL_NAME];  //Í¨µÀÃû³Æ, 0½áÎ²µÄ×Ö·û´®¡£ÏàÍ¬Çý¶¯ÏÂÎ¨Ò»£¬µ«ÊÇÒÔºóÔö¼ÓChannelID£¬Ó¦¸ÃÈ«¾ÖÎ¨Ò»¡£
    uint8_t    	channel_id;        //Í¨µÀID£¬È«¾ÖÎ¨Ò»£¬µÈÓÚ ucUART_COM 
    uint8_t		com_id;       //1~255£¬¶ÔÓ¦COM1~COM255
    uint8_t    	baud_rate;      // 0~4£¬ ·Ö±ð¶ÔÓ¦ {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    uint8_t    	data_bits;   //7,8
    uint8_t    	stop_bits;   //1,2
    //uint8_t    	parity; //Ð£ÑéÎ»  ÆæÅ¼Ð£Ñé
    uint8_t    	lc;          //Á÷¿Ø 0-ÎÞ; 1-Ó²¼þRTC/CTS
    uint8_t    	parity;         //0-ÎÞ£»1-ÆæODD£»2-Å¼EVEN
	uint8_t		retry_times;
    uint16_t    timeout;    //ºÁÃë  µÈ´ý´ÓÉè±¸»ØÏìÓ¦µÄ³¬Ê±Ê±¼ä
}channel_param_t;//41bytes

//ËùÓÐÍ¨µÀÅäÖÃ
typedef struct {
	channel_param_t	channel_param[MAX_CHANNELS];
}channels_t;

//ËùÓÐÉè±¸
typedef struct {
    uint8_t		valid;    //0-ÎÞÐ§£»1-ÓÐÐ§µÄÉè±¸ÅäÖÃ
    char		device_name[MAX_DEVICENAME];    //lfa 201808
	uint8_t		device_id;       //Éè±¸ID£¬ÔÚChannelÏÂÎ¨Ò»¡£È«¾Ö²»Î¨Ò»
    uint8_t		channel_id;   //lfa 201808 ¼ÇÂ¼ÔÚÄÄ¸öÍ¨µÀÏÂ  À´×Ô CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
	uint16_t	req_inteval;
	uint16_t	wrefresh;
	uint8_t		word_seq;
	uint8_t		dword_seq;
	uint8_t		float_seq;
	uint8_t		analog_group_jump;
	uint8_t		analog_group_num;
	uint8_t		digital_group_jump;
	uint8_t		digital_group_num;
	
}device_param_t;//30bytes

typedef struct {
	device_param_t device_param[MAX_DEVICE_NUM];
}devices_t;

typedef struct {
    uint8_t 	valid;   //0--ÎÞÐ§;  1--ÓÐÐ§µÄtagµãÅäÖÃ
    uint8_t   	channel_id;   //lfa 201808 ¼ÇÂ¼ÔÚÄÄ¸öÍ¨µÀÏÂ  À´×Ô CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
	uint8_t		device_id;                   //tagµã¶ÔÓ¦µÄ modbus ID  £¨Éè±¸ID£©    À´×Ô Éè±¸ID g_aDeviceDatastyle[i].DEVICEID
	//uint8_t		data_seq;				//tagµã£¬×î¸ßÎ»±íÊ¾2×Ö½ÚµÄÊý¾ÝË³Ðò£¬6¡¢5¡¢4Î»±íÊ¾4×Ö½ÚµÄÊý¾ÝË³Ðò£¬ºóËÄÎ»±íÊ¾µ¥¾«¶È¸¡µãÊýÊý¾ÝË³Ðò¡£À´×ÔÍ¨µÀÏÂÉè±¸µÄÅäÖÃ£¬Ã»ÓÐÊ¹ÓÃµ½
	//uint16_t	req_interval;                //ÇëÇóÖ¡¼ä¸ô£¬À´×ÔÍ¨µÀÏÂÉè±¸µÄÅäÖÃ£¬Ã»ÓÐÊ¹ÓÃµ½
	//uint16_t	wrefresh;                   //Ð´Ë¢ÐÂ¼ä¸ô£¬À´×ÔÍ¨µÀÏÂÉè±¸µÄÅäÖÃ£¬Ã»ÓÐÊ¹ÓÃµ½
	char		point_name[MAX_POINTNAME];       //tagµã Ãû³Æ
	char		point_desc[MAX_CHARS_GATEWAY_NAME];
	uint8_t		mb_reg_type;                           //tagµã modbus ¼Ä´æÆ÷ÀàÐÍ
	uint16_t	mb_reg_addr;	                        //tagµã modbus ¼Ä´æÆ÷µØÖ
	uint8_t		dt;				// 0-Boolean;1-Word(2Byte, 0 ~ 65535); 2-Short (2Byte, -32768 ~ 32767; 3-DWord (4Byte, 0 ~ 4294967295); 4-Long; 5-Float
	uint8_t		bit_mode;		//1:°´Î»È¡Öµ
	uint8_t		which_bit;
	uint8_t		scale_mode;		//1:ÏßÐÔ±ä»»
	uint8_t		scale_factor;					//tagµã modbus  ×î¸ßÎ»Î»1±íÊ¾ÉèÖÃ±ÈÀýÒò×Ó£¬ºóËÄÎ»±íÊ¾4ÖÖ±ÈÀýÒò×Ó,0.001, 0.01, 0.1, 10, 100, 1000
	uint8_t		bn_reg_type;              //bacnet ¼Ä´æÆ÷ÀàÐÍ
	uint16_t	bn_reg_addr;               //bacnet ¼Ä´æÆ÷ µØÖ·
	uint8_t		bn_reg_unit;                  //bacnet Êý¾Ýµ¥Î»·
}point_param_t;//37bytes

//ËùÓÐtagµã
typedef struct _item_struct{
	point_param_t	point_param[MAX_POINTNUM];
}points_t;

typedef struct {
	pc_msg_cmd_t		cmd;
	uint32_t			length;
	gw_param_t			gw_param;
	driver_param_t		drv_param;
	channels_t			chn_param;
	devices_t			dev_param;
	points_t			pnt_param;
}glb_cfg_t;

#pragma pack(4)

void load_cfg(void);
int flash_write_pages(uint32_t idx,uint8_t *data,uint32_t count);
int flash_read_pages(uint32_t idx,uint8_t *data,uint32_t count);
#endif
