

#使用手册

更新
--
2014-10-6 增加了 Macox 版本

**下载七牛官方同步工具 Mac 版(请切换到mac-version 分支)**  

* [http://developer.qiniu.com/docs/v6/tools/qrsync.html](http://developer.qiniu.com/docs/v6/tools/qrsync.html)

* [http://devtools.qiniu.io/qiniu-devtools-darwin_amd64-current.tar.gz](http://devtools.qiniu.io/qiniu-devtools-darwin_amd64-current.tar.gz)

![image](http://leeyoung-image.qiniudn.com/%E5%B1%8F%E5%B9%95%E5%BF%AB%E7%85%A7%202014-10-06%2017.51.25.jpg)

*upload.sh*内容如下(代替 upload.bat)

```
#!/bin/bash
cd .
./qrsync  conf.json
```


软件预览
---

![http://leeyoung-image.qiniudn.com/2014-09-18_00004.jpg](http://leeyoung-image.qiniudn.com/2014-09-18_00004.jpg)


how to use
---

1. 编译源码
2. 下载解压[http://pan.baidu.com/s/1c0Cgl1Y](http://pan.baidu.com/s/1c0Cgl1Y)到任意目录
3. 拷贝编译后的可执行文件到update.bat所在目录

目录结构如下：

```

2014/09/18  08:16    <DIR>          .
2014/09/18  08:16    <DIR>          ..
2014/09/18  08:29               217 conf.json
2014/06/30  23:22         9,037,912 qboxrsctl.exe
2014/06/30  23:22         2,516,040 qetag.exe
2014/09/17  20:50           229,376 qiniu.exe    <------------------编译的可执行文件
2014/06/30  23:22        10,430,544 qrsboxcli.exe
2014/06/30  23:22        11,257,928 qrsync.exe
2014/09/17  17:33                25 update.bat
               7 个文件     33,472,042 字节
               2 个目录 31,657,132,032 可用字节
```


4. 修改AK,SK,空间名字和上传目录

> 拖拽的文件将会拷贝到上传目录后再上传到七牛。


![](http://leeyoung-image.qiniudn.com/2014-09-18_00006.jpg)