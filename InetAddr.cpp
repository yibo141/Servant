/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "InetAddr.h"

namespace servant
{

InetAddr::InetAddr(const uint16_t port)
{
    bzero(&_addr, sizeof(addr));
    _addr.sin_family = AF_INET;
    _addr.sin_addr.s_addr = ::htonl(INADDR_ANY);
    _addr.sin_port = ::htons(port);
}

InetAddr::InetAddr(const std::string &ip, const uint16_t port)
{
    ::inet_pton(AF_INET, ip.c_str(), &_addr.sin_addr);
    _addr.sin_port = ::htons(port);
}

}