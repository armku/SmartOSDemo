#ifndef _IOK027X_H_
#define _IOK027X_H_

<<<<<<< master
#include "B8266.h"
=======
#include "BaseBoard.h"
#include "Esp8266Module.h"

#include "TokenNet\TokenClient.h"
>>>>>>> local

#include "APP\Button_GrayLevel.h"

// WIFI触摸开关
<<<<<<< master
class IOK027X : public B8266
=======
class IOK027X : public BaseBoard, public Esp8266Module
>>>>>>> local
{
public:
	byte	LedsShow;					// LED 显示状态开关  0 刚启动时候的20秒   1 使能   2 失能
	uint	LedsTaskId;
<<<<<<< master
=======
	TokenClient*	Client;
>>>>>>> local

	IOK027X();

	// 联动开关
	void Union(Pin pin1, Pin pin2, bool invert);
	void InitLeds();
	void Restore();
	void FlushLed();			// 刷新led状态输出
	byte LedStat(byte showmode);

	static IOK027X* Current;
};

#endif
