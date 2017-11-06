董董，我不知道你老人家以前接触过多少，这是一篇从零开始的介绍，所以，通用：

重要提示：
1、深坑，慎入！！董董，这不是一个深坑，这是一个无底洞！！！不是说你需要投入多少金钱，而是无穷无尽的时间和精力。
2、我以亲身经历奉劝你：别超过22：30睡觉！
3、有拿不定的咱俩一块研究，没有必要死啃，这上面，我走了不少弯路（唉，能说的都是泪！！！55555....）。
4、不建议新手直接在台式机硬盘上安装Linux, 如果有兴趣，可以先用VMWare装虚拟机（我几乎安装了Linux的所有有名的版本，不下30遍，并在台式机上安装了不下5遍，但是我还是新手）。了解了Linux，你会讨厌windows，你会看到另一片天地。我承认我是Linux的死忠粉，也是opensource的死忠粉。

建立自己的私有云方法:
1、购买NAS（没玩过）；
2、或用黑群晖（没玩过）；
3、或买一个小米路由器（见别人玩过）；
4、或自己搭建一个服务器,要求功耗要低（玩过，现用）采用syncthing这套软件（开源）.
我们采用方法4；

注：
我的用户名：fan
"$"符号开头的是Linux命令行(在pi上)
PI/pi指树莓派
以下是我亲自操作过的过程。
为pi分配静态ip：192.168.10.10
编辑文件时的“添加”一般是指在最后一行之后添加。
建议保存一套自己的软件版本。

树莓派试验室：
http://shumeipai.nxez.com/download
（我就是从这里开始的，但这里面有好多都不对或过期了）

准备:
硬件: 
树莓派2B主机(220元左右,淘宝)、
TF卡（30元左右，至少8G，推荐class10全高速卡，容量无上限，但是成本也更高，别忘了这个是有寿命的）
外壳（20元左右）、
散热片（4元左右，可以自己制作）、
HDMI高清线（非必要，因为有线电视上都有）、
HDMI转VGA线（非必要）
路由器(这个你家应该有吧，:P )
读卡器
1米网线(两边带水晶头的)
移动硬盘或自制移动硬盘（我用U盘代替）；

软件:
树莓派操作系统:Linux的arm版,推荐官方: Raspbian杰茜,扩展名".img"
    备选:Arch Linux(更大的深坑)、win10（不推荐，因为我没用过，虽然我的台式机装的是win10）、Kali Linux
映像烧录工具：Win32DiskImager v0.9.zip (sourceforge.net)（也可以选别的，我用的这个最快）

最好用的工具：
google.com(需翻墙)

开工：
一、准备系统
1、把TF卡插到电脑上，打开Win32DiskImager；
2、选**raspberrypi***.img（记不清文件名了）文件，写入TF卡。

二、加电：
1、把TF卡插到树莓派上，用HDMI线连接树莓派和电视机显示屏（当然，也可以边电脑显示屏）；
2、用网线连接PI和路由器（非必须）；
3、用手机充电器给树莓派充电的一瞬间，它就启动了。
4、按屏幕提示操作，操作步骤忘了。

三、登录系统：
用户名：pi（所有Unix Like系统区分大小写）
密码：raspberry

四、重要建议：
重要的事情说十遍！！！！
现有，拿起你的笔记本，写下你所有的实际操作过程，就像航海日志。我以血的教训告诉你，这非常重要！！！！

五、进入系统：

进入命令行

切换用户：
$ su pi

更改pi的密码：
$ passwd

$ sudo passwd（修改root密码，建议复杂的密码）
root密码莫忘，忘了的话，比较烦人。
一般不用root用户进行操作，而用
$ sudo ...

更新系统：
$ sudo apt-get update
$ sudo apt-get upgrade -y

建议每天更新系统：
$ crontab -e
添加：
30 6 * *　*　*　apt-get update && apt-get upgrade -y
# 每天早晨6：30更新系统

查看crond进程是否存在:（非必要）
$ service crond status    /$ /etc/init.d/cron status
$ service crond start    $/etc/init.d/cron start


创建你自己的用户名：
$ sudo useradd -m fan
同时创建密码：
$ passwd fan
假定为：123456（你当然不能用这么简单的密码，这是非常危险的）

