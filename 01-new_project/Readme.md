新建一个项目。
=======
项目创建
使用 cocos new 命令创建新项目，命令格式如下：
```bash
cocos new <game name> -p <package identifier> -l <language> -d <location>
```
执行我们自己的命令。注意最后的生成路径。将在生成路径下，产生一个名称为游戏名的文件夹。其中就是我们的项目
```bash
cocos new DemoGame -p com.fifth-ai.cc.gamedemo -l cpp -d ./01-new_project
```
生成后，我查看了一下项目。嗯。。。300M。因为项目将所有的SDK内容都拷贝进了项目文件。

嗯。需要增加一个gitignore来回避300M的SDK文件。。
```.gitignore
# Ignore cocos2d-x files, now cocos2d-x 3.0rc
/cocos2d


# Ignore files build by ndk and eclipse
libs/
bin/
obj/
gen/
assets/
local.properties


# Ignore python compiled files
*.pyc


# Ignore files build by xcode
*.mode*v*
*.pbxuser
*.xcbkptlist
*.xcscheme
*.xcworkspacedata
*.xcuserstate
*.xccheckout
xcschememanagement.plist
.DS_Store
._.*
xcuserdata/
DerivedData/


# cocostudio
cocostudio/Backup
cocostudio/Resources
	
# Others should Ignored
```

所以更新本教程代码后，项目中`/cocos2d`这个文件下的SDK还是需要自己导入的。

根据官方文档使用命令,启动项目，测试效果
```bash
cocos run . -p mac -m debug
```
其他平台、编译、发布可以查看[文档][doc cocos cmd]

追加忽略
==========
编译后会出现一下文件夹。记得在忽略文件末尾加入
```bash
/bin
/ios-build
/mac-build
/android-build
/linux-build
/win32-build
```


[doc cocos cmd]: https://docs.cocos.com/cocos2d-x/v4/manual/zh/editors_and_tools/cocosCLTool.html "引擎工具-cocos 命令"