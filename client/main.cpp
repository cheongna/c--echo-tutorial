#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>
using namespace std;
void Error(string message) {
	cout << message << '\n';
	system("pause");
	exit(1);
}
int main()
{
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAddress;
	int port = 8484;
	char received[256];
	string sent;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		Error("��ŸƮ������");
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == SOCKET_ERROR)
		Error("���Ͽ���");
	memset(&serverAddress, 0, sizeof(serverAddress));	
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);
	serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (connect(clientSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) != 0)
		Error("Ŀ��Ʈ����");
	while (1)
	{
		cout << "[�޼��� ����] : ";
		getline(cin, sent);
		if (sent == "")continue;
		send(clientSocket, sent.c_str(),sent.length(), 0);
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		if (strcmp(received, "exit") == 0) {
			cout << "�����մϴ�.\n";
			break;
		}
		cout << "[���� �޼���] : " << received << '\n';
	}
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}