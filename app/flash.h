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
#define MAX_CHANNELS    4  //最大通道数目

#define MAX_POINTNAME  MAX_CHARS_GATEWAY_NAME
#define MAX_DEVICENAME MAX_CHARS_GATEWAY_NAME

#define MAX_POINTNUM	260
#define MAX_DEVICE_NUM  32



#pragma pack(1)

//lfa 201808  网关全局配置
typedef struct {
    char		gw_name[MAX_CHARS_GATEWAY_NAME];  //网关名称, 0结尾的字符串
	uint8_t		gw_ip[4];       //网关IP， 0结尾的字符串
    uint16_t    ip_port;         //网关IP端口号
    uint16_t    gw_id;       //BACnet 网关 设备 ID
    uint8_t		mstp_enable;        //0-不启用，即作为BACNET IP网关；1-启用MSTP，即作为MSTP网关
    uint8_t		mac_addr;     //1~255
    uint8_t		com_id;       //1~255，对应COM1~COM255
    uint8_t		baud_rate;      // 0~4， 分别对应 {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    uint8_t    	data_bits;   //7,8
    uint8_t    	stop_bits;   //1,2
    //uint8_t   	parity; //校验位  奇偶校验
    uint8_t    	lc;          //流控 0-无; 1-硬件RTC/CTS
    uint8_t    	parity;         //0-无；1-奇ODD；2-偶EVEN
    uint16_t    timeout;    //毫秒  MSTP时，超时时间
    uint8_t		encode_type;     //网关字符编码 0-ANSCii; 1-UNICODE; 2-UTF8
	uint8_t		ai_num;       //网关BACNET中AI的总点数
	uint8_t		ao_num;
	uint8_t		av_num;
	uint8_t		bi_num;
	uint8_t		bo_num;
	uint8_t		bv_num;
	uint8_t		msi_num;
	uint8_t		mso_num;
}gw_param_t;//56bytes

typedef struct {
	char		driver_name[MAX_CHARS_DRIVER_NAME];  //驱动名称, 0结尾的字符串  全局唯一
    char		driver_imp_name[MAX_CHARS_DRIVER_NAME];  //驱动实现的(代码)名称, 0结尾的字符串.  目前固定为  ModbusRTUClient
    uint16_t	polling_time;   //毫秒  轮训时间，访问所有设备的轮询时间，如果访问完所有设备所需要时间小于设定时间，则等待到达时间后，再轮询。否则轮询时间无效，已实际轮询话费的时间为准
}driver_param_t;//62bytes

//单通道配置
typedef struct {
    uint8_t    	valid;       //0-无效；1-有效的通道配置
	char    	channel_name[MAX_CHARS_CHANNEL_NAME];  //通道名称, 0结尾的字符串。相同驱动下唯一，但是以后增加ChannelID，应该全局唯一。
    uint8_t    	channel_id;        //通道ID，全局唯一，等于 ucUART_COM 
    uint8_t		com_id;       //1~255，对应COM1~COM255
    uint8_t    	baud_rate;      // 0~4， 分别对应 {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    uint8_t    	data_bits;   //7,8
    uint8_t    	stop_bits;   //1,2
    //uint8_t    	parity; //校验位  奇偶校验
    uint8_t    	lc;          //流控 0-无; 1-硬件RTC/CTS
    uint8_t    	parity;         //0-无；1-奇ODD；2-偶EVEN
	uint8_t		retry_times;
    uint16_t    timeout;    //毫秒  等待从设备回响应的超时时间
}channel_param_t;//41bytes

//所有通道配置
typedef struct {
	channel_param_t	channel_param[MAX_CHANNELS];
}channels_t;

//所有设备
typedef struct {
    uint8_t		valid;    //0-无效；1-有效的设备配置
    char		device_name[MAX_DEVICENAME];    //lfa 201808
	uint8_t		device_id;       //设备ID，在Channel下唯一。全局不唯一
    uint8_t		channel_id;   //lfa 201808 记录在哪个通道下  来自 CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
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
    uint8_t 	valid;   //0--无效;  1--有效的tag点配置
    uint8_t   	channel_id;   //lfa 201808 记录在哪个通道下  来自 CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
	uint8_t		device_id;                   //tag点对应的 modbus ID  （设备ID）    来自 设备ID g_aDeviceDatastyle[i].DEVICEID
	//uint8_t		data_seq;				//tag点，最高位表示2字节的数据顺序，6、5、4位表示4字节的数据顺序，后四位表示单精度浮点数数据顺序。来自通道下设备的配置，没有使用到
	//uint16_t	req_interval;                //请求帧间隔，来自通道下设备的配置，没有使用到
	//uint16_t	wrefresh;                   //写刷新间隔，来自通道下设备的配置，没有使用到
	char		point_name[MAX_POINTNAME];       //tag点 名称
	char		point_desc[MAX_CHARS_GATEWAY_NAME];
	uint8_t		mb_reg_type;                           //tag点 modbus 寄存器类型
	uint16_t	mb_reg_addr;	                        //tag点 modbus 寄存器地�
	uint8_t		dt;				// 0-Boolean;1-Word(2Byte, 0 ~ 65535); 2-Short (2Byte, -32768 ~ 32767; 3-DWord (4Byte, 0 ~ 4294967295); 4-Long; 5-Float
	uint8_t		bit_mode;		//1:按位取值
	uint8_t		which_bit;
	uint8_t		scale_mode;		//1:线性变换
	uint8_t		scale_factor;					//tag点 modbus  最高位位1表示设置比例因子，后四位表示4种比例因子,0.001, 0.01, 0.1, 10, 100, 1000
	uint8_t		bn_reg_type;              //bacnet 寄存器类型
	uint16_t	bn_reg_addr;               //bacnet 寄存器 地址
	uint8_t		bn_reg_unit;                  //bacnet 数据单位�
}point_param_t;//37bytes

//所有tag点
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
