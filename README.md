# Servant

在以下环境下测试通过

 运行环境：Linux 4.10.13

 编译器：g++ 6.3.1

# Usage

`$ make`

`$ ./Servant <port>`

`$ make clean`

**port**表示为端口号，比如8080.

# Detail

Servant是一个简单的用C++写的基于Reactor模式的多线程HTTP服务器，暂时只支持静态页面。

各个文件的功能如下：

**Servant.cpp**: 主函数文件，创建监听套接字并监听，选择一个线程将已连接套接字注册到其EventLoop中。

**Socket.cpp Socket.h**: 封装对套接字的各种操作，包括创建，绑定，监听等。

**Thread.cpp Thread.h**: 封装pthread线程的类。

**Epoll.cpp Epoll.h**: 封装epoll的各种操作的类。

**Parser.cpp Parser.h**: 用于解析客户端HTTP请求的类，将解析的结果传递给Handler类做后续处理。

**Handler.cpp Handler.h**: 相应客户端HTTP请求的类。

**Buffer.cpp Buffer.h**: 缓冲区，用于缓存客户发送的请求和服务器的相应，有读取请求和发送相应的功能。

**EventLoop.cpp EventLoop.h**: 事件循环的类，循环会不断获取Epoll类返回的活动套接字并交给Handler类处理。

**EventLoopThread.cpp EventLoopThread.h**: 将EventLoop和Thread结合的类，让每个线程都运行一个EventLoop。

**EventLoopThreadPool.cpp EventLoopThreadPool.h**: EventLoopThread线程池。

**CurrentThread.h**: 获取当前线程的线程ID。

**Mutex.h Condition.h**: 封装互斥量和条件变量的类。

**Makefile**: Makefile文件。

**home.html**: 测试用的HTML页面。

**test文件夹**是我的一些测试。

### 更多详细信息请参考我的博客：(正在写)