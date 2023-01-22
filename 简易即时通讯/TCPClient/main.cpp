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
	SOCKADDR_IN siServerAddr;
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
		WSACleanup(); // πÿ±’socket£¨ Õ∑≈addr
	}
	else
	{
		printf("Version Success!\n");
	}

	siServerAddr.sin_family = AF_INET;
	siServerAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	siServerAddr.sin_port = htons(1234);

	sServer = socket(AF_INET, SOCK_STREAM, 0);

	if (connect(sServer, (SOCKADDR*)&siServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		printf("Connect Error!\n");
		WSACleanup();
	}
	else
	{
		printf("Connect Success!\n");
	}

	while (true)
	{
		printf("Send to Server Data: ");
		scanf("%s", cSendBuffer);
		nSendLength = send(sServer, cSendBuffer, 100, 0);
		if (nSendLength < 0)
		{
			printf("Send Error!\n");
			break;
		}
		else
		{
			printf("Send Success!\n");
		}

		nRecvLength = recv(sServer, cRecvBuffer, 100, 0);
		if (nRecvLength < 0)
		{
			printf("Recv Error!\n");
			break;
		}
		else
		{
			printf("%s\n", cRecvBuffer);
		}
	}
	closesocket(sServer);
	WSACleanup();
	return 0;
}