#ifndef _AP0803_H_
#define _AP0803_H_

<<<<<<< master
#include "TokenBoard.h"

#include "Net\Socket.h"

#include "Device\SerialPort.h"
#include "App\Alarm.h"

// 阿波罗0803 GPRS通信
class AP0803 : public TokenBoard
=======
#include "BaseBoard.h"
#include "GsmModule.h"

// 阿波罗0803 GPRS通信
class AP0803 : public BaseBoard, public GsmModule
>>>>>>> local
{
public:
	List<OutputPort*>	Outputs;
	List<InputPort*>	Inputs;

<<<<<<< master
	Alarm*			AlarmObj;

	SerialConfig	Gsm;

	AP0803();

	// 打开GPRS
	NetworkInterface* CreateA67();
	NetworkInterface* CreateSIM900A();

	void InitNet();
	void InitProxy();
	void InitAlarm();

=======
	AP0803();

>>>>>>> local
	static AP0803* Current;
};

#endif
