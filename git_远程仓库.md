## 修改远程仓库地址
+ 修改命令
+ + `git remote origin set-url [url]`

+ 先删后加
+ + `git remote rm origin`
+ + `git remote add origin [url]`

+ 直接修改config文件

## 远程仓库管理

+ 查看当前的远程库

` git remote `

> 它会列出每个远程库的简短名字.在克隆完某个项目后,至少可以看到一个名为 origin 的远程库,Git 默认使用这个名字来标识你所克隆的原始仓库:

> origin也可以加上 -v 选项(译注:此为 ?verbose 的简写,取首字母),显示对应的克隆地址:

`git remote -v`

+ 添加远程仓库

> 要添加一个新的远程仓库,可以指定一个简单的名字,以便将来引用,运行

`git remote add [shortname] [url]:`

> ```
git remote
# origin
git remote add pb git://github.com/paulboone/ticgit.git
git remote -v
# origin git://github.com/schacon/ticgit.git
pb git://github.com/paulboone/ticgit.git
```

> 现在可以用字串 pb 指代对应的仓库地址了.比如说,要抓取所有 Paul 有的,但本地仓库没有的信息,可以运行 `git fetch pb`

## 从远程仓库抓取数据

`git fetch [remote-name]`
> + 此命令会到远程仓库中拉取所有你本地仓库中还没有的数据.
运行完成后,你就可以在本地访问该远程仓库中的所有分支,将其中某个 分支合并到本地,或者只是取出某个分支,一探究竟.
> + 如果是克隆了一个仓库,此命令会自动将远程仓库归于 origin 名下.所以,git fetch origin 会抓取从你上次克隆以来别人上传到此远程仓库中的所有更新(或是上次 fetch 以来别人提交的更新).有一点很重要,需要记住,fetch 命令只是将远端的数据拉到本地仓库,并不自动合并到当前工作分支,只有当你确实准备好了,才能手工合并.(说 明:事先需要创建好远程的仓库,然后执行:git remote add [仓库名] [仓库url],git fetch [远程仓库名],即可抓取到远程仓库数据到本地,再用git merge remotes/[仓库名]/master就可以将远程仓库merge到本地当前branch.这种分支方式比较适合独立-整合开发,即各自开发测试好后 再整合在一起.比如,Android的Framework和AP开发.

> 可以使用--bare 选项运行git init 来设定一个空仓库,这会初始化一个不包含工作目录的仓库.

> 如果设置了某个分支用于跟踪某个远端仓库的分支(参见下节及第三章的内容),可以使用 git pull 命令自动抓取数据下来,然后将远端分支自动合并到本地仓库中当前分支.在日常工作中我们经常这么用,既快且好.实际上,默认情况下 git clone 命令本质上就是自动创建了本地的 master 分支用于跟踪远程仓库中的 master 分支(假设远程仓库确实有 master 分支).所以一般我们运行 git pull,目的都是要从原始克隆的远端仓库中抓取数据后,合并到工作目录中当前分支.

## 推送数据到远程仓库

`git push [remote-name] [branch-name]`
> 如果要把本地的 master 分支推送到 origin 服务器上(再次说明下,克隆操作会自动使用默认的 master 和 origin 名字),可以运行下面的命令:
`git push origin master`

> 只有在所克隆的服务器上有写权限,或者同一时刻没有其他人在推数据,这条命令才会如期完成任务.如果在你推数据前,已经有其他人推送了若干更新,那 你的推送操作就会被驳回.你必须先把他们的更新抓取到本地,并到自己的项目中,然后才可以再次推送.

## 查看远程仓库信息
`git remote show [remote-name]`

## 远程仓库的删除和重命名
+ 在新版 Git 中可以用 git remote rename 命令修改某个远程仓库的简短名称,比如想把 pb 改成 paul,可以这么运行:

`git remote rename pb paul`

>paul注意,对远程仓库的重命名,也会使对应的分支名称发生变化,原来的 pb/master 分支现在成了paul/master.

+ 移除远端仓库,可以运行 git remote rm 命令:
`git remote rm paul`
