#ifndef _
#pragma once

#define BAC_SUCCESS 0
#define BAC_FAILURE 1

//BYTE cmd_set[] = "bset";
//BYTE cmd_get[] = "bget";

typedef enum
{
    BAC_FALSE          = 0,
    BAC_TRUE           = 1
}BAC_BOOL_ENUM;

typedef unsigned char BYTE;
typedef unsigned char BAC_BOOL;  //2字节

//lfa 201808
#define DEFAULT_GATEWAY_IPADDR  "127.0.0.1"
#define DEFAULT_GATEWAY_IPPORT  4780

#define MSG_UPLOAD_PROJ_BEGIN_STRING "BEGIN UPLOAD PROJECT TO GATEWAY"
#define MSG_UPLOAD_PROJ_END_STRING   "END UPLOAD PROJECT TO GATEWAY"

#define MSG_DOWNLOAD_PROJ_BEGIN_STRING "BEGIN DOWNLOAD PROJECT TO PC"
#define MSG_DOWNLOAD_PROJ_END_STRING   "END DOWNLOAD PROJECT TO PC"

static BYTE g_MsgUploadProjBeginStr[] = "BEGIN UPLOAD PROJECT TO GATEWAY";
static BYTE g_MsgUploadProjEndStr[] = "END UPLOAD PROJECT TO GATEWAY";

static BYTE g_MsgDownloadProjBeginStr[] = "BEGIN DOWNLOAD PROJECT TO PC";
static BYTE g_MsgDownloadProjEndStr[] = "BEGIN UPLOAD PROJECT TO GATEWAY";

//所有PC发给网关的消息类型定义，2字节，WORD  (unsigned short)
typedef enum
{
    PC_GATEWAY_UPLOAD_PROJ_TO_GATEWAY          = 1000,
    PC_GATEWAY_DOWNLOAD_PROJ_TO_PC             = 1001
}MSG_TYPE_PC_TO_GATEWAY;

#define MAX_CHARS_IP_STRING  20
#define MAX_CHARS_GATEWAY_NAME  30
#define MAX_CHARS_DRIVER_NAME  MAX_CHARS_GATEWAY_NAME
#define MAX_CHARS_CHANNEL_NAME  MAX_CHARS_GATEWAY_NAME
#define MAX_CHANNELS    8  //最大通道数目

#define MAX_POINTNAME  20
#define MAX_DEVICENAME MAX_POINTNAME

//////////

#define	PackageNUM		200
#define	CODE_LEN(x)	(int)(sizeof(x)-1)
#define MAX_POINTNUM	260
#define MAX_DEVICE_NUM  32
#define DATASTYLENUM		7
#define REGSTYLENUM		4
#define BACNETUNITNUM	32
#define BACNETREGNUM	8
#define DATASQNUM			8

#define POINTSCALENUM	6
#define POINTBITNUM			16
#define UARTBAUDNUM		5
#define UARTPORTNUM		9
#define ROWNUM					12


#pragma pack(1)

//lfa 201808  网关全局配置
typedef struct _gateway_param{
    char    aGatewayName[MAX_CHARS_GATEWAY_NAME];  //网关名称, 0结尾的字符串
	char    aGatewayIP[MAX_CHARS_IP_STRING];       //网关IP， 0结尾的字符串
    WORD    usIpPort;         //网关IP端口号
    WORD    usDeviceID;       //BACnet 网关 设备 ID
    BYTE    bStartMst;        //0-不启用，即作为BACNET IP网关；1-启用MSTP，即作为MSTP网关
    BYTE    ucMac;     //1~255
    BYTE	ucUART_COM;       //1~255，对应COM1~COM255
    BYTE    ucUART_BAUD;      // 0~4， 分别对应 {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    BYTE    UART_DATA_BITS;   //7,8
    BYTE    UART_STOP_BITS;   //1,2
    BYTE    UART_PARITY_BITS; //校验位  奇偶校验
    BYTE    UART_LC;          //流控 0-无; 1-硬件RTC/CTS
    BYTE    UART_CRC;         //0-无；1-奇ODD；2-偶EVEN
    WORD    usMstpTimeout;    //毫秒  MSTP时，超时时间

    BYTE    ucEncodeType;     //网关字符编码 0-ANSCii; 1-UNICODE; 2-UTF8

	BYTE		AI_NUM;       //网关BACNET中AI的总点数
	BYTE		AO_NUM;
	BYTE		AV_NUM;
	BYTE		BI_NUM;
	BYTE		BO_NUM;
	BYTE		BV_NUM;
}GATEWAY_PARAM;

