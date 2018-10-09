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
typedef unsigned char BAC_BOOL;  //2�ֽ�

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

//����PC�������ص���Ϣ���Ͷ��壬2�ֽڣ�WORD  (unsigned short)
typedef enum
{
    PC_GATEWAY_UPLOAD_PROJ_TO_GATEWAY          = 1000,
    PC_GATEWAY_DOWNLOAD_PROJ_TO_PC             = 1001
}MSG_TYPE_PC_TO_GATEWAY;

#define MAX_CHARS_IP_STRING  20
#define MAX_CHARS_GATEWAY_NAME  30
#define MAX_CHARS_DRIVER_NAME  MAX_CHARS_GATEWAY_NAME
#define MAX_CHARS_CHANNEL_NAME  MAX_CHARS_GATEWAY_NAME
#define MAX_CHANNELS    8  //���ͨ����Ŀ

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

//lfa 201808  ����ȫ������
typedef struct _gateway_param{
    char    aGatewayName[MAX_CHARS_GATEWAY_NAME];  //��������, 0��β���ַ���
	char    aGatewayIP[MAX_CHARS_IP_STRING];       //����IP�� 0��β���ַ���
    WORD    usIpPort;         //����IP�˿ں�
    WORD    usDeviceID;       //BACnet ���� �豸 ID
    BYTE    bStartMst;        //0-�����ã�����ΪBACNET IP���أ�1-����MSTP������ΪMSTP����
    BYTE    ucMac;     //1~255
    BYTE	ucUART_COM;       //1~255����ӦCOM1~COM255
    BYTE    ucUART_BAUD;      // 0~4�� �ֱ��Ӧ {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    BYTE    UART_DATA_BITS;   //7,8
    BYTE    UART_STOP_BITS;   //1,2
    BYTE    UART_PARITY_BITS; //У��λ  ��żУ��
    BYTE    UART_LC;          //���� 0-��; 1-Ӳ��RTC/CTS
    BYTE    UART_CRC;         //0-�ޣ�1-��ODD��2-żEVEN
    WORD    usMstpTimeout;    //����  MSTPʱ����ʱʱ��

    BYTE    ucEncodeType;     //�����ַ����� 0-ANSCii; 1-UNICODE; 2-UTF8

	BYTE		AI_NUM;       //����BACNET��AI���ܵ���
	BYTE		AO_NUM;
	BYTE		AV_NUM;
	BYTE		BI_NUM;
	BYTE		BO_NUM;
	BYTE		BV_NUM;
}GATEWAY_PARAM;

//�����������ã���ʱֻ֧��RTUһ������
typedef struct _drivers_struct{
	char    aDriverName[MAX_CHARS_DRIVER_NAME];  //��������, 0��β���ַ���  ȫ��Ψһ
    char    aDriverImpName[MAX_CHARS_DRIVER_NAME];  //����ʵ�ֵ�(����)����, 0��β���ַ���.  Ŀǰ�̶�Ϊ  ModbusRTUClient
    WORD    usPollingTime;   //����  ��ѵʱ�䣬���������豸����ѯʱ�䣬��������������豸����Ҫʱ��С���趨ʱ�䣬��ȴ�����ʱ�������ѯ��������ѯʱ����Ч����ʵ����ѯ���ѵ�ʱ��Ϊ׼
}DRIVERS_STRUCT;

//��ͨ������
typedef struct _channel_param{
    BYTE    cIsValid;       //0-��Ч��1-��Ч��ͨ������
	char    aChannelName[MAX_CHARS_CHANNEL_NAME];  //ͨ������, 0��β���ַ�������ͬ������Ψһ�������Ժ�����ChannelID��Ӧ��ȫ��Ψһ��
    BYTE    usChannelId;        //ͨ��ID��ȫ��Ψһ������ ucUART_COM 
    BYTE	ucUART_COM;       //1~255����ӦCOM1~COM255
    BYTE    ucUART_BAUD;      // 0~4�� �ֱ��Ӧ {L"9600",L"19200",L"38400",L"57600",L"115200"}  CString StrUartBaud
    BYTE    UART_DATA_BITS;   //7,8
    BYTE    UART_STOP_BITS;   //1,2
    BYTE    UART_PARITY_BITS; //У��λ  ��żУ��
    BYTE    UART_LC;          //���� 0-��; 1-Ӳ��RTC/CTS
    BYTE    UART_CRC;         //0-�ޣ�1-��ODD��2-żEVEN
    WORD    usTimeout;    //����  �ȴ����豸����Ӧ�ĳ�ʱʱ��
}CHANNEL_PARAM;

//����ͨ������
typedef struct _channels_struct{
	CHANNEL_PARAM	aChannels[MAX_CHANNELS];
}CHANNELS_STRUCT;

//�����豸
typedef struct _devicedatastyle{
    BYTE    bIsValid;    //0-��Ч��1-��Ч���豸����
    char    aDevicename[MAX_DEVICENAME];    //lfa 201808
	BYTE	DEVICEID;       //�豸ID����Channel��Ψһ��ȫ�ֲ�Ψһ
    BYTE    usChannelId;   //lfa 201808 ��¼���ĸ�ͨ����  ���� CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)
	WORD	REQINTEVAL;
	WORD	WREFRASH;
	BYTE	WORDSQ;
	BYTE	DWORDSQ;
	BYTE	FLOATSQ;	
}DEVICEDATASTYLE;



