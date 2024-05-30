# Game Archive Manager 存档管理器
在这里非常感谢https://github.com/Xiaomony/NoitaArchiveManager 这个项目，因为整体架构以及绝大部分代码都是直接使用此项目的源码。
### 为什么要做这种小工具？
我很喜欢玩肉鸽游戏，比如以撒的结合、noita，但是有时候肉鸽游戏的死亡惩罚过于严重了，例如辛辛苦苦几个小时构建的build因为一个走神误操作被小怪一波带走了，这让我让我感到非常的难过，以及有一种生命被浪费了的感觉，因此萌生出了要做一个能根据时间序列对游戏存档进行备份的工具，只要存档还在，我们为这个游戏付出的努力就没有白白浪费！
### 这是作弊工具吗？
可以算是，但是对于拥有几乎无尽变化的肉鸽游戏而言，这种作弊形式反而是最轻微的降低难度，仅仅添加了死亡可以重来这一功能，对于萌新或者手残党都是非常友好的，而且不像风灵月影那样过度滥用导致游戏性全无。
再者，单机游戏，很多时候作弊与否都是无所谓的，你玩得开心就好啦。


在此，再次感谢@Xiaomony，你的代码给了我实现这一切的基础。




- [Game Archive Manager 存档管理器](#game-archive-manager-存档管理器)
    - [为什么要做这种小工具？](#为什么要做这种小工具)
    - [这是作弊工具吗？](#这是作弊工具吗)
  - [使用说明及注意事项](#使用说明及注意事项)
  - [实现原理](#实现原理)
  - [构建环境](#构建环境)
      - [构建：直接运行build.bat](#构建直接运行buildbat)
  - [问题反馈](#问题反馈)
  
## 使用说明及注意事项

1. 本程序运行时会在程序所在目录下建立一个 **_Archive文件夹_** 用于存储日志文件和保存的存档,请勿删除(若删除,则相当于恢复程序第一次运行的状态)

2. 建议将程序放在C盘中的某个文件夹下,避免权限问题导致报错


3. 建议关闭Steam云存档

4. 请在游戏 **_正常保存、关闭_** 后再进行存档(游戏进行中存档的话保存的是游戏的 **自动存档** ,可能是几分钟前的存档,并非保存时的存档)

5. 游戏进行中请勿读取存档

6. 随着游戏的进行,每次存档 **所用的时间** 和 **占用的空间** 也会不断 **增大** ,请耐心等待

7. 命令操作：
   | 命令          | 含义             | 简写  | 说明                           |
   |:-----------:|:--------------:|:---:|:----------------------------:|
   | quit        |                | q   | 退出程序                         |
   | help        |                | h   | 帮助及注意事项                      |
   | clearScreen |                | cls | 清屏                           |
   | save        |                | s   | 保存（存档）                       |
   | qsave       | quick save     | qs  | 快速保存（无需填写存档名称和备注）            |
   | rsave       | repalce save   | rs  | 保存 且 覆盖最新存档（存档名与备注不变，存档时间更新） |
   | load        |                | l   | 指定存档进行读取                     |
   | qload       | quick load     | ql  | 快速读取（最近一次的存档）                |
   | log         |                | lo  | 查看所有存档极其信息                   |
   | slog        | short log      | sl  | 查看近七次存档                |
   | mArchive    | modify Archive | ma  | 修改某个存档的信息                    |
   | delArch     | delete Archive | del | 删除某个存档                       |
   | qDelete     | quick Delete   | qd  | 删除最新的存档                      |
   | usage       |                | use | 查看存档的占用空间            |

## 实现原理/使用说明
需要新建一个文件夹，将编译好的程序放在这个文件夹下，在文件夹下建立一个'path.txt'，然后向其中输入你想要存档的游戏存档文件夹的绝对路径路径（单行，不要回车或者空格断开），程序会读取此路径，通过复制该文件夹的内容并还原以达到存档和读档的目的。
注意：目前一个程序只支持一个游戏存档目录。
## 构建环境

- CMake VERSION 3.15
- MinGW gcc version 13.2.0

**_构建时注意要将cmake与mingw32-make添加到环境变量_**

>若未将cmake或mingw添加到环境变量,则分别需要将build.bat中的MAKER改为cmake的路径,GENERATOR改为mingw下bin目录的路径

```bat
set MAKER= path_to_cmake/cmake.exe
set GENERATOR= path_to_mingw/bin/mingw32-make.exe
```

#### 构建：直接运行build.bat

## 问题反馈
正在修bug,发行版的事也在弄，奈何没有开发经验，在学啦，不急不急。