//所有驱动配置，暂时只支持RTU一个驱动
typedef struct _drivers_struct{
	char    aDriverName[MAX_CHARS_DRIVER_NAME];  //驱动名称, 0结尾的字符串  全局唯一
    char    aDriverImpName[MAX_CHARS_DRIVER_NAME];  //驱动实现的(代码)名称, 0结尾的字符串.  目前固定为  ModbusRTUClient
    WORD    usPollingTime;   //毫秒  轮训时间，访问所有设备的轮询时间，如果访问完所有设备所需要时间小于设定时间，则等待到达时间后，再轮询。否则轮询时间无效，已实际轮询话费的时间为准
}DRIVERS_STRUCT;

//单通道配置
typedef struct _channel_param{
    BYTE    cIsValid;       //0-无效；1-有效的通道配置
	char    aChannelName[MAX_CHARS_CHANNEL_NAME];  //通道名称, 0结尾的字符串。相同驱动下唯一，但是以后增加ChannelID，应该全局唯一。
    BYTE    usChannelId;        //通道ID，全局唯一，等于 ucUART_COM 
    BYTE	ucUART_COM;       //1~255，对应COM1~COM255
    BYTE    ucUART_BAUD;      // 0~4， 分别对应 {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    BYTE    UART_DATA_BITS;   //7,8
    BYTE    UART_STOP_BITS;   //1,2
    BYTE    UART_PARITY_BITS; //校验位  奇偶校验
    BYTE    UART_LC;          //流控 0-无; 1-硬件RTC/CTS
    BYTE    UART_CRC;         //0-无；1-奇ODD；2-偶EVEN
    WORD    usTimeout;    //毫秒  等待从设备回响应的超时时间
}CHANNEL_PARAM;

//所有通道配置
typedef struct _channels_struct{
	CHANNEL_PARAM	aChannels[MAX_CHANNELS];
}CHANNELS_STRUCT;

//所有设备
typedef struct _devicedatastyle{
    BYTE    bIsValid;    //0-无效；1-有效的设备配置
    char    aDevicename[MAX_DEVICENAME];    //lfa 201808
	BYTE	DEVICEID;       //设备ID，在Channel下唯一。全局不唯一
    BYTE    usChannelId;   //lfa 201808 记录在哪个通道下  来自 CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
	WORD	REQINTEVAL;
	WORD	WREFRASH;
	BYTE	WORDSQ;
	BYTE	DWORDSQ;
	BYTE	FLOATSQ;	
}DEVICEDATASTYLE;



