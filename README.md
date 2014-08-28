cppdnspod
=========

cppddnspod for linux

安装方法：

下载源码后进入程序目录，

修改cppdnspod.cc中的相关变量的值，

执行make命令编译源码，

自己想办法将生成的执行文件加到开机自启动。
（我在rc.local里添加了这句话实现开机自启动 nohup /home/menter/cppdnspod/cppdnspod &）

注意：

编译源码前需要用到libcurl库，如果没有请先安装。


程序执行步骤：

1、循环访问私有url获取验证，如果访问成功则说明ip没有改变，不需要更新dns。
2、如果访问私有url失败则访问公网url获取ip，公网url自己定义，但不要滥用，否则可能被禁。如果公网返回的结果ip没有改变，则不需要更新dns，如果发现ip改变则访问dnspod api更新dns。

此程序优点：

通过双重方式验证私有ip是否改变，在ip没有改变的情况下，不会更新dns，彻底杜绝了滥用dnspod api的行为。
