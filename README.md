Qt 拼音输入法，采用Google拼音内核

文件夹说明：
	1. googlepinyin：
		Google拼音核心源码
	2. plugin
		输入法插件源码
	3. window
		对输入法的简单测试窗口

编译说明：
	1. 先编译googlepinyin；
	2. 把编译好的库文件放到插件源码下；
	3. 插件源码编译好后，把编译后的库文件放到.exe文件夹下的platforminputcontext文件夹下；
	4. 运行window测试代码即可测试输入法。


