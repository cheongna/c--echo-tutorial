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
		ShowErrorMessage("��ŸƮ�� ����");
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
		ShowErrorMessage("���ϼ�������");
	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) != 0)
		ShowErrorMessage("���ε忡��");
	cout << "[Bind OK]" << '\n';
	if (listen(serverSocket, 2) != 0)
		ShowErrorMessage("��������");
	cout << "[Listen OK]" << '\n';
	cout << "[Accept OK]" << '\n';	
	int sizeclientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeclientAddress);
	char received[256];
	while (1)
	{
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "[Ŭ���̾�Ʈ] : " << received << '\n';
		cout << "[�޼��� ����] : " << received << '\n';
		if (strcmp(received, "exit") == 0) {
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "�����մϴ�." << '\n';
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