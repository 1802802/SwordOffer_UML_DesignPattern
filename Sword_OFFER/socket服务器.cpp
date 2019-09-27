#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll

/*

�� server.cpp �� client.cpp �ֱ����Ϊ server.exe �� client.exe�������� server.exe�������� client.exe��������Ϊ��
Message form server: Hello World!

Windows �µ� socket ����� Linux ˼·��ͬ����ϸ���������
1) Windows �µ� socket �������� Winsock.dll �� ws2_32.dll��������ǰ���ء�DLL �����ּ��ط�ʽ����鿴����̬���ӿ�DLL�ļ���
2) Linux ʹ�á��ļ����������ĸ���� Windows ʹ�á��ļ�������ĸ��Linux ������ socket �ļ�����ͨ�ļ���
�� Windows ���֣�Linux �� socket() �����ķ���ֵΪ int ���ͣ��� Windows ��Ϊ SOCKET ���ͣ�Ҳ���Ǿ����
3) Linux ��ʹ�� read() / write() ������д���� Windows ��ʹ�� recv() / send() �������ͺͽ��ա�
4) �ر� socket ʱ��Linux ʹ�� close() �������� Windows ʹ�� closesocket() ������

*/

#define BUF_SIZE 100

int main_ser() 
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//�����׽���
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, 0);

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	//�������״̬
	listen(servSock, 20);

	//���տͻ�������ѭ�����ܲ�����
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	char buffer[BUF_SIZE] = { 0 };  //�������������д�����Խ�һ���Լ�����Ļ�����������ʵ����sokcet�ڲ������Լ��Ľ����뷢�ͻ�������
	while (1) 
	{
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);  //���տͻ��˷���������
		send(clntSock, buffer, strLen, 0);  //������ԭ������

		closesocket(clntSock);  //�ر��׽���
		memset(buffer, 0, BUF_SIZE);  //���û�����
	}

	//�ر��׽���
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();

	return 0;
}