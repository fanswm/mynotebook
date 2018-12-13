+ The following packages have been kept back
> 据说是因为有部份packages的安装版比release版新而出现”The following packages have been kept back”这个问题，解决方法是使用apt-get -u dist-upgrade 统一更新到发布的版本。这条命令会强制更新软件包到最新版本，并自动解决缺少的依赖包。

+ 根目录空间不足:
> + dpkg --get-selections|grep linux 
> + sudo apt-get remove linux-image-2.6.15-23-386 
> + uname -a 

+ 查看版本：
>+ uname -a 
> + cat /proc/version （Linux查看当前操作系统版本信息） 
> + cat /etc/issue 或cat /etc/redhat-release（Linux查看版本当前操作系统发行版信息） 
> + cat /proc/cpuinfo （Linux查看cpu相关信息，包括型号、主频、内核信息等） 
> + getconf LONG_BIT （Linux查看版本说明当前CPU运行在32bit模式下， 但不代表CPU不支持64bit） 
> + lsb_release -a

+ unexpected inconsistency RUN fsck ma...
> fsck -y sda11
reboot,ok

+ xmin:Theme directory devices/scalable of theme maia has no size field;An error has occurred. See the log file /home/fanswm/configuration/1500870303567.log;
> null;

+ 修复grub：Parrot Linux
> 判断主分区；例如是：`/dev/sda`
`sudo mount /dev/sda11  / mnt` 
`mount --bind /dev/ /mnt/dev`
`mount --bind /proc /mnt/proc`
`mount --bind  /sys /mnt/sys`
`chroot /mnt`
`sudo update-grub`
`sudo update-grub2`
进入系统后：
`update-grub2`

+ ubuntu卸载amazon:
> `sudo apt-get remove unity-webapps-common`
> + simple-scan: 扫描易
> + gnome-mahjongg: 麻将


+ You might want to run 'apt-get -f install' to correct these.
The following packages have unmet dependencies:
 linux-generic : Depends: linux-headers-generic (= 4.4.0.71.77) but 4.4.0.66.70 is installed
E: Unmet dependencies. Try using -f.

> 删除提示的`linux-generic`未完全安装的软件。
    `$sudo dpkg --purge linux-generic`
    
+ E: Failed to fetch http://cn.archive.ubuntu.com/ubuntu/pool/main/q/qtbase-opensource-src/libqt5netwo

> 本人的解决方法是：
`sudo mv /var/lib/apt/lists /var/lib/apt/lists.bak`
`sudo mkdir /var/lib/apt/lists`
> > 就是备份下lists目录，创建一个新的lists目录。再执行sudo apt-get update问题解决。但是这可以解决大部分问题，个别源不能解决，如"/var/lib/apt/lists/partial /extras.ubuntu.com_ubuntu_dists_precise_main_binary-i386_Packages"，无耐进入 /var/lib/apt/lists/将对应的文件删除

+ 查看文件系统
> `df -Th`

+ 在Linux系统下用dd命令制作ISO镜像U盘启动盘
> `sudo dd if=~/images/ubuntu.iso of=/dev/sdx`
