# 实验要求

![1538926267113](report.assets/homework_requirements.png)

# 实验前准备

## 实验器材

一共三台装有Linux系统的电脑。源主机用的是Arch系统，目标主机用的是Ubuntu系统，NFS服务器用的是Ubuntu系统。

## 实验软件

- virt-manager
- nfsserver

# 实验过程

## 搭建NFS服务器



## 建立虚拟机

1. 添加 NFS 存储池到源主机的virt-manager中
2. 源主机上创建建立在NFS共享存储上的虚拟机
3. 开启虚拟机

## 在目标主机上的链接

1. 添加 NFS 存储池到目标主机的virt-manager中

# 实验结论

遇到特别困难的bug，做不出来。


#参考资料

- [KVM virtual machine mirgration tutorials](https://www.linux-kvm.org/page/Migration)
- https://blog.csdn.net/taiyang1987912/article/details/47973479
- https://www.ibm.com/developerworks/cn/linux/l-linux-kvm/index.html    
- https://www.ibm.com/developerworks/cn/linux/l-cn-mgrtvm2/index.html
- http://www.cnblogs.com/liuyansheng/p/5985633.html
- https://www.ibm.com/developerworks/cn/linux/l-cn-mgrtvm2/index.html