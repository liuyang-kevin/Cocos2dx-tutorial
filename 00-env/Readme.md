*预习：Cocos种类、历史、阅读官方文档*

**目标: 配置好开发环境**

本项目使用Cocos2d-x。如果查询过相关资料。你就会知道2dx这个版本是一种移植版本，C++版本。多平台通用。但是2dx跟官方提供的其他几个，或IDE、或JS版本并不是一种东西。

So。第一步
1. 基础编译环境：Python、CMake、C++
2. IDE方面：VScode、Xcode 
    1. Android Studio、Android SDK 如果需要可以单独下载
3. 下载cocos2dx的sdk
4. 安装sdk中的命令行工具。
Mac下。cmake，c++什么的用brew这个工具来装，网上查一下，然后就：
```bash
brew install cmake # 便完成了
brew install xxxxx # 需要的其他依赖，网上查查，都可安装
brew cask install xxx # brew-cask可以搜索一下，有图形界面的使用本命令安装
```
对于IDE方面，官网下载安装，Xcode在AppStore上安装。

第三步，[cocos sdk][cocos sdk]下载，前往官方、或github直接clone。

随后阅读一下[官方文档][cocos docs]。4.0版本。查看【[引擎工具-cocos 命令][doc cocos cmd]】

使用命令行进入到CocosSDk所在目录
```bash
cd /xxxx/xxxx # cocos sdk 所在目录
# 执行安装脚本。
# 本脚进行各种相关环境变量的配置更改，将cocos命令写入到配置文件。
# 过程中需要关联其他SDK的环境变量位置。根据需要选择跳过，或手动输入
python setup.py 
# 检查命令是否安装成功
cocos -v
```

> 没啥用的细节。查看环境变量后，我发现，setup.py脚本修改了我的环境变量。
> ```bash
> # Add environment variable COCOS_CONSOLE_ROOT for cocos2d-x
> export COCOS_CONSOLE_ROOT="/Users/fd/cocos2d-x-4.0/tools/cocos2d-console/bin"
> export PATH=$COCOS_CONSOLE_ROOT:$PATH
> 
> # Add environment variable COCOS_X_ROOT for cocos2d-x
> export COCOS_X_ROOT="/Users/fd"
> export PATH=$COCOS_X_ROOT:$PATH
> 
> # Add environment variable COCOS_TEMPLATES_ROOT for cocos2d-x
> export COCOS_TEMPLATES_ROOT="/Users/fd/cocos2d-x-4.0/templates"
> export PATH=$COCOS_TEMPLATES_ROOT:$PATH
> ```



[cocos sdk]: https://github.com/cocos2d/cocos2d-x "cocos sdk"
[cocos docs]: https://docs.cocos.com/cocos2d-x/v4/manual/zh/ "4.0文档"
[doc cocos cmd]: https://docs.cocos.com/cocos2d-x/v4/manual/zh/editors_and_tools/cocosCLTool.html "引擎工具-cocos 命令"