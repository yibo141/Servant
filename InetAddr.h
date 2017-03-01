/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef INETADDR_H
#define INETADDR_H
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

namespace servant
{

class InetAddr 
{
public:
    // 参数ip为点分十进制表示的ip地址
    InetAddr(const std::string &ip, uint16_t port);
    InetAddr(const struct sockaddr_in &addr): _addr(addr)
    { }
    const struct sockaddr_in& getSockAddrInet() const { return _addr; }
private:
    struct sockaddr_in _addr;
};

}

#endif // INETADDR_H