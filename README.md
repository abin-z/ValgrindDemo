# ValgrindDemo

一个简单的 C++ 示例项目，用于演示如何使用 [Valgrind](https://valgrind.org/) 检测内存泄漏和内存管理错误。

本项目包含有意制造内存问题的示例代码（`leak_demo.cpp`）以及正确的内存管理示例（`normal_demo.cpp`），适合学习和教学使用。

---

## 📁 项目结构
```sh
.
├── CMakeLists.txt
├── LICENSE
├── README.md
└── src
    ├── leak_demo.cpp
    └── normal_demo.cpp
```

## 🧰 环境要求

- 支持 C++11 及以上的编译器
- [CMake](https://cmake.org/) ≥ 3.10
- [Valgrind](https://valgrind.org/) 已安装并可在终端中使用

### Valgrind 选项说明

| 选项                             | 说明                                                 |
| ------------------------------ | -------------------------------------------------- |
| `--tool=memcheck`              | 指定使用 `memcheck` 工具（默认就是它，但显式写更清晰）                  |
| `--leak-check=full`            | 开启详细的内存泄漏检查                                        |
| `--show-leak-kinds=all`        | 显示所有类型的泄漏（definite, indirect, possible, reachable） |
| `--track-origins=yes`          | 显示无效内存读取/使用的来源，更容易定位 bug（代价是性能更低）                  |
| `--verbose`                    | 提供更详细的信息                                           |
| `--log-file=valgrind.log`      | 将输出写入到文件中，便于后续分析                                   |
| `./build_output/bin/leak_demo` | 你要检测的程序                                            |


---

## 🔨 构建方式
在项目根目录下执行：
```bash
cmake -B build
cmake --build build
```
构建完成后，会生成两个可执行文件：

`leak_demo`：包含内存泄漏和 delete 错误

`normal_demo`：无内存问题的正确示例
```bash
/.../ValgrindDemo/build_output/bin/leak_demo
/.../ValgrindDemo/build_output/bin/normal_demo
```
## 🔍 使用 Valgrind 运行程序  
**检测内存问题的示例（leak_demo）**
```bash
valgrind --leak-check=full ./build_output/bin/leak_demo
```
会输出一下内容:
```bash
[abin@rocky ValgrindDemo]$ valgrind --leak-check=full ./build_output/bin/leak_demo
==102365== Memcheck, a memory error detector
==102365== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==102365== Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
==102365== Command: ./build_output/bin/leak_demo
==102365==
Running leak demo...
Memory leak in leak_memory01()...
==102365== Mismatched free() / delete / delete []
==102365==    at 0x48486DF: operator delete(void*) (vg_replace_malloc.c:1131)
==102365==    by 0x4011DF: leak_memory02() (leak_demo.cpp:14)
==102365==    by 0x401246: main (leak_demo.cpp:22)
==102365==  Address 0x4d9d110 is 0 bytes inside a block of size 400 alloc'd
==102365==    at 0x4846743: operator new[](unsigned long) (vg_replace_malloc.c:729)
==102365==    by 0x4011C0: leak_memory02() (leak_demo.cpp:12)
==102365==    by 0x401246: main (leak_demo.cpp:22)
==102365==
Memory leak in leak_memory02()...
Done.
==102365==
==102365== HEAP SUMMARY:
==102365==     in use at exit: 4 bytes in 1 blocks
==102365==   total heap usage: 4 allocs, 3 frees, 74,132 bytes allocated
==102365==
==102365== 4 bytes in 1 blocks are definitely lost in loss record 1 of 1
==102365==    at 0x4844FB5: operator new(unsigned long) (vg_replace_malloc.c:487)
==102365==    by 0x401197: leak_memory01() (leak_demo.cpp:5)
==102365==    by 0x401216: main (leak_demo.cpp:20)
==102365==
==102365== LEAK SUMMARY:
==102365==    definitely lost: 4 bytes in 1 blocks
==102365==    indirectly lost: 0 bytes in 0 blocks
==102365==      possibly lost: 0 bytes in 0 blocks
==102365==    still reachable: 0 bytes in 0 blocks
==102365==         suppressed: 0 bytes in 0 blocks
==102365==
==102365== For lists of detected and suppressed errors, rerun with: -s
==102365== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
[abin@rocky ValgrindDemo]$
```
说明：

存在内存泄漏（没有调用 delete）

错误使用 delete 释放数组（应使用 delete[]）

**正确的内存管理示例（normal_demo）**
```bash
valgrind --leak-check=full ./build_output/bin/normal_demo
```
预期输出：
```bash

[abin@rocky ValgrindDemo]$ valgrind --leak-check=full ./build_output/bin/normal_demo
==103367== Memcheck, a memory error detector
==103367== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==103367== Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
==103367== Command: ./build_output/bin/normal_demo
==103367==
Running normal demo...
Memory normal in normal_memory01()...
Memory normal in normal_memory02()...
Done.
==103367==
==103367== HEAP SUMMARY:
==103367==     in use at exit: 0 bytes in 0 blocks
==103367==   total heap usage: 4 allocs, 4 frees, 74,132 bytes allocated
==103367==
==103367== All heap blocks were freed -- no leaks are possible
==103367==
==103367== For lists of detected and suppressed errors, rerun with: -s
==103367== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
[abin@rocky ValgrindDemo]$
```
说明该程序没有内存泄漏或释放错误。