## apt
> Advanced Package Tool
+ 软件源设置	/etc/apt/sources.list
+ 更新软件源数据`apt-get update`
+ 更新已安装软件`apt-get upgrade`
+ 更换系统版本`apt-get dist-upgrade`
+ 通过安装包或卸载包来修复依赖错误`apt-get -f install`
+ 搜索软件源数据`apt-cache search foo`
+ 解压安装软件包`apt-get install foo`
+ 重新安装软件包`apt-get --reinstall install foo`
+ 删除软件包释放的内容`apt-get remove foo`
+ 卸载软件，同时清除该软件配置文件`apt-get --purge remove foo`
+ 删除不需要的包`apt-get autoclean`
+ 删除所有已下载的包`apt-get clean`
+ 自动安装编译一软件所需要的包`apt-get build-dep foo`


## dpkg
> package manager for Debian
+ 显示DEB包信息	dpkg -I xx.deb
+ 显示DEB包文件列表	dpkg -c xx.deb
+ 安装DEB包	dpkg -i xx.deb
+ 安装DEB包（指定根目录）	dpkg --root=<directory> -i xx.deb
+ 显示所有已安装软件	dpkg -l
+ 显示已安装包信息	dpkg -s foo
+ 显示已安装包文件列表	dpkg -L foo
+ 卸载包	dpkg -r foo
+ 卸载软件包并删除其配置文件	dpkg -P foo
+ 重新配置已安装程序	dpkg-reconfigure foo



## 从软件源中编译软件流程

> 适用于少量代码改动或者配置修改
## 功能	具体语句	示例
+ 获取源码	`apt-get source foo`
	> `apt-get source rox-filer`
+ 安装编译依赖	`apt-get build-dep foo`	
	> `apt-get build-dep rox-filer`
+ 解压源码	`dpkg-source -x foo_version-revision.dsc`	
	> `dpkg-source -x rox_2.11-3.dsc`
+ 修改源码部分	　	`nano ROX-Filer/src/main.c`
+ 创建包	`dpkg-buildpackage -rfakeroot -b`	　
+ 修改软件可升级状态	`echo -e "foo hold" | dpkg --set-selections`