typedef struct _device_param{
	//char        BACnetName[MAX_DEVICENAME];   //lfa 201808  ��������
    //WORD        wBACnetIpPortNo;
    //BYTE        bStartMSTP;    //lfa 201808  �Ƿ�����MSTP��Ҳ������������תΪBACNET MSTP��������BACNET IP
   
	//WORD		BACnetID;       //bacnet ID

	//BYTE		MAC;            //bacnet MAC

    //ȱ��bacnet mstp ͨ�ų�ʱʱ�� ?

	BYTE		DeviceNUM;

	BYTE		Device_Points[MAX_DEVICE_NUM];

	//BYTE		AI_NUM;         //�¹ҵ�һ��modbus�豸���ж��ٵ�ת��Ϊ�� bacnet AI
	//BYTE		AO_NUM;
	//BYTE		AV_NUM;
	//BYTE		BI_NUM;
	//BYTE		BO_NUM;
	//BYTE		BV_NUM;

	//WORD		TIMEOUT;           //modbus ͨ�� ͨѶ��ʱʱ��
	//BYTE		UART_COM;			//Ŀǰֻ�����1��ͨ����������Ψһͨ���� COM������: ����λ��ʾͨ�� modbus COM������λ��ʾ BACnet COM
	//BYTE		UART_BAUD;			//Ŀǰֻ�����1��ͨ����������Ψһͨ���� COM������: ����λ��ʾͨ�� modbus �����ʣ�����λ��ʾ BACnet ������

	//BYTE		UART_DATA_BIT;	    //Ŀǰֻ�����1��ͨ����������Ψһͨ���� COM������: modbus ���� ����λ��ֹͣλ
	//BYTE		UART_LC_CRC;		//Ŀǰֻ�����1��ͨ����������Ψһͨ���� COM������: modbus ���� ���أ�У��λ  ����λ���أ�����λCRC
}DEVICE_PARAM;

typedef struct _point_param{
    BYTE bIsValid;   //0--��Ч;  1--��Ч��tag������
    BYTE    usChannelId;   //lfa 201808 ��¼���ĸ�ͨ����  ���� CHANNELS_STRUCT.aChannels[].usChannelId  (CHANNEL_PARAM)

	BYTE	modbusID;                   //tag���Ӧ�� modbus ID  ���豸ID��    ���� �豸ID g_aDeviceDatastyle[i].DEVICEID
	BYTE	datasequence;				//tag�㣬���λ��ʾ2�ֽڵ�����˳��6��5��4λ��ʾ4�ֽڵ�����˳�򣬺���λ��ʾ�����ȸ���������˳������ͨ�����豸�����ã�û��ʹ�õ�

	WORD	reqinterval;                //����֡���������ͨ�����豸�����ã�û��ʹ�õ�
	WORD	refrashw;                   //дˢ�¼��������ͨ�����豸�����ã�û��ʹ�õ�

	char	pointname[MAX_POINTNAME];       //tag�� ����

	BYTE	regStyle;                           //tag�� modbus �Ĵ�������
	WORD	regAddr;	                        //tag�� modbus �Ĵ�����ַ
	BYTE	dataStyle_Bit;				//tag�� modbus ���λΪ1��ʾ����bitλȡֵ�����λλ0��ʾ������bitλȡֵ������λ��ʾ�������ͣ�����λ��ʾ��λȡֵʱ��bitλ
	BYTE	scalefactor;					//tag�� modbus  ���λλ1��ʾ���ñ������ӣ�����λ��ʾ4�ֱ�������

	BYTE	bRegStyle;              //bacnet �Ĵ�������
	WORD	bRegAddr;               //bacnet �Ĵ��� ��ַ
	BYTE	bUnit;                  //bacnet ���ݵ�λ
}POINT_PARAM;

//����tag��
typedef struct _item_struct{
	DEVICE_PARAM	device_param;   //Ŀǰֻ�����1��ͨ���������豸��COM������ ����
	POINT_PARAM		point_param[MAX_POINTNUM];
}ITEM_STRUCT;


//lfa 201808        ���������ϴ�������
//1�� 2�ֽ������� MSG_TYPE_PC_TO_GATEWAY  �ϴ������أ����ȷ� 1000  (PC_GATEWAY_UPLOAD_PROJ_TO_GATEWAY)
//2�� g_GatewayPara ��������
//3�� g_Drivers ������Ϣ ��Ŀǰֻ֧������ RTU һ��������
//4�� g_Channels  ����ͨ�� �����飩
//5�� g_aDeviceDatastyle  �����豸�����飩   ͨ���ֶ� g_aDeviceDatastyle[].usChannelId ��¼��ͨ����ӳ���ϵ��
//6�� g_ItemStruct  ����tag�㣬�����飩 ͨ���ֶ�g_ItemStruct.point_param[].usChannelId �� g_ItemStruct.point_param[].modbusID ����¼tag�����ĸ�ͨ�����ĸ��豸��
extern GATEWAY_PARAM g_GatewayPara;
extern DRIVERS_STRUCT g_Drivers;
extern CHANNELS_STRUCT g_Channels;
extern DEVICEDATASTYLE	g_aDeviceDatastyle[MAX_DEVICE_NUM];
extern ITEM_STRUCT  g_ItemStruct;
//////////

//extern MSG_BUFFER_STRUCT g_MsgBuffer;

#pragma pack(4)