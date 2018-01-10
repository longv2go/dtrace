DTrace
------
苹果官网的 DTrace 源码不能直接编译，需要引入一些内核的头文件，还要做一些修改，这个工程就是修改过后的，可以直接编译 dtrace 目标。

源代码地址： [https://opensource.apple.com/source/dtrace/dtrace/]()

# 更改

### include
添加 include 目录，主要用来存放一些缺少的头文件，这些缺少的头文件都是从 xnu 源码中搜索到的。

```
➜  include git:(master) ✗ tree .
.
├── CoreSymbolication
│   ├── CoreSymbolication.h
│   └── CoreSymbolicationPrivate.h
├── System
│   └── kern
│       └── cs_blobs.h
└── sys
    ├── codesign.h
    ├── csr.h
    ├── kas_info.h
    └── proc.h
```

其中 CoreSymbolication 来自 `https://github.com/longv2go/CoreSymbolication`


### 工程修改
修改 dtrace project 的 Build Settings -> Header Search Paths 为 $(SRCROOT)/include

### 源码修改
......