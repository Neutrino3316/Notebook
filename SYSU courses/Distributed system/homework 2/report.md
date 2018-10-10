# 分布式系统第二次作业

小组人员：

- 16337085 胡中林
- 16337339 朱祎康

# 实验要求

![homework_requirements](report.assets/homework_requirements.png)

# 实验原理

动态迁移就是在保证虚拟机上服务正常运行的同时，将一个虚拟机系统从一个物理主机移动到另一个物理主机的过程。该过程不会对最终用户造成明显的影响，从而使得管理员能够在不影响用户正常使用的情况下，对物理服务器进行离线维修或者升级。与静态迁移不同的是，为了保证迁移过程中虚拟机服务的可用，迁移过程仅有非常短暂的停机时间。迁移的前面阶段，服务在源主机的虚拟机上运行，当迁移进行到一定阶段，目的主机已经具备了运行虚拟机系统的必须资源，经过一个非常短暂的切换，源主机将控制权转移到目的主机，虚拟机系统在目的主机上继续运行。对于虚拟机服务本身而言，由于切换的时间非常短暂，用户感觉不到服务的中断，因而迁移过程对用户是透明的。动态迁移适用于对虚拟机服务可用性要求很高的场合。

目前主流的动态迁移工具，VMware 的 VMotion，Citrix 的 XenMotion，他们都依赖于物理机之间采用 SAN（storage area network）或 NAS（network-attached storage）之类的集中式共享外存设备，因而在迁移时只需要进行虚拟机系统内存执行状态的迁移，从而获得较好的迁移性能。

本实验用的是virt-manager程序自带的迁移

# 实验前准备

## 实验器材

一共三台装有Linux系统的电脑。源主机用的是Arch系统，目标主机用的是Ubuntu系统，NFS服务器用的是Ubuntu系统。

## 实验软件

主要用到以下软件：
- virt-manager
- nfs server
- openssh server

# 实验过程

## 搭建NFS服务器

- 服务器地址：`192.168.199.166`
- 此处分享的目录文件为：`/home/zyhhaohao55/Downloads`
- 可以连接的IP为：`192.168.199.*` 
- 挂载用户的权限：`（rw, sync, no_subtree_check, no_root_squash）`
目的：虚拟机迁移需要将虚拟机的磁盘文件存储在NFS服务器上，这样在传递数据的时候就不用传递磁盘数据，传递的时候就只用传递内存数据就可以了。
1. 首先在系统中安装nfs-kernel-server,这是搭建NFS服务器需要的软件
2. 然后进入/etc/exports文档当中，修改文档，在文档的最后一行加上共享地址、IP和权限
3. 在源主机和目标主机上用`showmount -e 192.168.199.166`这条命令来查看是否成功搭建NFS服务器


## 建立虚拟机

1. 在源主机上挂载NFS服务器
2. 添加 NFS 存储池到源主机的virt-manager中。在存储池中新增一个池，命名为`nfs`，类型选择`netfs`，目标路径使用自动创建的，主机名用`192.168.199.166`， 共享目录为`/home/zyhhaohao55/Downloads`
![KVM Storage](report.assets/01.png)
![create storage pool 1/2](report.assets/02.png)
![create storage pool 2/2](report.assets/03.png)
然后创建一个10GB大小的`qcow2`虚拟磁盘文件，创建完之后刷新下，并且在NFS服务器相应的目录查看一下，确保创建成功。
![create storage pool finish](report.assets/04.png)
3. 源主机上创建建立在NFS共享存储上的虚拟机。
![create new virtual machine 1/5](report.assets/05.png)
使用本地的Ubuntu ISO镜像文件安装虚拟机
![create new virtual machine 2/5](report.assets/06.png)
![create new virtual machine 3/5](report.assets/07.png)
内存1024MB，分配一个CPU
![create new virtual machine 4/5](report.assets/08.png)
存储文件就选择刚才创建的那个10GB的虚拟磁盘文件。
![create new virtual machine 5/5](report.assets/09.png)
3. 在虚拟机中使用iso镜像文件安装系统
![install ubuntu](report.assets/10.png)

## 在目标主机上的连接

1. 添加 NFS 存储池到目标主机的virt-manager中，方法和在源主机的方法一致
2. 在目标主机上开启ssh服务
3. 在源主机的virt-manager新建连接，然后输入目标主机的用户名和目标主机IP地址，就可以连接了。不过这里遇到一个小问题，可以通过`sudo virt-manager --no-fork`来再次打开软件解决，不然的话无法输入ssh的密码。

## 迁移虚拟机

1. 在源主机上开启虚拟机
2. 在源主机的virt-manager中连接到目标主机
![connect to the target](report.assets/11.png)
3. 待开机完成后迁移虚拟机
![migrate](report.assets/15.png)

# 实验结论

因为每一次重启虚拟机要花费半个小时以上的时间，这个时间太长，让人无法接受。所以我们放弃了尝试解决最后一个问题。

# 遇到的问题

## 1. 无法在源主机的virt-manager中连接到NFS服务器

在源主机的Arch系统重启网络服务。

## 2. 无法在源主机的virt-manager中连接到目标主机

Arch系统下的virt-manager不能弹窗，所以在ssh连接过程中无法输目标主机的密码，因而无法连接。要用`sudo virt-manager --no-fork`来打开软件，在要输密码的时候，回到命令行界面输入目标主机的密码。

## 3. 装在NFS上的虚拟机运行速度很慢

当时装个Ubuntu系统都用了一个多小时，装好之后虚拟机每一次开机都需要20分钟以上的时间。瓶颈可能是网络传输速度过低和硬盘相应延时。每一次重启虚拟机要花费半个小时以上的时间，这个时间太长，让人无法接受。

## 4. 无法迁移虚拟机 提示不安全

在Advanced选项中，允许不安全的迁移。

## 5. 无法迁移虚拟机 host CPU does not provide required features

换了不同的电脑，重头再次创建虚拟机，最后还是会遇到这个错误，不过required features后面的报错信息略有区别。尝试安装intel -ucode后更新配置文件并重启，仍然无法解决问题。

删除虚拟机中的设置对aes的支持也是不可以。把虚拟机的配置文件(一般是在`/etc/libvirt/qemu/[虚拟机名字].xml`)，编辑这个xml文件找到`<cpu model=...>`这一栏，在它下面加上`<feature policy='disable' name='aes'/>`，保存了之后，先关了虚拟机，终端输入sudo virsh define [你的虚拟机名字].xml之后再重启虚拟机。这种方法也还是不行，在迁移虚拟机的时候同样是报错了。


# 参考资料

- [KVM virtual machine mirgration tutorials](https://www.linux-kvm.org/page/Migration)
- https://blog.csdn.net/taiyang1987912/article/details/47973479
- https://www.ibm.com/developerworks/cn/linux/l-linux-kvm/index.html    
- https://www.ibm.com/developerworks/cn/linux/l-cn-mgrtvm2/index.html
- http://www.cnblogs.com/liuyansheng/p/5985633.html
- https://www.ibm.com/developerworks/cn/linux/l-cn-mgrtvm2/index.html
- https://blog.csdn.net/xiyue/article/details/51446343