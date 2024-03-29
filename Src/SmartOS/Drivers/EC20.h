﻿#ifndef __EC20_H__
#define __EC20_H__

#include "Device\Port.h"

#include "App\AT.h"
#include "App\FlushPort.h"

#include "Net\Socket.h"
#include "Net\NetworkInterface.h"
#include "Net\ITransport.h"

#include "Message\DataStore.h"
#include "Message\Pair.h"

// 4G的AT指令集 EC20
class EC20 : public NetworkInterface
{
public:
	AT		At;		// AT操作对象
	cstring	APN;
	bool	Mux;	// 开启多路socket模式，最多同时开启4路

	FlushPort*	NetLed;		// 网络指示灯
	FlushPort*	DataLed;	// 数据指示灯

	OutputPort	_Power;	// 电源
	OutputPort	_Reset;	// 重置
	OutputPort	_LowPower;	// 低功耗

	// 多个硬件socket
	void*	Sockets[11];

	Delegate<Buffer&>	Received;

	//ushort	Country;	// 国家MCC 3位
	//ushort	Network;	// 网络MNC 2位
	uint	Network;	// 国家MCC + 网络MNC 3位+2位
	ushort	Area;		// 基站区域
	ushort	CellID;		// 基站编码

	EC20();
	virtual ~EC20();

	void Init(ITransport* port);
	void Init(COM idx, int baudrate = 115200);
	void Set(Pin power = P0, Pin rst = P0, Pin low = P0);

	virtual bool Config();
	void SetLed(Pin led);
	void SetLed(OutputPort& led);
	void SetLed(OutputPort& netled, OutputPort& dataled);
	void RemoveLed();

	virtual Socket* CreateSocket(NetType type);

	/******************************** 基础指令 ********************************/
	bool Test(int times = 10, int interval = 500);
	String GetVersion();
	bool Echo(bool open);
	String GetIMSI();
	// 查询SIM的CCID，也可以用于查询SIM是否存或者插好
	String GetCCID();
	
	/******************************** GPS服务 ********************************/
	bool GpsPower();
	bool GetFormat();
	bool NmeaEnable();
	bool GpsClose();
	void NmeaGga();

	/******************************** 网络服务 ********************************/
	// 获取当前运营商
	String GetMobile();
	// 检查网络是否注册
	bool QueryRegister();
	String QuerySignal();
	bool SetPDP();

	/******************************** TCP/IP ********************************/
	int IPStart(const NetUri& remote);
	virtual bool IPSend(int index, const Buffer& data);
	bool ModeSet(int index);
	bool SendData(const String& cmd, const Buffer& bs);
	bool IPClose(int index);
	String IPStatus();

protected:
	uint		_task;		// 调度任务
	ByteArray	_Buffer;	// 待处理数据包
	IPEndPoint	_Remote;	// 当前数据包远程地址
	int		_Error;

	// 打开与关闭
	virtual bool OnOpen();
	virtual void OnClose();
	// 检测连接
	virtual bool OnLink(uint retry);

	bool CheckReady();

	// 数据到达
	virtual void OnReceive(Buffer& bs);
	void OnProcess(int index, Buffer& data, const IPEndPoint& remote);

	// 处理收到的数据包
	void Process();
};

class EC20Socket : public ITransport, public Socket
{
protected:
	EC20&	_Host;
	byte	_Index;
	int		_Error;

public:
	EC20Socket(EC20& host, NetType protocol, byte idx);
	virtual ~EC20Socket();

	// 打开Socket
	virtual bool OnOpen();
	virtual void OnClose();

	virtual bool OnWrite(const Buffer& bs);
	virtual uint OnRead(Buffer& bs);

	// 发送数据
	virtual bool Send(const Buffer& bs);
	// 接收数据
	virtual uint Receive(Buffer& bs);

	// 收到数据
	virtual void OnProcess(const Buffer& bs, const IPEndPoint& remote);
};

class EC20Tcp : public EC20Socket
{
public:
	EC20Tcp(EC20& host, byte idx);

	virtual String& ToStr(String& str) const { return str + "Tcp_" + Local.Port; }
};

class EC20Udp : public EC20Socket
{
public:
	EC20Udp(EC20& host, byte idx);

	virtual bool SendTo(const Buffer& bs, const IPEndPoint& remote);

	virtual String& ToStr(String& str) const { return str + "Udp_" + Local.Port; }

private:
	virtual bool OnWriteEx(const Buffer& bs, const void* opt);
};

#endif
