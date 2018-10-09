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
#define MAX_CHANNELS    4  //���ͨ����Ŀ

#define MAX_POINTNAME  MAX_CHARS_GATEWAY_NAME
#define MAX_DEVICENAME MAX_CHARS_GATEWAY_NAME

#define MAX_POINTNUM	260
#define MAX_DEVICE_NUM  32



#pragma pack(1)

//lfa 201808  ����ȫ������
typedef struct {
    char		gw_name[MAX_CHARS_GATEWAY_NAME];  //��������, 0��β���ַ���
	uint8_t		gw_ip[4];       //����IP�� 0��β���ַ���
    uint16_t    ip_port;         //����IP�˿ں�
    uint16_t    gw_id;       //BACnet ���� �豸 ID
    uint8_t		mstp_enable;        //0-�����ã�����ΪBACNET IP���أ�1-����MSTP������ΪMSTP����
    uint8_t		mac_addr;     //1~255
    uint8_t		com_id;       //1~255����ӦCOM1~COM255
    uint8_t		baud_rate;      // 0~4�� �ֱ��Ӧ {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    uint8_t    	data_bits;   //7,8
    uint8_t    	stop_bits;   //1,2
    //uint8_t   	parity; //У��λ  ��żУ��
    uint8_t    	lc;          //���� 0-��; 1-Ӳ��RTC/CTS
    uint8_t    	parity;         //0-�ޣ�1-��ODD��2-żEVEN
    uint16_t    timeout;    //����  MSTPʱ����ʱʱ��
    uint8_t		encode_type;     //�����ַ����� 0-ANSCii; 1-UNICODE; 2-UTF8
	uint8_t		ai_num;       //����BACNET��AI���ܵ���
	uint8_t		ao_num;
	uint8_t		av_num;
	uint8_t		bi_num;
	uint8_t		bo_num;
	uint8_t		bv_num;
	uint8_t		msi_num;
	uint8_t		mso_num;
}gw_param_t;//56bytes

typedef struct {
	char		driver_name[MAX_CHARS_DRIVER_NAME];  //��������, 0��β���ַ���  ȫ��Ψһ
    char		driver_imp_name[MAX_CHARS_DRIVER_NAME];  //����ʵ�ֵ�(����)����, 0��β���ַ���.  Ŀǰ�̶�Ϊ  ModbusRTUClient
    uint16_t	polling_time;   //����  ��ѵʱ�䣬���������豸����ѯʱ�䣬��������������豸����Ҫʱ��С���趨ʱ�䣬��ȴ�����ʱ�������ѯ��������ѯʱ����Ч����ʵ����ѯ���ѵ�ʱ��Ϊ׼
}driver_param_t;//62bytes

//��ͨ������
typedef struct {
    uint8_t    	valid;       //0-��Ч��1-��Ч��ͨ������
	char    	channel_name[MAX_CHARS_CHANNEL_NAME];  //ͨ������, 0��β���ַ�������ͬ������Ψһ�������Ժ�����ChannelID��Ӧ��ȫ��Ψһ��
    uint8_t    	channel_id;        //ͨ��ID��ȫ��Ψһ������ ucUART_COM 
    uint8_t		com_id;       //1~255����ӦCOM1~COM255
    uint8_t    	baud_rate;      // 0~4�� �ֱ��Ӧ {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    uint8_t    	data_bits;   //7,8
    uint8_t    	stop_bits;   //1,2
    //uint8_t    	parity; //У��λ  ��żУ��
    uint8_t    	lc;          //���� 0-��; 1-Ӳ��RTC/CTS
    uint8_t    	parity;         //0-�ޣ�1-��ODD��2-żEVEN
	uint8_t		retry_times;
    uint16_t    timeout;    //����  �ȴ����豸����Ӧ�ĳ�ʱʱ��
}channel_param_t;//41bytes

//����ͨ������
typedef struct {
	channel_param_t	channel_param[MAX_CHANNELS];
}channels_t;

//�����豸
typedef struct {
    uint8_t		valid;    //0-��Ч��1-��Ч���豸����
    char		device_name[MAX_DEVICENAME];    //lfa 201808
	uint8_t		device_id;       //�豸ID����Channel��Ψһ��ȫ�ֲ�Ψһ
    uint8_t		channel_id;   //lfa 201808 ��¼���ĸ�ͨ����  ���� CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
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
    uint8_t 	valid;   //0--��Ч;  1--��Ч��tag������
    uint8_t   	channel_id;   //lfa 201808 ��¼���ĸ�ͨ����  ���� CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
	uint8_t		device_id;                   //tag���Ӧ�� modbus ID  ���豸ID��    ���� �豸ID g_aDeviceDatastyle[i].DEVICEID
	//uint8_t		data_seq;				//tag�㣬���λ��ʾ2�ֽڵ�����˳��6��5��4λ��ʾ4�ֽڵ�����˳�򣬺���λ��ʾ�����ȸ���������˳������ͨ�����豸�����ã�û��ʹ�õ�
	//uint16_t	req_interval;                //����֡���������ͨ�����豸�����ã�û��ʹ�õ�
	//uint16_t	wrefresh;                   //дˢ�¼��������ͨ�����豸�����ã�û��ʹ�õ�
	char		point_name[MAX_POINTNAME];       //tag�� ����
	char		point_desc[MAX_CHARS_GATEWAY_NAME];
	uint8_t		mb_reg_type;                           //tag�� modbus �Ĵ�������
	uint16_t	mb_reg_addr;	                        //tag�� modbus �Ĵ������
	uint8_t		dt;				// 0-Boolean;1-Word(2Byte, 0 ~ 65535); 2-Short (2Byte, -32768 ~ 32767; 3-DWord (4Byte, 0 ~ 4294967295); 4-Long; 5-Float
	uint8_t		bit_mode;		//1:��λȡֵ
	uint8_t		which_bit;
	uint8_t		scale_mode;		//1:���Ա任
	uint8_t		scale_factor;					//tag�� modbus  ���λλ1��ʾ���ñ������ӣ�����λ��ʾ4�ֱ�������,0.001, 0.01, 0.1, 10, 100, 1000
	uint8_t		bn_reg_type;              //bacnet �Ĵ�������
	uint16_t	bn_reg_addr;               //bacnet �Ĵ��� ��ַ
	uint8_t		bn_reg_unit;                  //bacnet ���ݵ�λ�
}point_param_t;//37bytes

//����tag��
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
