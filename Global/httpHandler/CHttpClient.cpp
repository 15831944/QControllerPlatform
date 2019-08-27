/*
 * CHttpClient.cpp
 *
 *  Created on: 2015年12月9日
 *      Author: Louis Ju
 */

#include "CHttpClient.h"
#include <stdio.h>          // for printf() and fprintf()
#include <sys/socket.h>     // for socket(), bind(), and connect()
#include <arpa/inet.h>      // for sockaddr_in and inet_ntoa()
#include <stdlib.h>         // for atoi() and exit()
#include <string.h>         // for memset()
#include <unistd.h>         // for close()
#include <fcntl.h>          // for fcntl()
#include <errno.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h> // for gethostbyname()
#include <sstream>
#include <sys/epoll.h>
#include "common.h"
#include "utility.h"
#include "LogHandler.h"

extern int h_errno;
#define MAXLINE 4096
#define MAXSUB  200
#define CHUNK_SIZE 256

using namespace std;

inline void make_socket_non_blocking(int sfd)
{
	int flags, s;

	flags = fcntl(sfd, F_GETFL, 0);

	if(flags == -1)
	{
		perror("fcntl");
		return;
	}

	flags |= O_NONBLOCK;
	s = fcntl(sfd, F_SETFL, flags);

	if(s == -1)
	{
		perror("fcntl");
		return;
	}
}

CHttpClient::CHttpClient()
{
}

CHttpClient::~CHttpClient()
{
}

