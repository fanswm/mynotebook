##安装arch linux
（一）磁盘分区：
`# fdisk /dev/sda`

+ 创建分区表：

	· Command (m for help): 输入 o 并按下 Enter 

	然后建立第一个分区：

	1. Command (m for help): 输入 n 并按下 Enter 
	2. Partition type: Select (default p): 按下 Enter 
	3. Partition number (1-4, default 1): 按下 Enter 
	4. First sector (2048-209715199, default 2048): 按下 Enter 
	5. Last sector, +sectors or +size{K,M,G} (2048-209715199....., default 209715199): 输入 +15G 并按下 Enter 

	然后建立第二个分区：

	1. Command (m for help): 输入 n 并按下 Enter 
	2. Partition type: Select (default p): 按下 Enter 
	3. Partition number (1-4, default 2): 按下 Enter 
	4. First sector (31459328-209715199, default 31459328): 按下 Enter 
	5. Last sector, +sectors or +size{K,M,G} (31459328-209715199....., default 209715199): 按下 Enter 

	现在预览下新的分区表:

	· Command (m for help): 输入 p 并按下 Enter 
	Disk /dev/sda: 107.4 GB, 107374182400 bytes, 209715200 sectors
	Units = sectors of 1 * 512 = 512 bytes
	Sector size (logical/physical): 512 bytes / 512 bytes
	I/O size (minimum/optimal): 512 bytes / 512 bytes
	Disk identifier: 0x5698d902
	Device Boot     Start         End     Blocks   Id  System
	/dev/sda1           2048    31459327   15728640   83   Linux
	/dev/sda2       31459328   209715199   89127936   83   Linux

	然后向磁盘写入这些改动：

	· Command (m for help): 输入 w 并按下 Enter 

> 如果一切顺利无错误的话，fdisk 程序将显示如下信息:

	The partition table has been altered!
	Calling ioctl() to re-read partition table.
	Syncing disks.

	若因 fdisk 遇到错误导致以上操作无法完成，可以用 q 命令来退出。
	（当然你也可以分多个分区，分别挂载/boot,/home/,/,/var等）
	
+ 接下来格式化成ext4文件系统
`# mkfs.ext4 /dev/sda1`
`# mkfs.ext4 /dev/sda2`
（ 若您分了一个 swap 区，也不要忘了格式化并启用它（x代表你的那个分区数字）：
`# mkswap /dev/sdaX`
`# swapon /dev/sdaX` ）
注意要按照顺序挂载，先挂载根分区到 /mnt （你实际所要挂载的分区名当然可能会不同）：
`# mount /dev/sda1 /mnt`
然后挂载 /home 分区（以及其它其余单独分区，比如 /boot，/var，如果您有的话）：
`# mkdir /mnt/home`
`# mount /dev/sda2 /mnt/home`
（如果有其他分区，先创建目录，再挂载）

---

（二）安装基本系统
重申一遍，这里及以后一些步骤必须联网，尤其是运行pacman命令时。关于联网问题请参照archwiki,里面有十分详细的解说。

+ 安装前需要编辑文件/etc/pacman.d/mirrorlist, 你的系统和软件将从这里的地址下载。将偏好的镜像放到最前面，下面加入了一个比较快的源，当然你可以去网上搜其他比较好的源：

```
# nano /etc/pacman.d/mirrorlist
##
## Arch Linux repository mirrorlist
## Sorted by mirror score from mirror status page
## Generated on 2012-MM-DD
##
 
Server = http://mirror.bjtu.edu.cn/archlinux/$repo/os/$arch
```
如果您愿意，您可以只使用一个镜像并全删光其他行，但为保险，还是留其他几个离您较近的镜像作备用好。
然后敲入：
` # pacman -Syy          刷新列表`
`# pacstrap -i /mnt base    安装基本系统`
 
若运行 pacstrap 时卡住并出现 failed retrieving file 'core.db' from mirror... : Connection time-out 字样，请检查刚才的源是否正确或去网上搜索其他能用的源。

+ 生成fstab分区表
`# genfstab -U -p /mnt >> /mnt/etc/fstab`

+ 下面要 chroot 到新系统开始配置：
`# arch-chroot /mnt /bin/bash`

+ 系统本地化，设置本地语言，地点等信息
`# nano /etc/locale.gen`
```    
en_US.UTF-8 UTF-8
zh_CN.UTF-8 UTF-8
zh_TW.UTF-8 UTF-8
```

+ 接着执行locale-gen以生成locale讯息：
`# locale-gen`

+ 创建 locale.conf 并提交您的本地化选项：
`# echo LANG=en_US.UTF-8 > /etc/locale.conf`

> 这里先不要设置中文编码，等安装了图形界面再修改，否则会乱码）

+ 设置时区，一般以上海就行：

`# ln -s /usr/share/zoneinfo/Asia/Shanghai /etc/localtime`

+ 设置时间
`# hwclock --systohc --utc`

