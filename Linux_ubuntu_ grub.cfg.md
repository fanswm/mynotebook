> Ubuntu使用Grub2来引导系统启动，配置文件: /boot/grub/grub.cfg，如果你有这些需求：

+ 双系统，将Windows设为默认启动项。
+ 看见Memory Test不爽。
+ 想把启动想弄的个性点。
+ 其实还可以改颜色，弄漂亮点。

那就来修改启动配置文件吧：

+ 打开终端 输入 `sudo gedit /boot/grub/grub.cfg`
接下来将会在Gedit中打开配置文件。
首先请仔细阅读 #后的说明

> 其中包含以下几大块：

+ BEGIN /etc/grub.d/00_header ###
> 其中包含默认启动项  等待时间
(找 set default="0"  这句，然后从0开始，数一下你想默认启动的启动项是第几个，将数字替换掉“0”)
(找 set timeout=10  这句，也就是你的默认等待时间是10秒，改成你想要的时间就行了)
> END /etc/grub.d/00_header ###

+ BEGIN /etc/grub.d/05_debian_theme ###
> Grub的样式，算是主题吧
(总共就两句，分别是菜单颜色和背景颜色，改的话也很简单，就是  前景色/背景色：
set menu_color_normal=white/black          
set menu_color_highlight=black/light-gray
)
> END /etc/grub.d/05_debian_theme ###

+ BEGIN /etc/grub.d/10_linux ###
> 你的Ubuntu了，没有可以更改的，别动它
(如果想改改启动项的名字的话改改单引号里面的字母，只能改单引号里面的！)
> END /etc/grub.d/10_linux ###

+ BEGIN /etc/grub.d/20_linux_xen
> 我的这里面没东西，不知到做什么的
>  END /etc/grub.d/20_linux_xen ###

+ BEGIN /etc/grub.d/20_memtest86+ ###
>  Memory Test
(不想要的话把每句前加个#好给注释掉)
> END /etc/grub.d/20_memtest86+ ###

+ BEGIN /etc/grub.d/30_os-prober ###
> 其他操作系统，看你有几个，里面就有几个
(也就能改个系统启动项显示的名字了，改双引号里面的，只能改双引号里面的！)
> END /etc/grub.d/30_os-prober ###

保存修改就行了
