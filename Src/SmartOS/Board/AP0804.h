#ifndef _AP0804_H_
#define _AP0804_H_

#include "BaseBoard.h"
#include "GsmModule.h"

// 阿波罗0804 4G通信
class AP0804 : public BaseBoard, public GsmModule
{
public:
	List<OutputPort*>	Outputs;
	List<InputPort*>	Inputs;

	AP0804();

	static AP0804* Current;
};

#endif
