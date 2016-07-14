# 全日志A20平台的GPIO驱动例子
## 开发环境 android studio ##

GPIO_DEMO程序例子里面有两种操作GPIO的方法


1.直接读取修改 /sys/class/gpio_sw目录下文件

	修改对应GPIO目录下的data实现高低电平变化

	修改对应GPIO目录下的cfg实现输入输出控制

2.调用官方提供的库

![](/png/gpio.png)

	A20-gpio 调用 gpio_lib