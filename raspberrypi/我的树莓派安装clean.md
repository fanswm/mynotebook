$ sudo apt-get install aria2
 
$ mkdir ~/.aria2 //新建文件夹
$ touch ~/.aria2/aria2.session //新建session文件
$ vim ~/.aria2/aria2.conf //新建配置文件
https://repo.continuum.io/archive/Anaconda2-4.4.0-Linux-x86.sh
 
# 在aria2.conf配置文件里粘贴以下代码，
# 别忘记将里边的路径替换为自己的：
 
 
dir=/mnt/usb/Download	#下载的默认目录
disable-ipv6=true
enable-rpc=true
rpc-allow-origin-all=true
rpc-listen-all=true
#rpc-listen-port=6800
continue=true
input-file=/home/fanswm/.aria2/aria2.session  #路径要绝对路径
save-session=/home/fanswm/.aria2/aria2.session  #保存你的下载列表
max-concurrent-downloads=3
 
#查看6800端口是否占用：
$ netstat -tunlp | grep 6800
$ kill -9 ID
#用配置文件启动aria2:
$ aria2c --conf-path=/home/fanswm/.aria2/aria2.conf &(后台运行) 或:
$ aria2c --conf-path=/home/fanswm/.aria2/aria2.conf -D 
 
$ sudo vim /etc/init.d/aria2c	粘贴以下内容:
 
#!/bin/sh
### BEGIN INIT INFO
# Provides:          aria2
# Required-Start:    $remote_fs $network
# Required-Stop:     $remote_fs $network
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Aria2 Downloader
### END INIT INFO
case "$1" in
start)
    echo -n "Starting aria2c"
    sudo -u fanswm aria2c --conf-path=/home/fanswm/.aria2/aria2.conf -D 
    #sudo -u后面的是你正在使用的用户名，因为我用的fanswm，别忘记改成自己的
;;
stop)
    echo -n "Shutting down aria2c "
    killall aria2c
;;
restart)
    killall aria2c
    sudo -u fanswm aria2c --conf-path=/home/fanswm/.aria2/aria2.conf -D
    #同上面的一样，根据自己的用户名改fanswm;;
esac
exit
 
 
$ sudo chmod 755 /etc/init.d/aria2c
 
# 测试启动如果只显示Starting aria2c，
# 没有其他错误提示的话就说明成功了。
# 然后添加aria2c服务到开机启动:
 
$ sudo /etc/init.d/aria2c start
 
# 开机启动.
 
$ sudo update-rc.d aria2c defaults
 2016/11/21 19:18 
开机不启动：
$ sudo update-rc.d aria2c remove
 
# 查看aria2版本
$ aria2c --version
 
设置好apache2的权限：
$ sudo visudo
底部添加这行：
www-data ALL=(ALL) NOPASSWD: ALL
 
重启 apache:
$ sudo /etc/init.d/apache2 restart
 
暂时访问:
http://192.168.*.*:6800/jsonrpc
 
http://ziahamza.github.io/webui-aria2/
 
http://yaaw.ghostry.cn/
参考:CentOS 下搭建 aria2 远程下载环境     (fanswm笔记)
 
# 安装yaaw:
# cd /var/www/
$ sudo git clone http://github.com/wzhy90/yaaw
$ sudo chmod -R o+x ./yaaw/
http://token:secret@hostname:port/jsonrpc
 
 
error:
/var/log/messages：
rsyslogd-2007: action 'action 17' suspended, next retry is wed sep
http://www.rsyslog.com/e/2007
 
 
# apt-get upgrade:
err http://mirror.sysu.edu.cn/raspbian/raspbian/ jessie/main libssl-doc all 1.0.1t-1+deb8u5
404 Not Found [IP: 202.141.176.110 80]
err http://mirror.sysu.edu.cn/raspbian/raspbian/ jessie/main libssl-dev armhf 1.0.1t-1+deb8u5
404 Not Found [IP: 202.141.176.110 80]
err http://mirror.sysu.edu.cn/raspbian/raspbian/ jessie/main libssl1.0.0 armhf 1.0.1t-1+deb8u5
404 Not Found [IP: 202.141.176.110 80]
err http://mirror.sysu.edu.cn/raspbian/raspbian/ jessie/main libarchive13 armhf 3.1.2-11+deb8u3
404 Not Found [IP: 202.141.176.110 80]
E: Failed to fetch http://mirror.sysu.edu.cn/raspbian/raspbian/pool/main/o/openssl/libssl-doc-1.0.1t-1+deb8u5_all.deb 
 
 
以下这些是syncthing官网的配置选项:
在~/.config/config.xml:
 
ignorePerms
    True if the folder should ignore permissions.
 
minDiskFreePct
    The percentage of space that should be available on the disk this folder resides. The folder will be stopped when the percentage of free space goes below the threshold. Set to zero to disable.
 
maxConflicts
    The maximum number of conflict copies to keep around for any given file. The default, -1, means an unlimited number. Setting this to zero disables conflict copies altogether.
ignoreDelete
    When set to true, this device will pretend not to see instructions to delete files from other devices.
 
