#ifndef _AP0801_H_
#define _AP0801_H_

<<<<<<< master
#include "TokenBoard.h"

#include "Net\Socket.h"

#include "Device\Spi.h"
#include "Device\SerialPort.h"

#include "App\Alarm.h"

// 阿波罗0801
class AP0801 : public TokenBoard
=======
#include "BaseBoard.h"
#include "W5500Module.h"
#include "Esp8266Module.h"

// 阿波罗0801
class AP0801 : public BaseBoard, public W5500Module, public Esp8266Module
>>>>>>> local
{
public:
	List<OutputPort*>	Outputs;
	List<InputPort*>	Inputs;

<<<<<<< master
	Alarm*			AlarmObj;

	SpiConfig		Net;
	SerialConfig	Esp;

	AP0801();

	// 打开以太网W5500
	NetworkInterface* Create5500();
	// 打开Esp8266，作为主控或者纯AP
	NetworkInterface* Create8266();

	// ITransport* Create2401();

	void InitNet();
	void InitProxy();
	void InitAlarm();

=======
	AP0801();

>>>>>>> local
	static AP0801* Current;
};

#endif
