/**
 ** Ideas from https://gist.github.com/jirihnidek/bf7a2363e480491da72301b228b35d5d
 ** and mqttnet.c
 **/
#include "legato.h"
#include "interfaces.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

/*
 * Takes url (host) and if available returns first ip address as a string of form XXX.XXX.XXX.XXX
 *
 * Failure to find an ipAddressAsString address function will return an empty string
 *
 * Hints often look like this:
 *  hints.ai_family = AF_INET;
 *  hints.ai_socktype = SOCK_STREAM;
 *  hints.ai_protocol = IPPROTO_TCP;
 *
 *  if(hints_ai_family) is AF_INET this causes the app to look for IPv4
 *  if(hints_ai_family) is AF_INET6 this may cause the app to look for IPv6 *** untested
*/

void net_getAddrInfo
(
    int32_t hints_ai_family,
        ///< [IN]

    int32_t hints_ai_socktype,
        ///< [IN]

    int32_t hints_ai_protocol,
        ///< [IN]

    const char* host,
        ///< [IN]

    char* ipAddressAsString,
        ///< [OUT]

    size_t ipAddressAsStringNumElements
        ///< [IN]
)
{
    int rc = -1;
    struct addrinfo hints;
    struct addrinfo *res = NULL;

    void *ptr;

    memset(ipAddressAsString,0,ipAddressAsStringNumElements);  // Set ipV4NumElements to empty string

    memset (&hints, 0, sizeof(hints));
    hints.ai_family = hints_ai_family;
    hints.ai_socktype = hints_ai_socktype;
    hints.ai_protocol = hints_ai_protocol;

    rc = getaddrinfo(host, NULL, &hints, &res);

    if (rc >= 0 && res != NULL)
    {
        while (res)
        {
            if (res->ai_family == hints.ai_family)
            {
                ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
                inet_ntop (res->ai_family, ptr, ipAddressAsString, ipAddressAsStringNumElements);
                break; // Found first IP address - exit loop
            }
        }
        freeaddrinfo(res);
    }
    else
    {
        LE_INFO("getaddrinfo() failed returning: %s %d", gai_strerror(rc), rc) ;
    }
}


void net_test(void)
{
    char ipAddress[2000];

    net_getAddrInfo(AF_INET, SOCK_STREAM , IPPROTO_TCP, "www.bbc.co.uk", ipAddress, sizeof(ipAddress) );
    LE_INFO("IPv4 %s", ipAddress);

    net_getAddrInfo(AF_INET6, SOCK_STREAM , IPPROTO_TCP, "www.bbc.co.uk", ipAddress, sizeof(ipAddress) );
    LE_INFO("IPv6 %s", ipAddress);
}



/*
hints.ai_family = AF_INET;
hints.ai_socktype = SOCK_STREAM;
hints.ai_protocol = IPPROTO_TCP;
*/

COMPONENT_INIT
{   
    LE_INFO("started\n");

    // net_test();

}
