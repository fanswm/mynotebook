openvpn的证书分为三部分：CA证书、Server端证书、Client端证书。

安装openvpn:
$ sudo apt-get install openvpn
$ cp -r /usr/share/doc/openvpn/examples/easy-rsa/2.0  /etc/openvpn/easy-rsa 
$ cd /etc/openvpn/easy-rsa

$ cd /usr/share/easy-rsa
$ cd /etc/openvpn/easy-rsa
$ vim ./vars
    edit:    KEY_SIZE=1024
    修改 export EASY-RSA "/etc/openvpn/easy-rsa"
    export KEY_COUNTRY=”CN”
    export KEY_PROVINCE=”HZ”
    export KEY_CITY=”HangZhou”
    export KEY_ORG=”fanswm”
    export KEY_EMAIL=”fanswm@pi.com”
    export KEY_OU=”fanswm”
    export KEY_NAME=”fanswm_key”

$ source ./vars

清除原来所有密钥：
$ ./clean-all
$ ./build-ca: /etc/openvpn/easy-rsa/pkitool: not found
$ cp /usr/share/easy-rsa /etc/openvpn/easy-rsa
$ cp /usr/share/doc/openvpn/examples/sample-config-files/server.conf.gz /etc/open
$ gzip -d sever.conf.gz
$ cp -r /usr/share/doc/openvpn/example/* /etc/openvpn/

$ cd /etc/openvpn/easy_rsa/

制作CA证书：ca.crt(要用的), ca.key
$ ./build-ca
    EasyRSA NAME:easy-rsa-name #默认:EasyRSA
    Commom Name 必须是你为服务器取的名字.fanswm:server

制作server端证书：server.crt（要用的）,server.csr,server.key（要用的）
$ ./build-key-server fan_vpn-server     #我的"服务器名"备注:fan_vpn_server
    Commom Name必须是你为服务器取的名字;
    A challenge password? 必须啥也不输，回车即可。
    Sign the certificate? [y/n] 废话，你必须输入"y"。
    1 out of 1 certificate requests certified, commit?[y/n] y

制作client端证书(.crt, .key, .csr )，创建用户：
$ cd /etc/openvpn/easy-rsa/
$ ./build-key-pass client1        #build-key ?
    CLIENT1    client12
    client2(capslocak)    client223
    client3
    google.com ID:abstract.hex@gamil.com

如果你想快速生成用户证书不需要手工交互的话，
可以使用如下命令：$ ./build-key –batch

$ cd keys
$ openssl rsa -in Client1.key -des3 -out Client1.3des.key

为服务器生成加密交换时的Diffie-Hellman文件：dh1024.pem
$ cd /etc/openvpn/easy-rsa/
$ ./build-dh    # 运行了近一个小时;2016/07/21 21:21第二次运行,改成1024之后,运行了一分钟左右.
    起始时间：2016/09/06 14:05
    完毕时间：2016/09/06 14:16
$ openvpn --genkey --secret keys/ta.key

$ vim /etc/openvpn/server.conf
    1、更改ip为pi的ip.    
    7、cert /etc/openvpn/easy-rsa/keys/Server.crt # SWAP WITH YOUR CRT NAME
    8、key /etc/openvpn/easy-rsa/keys/Server.key # SWAP WITH YOUR KEY NAME
    9、dh /etc/openvpn/easy-rsa/keys/dh1024.pem #If you changed to 2048, change that here! 
    18、push "route 192.168.2.0 255.255.255.0"# SWAP THE IP NUMBER WITH YOUR RASPBERRY PI IP ADDRESS

$ vim /etc/sysctl.conf
    有一行“取消这行的注释来启用 IPV4 包转发”
$ sysctl -p
$   vim /etc/firewall-openvpn-rules.sh
    type:
#!/bin/sh
iptables -t nat -A POSTROUTING -s 10.8.0.0/24-o eth0 -j SNAT --to-source 192.168.31.142
$    chmod 700 /etc/firewall-OpenVPN-rules.sh
$    chown root /etc/firewall-OpenVPN-ruels.sh
$    vim /etc/network/interfaces
    iface eth0 inet dhcp
        pre-up /etc/firewall-openvpn-rules.sh

配置文件修改完毕后，我们现在来启动openvpn，使用如下命令：
$ /etc/init.d/openvpn start
$ netstat -tunlp |grep 1194

制作.ovpn文件：
$ vim /etc/openvpn/easy-rsa/keys/Default.txt
client
dev tun
proto udp
remote <你的公网ip地址> 1194
resolv-retry infinite
nobind
persist-key
persist-tun
mute-replay-warnings
ns-cert-type server
key-direction 1
cipher AES-128-CBC
comp-lzo
verb 6
mute 20
#fanswm: end

$ vim /etc/openvpn/easy-rsa/keys/MakeOPVN.sh
#!/bin/bash
# filename:MakeOPVN.sh

# Default Variable Declarations 
DEFAULT="Default.txt" 
FILEEXT=".ovpn" 
CRT=".crt" 
KEY=".3des.key" 
CA="ca.crt" 
TA="ta.key" 

#Ask for a Client name 
echo "Please enter an existing Client Name:"
read NAME 


#1st Verify that client’s Public Key Exists 
if [ ! -f $NAME$CRT ]; then 
 echo "[ERROR]: Client Public Key Certificate not found: $NAME$CRT" 
 exit 
fi 
echo "Client’s cert found: $NAME$CR" 


#Then, verify that there is a private key for that client 
if [ ! -f $NAME$KEY ]; then 
 echo "[ERROR]: Client 3des Private Key not found: $NAME$KEY" 
 exit 
fi 
echo "Client’s Private Key found: $NAME$KEY"

#Confirm the CA public key exists 
if [ ! -f $CA ]; then 
 echo "[ERROR]: CA Public Key not found: $CA" 
 exit 
fi 
echo "CA public Key found: $CA" 

#Confirm the tls-auth ta key file exists 
if [ ! -f $TA ]; then 
 echo "[ERROR]: tls-auth Key not found: $TA" 
 exit 
fi 
echo "tls-auth Private Key found: $TA" 

#Ready to make a new .opvn file - Start by populating with the 
default file 
cat $DEFAULT > $NAME$FILEEXT 

#Now, append the CA Public Cert 
echo "<ca>" >> $NAME$FILEEXT 
cat $CA >> $NAME$FILEEXT 
echo "</ca>" >> $NAME$FILEEXT

#Next append the client Public Cert 
echo "<cert>" >> $NAME$FILEEXT 
cat $NAME$CRT | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' >> $NAME$FILEEXT 
echo "</cert>" >> $NAME$FILEEXT 

#Then, append the client Private Key 
echo "<key>" >> $NAME$FILEEXT 
cat $NAME$KEY >> $NAME$FILEEXT 
echo "</key>" >> $NAME$FILEEXT 

#Finally, append the TA Private Key 
echo "<tls-auth>" >> $NAME$FILEEXT 
cat $TA >> $NAME$FILEEXT 
echo "</tls-auth>" >> $NAME$FILEEXT 

echo "Done! $NAME$FILEEXT Successfully Created."

#Script written by Eric Jodoin
#fanswm: MakeOPVN.sh end

$ chmod 700 ./MakeOVPN.sh
$ ./MakeOVPN.sh

配置client客户端：
    把client.ovpn，ca.crt，client1.crt，client1.key这4个文件拷贝至Openvpn的配置目录下

安装openVPN后：
    CreateProcess failed, exe='d:\Program Files\OpenVPN\bin\openvpn.exe'
    cmdline='openvpn --version' dir='d:\Program Files\OpenVPN\bin'

$ cp client1.ovpn /mnt/usb/shares/
$ cp ca.crt /mnt/usb/shares/

下载的客户端版本号一定要与服务器端openvpn的版本一直，否则可能会出现无法连接服务器的现象。

#测试服务器配置文件正确，没有输出说明正确，错误会提示哪行配错了
$ openvpn server.conf

#开始Openvpn服务，提示ok说明启动成功了
$ /etc/init.d/openvpn start
查看版本：
$ openvpn --version    #2016/09/08 13:07    版本2.3.4
配置文件修改完毕后，我们现在来启动openvpn，使用如下命令：
$ /etc/init.d/openvpn start
$ netstat -tunlp | grep 1194
如果win连接vpn成功之后，在win，
    $ ipconfig
可以看到获得的ip地址是10.8.0.6。
日志文件：
/var/log/openvpn.log

开机启动：
$ vim /etc/rc.local
    edit: add:     systemctl start openvpn.service
            or:    /etc/init.d/openvpn start
linux客户端连接openvpn：
$ openvpn -config client.ovpn
$ ifconfig 查看获得的ip地址。
如果想让ubuntu开机启动并后台运行的话，可以把这条命令加入rc.local文件中：
/usr/sbin/openvpn –config /绝对路径/client.ovpn >/var/log/openvpn.log &
注意，命令末尾的&符号不能省略


2016/09/07 19:59
Connecting to client has failed！
Connection to Client has failed
There is something blocking the connection to the OpenVPN server. Here are the steps to solve this isssue.
First
Check the log files
Second
Check your Firewall
Third
Open your client.conf file and make sure that the paths to your certificates are absolute path
replace for example:
key client.key with
key "c:\\Program Files\\OpenVPN\\config\\client.key"

$ ping 10.8.0.1

2016/09/10 14:24：
把协议改为TCP，并把端口转发改为TCP，成功！！！！！
2016/09/10 21:44
改 server后，成功！
push "dhcp-option DNS 8.8.8.8"
push "dhcp-option DNS 8.8.4.4"
push "dhcp-option DNS 208.67.222.222"
push "dhcp-option DNS 208.67.220.220"


$ systemctl status openvpn@server.service




















错误记录：
Thu Mar 16 07:26:09 2017 TCP: connect to [AF_INET]221.192.153.42:1194 failed, will try again in 5 seconds: Connection timed out (WSAETIMEDOUT)
Thu Mar 16 07:26:14 2017 MANAGEMENT: >STATE:1489620374,RESOLVE,,,
Thu Mar 16 07:26:14 2017 MANAGEMENT: >STATE:1489620374,TCP_CONNECT,,,
Thu Mar 16 07:26:35 2017 TCP: connect to [AF_INET]221.192.153.42:1194 failed, will try again in 5 seconds: Connection timed out (WSAETIMEDOUT)
Thu Mar 16 07:26:40 2017 MANAGEMENT: >STATE:1489620400,RESOLVE,,,
Thu Mar 16 07:26:40 2017 MANAGEMENT: >STATE:1489620400,TCP_CONNECT,,,







