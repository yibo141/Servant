#include "../Buffer.h"
#include <iostream>

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
    return 0;
}