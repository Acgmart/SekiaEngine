
SSH优点：
1.安全性高，设备不用了就删除key，而不是http得改密码。
2.可连接性高，比http稳定
3.当用git命令进行push时要http登录时可以临时设置.gitconfig中代理为http://
4.第一次拉取的时候使用命令而不是客户端

# Git设置
添加一个新的public key教程：
	https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
1.命令生成公钥id_rsa.pub和私钥id_rsa，两个命令都能用，邮箱是github账号。
	ssh-keygen -t ed25519 -C "acgmart.com@gmail.com"
	ssh-keygen -t rsa -b 4096 -C "acgmart.com@gmail.com"
所有询问都可以回车默认执行，可选输入加密短语。

2.添加SSH密钥，如果使用githubdesktop只需要在网页端添加密钥。
将密钥文件移动到目录：C:\Users\Sekia\.ssh
	id_ed25519
	id_ed25519.pub
	config

2.1设置.ssh目录下新建的config文件(似乎都没用)
版本1：
Host GitHub.com
    HostName github.com
    User git
    ProxyCommand nc -x 127.0.0.1:7890 %h %p

版本二：
Host github.com
    ProxyCommand connect -H 127.0.0.1:7890 %h %p

版本三：
Host github.com
    ProxyCommand connect -S 127.0.0.1:7890 %h %p

3.下载安装git
	https://www.git-scm.com/download/win

4.克隆仓库
	git clone git@github.com:Acgmart/SekiaEngine.git
	git clone https://github.com/Acgmart/SekiaEngine.git
	在Clash的Connections页中可以看到git相关链接的下载速度

5.设置Fork仓库的使用目的
	GithubDesktop-Repository settings仓库设置-Fork behavior-For my own purposes

6.参考文章：
文章一：
	https://tyler-ytr.github.io/2021/07/02/git%E4%BB%A5%E5%8F%8Assh%E4%BB%A3%E7%90%86%E7%9A%84%E9%85%8D%E7%BD%AE/
文章二：
	https://www.lsjlt.com/news/436280.html
文章三：
	https://gist.github.com/evantoli/f8c23a37eb3558ab8765?permalink_comment_id=4285939

7.解决gitlab的push时遇到的missing OAhth问题：
因为用到了LFS 地址设置的不对 只能上传非LFS文件