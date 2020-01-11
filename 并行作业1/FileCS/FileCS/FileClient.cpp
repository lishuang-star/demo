#include <WinSock2.h>
#include <iostream>
#include <fstream>
#include "CBlockingSocket.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		cout << "Format Error!" << endl;
		return 0;
	}
	CBlockingSocket BlockingSocket = CBlockingSocket();
	if (BlockingSocket.Connect(argv[1], argv[2]))
	{
		cout << "Connection established to remote Server at " << argv[1] << ":" << argv[2] << endl;
		cout << "Input save path: ";
		BYTE filename[100];
		cin >> filename;
		if (BlockingSocket.Send(filename, 100))
		{
			cout << "  Requesting file on the server: " << filename << endl;

			cout << "  1.save the file to disk" << endl;
			cout << "  2.print out on the console" << endl;
			cout << "  Input your choise:";
			int choose;
			cin >> choose;
			cout << "  =========================================" << endl;
			if (choose == 1)
			{
				char filename2[100] = { 0 };
				cout << "  Input save path:";
				cin >> filename2;

				cout << "  Receiving file " << filename << endl;
				fstream fs;
				char recvBuf[101] = { 0 };
				fs.open(filename2, ios::out | ios::binary);
				int filerecvd = 0;
				while (filerecvd != -1)
				{
					filerecvd = BlockingSocket.Recv(recvBuf, sizeof(recvBuf));
					cout << "  Received " << filerecvd << " bytes." << endl;
					fs.write(recvBuf, filerecvd);
				}
			}
			else if (choose == 2) {

				int recvLen = 0;
				BYTE recvBuf[101] = { 0 };
				int len = 0;
				while ((len = BlockingSocket.Read(recvBuf, 100)) != -1 && len != 0)
				{
					recvLen += len;
					cout << recvBuf;
				}
				cout << endl << "  =========================================" << endl;
				cout << "  Received " << recvLen << " bytes" << endl;
			}
		}
	}
	return 0;
}