启用 root 账号:
$ sudo passwd --unlock root
为了安全起见，还是禁用掉 root。
$ sudo passwd -l root

建议以后开机默认启动的是命令行，否则，默认启动桌面的话，系统占用的资源太多，而且慢。

备份：
假定你的备份目录是/home/fan/backup/
$ cp /etc/passwd /home/fan/backup/passwd.old.201611011502
$ cp /etc/group /home/fan/backup/group.old.201611011502
$ cp /etc/fstab /home/fan/backpu/fstab.old.201611011502

你需要一个自己喜欢的编辑器：
推荐vim,系统默认带的是nano
示例：打开aaaa.txt文件：
$ vim aaaa.txt
或
$ nano aaaa.txt

去掉pi用户(非必要，慎用)：
$ sudo vim /etc/passwd
把其中的所有的pi的地方全部换成fan
$ sudo vim /etc/group
浏览整个文件，找到pi所在的那每一行，然后把,fan加到行尾。
把其中的所有的pi的地方全部换成fan

把/home/pi/这个文件夹全部复制到/home/fan/pi/（其实没有什么用）

切换用户到fan:
$ su fan


修改umask:
$ sudo cp /etc/login.defs
$ sudo vi /etc/login.defs
edit:
    UMASK=023
修改umask:
$ sudo vi /home/pi/.profile
edit:
    #umask = 022
to:    umask = 027
$ reboot


安装中文字体:文泉驿：（非必要）
$ sudo apt-get install ttf-wqy-zenhei


设置SSH默认启动（好像本身就是默认启动的）：
$ sudo /etc/init.d/ssh start
$ sudo update-rc.d ssh defaults

ssh创建key：
$ ssh-keygen
/home/fan/.ssh/id_rsa

设置静态的ip(需把pi连上你的路由器)
我的是小米路由青春版，上面有这个功能，
好像在PI上也行，不过我记得不太清了。
好像是：
$ sudo vim /etc/networking/interfaces
修改：
inet dhcp
为：
inet static
address: 192.168.10.10(假定这是你的ip，这个IP是内网的)

现在把你的PI关掉吧：
$ sync;sync;sync;
$ sudo shutdown -h now

把pi和电视分离；
把PI连上路由器；
重新加电开机；

打开台式机：
在台式机上安装putty,或git bash, 或msys32
建议putty，因为很小（我就喜欢小软件，:) ）。
我安的是git bash, 和msys32。

打开git bash(或putty):
$ ssh fan@192.168.10.10
输入fan在PI上的密码：123456
ssh的默认端口是：22

现在，你就是在windows上操作你的pi了


安装 exfat：（我也忘了这是干嘛的了，好像是扩展fat）
$ sudo apt-get install exfat-fuse

挂载U盘（我假定我们用这个做为“私有云”的物理介质）：
把你的U盘插到pi上（假定你只插了这一块）；
计划把U盘挂载到 /mnt/usb/
$ sudo mkdir /mnt/usb    （usb可以用你喜欢的另外一个名字）
$ sudo vim /etc/fstab
#添加
/dev/sda  /mnt/usb    auto    defaults,noexec,umask=0000    0    0
上面一共6项（我记得是6项，这个文件的上面有示例），用TAB键分隔

重启（你也可以待会儿再重启）：
$ sudo reboot

安装samba:（一款windows和linux共享文件的软件，安上之后，用你的手机连到 linux共享的电影吧，非必要）
$ sudo apt-get install -y samba samba-common-bin
$ sudo vim /etc/samba/smb.conf
#添加
[shares]
comment = Backup Folder
path = /mnt/usb/shares
valid users = @ fan_shares
force group = fan_shares
create mask = 0660
directory mask = 0771
read only = no
browseable = yes
public = yes
writable = yes

$ sudo /etc/init.d/samba restart
[ok]

$ sudo groupadd fan_shares
$ sudo usreadd fan_get_shares -b /mnt/usb -G fan_shares

################ passwd
$ sudo passwd fan_get_shares

$ sudo smbpasswd -a fan_get_shares
$ sudo smbpasswd -a fan_shares

$ cp /etc/rc.local /home/fan/backup/rc.local.old.201611011502

$ sudo vim /etc/rc.local
# append before "exit 0"
sudo /etc/init.d/samba restart

