树莓派学习笔记（7）：利用bypy实现树莓派NAS同步百度云

转载请注明：@小五义http://www.cnblogs.com/xiaowuyi  QQ群：64770604
树莓派制作NAS过程详见http://www.cnblogs.com/xiaowuyi/p/4051238.html。
 
Bypy是一个百度云/百度网盘的Python客户端，主要的目的就是在Linux环境下（命令行）同步百度云盘空间。Bypy要求python2.7以上版本，最新版下载地址为https://github.com/houtianze/bypy
一、bypy安装
1、所需环境
python 2.7x
python requests库（安装该库需要setuptools 和pip）
2、安装
（1）python 2.7 不在详述
（2）requests库安装
首先安装setuptools
wget https://bootstrap.pypa.io/ez_setup.py -O - | python
如果安装过程中出现问题，可能是没有安装zip解压的原因，zip如何安装请百度。
然后安装pip
https://pypi.python.org/pypi/pip 从这里下载pip－1.5.6.tar.gz
tar -zxvf pip-1.5.6.tar.gz
python setup.py install
安装完成后，pip install requests。实现requests的安装。
（3）安装bypy
直接从https://github.com/houtianze/bypy下载解压就可以了。
3、使用
（1）第一次使用
要把系统的区域编码设置为UTF-8
vi /etc/sysconfig/i18n
将原内容改为：

LANG="zh_CN.UTF-8"
SYSFONT=latarcyrheb-sun16

