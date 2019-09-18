# Dandelion

本项目是用C++重写Shadowsocks项目代码，向Shadowsocks致敬！
第一个版本要实现的功能如下：
1. 服务端：
a. 支持ipv4、ipv6
b. 支持TCP,暂不支持UDP
c. 实现事件驱动队列，目前仅支持epoll
d. DNS查询
e. 完成代理功能

2. 客户端

a. 支持ipv4、ipv6
b. 支持TCP,暂不支持UDP
c. 实现事件驱动队列，目前仅支持epoll
d. 完成代理功能

总结一下， 完成客户端和服务端的开发， 并建立完备的测试机制

项目代号： 野子，  英文名： Dandelion

Desgin

1. 配置读取
2. 事件队列封装
3. DNS查询
4. 代理协议封装
5. TCPRelay


编译：
安装univalue, https://github.com/jgarzik/univalue.git
运行make即可

