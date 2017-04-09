/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

namespace servant
{

class InetAddr;
class Socket 
{
public:
    explicit Socket(int socketfd): _socketfd { }

    ~Socket() 
    { close(_socketfd); }

    int fd()
    { return _socketfd; }

    void bindAddr(const InetAddr *addr);

    void listen();

    int accept(InetAddr *peerAddr);

    // 是否开启SO_REUSEADDR选项
    void setReuseAddr(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(_socketfd, SOL_SOCKET, SO_REUSEADDR,
                     &optval, sizeof(optval));
    }

    // socket相关操作
    static int createNonblock();
    static void bind(int sockfd, struct sockaddr_in &addr);
    static void listen(int sockfd);
    static int accept(int sockfd, struct sockaddr_in *addr);
    static void close(int sockfd);
    static void setNonBlockAndCloseOnExec(int sockfd);
private:
    const int _socketfd;
};

} // namespace servant

#endif // SOCKET_H