#include <iostream>
#include <string>
#include <WinSock2.h>
using namespace std;
void ShowErrorMessage(string message)
{
	cout << message << '\n';
	system("pause");
	exit(1);
}
int main()
{
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;
	int port = 8484;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ShowErrorMessage("스타트업 에러");
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("소켓설정에러");
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) != 0)
		ShowErrorMessage("바인드에러");
	cout << "[Bind OK]" << '\n';
	if (listen(serverSocket, 2) != 0)
		ShowErrorMessage("리슨에러");
	cout << "[Listen OK]" << '\n';
	cout << "[Accept OK]" << '\n';	
	int sizeclientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeclientAddress);
	char received[256];
	while (1)
	{
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "[클라이언트] : " << received << '\n';
		cout << "[메세지 전송] : " << received << '\n';
		if (strcmp(received, "exit") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "종료합니다." << '\n';
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
	}
	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}