
SSH优点：
1.安全性高，设备不用了就删除key，而不是http得改密码。
2.可连接性高，比http稳定

# Git本地代理设置
[socks]
	proxy=socks5://127.0.0.1:7890
[http]
	proxy=socks5://127.0.0.1:7890
[https]
	proxy=socks5://127.0.0.1:7890
注：当push要http登录时可以临时将socks5为http

# Git设置
添加一个新的public key教程：
	https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent
1.命令生成公钥id_rsa.pub和私钥id_rsa，两个命令都能用，邮箱是github账号。
	ssh-keygen -t ed25519 -C "xxx@gmail.com"
	C:\Users\Sekia\.ssh
		id_ed25519
		id_ed25519.pub
	所有询问都可以回车默认执行：
		1.邮箱是github登录邮箱
		2.可选输入额外的验证短语用于首次建立连接时的确认
	网页端添加SSH公钥：设置-SSH and GPG keys

2.下载安装git
	https://www.git-scm.com/download/win

3.克隆仓库
	git clone ssh://git@ssh.github.com:443/Acgmart/SekiaEngine.git
	git clone ssh://git@ssh.github.com:22/Acgmart/SekiaEngine.git
	git clone https://github.com/Acgmart/SekiaEngine.git
	如果触发了代理，可在Clash的Connections页中到相关链接的下载速度。

4.设置Fork仓库的使用目的
	GithubDesktop-Repository settings仓库设置-Fork behavior-For my own purposes