申请noip.com动态域名
（国内花生壳也行，这两个我都用着呢，没有必要用收费的，除非你觉得必要）：
假定你申请到的是：fan.ddns.net（当然，不要用你的系统用户名注册DDNS，因为你的用户名也是应该保密的）
登录noip.com，按提示操作。

我的体会：花生壳不如noip稳定。


申请公网IP
（重要提示，把自己的IP暴露到互联网中是非常非常危险的一件事情，有可能吃上官司，但是，我还没有找到不用公网IP的办法）

路由器设置端口转发：
外网：22，内网：192.168.10.10：22；

在路由器上设置DDNS：
把你的noip.com的账号和密码填到路由器的DDNS页面了（每个路由器都不一样，取决于你的路由器有没有这个功能，和功能的实现方式）
如果路由器没有这个功能也没有关系，
noip.com有一个软件可以实现这个功能。
启动：
$ sudo /usr/local/bin/noip2（当然，在启动这个之前你得安装：apt-get install niip2）
要设置开机启动，把上面这行加入/etc/rc.local，要加在exit 0那行以前 
附两个命令：
$ sudo /usr/local/bin/noip2 -C     重新配置一次（就是问安装过程中那几个问题）
$ sudo /usr/local/bin/noip2 -S      显示当前运行状态、信息

更改软件源:（非必要）
$ sudo vim /etc/apt/source.list

安装syncthing（这是标的）：
访问：http://apt.syncthing.net/
The release channel is updated with full release builds, approximately once a week.
# Add the release PGP keys:
$ curl -s https://syncthing.net/release-key.txt | sudo apt-key add -

# Add the "release" channel to your APT sources:
$ echo "deb http://apt.syncthing.net/ syncthing release" | sudo tee /etc/apt/sources.list.d/syncthing.list

# Update and install syncthing:
$ sudo apt-get update
$ sudo apt-get install syncthing

配置syncthing:
以下这些是syncthing官网的配置选项:
在/home/fan/.config/config.xml:
找到这一项：
ignorePerms
True if the folder should ignore permissions.
（忽略/mnt/usb/syncthing的权限，否则只能在/home/fan/Sync/同步）
~/Sync/是syncthing的默认文件夹（我们把它改成了/mnt/usb/syncthing/）

在windows上打开浏览器：
输入：192.168.10.10：8384
->设置
GUI用户名:syncthingadmin
GUI密码码:123456sync
为你的syncthing在PI上分配一个根目录(在PI的U盘上):
比如:
$ mkdir -p /mnt/usb/syncthing/
并把这个目录配置给syncthing

启动：
$ syncthing & (后台运行)

查看syncthing是否启动：
$ netstat -tunlp | grep 8384    (8384是syncthing的默认端口，当然，你可以配置别的端口)


在windows上下载:syncthing
解压
打开syncthing.exe
推荐用chrome或FireFox浏览器
这时,应该自动弹出:127.0.0.1:8384
连你的PI上的syncthing
指定一个文件夹分配给syncthing,比如是D:/syncthing/
你只要把文件存到这里,就会自动上传到PI:/mnt/usb/syncthing/windowns/.....
当然,远程访问需:fan.ddns.net:8384

在手机上下载:syncthing
打开
连你的PI上的syncthing
为你的syncthing配置默认的共享目录:
比如你的相机所在的目录(以后,只要你回家打开手机的wifi,你的照片自动上传到PI: /mnt/usb/syncthing/android/DCIM/....)
当然,远程访问需:fan.ddns.net:8384

我实测下载上传速度比百度云快,取决于你的网速.
内网速度更快.


手机安装SSH客户端远程控制树莓派：
$ ssh fan@fan.ddns.net
远程关机：
$ sync;sync;sync;
$ sudo shutdown -h now

买一个小米插座（当然别的也可以，我用的是小米的）：
远程断掉电源，不用的时候可以远程关掉。

建议备份自己的系统卡（TF卡）：
windows上不知道，Linux用命令：dd
否则，系统有一点毛病，你想重新安装一遍，看看吧，上面那些，你有信心再来一遍吗？？？

畅享你的私有云吧~~~~~~~~~

以上大部分凭记忆，有可能有纰漏。

有好多坑我还没有挖过，你有兴趣的话自己挖吧。

















