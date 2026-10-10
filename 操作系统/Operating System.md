先学xv6，然后写lab在xv6上增加新特性

Operating System eg:Ubuntu
├── Kernel eg:Linux
├── system libraries
├── shell
├── utilities
├── services
└── GUI 等


Kernel 利用 CPU 提供的特权机制，把硬件资源抽象成进程、虚拟内存、文件等软件概念，并安全地分配给多个程序使用。

kernel/proc.c
kernel/vm.c
kernel/syscall.c
kernel/trap.c
kernel/fs.c
通过上面源码学会：
进程怎么实现
页表怎么实现
系统调用怎么实现
文件系统怎么实现
调度器怎么实现
锁怎么实现

**九、Kernel 启动时发生什么？**
Power on
↓
固件 BIOS / UEFI
↓
加载 bootloader
↓
加载 kernel 到内存
↓
CPU 开始执行 kernel
↓
kernel 初始化：
    内存
    页表
    CPU
    中断
    设备
    文件系统
    进程系统
↓
创建第一个用户进程
↓
启动 shell / init

**xv6 kernel会干什么？**
entry.S
↓
start.c
↓
main.c
↓
userinit()
↓
第一个用户进程

**计算机分层**
你写的用户程序
    ↓
xv6 操作系统 / kernel
    ↓
RISC-V 指令集架构 ISA
ISA 理解成软件和 CPU 之间的语言协议
类似的还有x86-64（电脑），ARM（手机）
    ↓
RISC-V CPU CPU 
厂商只要做出一个 CPU，能够正确执行这些 RISC-V 指令，那它就是一个 RISC-V CPU。
    ↓
硬件


kernel执行硬件和软件之间的协议ISA，合理的让软件调用硬件
ISA把硬件和对硬件能进行的操作定义成抽象的概念，便于软件程序使用


xv6