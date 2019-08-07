1、编译SmartOS_F1D.lib放入Src\SmartOS目录下

2、运行Src\SampleF1\SmartOSF1.uvprojx编译通过下载到开发板上运行正常



编译方法库：

1、需要SmartOS、STM32F1xx（此库文件夹改名为LibF1）放入同一个文件夹

2、文件夹SmartOS\TOOL\下新建F1.bat,文件内容如下

XScript.exe Build_SmartOS_F1.cs

3、运行新建的bat文件

4、拷贝文件夹SmartOS\下生成的SmartOS_F1D.lib使用