设置token：
./bypy.py info
程序会要求你访问一个网址(fanswm:https://openapi.baidu.com/oauth/2.0/authorize?scope=basic+netdisk&redirect_uri=oob&response_type=code&client_id=q8WE4EpCsau1oS0MplgMKNBn)，获取你授权码(fanswm:7e59320eee38071d03b4fb3f809b436a)，授权后复制code给程序，程序会利用不同的服务器进行认证，认证成功会显示百度网盘的容量，如果一次没成功，可以多试几次，容易被墙。

这时百度网盘的“我的应用管理”下会形成bypy文件＋。
安装完全后，可以使用./bypy.py list 来看一下列表。
（2）主要命令参数
optional                 arguments:
  -h, --help            show this help message and exit
  --TESTRUN             Perform python doctest [default: False]
  --PROFILE             Profile the code [default: False]
  -V, --version         show program's version number and exit
  -d, --debug           enable debugging & logging [default: 0]
  -v, --verbose         set verbosity level [default: 0]
  -r RETRY, --retry RETRY
                        number of retry attempts on network error [default: 5
                        times]
  -q QUIT, --quit-when-fail QUIT
                        quit when maximum number of retry failed [default:
                        False]
  -t TIMEOUT, --timeout TIMEOUT
                        network timeout in seconds [default: 60]
  -s SLICE, --slice SLICE
                        size of file upload slice (can use '1024', '2k',
                        '3MB', etc) [default: 20 MB]
  --chunk CHUNK         size of file download chunk (can use '1024', '2k',
                        '3MB', etc) [default: 20 MB]
  -e, --verify          Verify upload / download [default : False]
  -f, --force-hash      force file MD5 / CRC32 calculation instead of using
                        cached values [default: False]
  -l LISTFILE, --list-file LISTFILE
                        input list file (used by some of the commands only
                        [default: None]
  --resume-download RESUMEDL
                        resume instead of restarting when downloading if local
                        file already exists [default: True]
  --include-regex INCREGEX
                        regular expression of files to include. if not
                        specified (default), everything is included. for
                        download, the regex applies to the remote files; for
                        upload, the regex applies to the local files. to
                        exclude files, think about your regex, some tips here:
                        https://stackoverflow.com/questions/406230/regular-
                        expression-to-match-string-not-containing-a-word
                        [default: ]
  --on-dup ONDUP        what to do when the same file / folder exists in the
                        destination: 'overwrite', 'skip', 'prompt' [default:
                        overwrite]
  --no-symlink          DON'T follow symbol links when uploading / syncing up
                        [default: True]
  --disable-ssl-check   DON'T verify host SSL cerificate [default: True]
  -c, --clean           1: clean settings (remove the token file) 2: clean
                        settings and hash cache [default: 0]

Commands:
help command - provide some information for the command
cleancache - remove invalid entries from hash cache file
combine <remotefile> [md5s] [localfile] - try to create a file at PCS by combining slices, having MD5s specified
compare [remotedir] [localdir] - compare the remote direcotry with the local directory
copy/cp <from> <to> - copy a file / dir remotely at Baidu Yun
delete/remove/rm <remotepath> - delete a file / dir remotely at Baidu Yun
downdir <remotedir> [localdir] - download a remote directory (recursively)
downfile <remotefile> [localpath] - download a remote file.
dumpcache - display file hash cache
list/ls [remotepath] [format] [sort] [order] - list the 'remotepath' directory at Baidu PCS
listrecycle [start] [limit] - list the recycle contents
meta <remotepath> [format] - get information of the given path (dir / file) at Baidu Yun.
mkdir <remotedir> - create a directory at Baidu Yun
move/mv/rename/ren <from> <to> - move a file / dir remotely at Baidu Yun
quota/info - displays the quota information
refreshtoken - refresh the access token
restore <remotepath> - restore a file from the recycle bin
search <keyword> [remotepath] [recursive] - search for a file using keyword at Baidu Yun
stream <remotefile> <localpipe> [format] [chunk] - stream a video / audio file converted to M3U format at cloud side, to a pipe.
syncdown [remotedir] [localdir] [deletelocal] - sync down from the remote direcotry to the local directory
syncup [localdir] [remotedir] [deleteremote] - sync up from the local direcotry to the remote directory
upload [localpath] [remotepath] [ondup] - upload a file or directory (recursively)


https://github.com/fanswm/bypy/blob/master/README.md
中文说明 (English readme is at the bottom)

这是一个百度云/百度网盘的Python客户端。主要的目的就是在Linux环境下（Windows下应该也可用，但没有仔细测试过）通过命令行来使用百度云盘的2TB的巨大空间。比如，你可以用在Raspberry Pi树莓派上。它提供文件列表、下载、上传、比较、向上同步、向下同步，等操作。
由于百度PCS API权限限制，程序只能存取百度云端/apps/bypy目录下面的文件和目录。
特征: 支持Unicode/中文；失败重试；递归上传/下载；目录比较; 哈希缓存。
界面是英文的，主要是因为这个是为了Raspberry Pi树莓派开发的。
程序依赖

重要：想要支持中文，你要把系统的区域编码设置为UTF-8。（参见：http://perlgeek.de/en/article/set-up-a-clean-utf8-environment)
重要：你需要安装Python Requests 库. 在 Debian / Ubuntu / Raspbian 环境下，只需执行如下命令一次：
sudo pip install requests
安装

稳定版：直接通过pip来安装：sudo pip install bypy （支持Python 2.7+, 3.3+)
开发版：git clone到任意目录。（为了运行方便，可以把bypy.py和bypygui.pyw拷贝至/usr/bin/目录
运行

作为独立程序
稳定版（pip安装的）：运行 bypy (或者python -m bypy，或者python3 -m bypy）
开发版(git clone的）：进入clone目录，运行./bypy (或者python ./bypy，或者python3 ./bypy）
可以看到命令行支持的全部命令和参数。
作为一个包，在代码中使用
import bypy
简单的图形界面： ./bypygui.pyw
要找多线程图形界面的，这个貌似不错：bcloud
基本操作

显示使用帮助和所有命令（英文）:
bypy.py
第一次运行时需要授权，只需跑任何一个命令（比如 bypy.py info）然后跟着说明（登陆等）来授权即可。授权只需一次，一旦成功，以后不会再出现授权提示.
更详细的了解某一个命令：
bypy.py help <command>
显示在云盘（程序的）根目录下文件列表：
bypy.py list
把当前目录同步到云盘：
bypy.py syncup
or
bypy.py upload
把云盘内容同步到本地来：
bypy.py syncdown
or
bypy.py downdir /
比较本地当前目录和云盘（程序的）根目录（个人认为非常有用）：
bypy.py compare
更多命令和详细解释请见运行bypy.py的输出。
调试

运行时添加-v参数，会显示进度详情。
运行时添加-d，会显示一些调试信息。
运行时添加-ddd，还会会显示HTTP通讯信息（警告：非常多）
经验分享

请移步至wiki，方便分享/交流。