Device Element
compression
 
    Whether to use protocol compression when sending messages to this device. The possible values are:
 
    metadata
        Compress metadata packets, such as index information. Metadata is usually very compression friendly so this is a good default.
    always
        Compress all packets, including file data. This is recommended if the folders contents are mainly compressible data such as documents or text files.
    never
        Disable all compression.
 
GUI Element
enabled
    If not true, the GUI and API will not be started.
The following child elements may be present:
 
address
    Set the listen addresses. One or more address elements must be present. Entries must have the protocol prefix tcp://. Allowed address formats are:
    IPv4 address and port (tcp://127.0.0.1:8384)
        The address and port is used as given.
    IPv6 address and port (tcp://[::1]:8384)
        The address and port is used as given. The address must be enclosed in square brackets.
    Wildcard and port (tcp://0.0.0.0:12345, tcp://[::]:12345, tcp://:12345)
        These are equivalent and will result in Syncthing listening on all interfaces via both IPv4 and IPv6.
 
Options Element
listenAddress
    The listen address for incoming sync connections. See Listen Addresses for allowed syntax.
startBrowser
    Whether to attempt to start a browser to show the GUI when Syncthing starts.
 
以下是把syncthing的安装包解压后在查年的文件:
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-runit/README.md:
This directory contains a configuration for running syncthing under the
"runit" service manager on Linux. It probably works perfectly fine on
other platforms also using runit.
 1. Install runit.
 2. Edit the `run` file to set the username to run as, the user's home
    directory and the place where the syncthing binary lives. It is
    recommended to place it in a directory writeable by the running user
    so that automatic upgrades work.
 
 3. Copy this directory (containing the edited `run` file and `log` folder) to
    `/etc/service/syncthing`.
 
Log output is sent to syslogd.
 
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-runit/run
#!/bin/sh
export USERNAME=jb
export HOME="/home/$USERNAME"
export SYNCTHING="$HOME/bin/syncthing"
 
exec 2>&1
exec chpst -u "$USERNAME" "$SYNCTHING" -logflags 0
 
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-systemd/README.md
# Systemd Configuration
 
This directory contains configuration files for running Syncthing under the
"systemd" service manager on Linux both under either a systemd system service or
systemd user service. For further documentation take a look at the [systemd
section][1] on http://docs.syncthing.net.
 
[1]: http://docs.syncthing.net/users/autostart.html#systemd
 
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-systemd/system/syncthing@.service:
[Unit]
Description=Syncthing - Open Source Continuous File Synchronization for %I
Documentation=man:syncthing(1)
After=network.target
Wants=syncthing-inotify@.service
 
[Service]
User=%i
ExecStart=/usr/bin/syncthing -no-browser -no-restart -logflags=0
Restart=on-failure
SuccessExitStatus=3 4
RestartForceExitStatus=3 4
 
[Install]
WantedBy=multi-user.target
 
 
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-systemd/user/syncthing.service 
[Unit]
Description=Syncthing - Open Source Continuous File Synchronization
Documentation=man:syncthing(1)
Wants=syncthing-inotify.service
 
[Service]
ExecStart=/usr/bin/syncthing -no-browser -no-restart -logflags=0
Restart=on-failure
SuccessExitStatus=3 4
RestartForceExitStatus=3 4
 
[Install]
WantedBy=default.target
 
 
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-upstart/READMI.md 
# Upstart Configuration
 
This directory contains example configuration files for running Syncthing under
the "Upstart" service manager on Linux. To have syncthing start when you login
place "user/syncthing.conf" in the "/home/[username]/.config/upstart/" folder.
To have syncthing start when the system boots place "system/syncthing.conf"
in the "/etc/init/" folder.
To manualy start syncthing via Upstart when using the system configuration use:
 
```
    sudo initctl start syncthing
```
 
For further documentation see [http://docs.syncthing.net/users/autostart.html][1].
 
[1]: http://docs.syncthing.net/users/autostart.html#Upstart
~                                                                
 
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-upstart/system/syncthing.conf 
description "Syncthing"
 
start on (local-filesystems and net-device-up IFACE!=lo)
stop on runlevel [!2345]
 
env STNORESTART=yes
env HOME=/home/$USER
setuid "$USER"
setgid "$USER"
 
exec /usr/local/bin/syncthing
 
respawn
 
~/src/syncthing-linux-arm-v0.14.9/etc/linux-upstart/user/syncthing.conf	
# Location of the syncthing executable
env SYNCTHING_EXE="/usr/local/bin"
 
# Set the name of the application
description "Syncthing"
 
# Start syncthing you login to your desktop
start on desktop-start
 
# Stop syncthing you logout of your desktop
stop on desktop-end
 
# Set STNORESTART to yes to have Upstart monitor the process instead
# of having a separate syncthing process do the monitoring
env STNORESTART=yes
 
# If Upstart detects syncthing has failed - it should restart it
respawn
 
# the syncthing command Upstart is to execute when it is started up
exec $SYNCTHING_EXE -no-browser
 