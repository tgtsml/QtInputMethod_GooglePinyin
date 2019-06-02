# Qt 拼音输入法，采用Google拼音内核



## 文件夹说明

###  googlepinyin
​		Google拼音核心源码

###  plugin
​		输入法插件源码

### window
​		对输入法的简单测试窗口

### Windows_test
​		Windows上运行测试结果
​		![](https://github.com/tgtsml/QtInputMethod_GooglePinyin/Windows_test/res.png)

## 编译说明（以release版本为例）
​	选择release版本
1. 先编译测试程序，再编译googlepinyin源码；
2. 把编译好的库文件libgooglepinyin.a放到plugin/googlepinyin目录下；
3. 再编译plugin源码，把编译后的库文件放到测试程序执行文件所在目录下的platforminputcontexts文件夹下；
4. 复制plugin目录下的dict目录到测试程序执行文件所在目录下；
5. 运行window测试代码即可测试输入法。


