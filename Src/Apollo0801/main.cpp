#include "Board\AP0801.h"
#include "Board\LinkBoard.h"
#include "Device\SerialPort.h"
#include "Message\Api.h"

#pragma pack(push)	// 保存对齐状态
#pragma pack(1)
// 主要数据区
typedef struct
{
	byte	Length;
	byte	Leds[2];

	byte Size() { return sizeof(this[0]); }
} TData;
#pragma pack(pop)
TData* Data;
#define DOF(P) offsetof(TData, P)

AP0801 bsp;
LinkBoard link;

// 按键中断
void OnPress(InputPort& port, bool down)
{
	if (down) return;

	// 翻转跟按钮相同位置的指示灯
	link.Write(DOF(Leds) + port.Index, 2);

	link.OnLongPress(&port, down);
}

void InitPort()
{
	// 绑定指示灯到数据区
	static DataOutputPort	DLED[2];
	for (int i = 0; i < ArrayLength(DLED); i++)
	{
		DLED[i].Port = bsp.Leds[i];
		link.Register(DOF(Leds) + i, DLED[i]);
	}
}

// API测试调用
int Test(void* param, const String& args, String& result)
{
	if(!args) return 0;
	
	args.Show(true);				// 显示API指令
	result = "this is test";		// 返回API执行的结果
	
	return 0;
}

//网络设置
static void InitNet()
{
	// 打开网络电源
	static OutputPort power(PE2);
	power = true;

	//bsp.InitProxy();
	//bsp.InitAlarm();
	
	// 初始化令牌客户端，后续端口注册数据区
	link.InitClient("tcp://front.peaceiot.com:22333");
	
	//W5500设置
	bsp.Create5500(bsp.Leds[0]);
	//WiFi设置
	//bsp.InitWiFi("TEST","12345678");						//设置默认WiFi
	bsp.Create8266(bsp.Leds[1]);
	
	link.Client->PingTime = 30;//3 * 60;					//心跳时间*1000ms
	link.Client->MaxNotActive = 10 * 60 * 1000;				//最大不活跃时间ms
	
	link.Client->Open();
}

//主函数
int main(void)
{
	// 初始化系统
	bsp.Init(0x0801, "AP0801");
	// 初始化数据区
	Data = (TData*)link.InitData(Data, Data->Size());

	bsp.InitLeds();
	bsp.InitButtons(OnPress);

	Api.Register("Api/Test", &Test, nullptr);		    	// 注册API
	InitPort();

	//网络设置
	InitNet();

	Sys.Start();
}

