#include "../Buffer.h"
#include <iostream>
#include <fcntl.h>

using namespace std;

void print(Buffer &buf)
{
    cout << "--------------------" << endl;
    cout << buf.writableBytes() << endl;
    cout << buf.readableBytes() << endl;
    cout << buf.readAllAsString() << endl;
    cout << buf.writableBytes() << endl;
    cout << buf.readableBytes() << endl;
}

int main()
{
    Buffer buf;
    string str = "Hello World!";
    buf.append(str.c_str(), str.size());
    print(buf);
    str = "buffer test";
    buf.append(str.c_str(), str.size());
    print(buf);
    int fd = open("Buffer_test", O_RDONLY, 0);
    buf.readFd(fd);
    // print(buf);
    int fd2 = open("Buffer_test_copy", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
    buf.sendFd(fd2);
    return 0;
}