+ 设置个您喜欢的主机名，例如：
`# echo 主机名 > /etc/hostname`
并在 /etc/hosts 添加同样的主机名：
```
# nano /etc/hosts
#
# /etc/hosts: static lookup table for host names
#
 
#<ip-address> <hostname.domain.org> <hostname>
127.0.0.1    localhost.localdomain  localhost 主机名   
::1          localhost.localdomain  localhost
 
# End of file
```
+ 设置root密码
`# passwd`

+ 安装启动引导器grub:
安装 grub 包，并执行 grub-install 已安装到 MBR:
`# pacman -S grub`
`# grub-install --target=i386-pc --recheck /dev/sda`
`# grub-mkconfig -o /boot/grub/grub.cfg`

> 须根据实际分区自行调整 /dev/sda, 切勿在块设备后附加数字，比如
/dev/sda1 就不对

---
(三) 卸载分区并重启系统

+ 离开 chroot 环境：
`# exit`
+ 重启计算机：
`# reboot`

> 好了，一个最基本的字符系统建好了，接下来可以选择安装桌面等图形环境了。

---
(四)安装图形界面
+ 先进行网络设置，在上面的livecd中一般会自动联网
`# ip link`
+ 找到网络设备，我的是enp0s3
`# ip link set enp0s3 up`
`# dhcpcd enp0s3`
`# systemctl enable dhcpcd@enp0s3.service`

> 以后系统就会自动联网了
对于无线还未尝试，可以看archwiki。

+ 进入系统后首先更新软件包
`# pacman -Syu`

+ 然后安装x window:
`# pacman -S xorg`

> 默认安装就行

+ 安装显卡驱动

`# pacman -S xf86-video-vesa` 
> 通用显卡驱动，不提供任何2D和3D加速功能

`# pacman -S xf86-video-intel `

> Intel

`# pacman -S xf86-video-nouveau # Nvidia`
`# pacman -S nouveau-dri`
`# pacman -S xf86-video-ati # Ati`

`# 虚拟机: pcaman -S xf86-video-vesa`

+ 安装声卡驱动键入 
`# pacman -S alsa-utils`

+ 安装XFCE4 桌面套件

`# pacman -S xfce4`

+ 安装登陆管理器,这样不需要手动去输入启动X的命令,登陆管理器也有很多,这里选一个小巧的slim:
`# pacman -S slim`

+ 安装sudo,让普通用户无需切换执行一些root用户指令:
`# pacman -S sudo`

+ 安装中文字体
`# pacman -S wqy-zenhei(文泉骈-正黑）`

+ 添加一个普通用户,比如这里的kimolte
`# useradd -m -s /bin/bash kimolate`
+ 添加完毕为普通用户设定一个密码
`# passwd kimolate`
+ 为刚才添加的普通用户添加sudo的相关权限
`# visudo`

```
#找到如图位置并添加kimolate一行
保存重启）
```
 
+ 为了避免出现没有~/.xinitrc的情况，所以可以从系统中复制一个：
`# cp /etc/skel/.xinitrc ~`
> （或者直接新建一个 #touch ~/.xinitrc）
> 然后打开.xinitrc
```
# cd ~
# sudo nano .xinitrc
找到
#exec gnome-session
#exec startkde
#exec startlxde
#exec startxfce4
```
> 添加 exec startxfce4或直接去掉你对应桌面的语句前面的'#'
保存退出
 
+ 添加执行权限
`#sudo chmod +x ~/.xinitrc`
+ 最后设置自动启动slim登陆器
`# sudo systemctl enable slim.service`

现在一个基本的图形界面建好了。
登陆系统后，打开终端：
`# nano /etc/locale.conf`
> 修改LANG变量en_US.UTF-8为zh_CN.UTF-8,重启后就能显示中文了。
```
# export  LANG=zh_CN.UTF-8
# export  LC_ALL="zh_CN.UTF-8"
改.xprofile的，归根结底就是在启动xfce之前把环境变量LANG改成zh_CN.utf-8
```
+ 接下来安装fcitx输入法
`# sudo pacman -S fcitx-im fcitx-configtool`
>（如果你采用 KDM、GDM、LightDM等显示管理器，请在~/.xprofile (没有则新建一个)中加入如下3行）如果你采用 startx 或者 Slim 启动 （即使用.xinitrc的场合），则在 ~/.xinitrc 中加入：
> ``` 
 export GTK_IM_MODULE=fcitx
 export QT_IM_MODULE=fcitx
 export XMODIFIERS="@im=fcitx"
 ```
重新登录后让环境变量生效。
如果你使用 XDG 兼容的桌面环境如 KDE, GNOME, XFCE, LXDE, 当你重新登录后，Fcitx 应该会自动启动，如果没有的话，可以打开控制台并运行：
 `# fcitx`


现在终于大功告成了，重启后你应该会看到这样的画面.

```
$ pacman-key --init
$ pacman-key --populate

+ 更新已知密钥：
`$ pacman-key --refresh-keys`

+ 手动升级archlinux-keyring软件包：
`$ pacman -S archlinux-keyring`
```

> error: krb5: signature from "Levente Polyak (anthraxx) <levente@leventepolyak.net>" is unknown trust
:: File /mnt/var/cache/pacman/pkg/krb5-1.15.1-i686.pkg.tar.xz is corrupted (invalid or corrupted package(PGP signature))

