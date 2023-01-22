#include <stdio.h>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	char cSendBuffer[100];
	char cRecvBuffer[100];
	int nSendLength = 0;
	int nRecvLength = 0;
	int nLength = 0;

	SOCKET sServer;
	SOCKET sAccept;
	SOCKADDR_IN siServerAddr;
	SOCKADDR_IN siAcceptAddr;
	WORD wRet = MAKEWORD(2, 2);
	WSADATA wsaData;

	int nErrorCode;
	nErrorCode = WSAStartup(wRet, &wsaData);
	if (nErrorCode != 0)
	{
		printf("Init nErrorCode Failed!\n");
	}
	else
	{
		printf("Init nErrorCode Success!\n");
	}

	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wHighVersion) != 2)
	{
		printf("Version Error!\n");
		WSACleanup(); // 关闭socket，释放addr
	}
	else
	{
		printf("Version Success!\n");
	}

	siServerAddr.sin_family = AF_INET;
	siServerAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); // 绑定本地IP
	siServerAddr.sin_port = htons(1234); // 绑定端口
	sServer = socket(AF_INET, SOCK_STREAM, 0); // 创建socket

	if (bind(sServer, (SOCKADDR*)&siServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("Bind Error!\n");
		WSACleanup();
	}
	else
	{
		printf("Bind Success!\n");
	}

	if (listen(sServer, SOMAXCONN) < 0) // 设定监听状态
	{
		printf("Listen Error!\n");
	}
	else
	{
		printf("Listen Success!\n");
	}

	nLength = sizeof(SOCKADDR);
	sAccept = accept(sServer, (SOCKADDR*)&siAcceptAddr, &nLength);
	if (sAccept == SOCKET_ERROR)
	{
		printf("Accept Error!\n");
		WSACleanup();
		return 0;
	}
	else
	{
		printf("Accept Success!\n");
	}

	while (true)
	{
		nRecvLength = recv(sAccept, cRecvBuffer, 100, 0);
		if (nRecvLength < 0)
		{
			printf("Recv Error!\n");
			break;
		}
		else
		{
			printf("%s\n", cRecvBuffer);
		}
		printf("Send to Client Data: ");
		scanf("%s\n", cSendBuffer);
		nSendLength = send(sAccept, cSendBuffer, 100, 0);
		if (nSendLength < 0)
		{
			printf("Send Error!\n");
			break;
		}
	}
	closesocket(sServer);
	closesocket(sAccept);
	WSACleanup();
	return 0;
}