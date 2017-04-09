/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include "Socket.h"
#include "InetAddr.h"
#include <cstring>
#include <iostream>
#include <fcntl.h>
#include <errno.h>

namespace servant
{

void Socket::bindAddr(const InetAddr *addr)
{
    bind(_socketfd, addr.getSockAddrInet());
}

void Socket::listen()
{
    listen(_socketfd);
}

int Socket::accept(InetAddr *peerAddr)
{
    struct sockaddr_in addr;
    ::memset(&addr, 0, sizeof(addr));
    int connfd = accept(_socketfd, &addr);
    if(connfd >= 0)
    {
        peeraddr->setSockAddrInet(addr);
    }
    return connfd;
}

int Socket::createNonblock()
{
    int sockfd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        // FIXME: 写入日志
        std::cout << "Socket::createNonblock error" << std::endl;
        exit(1);
    }
    setNonBlockAndCloseOnExec(sockfd);
    return sockfd;  
}

void Socket::bind(int sockfd, struct sockaddr_in &addr)
{
    int ret = ::bind(sockfd, static_cast<struct sockaddr*>(addr), sizeof(addr));
    if(ret < 0) 
    {
        std::cout << "Socket::bind error" << std::endl;
        exit(1);
    }
}

void Socket::listen(int sockfd)
{
    if(::listen(sockfd, 15) < 0)
    {
        std::cout << "Socket::listen error" << endl;
        exit(1);
    }
}

int Socket::accept(int sockfd, struct sockaddr_in *addr)
{
    socklen_t addrlen = sizeof(*addr);
    int connfd = ::accept(sockfd, static_cast<struct sockaddr*>(addr), &addrlen);
    setNonBlockAndCloseOnExec(connfd);
    if(connfd < 0)
    {
        std::cout << "Socket::accept error" << std::endl;
        switch(errno)
        {
            // 非致命错误，忽略
            case EAGAIN:
            case ECONNABORTED:
            case EINTR:
            case EMFILE:
                break;
            // 致命错误，退出程序
            case EFAULT:
            case EINVAL:
            case ENFILE:
            case ENOMEM:
                std::cout << "Socket::accept error" << errno << std::endl;
                exit(1);
                break;
            // 未知错误，退出程序
            default:
                std::cout << "Socket::accept error" << errno << std::endl;
                exit(1);
                break;
        }
    }
    return connfd;
}

void Socket::close(int sockfd)
{
    if(::close(sockfd) < 0)
    {
        std::cout << "Socket::close error" << std::endl;
        exit(1);
    }
}

void Socket::setNonBlockAndCloseOnExec(int sockfd)
{
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    int ret = ::fcntl(sockfd, F_SETFL, flags);

    flags = ::fcntl(sockfd, F_GETFD, 0);
    flags |= FD_CLOEXEC;
    ret = ::fcntl(sockfd, F_SETFD, flags);
}

} // servant
