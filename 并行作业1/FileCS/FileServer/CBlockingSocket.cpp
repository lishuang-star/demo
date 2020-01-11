#include "CBlockingSocket.h"

CBlockingSocket::CBlockingSocket()
{
	WORD wVersionRequestd = MAKEWORD(2, 2);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequestd, &wsaData);
	if (err != 0)
	{
		cout << "WSAStartup failed!" << endl;
		this->m_socket = NULL;
		return;
	}

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socket == INVALID_SOCKET)
	{
		cout << "create socket failed!" << endl;
		this->m_socket = NULL;
		return;
	}
}

CBlockingSocket::~CBlockingSocket()
{
	if (m_socket != NULL)
	{
		Close();
	}
	if (WSACleanup() == SOCKET_ERROR)
	{
		cout << "WSACleanup failed!" << endl;
	}
}

BOOL CBlockingSocket::Open(const char *ip, const char *port)
{


	return TRUE;
}

BOOL CBlockingSocket::Close()
{
	if (closesocket(m_socket) == 0)
	{
		cout << "Connection is down" << endl;
		return TRUE;
	}
	else
	{
		cout << "Connection close failed!" << endl;
		return FALSE;
	}
}

BOOL CBlockingSocket::CloseConn() 
{
	if (closesocket(socketConn) == 0)
	{
		cout << "Connection closed by the client" << endl;
		return TRUE;
	}
	else
	{
		cout << "Accept Connection close failed!" << endl;
		return FALSE;
	}
}

BOOL CBlockingSocket::Listen(const char *port)
{
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(atoi(port));
	if (bind(m_socket, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR)) == 0)
	{
		if (listen(m_socket,5) == 0)
		{
			cout << "FileServer is listening on port:" << port << endl;
			return TRUE;
		}
		else
		{
			cout << "Listen failed!" << endl;
			return FALSE;
		}
	}
	else
	{
		cout << "Open socket failed!" << endl;
		return FALSE;
	}
}

BOOL CBlockingSocket::Accept()
{
	SOCKADDR_IN addrClient;
	int len = sizeof(addrClient);
	socketConn = accept(m_socket, (SOCKADDR *)&addrClient, &len);
	if (socketConn == -1)
	{
		cout << "Accpet failed!" << endl;
		return FALSE;
	}
	else
	{
		cout << "Accepted connection from " << inet_ntoa(addrClient.sin_addr) << endl;
		return TRUE;
	}
}

BOOL CBlockingSocket::Send(BYTE *s, UINT count)
{
	int sendLen = send(socketConn, (char *)s, count, 0);
	if (sendLen > 0)
	{
		return TRUE;
	}
	else
	{
		cout << "Send Failed!" << endl;
		return FALSE;
	}
}

INT CBlockingSocket::Read(BYTE *s, UINT count)
{
	int recvLen = recv(socketConn, (char *)s, count,0);
	if (recvLen == SOCKET_ERROR || recvLen == 0)
	{
		cout << "Receive failed!" << endl;
		return -1;
	}
	return recvLen;
}
