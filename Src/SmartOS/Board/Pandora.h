#ifndef _Pandora_H_
#define _Pandora_H_

#include "BaseBoard.h"
#include "W5500Module.h"
#include "Esp8266Module.h"

// 潘多拉0903
class PA0903 : public BaseBoard, public W5500Module, public Esp8266Module
{
public:
	//List<OutputPort*>	Outputs;
	//List<InputPort*>	Inputs;
	
	PA0903();

<<<<<<< master
	// 设置数据区
	void* InitData(void* data, int size);
	// 写入数据区并上报
	void Write(uint offset, byte data);
	void Register(int index, IDataPort& dp);

	void InitLeds();
	void InitButtons(const Delegate2<InputPort&, bool>& press);

	// 打开以太网W5500
	NetworkInterface* Create5500();

	// 打开Esp8266，作为主控或者纯AP
	NetworkInterface* Create8266();
	//ITransport* Create2401();

	void InitClient();
	void InitNet();
	void InitProxy();
	void InitAlarm();

	void Restore();
	void OnLongPress(InputPort* port, bool down);

=======
>>>>>>> local
	static PA0903* Current;
};

#endif
