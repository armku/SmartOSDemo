// 本脚本文件需要安装XScript才能双击运行，下载后解压缩运行一次XScript.exe即可完成安装
// http://x.newlifex.com/XScript.zip

var build = Builder.Create("MDK");
build.Init(false);
build.CPU = "Cortex-M0";
build.Defines.Add(Host.Items["def1"] + "");
build.Defines.Add(Host.Items["def2"] + "");
build.Defines.Add(Host.Items["def3"] + "");

var root = "..\\";
foreach(var item in root.AsDirectory().GetAllFiles("*.7z", true))
{
	var dz = item.FullName.TrimEnd(".7z").AsFile();
	if(!dz.Exists || dz.LastWriteTime < item.LastWriteTime && dz.LastAccessTime < item.LastWriteTime)
	{
		Console.WriteLine("解压缩 {0}", item.FullName);
		item.Extract(dz.DirectoryName, true);
	}
}

build.AddIncludes(root + "SmartOS");
build.AddLibs(root + "Lib", "STM32F0xx?.Lib");
build.AddLibs(root + "SmartOS", "SmartOS_M0?.Lib");
build.AddLibs(root + "SmartOS", "SmartOS_F0?.Lib");

build.AddFiles(".", "*.c;*.cpp", false);
build.CompileAll();
build.Build();

build.Debug = true;
//build.Preprocess = true;
build.CompileAll();
build.Build();