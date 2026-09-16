circuit（源自 circle“圆”+ it“走”）电路
我感觉找到了研究学习方向，但是我怎么跟我老师说呢

MCU
cpu + ROM + RAM + IO
处理 + 存写好的程序 + 存变量数据 + 输入输出
时钟控制每个部件按照周期运行，一个时间周期执行一条指令

晶体决定主要频率，外围电路保证并微调振荡，再
通过PLL变成高频时钟

【电赛零基础AI+速通，一个视频学完单片机。GPIO PWM ADC TIM IRQ I2C SPI UART WDG DMA【BA】】 https://www.bilibili.com/video/BV1ebwEzAE2a/?share_source=copy_web&vd_source=67c5cc72916ade0a68820da23fe51aba

【极其的巧妙设计！模拟转数字信号！5分钟让你看明白！ADC的工作原理，】 https://www.bilibili.com/video/BV1BV4y1V7nE/?share_source=copy_web&vd_source=67c5cc72916ade0a68820da23fe51aba

【什么是模拟信号？数字信号？区别是什么？它们又是如何完成转换的？】 https://www.bilibili.com/video/BV1Vp411o7aC/?share_source=copy_web&vd_source=67c5cc72916ade0a68820da23fe51aba

一、 模拟信号转数字信号（A/D 转换 / ADC）
采样 量化 编码
二、 数字信号转模拟信号（D/A 转换 / DAC）
解码和加权 平滑滤波

【CPU中寄存器的底层锁存器的原理】 https://www.bilibili.com/video/BV1efLQzZECs/?share_source=copy_web&vd_source=67c5cc72916ade0a68820da23fe51aba

锁存器的双稳态电路 
(0,0)是锁存状态输入 (1,1)是电平不断变化的混乱状态输入
通过或门将双稳态对应两种不同的输入(1,0) (0,1)
写入 保持 读出


数电触发器