typedef struct _device_param{
	//char        BACnetName[MAX_DEVICENAME];   //lfa 201808  网关名称
    //WORD        wBACnetIpPortNo;
    //BYTE        bStartMSTP;    //lfa 201808  是否启用MSTP，也就是网关用于转为BACNET MSTP。而不是BACNET IP
   
	//WORD		BACnetID;       //bacnet ID

	//BYTE		MAC;            //bacnet MAC

    //缺少bacnet mstp 通信超时时间 ?

	BYTE		DeviceNUM;

	BYTE		Device_Points[MAX_DEVICE_NUM];

	//BYTE		AI_NUM;         //下挂的一个modbus设备，有多少点转换为了 bacnet AI
	//BYTE		AO_NUM;
	//BYTE		AV_NUM;
	//BYTE		BI_NUM;
	//BYTE		BO_NUM;
	//BYTE		BV_NUM;

	//WORD		TIMEOUT;           //modbus 通道 通讯超时时间
	//BYTE		UART_COM;			//目前只能添加1个通道，这里存放唯一通道的 COM口配置: 高四位表示通道 modbus COM，低四位表示 BACnet COM
	//BYTE		UART_BAUD;			//目前只能添加1个通道，这里存放唯一通道的 COM口配置: 高四位表示通道 modbus 波特率，低四位表示 BACnet 波特率

	//BYTE		UART_DATA_BIT;	    //目前只能添加1个通道，这里存放唯一通道的 COM口配置: modbus 串口 数据位，停止位
	//BYTE		UART_LC_CRC;		//目前只能添加1个通道，这里存放唯一通道的 COM口配置: modbus 串口 流控，校验位  高四位流控；低四位CRC
}DEVICE_PARAM;

typedef struct _point_param{
    BYTE bIsValid;   //0--无效;  1--有效的tag点配置
    BYTE    usChannelId;   //lfa 201808 记录在哪个通道下  来自 CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)

	BYTE	modbusID;                   //tag点对应的 modbus ID  （设备ID）    来自 设备ID g_aDeviceDatastyle[i].DEVICEID
	BYTE	datasequence;				//tag点，最高位表示2字节的数据顺序，6、5、4位表示4字节的数据顺序，后四位表示单精度浮点数数据顺序。来自通道下设备的配置，没有使用到

	WORD	reqinterval;                //请求帧间隔，来自通道下设备的配置，没有使用到
	WORD	refrashw;                   //写刷新间隔，来自通道下设备的配置，没有使用到

	char	pointname[MAX_POINTNAME];       //tag点 名称

	BYTE	regStyle;                           //tag点 modbus 寄存器类型
	WORD	regAddr;	                        //tag点 modbus 寄存器地址
	BYTE	dataStyle_Bit;				//tag点 modbus 最高位为1表示设置bit位取值，最高位位0表示不设置bit位取值；高三位表示数据类型，低四位表示按位取值时的bit位
	BYTE	scalefactor;					//tag点 modbus  最高位位1表示设置比例因子，后四位表示4种比例因子

	BYTE	bRegStyle;              //bacnet 寄存器类型
	WORD	bRegAddr;               //bacnet 寄存器 地址
	BYTE	bUnit;                  //bacnet 数据单位
}POINT_PARAM;

//所有tag点
typedef struct _item_struct{
	DEVICE_PARAM	device_param;   //目前只能添加1个通道，所有设备的COM口配置 共用
	POINT_PARAM		point_param[MAX_POINTNUM];
}ITEM_STRUCT;


//lfa 201808        如下数据上传到网关
//1， 2字节命令码 MSG_TYPE_PC_TO_GATEWAY  上传到网关，首先发 1000  (PC_GATEWAY_UPLOAD_PROJ_TO_GATEWAY)
//2， g_GatewayPara 网关配置
//3， g_Drivers 驱动信息 （目前只支持配置 RTU 一个驱动）
//4， g_Channels  所有通道 （数组）
//5， g_aDeviceDatastyle  所有设备（数组）   通过字段 g_aDeviceDatastyle[].usChannelId 记录和通道的映射关系；
//6， g_ItemStruct  所有tag点，（数组） 通过字段g_ItemStruct.point_param[].usChannelId 和 g_ItemStruct.point_param[].modbusID ，记录tag点在哪个通道，哪个设备下
extern GATEWAY_PARAM g_GatewayPara;
extern DRIVERS_STRUCT g_Drivers;
extern CHANNELS_STRUCT g_Channels;
extern DEVICEDATASTYLE	g_aDeviceDatastyle[MAX_DEVICE_NUM];
extern ITEM_STRUCT  g_ItemStruct;
//////////

//extern MSG_BUFFER_STRUCT g_MsgBuffer;

#pragma pack(4)