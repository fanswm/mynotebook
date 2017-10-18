## 20171018
+ `sudo dpkg -i TeighaFileConverter_QT5_lnxX86_4.7dll.deb`
> tags: deb软件包 安装 install

## RSS 20171018
+ `sudo curl -sSL https://get.daocloud.io/docker | sh`
+ `sudo docker run -d --name ttrssdb nornagon/postgres`
+ `sudo docker run -d --link ttrssdb:db -p 80:80 -e SELF_URL_PATH=http://172.17.0.1 fischerman/docker-ttrss`
> -p 80:80：该参数表明，将该容器内应用的 80 端口（冒号后）映射到主机的 80 端口（冒号前）上；“172.17.0.1”是docker的ip。

# 显示所有已安装的容器
sudo docker ps

# 显示所有已安装的容器(包括未运行的)
sudo docker ps -a

# 停止一个容器
sudo docker stop 容器id

# 重启一个容器
sudo docker restart

# 删除一个容器
sudo docker rm 容器id

## net-tools: 20171018
+ `sudo apt-get install net-tools`