int CHttpClient::post(std::string strURL, int nPort, std::string strPage, std::string strParam,
		map<string, string> &mapData)
{
	string strTmp;
	int len;
	int h;
	int nRet = HTTP_ERROR;
	int sockfd;
	struct sockaddr_in servaddr;
	char str[50];
	struct hostent *hptr;
	char **pptr;
	fd_set fdset;
	struct timeval tv;
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	struct epoll_event ev;                     // Used for EPOLL.
	struct epoll_event events[5];         // Used for EPOLL.
	int noEvents;               						// EPOLL event number.

	if((hptr = gethostbyname(strURL.c_str())) == NULL)
	{
		_log("[HTTP Client] gethostbyname error for host: %s: %s", strURL.c_str(), hstrerror( h_errno));
		return nRet;
	}

	printf("http hostname: %s\n", hptr->h_name);
	if(hptr->h_addrtype == AF_INET && (pptr = hptr->h_addr_list) != NULL)
	{
		printf("address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
	}
	else
	{
		fprintf( stderr, "Error call inet_ntop \n");
	}

	if((sockfd = socket( AF_INET, SOCK_STREAM, 0)) < 0)
	{
		_log("[HTTP Client] Create Socket Fail, Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
		return nRet;
	};
	fcntl(sockfd, F_SETFL, O_NONBLOCK);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(nPort);
	if(0 >= inet_pton( AF_INET, str, &servaddr.sin_addr))
	{
		_log("[HTTP Client] Socket inet_pton Fail, Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
		return nRet;
	}

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	tv.tv_sec = 3; /*  second timeout */
	tv.tv_usec = 0;

	if(select(sockfd + 1, NULL, &fdset, NULL, &tv) == 1)
	{
		int so_error;
		socklen_t len = sizeof so_error;

		getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);

		if(so_error != 0)
		{
			_log("[HTTP Client] Socket Connect Fail Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
			return nRet;
		}
	}

	// Create epoll file descriptor.
	int epfd = epoll_create(5);

	// Add socket into the EPOLL set.
	ev.data.fd = sockfd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

	memset(sendline, 0, sizeof(sendline));
	strcat(sendline, "POST ");
	strTmp = strPage + " HTTP/1.1\r\n";
	strcat(sendline, strTmp.c_str());
	strcat(sendline, "Host: ");
	strTmp = strURL + "\r\n";
	strcat(sendline, strTmp.c_str());
	strcat(sendline, "Connection: keep-alive\r\n");
	strcat(sendline, "Content-Length: ");
	strTmp = ConvertToString(strParam.length()) + "\r\n";
	strcat(sendline, strTmp.c_str());
	strcat(sendline, "Cache-Control: no-cache\r\n");
	strcat(sendline, "Origin: chrome-extension://mkhojklkhkdaghjjfdnphfphiaiohkef\r\n");
	strcat(sendline,
			"User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2503.0 Safari/537.36\r\n");
	strcat(sendline, "Content-Type: application/x-www-form-urlencoded\r\n");
	strcat(sendline, "Accept: */*\r\n");
	strcat(sendline, "Accept-Language: zh-TW,zh;q=0.8,en-US;q=0.6,en;q=0.4,zh-CN;q=0.2\r\n");
	strcat(sendline, "\r\n");
	strcat(sendline, strParam.c_str());
	strcat(sendline, "\r\n\r\n");

	printf("%s\n", sendline);

	len = send(sockfd, sendline, strlen(sendline), 0);
	if(len < 0)
	{
		_log("[HTTP Client] Socket Send Fail Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
		return nRet;
	}
	else
	{
		_log("[HTTP Client] Socket Send Success, Size: %d\n\n", len);
		string strRecv;
		for(int i = 0; i < 3; ++i)
		{
			noEvents = epoll_wait(epfd, events, 5, 1000);
			for(int j = 0; j < noEvents; ++j)
			{
				if((events[j].events & EPOLLIN) && sockfd == events[j].data.fd)
				{
					memset(recvline, 0, sizeof(recvline));
					len = recv(sockfd, recvline, sizeof(recvline), MSG_NOSIGNAL);
				}
			}
		}

		bool bNextBody = false;
		if(0 < strlen(recvline))
		{
			string strToken;
			char *token = NULL;
			token = strtok(recvline, "\n");
			while(token)
			{
				printf("Current token: %s\r\n", token);
				strToken = token;
				if(string::npos != strToken.find("HTTP/1.1"))
				{
					mapData["code"] = strToken.substr(9, 3);
					nRet = HTTP_OK;
				}

				if(0 == strToken.compare("\r"))
				{
					bNextBody = true;
				}

				if(bNextBody)
				{
					mapData["body"] = strToken;
				}
				token = strtok( NULL, "\n");
			}
		}
	}
	close(epfd);
	close(sockfd);
	return nRet;
}

int CHttpClient::get(const char *szHost, int nPort, const char *szAPI, const char *szParam, RESULT &rfResult)
{
	string strTmp;
	int nSocket;
	struct epoll_event ev;                // Used for EPOLL.
	struct epoll_event events[5];         // Used for EPOLL.
	int noEvents;               		  // EPOLL event number.
	char sendline[MAX_SOCKET_WRITE], recvline[MAX_SOCKET_READ];
	int len;

	nSocket = httpConnect(szHost, nPort);
	if(0 >= nSocket)
	{
		printf("Socket Connect Fail Socket FD: %d\n", nSocket);
		return -1;
	}

	// Create epoll file descriptor.
	int epfd = epoll_create(5);

	// Add socket into the EPOLL set.
	ev.data.fd = nSocket;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, nSocket, &ev);

	//========================= HTTP GET Header ===========================//
	memset(sendline, 0, sizeof(sendline));
	strcat(sendline, format("GET %s?%s HTTP/1.1\r\n", szAPI, szParam).c_str());
	strcat(sendline, format("Host: %s\r\n", szHost).c_str());
	strcat(sendline, "Cache-Control: no-cache\r\n");

	_log("[CHttpClient] GET: \n%s\n", sendline);

	len = send(nSocket, sendline, strlen(sendline), 0);
	if(len < 0)
	{
		_log("[CHttpClient] Socket Send Fail Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
		return -1;
	}
	else
	{
		_log("[CHttpClient] GET Request Success, Size: %d", len);
		string strRecv;

		for(int i = 0; i < 3; ++i)
		{
			noEvents = epoll_wait(epfd, events, 5, 1000);
			_DBG("http receive noEvents:%d .................", noEvents);
			for(int j = 0; j < noEvents; ++j)
			{
				if((events[j].events & EPOLLIN) && nSocket == events[j].data.fd)
				{
					memset(recvline, 0, sizeof(recvline));
					len = recv(nSocket, recvline, sizeof(recvline), MSG_NOSIGNAL);
					_log("[CHttpClient] GET Response: %s", recvline);
				}
			}
		}

		bool bNextBody = false;
		if(0 < strlen(recvline))
		{
			_log("[CHttpClient] GET Response: %s", recvline);
//			string strToken;
//			char *token = NULL;
//			token = strtok(recvline, "\n");
//			while(token)
//			{
//				printf("Current token: %s\r\n", token);
//				strToken = token;
//				if(string::npos != strToken.find("HTTP/1.1"))
//				{
//					mapData["code"] = strToken.substr(9, 3);
//					nRet = HTTP_OK;
//				}
//
//				if(0 == strToken.compare("\r"))
//				{
//					bNextBody = true;
//				}
//
//				if(bNextBody)
//				{
//					mapData["body"] = strToken;
//				}
//				token = strtok( NULL, "\n");
//			}
		}
	}
	close(epfd);
	close(nSocket);
	return nSocket;
}

int CHttpClient::httpConnect(const char *szHost, int nPort)
{
	int sockfd;
	int nRet = HTTP_ERROR;
	struct hostent *hptr;
	char **pptr;
	char str[50];
	struct sockaddr_in servaddr;
	fd_set fdset;
	struct timeval tv;

	if((hptr = gethostbyname(szHost)) == NULL)
	{
		_log("[HTTP Client] gethostbyname error for host: %s: %s", szHost, hstrerror( h_errno));
		return nRet;
	}
	printf("http hostname: %s\n", hptr->h_name);
	if(hptr->h_addrtype == AF_INET && (pptr = hptr->h_addr_list) != NULL)
	{
		printf("address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
	}
	else
	{
		fprintf( stderr, "Error call inet_ntop \n");
		return -1;
	}

	if((sockfd = socket( AF_INET, SOCK_STREAM, 0)) < 0)
	{
		_log("[HTTP Client] Create Socket Fail, Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
		return nRet;
	};
	fcntl(sockfd, F_SETFL, O_NONBLOCK);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(nPort);
	_log("[CHttpClient] httpConnect Address: %s", str);
	if(0 >= inet_pton( AF_INET, str, &servaddr.sin_addr))
	{
		_log("[HTTP Client] Socket inet_pton Fail, Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
		return nRet;
	}

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
//	if(-1 == connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)))
//	{
//		_log("[HTTP Client] Socket connect Fail, Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
//		return -1;
//	}

	FD_ZERO(&fdset);
	FD_SET(sockfd, &fdset);
	tv.tv_sec = 3; /*  second timeout */
	tv.tv_usec = 0;

	if(select(sockfd + 1, NULL, &fdset, NULL, &tv) == 1)
	{
		int so_error;
		socklen_t len = sizeof so_error;

		getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &so_error, &len);

		if(so_error != 0)
		{
			close(sockfd);
			_log("[HTTP Client] Socket getsockopt Fail Error Code: %d，Error: %s\n", h_errno, hstrerror( h_errno));
			return -1;
		}
	}

	return sockfd;
}
