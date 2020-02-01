本章练习官方demo中的各种方法，系统了解cocos都提供了哪些内容。

```bash
# 新建项目
cocos new DemoGame -p com.fifth-ai.cc.gamedemo -l cpp -d ./02-exercise
```

项目结构
=======
* `/Classes`文件夹中的`*.cpp`,`*.h`文件是Cocos的入口。
* `/proj.*`等文件夹,提供了各个平台的兼容代码，与程序入口。
    * 其编译后，会借用`/Classes/AppDelegate.h`链接C++的编译结果。
* `AppDelegate.cpp`内部实现了生命周期。
    * `applicationDidFinishLaunching`方法会被各个平台回调。这里便是我们的入口函数。

> 对于编辑器方面，`/proj.*`等文件夹中提供了各个平台的项目入口。当使用`cocos run . -p mac -m debug`命令时，*-build文件夹内部会产生对应平台项目
> 所以，用vs code直接编辑cpp文件也是可以的。

基本概念
==========
梳理一下文档中的内容、以下是快速理解框架的基本概念
* 游戏的掌控者导演对象 - director
* 导演切换着一幕幕场景 - 场景(Scene)
* 场景里充满了演员与道具 - 精灵(Sprite)、节点(Node)
    * 精灵类继承于节点类，区别就是因为精灵可以包含动作(Action)
    * 演员可以作出各种动作 - 动作(Action)
    * 专业演员可以作出连续动作 - 序列(Sequence)
* 日志输出使用cocos提供的log() 函数。
* UI 组件，这个是单独一套轻量体系，用于菜单的制作。使用Menu类

> 官方文档中提及了精灵、节点的绘制树。这个还是需要专门去看一下的。

一、搭建菜单UI
=======
首先，本章即然是要练习，我们就需要尝试很多基础类。所以，需要像APP一样频繁的切换页面（场景）。

> 细节需要查看源码。细节操作还是有很多的。

1. 首先我们初始化导演对象，再初始化OpenGLView对象，并交由导演管理。
```c++
// 初始化 director/导演
auto director = Director::getInstance();
// 获取OpenGL的图形对象
auto glview = director->getOpenGLView(); 
// 初始化
...
...
// director 统筹管理
director->setOpenGLView(glview);
```
2. 增加用于UI的场景类
首先，修改CmakeLists文件。将导入文件修改为
```cmake
# 修改资源文件。导入Classes/文件夹下的cpp，h文件。
# 推荐手动维护项目，还可以保证项目结构干净。
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     Classes/HelloWorldScene.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     Classes/HelloWorldScene.h
     )

# 下面这种方法是导入所有代码文件。但是这里有个坑。需要到build目录执行cmake；
# 会导致直接在项目下用cocos run失败。推荐手动维护项目，还可以保证项目结构干净。
list(APPEND GAME_SOURCE
     Classes/**/*.cpp
     )
list(APPEND GAME_HEADER
     Classes/**/*.h
     )
```
然后仿照Helloworld类，写一个自己的MenuUI类型。并加载给director对象。
```cpp
// 创建第一个场景，demo中是HelloWorld，这里修改成我们自己编写的类
// auto scene = HelloWorld::createScene();
auto mMenuUIScene = MenuUI::createScene();
// 启动
director->runWithScene(mMenuUIScene);
```
3. 修改MenuUI类。实现UI列表功能。
保留HelloWorld的关闭按钮。并使用Menu菜单类添加菜单。
Menu 对象是一种特殊的 Node 对象。所以需要添加到场景中去
```cpp
// 创建菜单。
auto menu = Menu::create(closeItem, NULL);
menu->setPosition(Vec2::ZERO); // 添加在坐标0，0的位置，（目测是是左下角，menu会充满屏幕）
this->addChild(menu, 1);       // 添加到Scene中去
```
经过查看官方test-cpp的源码。源码写法略微高级。这里我们摘抄其关键代码。

* 需要：`extensions/cocos-ext.h` 中的 `tableview` 
* 需要：继承TableViewDataSource（数据源），TableViewDelegate（触屏事件处理），同时实现其虚函数。

> 1. cocos2dx 移植自 cocos2d，所以风格与IOS很像。tableview+delegate完成循环列表
> 2. 经过一番查询，列表有listview与tableview两种
>    * listview好写，多于20条数据就会卡顿。等于是android的scrollview
>    * tableview复杂一些，循环复用view，性能好，代码量就大一些。等于android的Listview，recycleview

> 代码中可以看到cocos的宏，其实就是名空间引用。省的写XXX::xx等长段引用
> ```cpp
> USING_NS_CC;
> USING_NS_CC_EXT;
> ```

其余部分实现查看代码

不理解的C++语法。
========
## auto
auto是c++程序设计语言的关键字。用于两种情况

（1）声明变量时根据初始化表达式自动推断该变量的类型

（2）声明函数时函数返回值的占位符

举例：对于值x=1；既可以声明： int x=1 或 long x=1，也可以直接声明 auto x=1



## std::nothrow
`s_testController = new (std::nothrow) TestController;`

对于比较健壮的代码来说，nothrow使用的情况比直接new多很多吧。直接new如果失败要抛出异常的，结果就是为了健壮性代码里到处都是try。

所以一般健壮的分配方式都用new (nothrow) xxx的(当然也有用malloc等的)，之后判断NULL就ok了。

还有在new出现异常，表示内存几经到达边缘了，再用try+catch来消耗内存也是无济于事的。

## Friend Classes（友元类）
C++中的friend关键字其实做这样的事情：在一个类中指明其他的类（或者）函数能够直接访问该类中的private和protected成员。
你可以这样来指明：

friend class aClass;