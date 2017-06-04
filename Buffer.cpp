/*
 * Author: Broglie 
 * E-mail: yibo141@outlook.com
 */

#include "Buffer.h"

size_t Buffer::readFd(int fd)
{
    char extrabuf[65535];
    char *ptr = extrabuf;
    size_t nleft = 65535;
    size_t nread = 0;
    while(true)
    {
        if((nread = read(fd, extrabuf, nleft)) < 0)
        {
            if((errno == EINTR))
                nread = 0;
            else 
                return 0;
        }
        else if(nread == 0)
            break;
        nleft -= nread;
        ptr += nread;
    }
    append(extrabuf, ptr - extrabuf);
    return (ptr - extrabuf);
}