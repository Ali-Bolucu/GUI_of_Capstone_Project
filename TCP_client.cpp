#include "MyForm.h"

#include<stdio.h>
#include<winsock2.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <algorithm>
#include <vcclr.h>

#include <ctime>
#include <cstdio>

#include <msclr/marshal.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment (lib, "Ws2_32.lib")

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Runtime::InteropServices;
using namespace std;


SOCKADDR_IN InterfaceCapstone::MyForm::TCP_CreateSocket()
{
	WSAData wsaData;
	SOCKADDR_IN server_addr;
	
	int addrLen = sizeof(server_addr);

	msclr::interop::marshal_context^ context = gcnew msclr::interop::marshal_context();
	//const char* server_ip = "127.0.0.1";
	const char* server_ip = "20.203.172.10"; // context->marshal_as<const char*>(textBox_TCP_IP_Addr->Text);
	const int server_port = Convert::ToInt32(textBox_TCP_Port->Text);


	// Create socket file descriptor
	WORD DllVersion = MAKEWORD(2, 2);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBox::Show("Winsock Connection Failed!");
		exit(1);
	}


	client_socket = socket(AF_INET, SOCK_STREAM, NULL);
	if (client_socket == INVALID_SOCKET) {
		std::cerr << "socket creation failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		exit(2);
	}


	server_addr.sin_addr.s_addr = inet_addr(server_ip);
	server_addr.sin_port = htons(server_port);
	server_addr.sin_family = AF_INET;

	return server_addr;
}






bool InterfaceCapstone::MyForm::TCP_Connect()
{
	SOCKADDR_IN server_addr;

	server_addr = TCP_CreateSocket();

	if (connect(client_socket, (SOCKADDR*)&server_addr, sizeof(server_addr))) {
		std::cerr << "connect failed: " << WSAGetLastError() << std::endl;
		closesocket(client_socket);
		WSACleanup();
		exit(3);

	}

	return true;
}

bool InterfaceCapstone::MyForm::TCP_Disconnect()
{
	if (closesocket(client_socket) == 0)
	{ 
		return true;
	}
	else if (closesocket(client_socket) == SOCKET_ERROR)
	{
		return false;
	}
}


void InterfaceCapstone::MyForm::TCP_Subscribe()
{
	const char* message = "Subs";
	bool status ;

	if (send(client_socket, message, sizeof(message), 0) > 0)
	{
		status = true;
	}
	else
	{
		status = false;
	}

	IsSubscribed(status);

	while (true)
	{

		// Receive the Folder Name in bytes
		char recv_FolderName[15];
		int recv_FolderName_recvByte;
		if ((recv_FolderName_recvByte = recv(client_socket, recv_FolderName, sizeof(recv_FolderName), 0)) < 0)
		{
			MessageBox::Show("Error : Folder Name couldn't received ");
		}
		string FolderName(recv_FolderName); // convert char array to string object
		FolderName.erase(remove(FolderName.begin(), FolderName.end(), '#'), FolderName.end()); // remove # from string

		// Receive the Image Name in bytes
		char recv_ImageName[31];
		int recv_ImageName_recvByte;
		if ((recv_ImageName_recvByte = recv(client_socket, recv_ImageName, sizeof(recv_ImageName), 0)) < 0)
		{
			MessageBox::Show("Error : Image Name couldn't received ");
		}
		string ImageName(recv_ImageName); // convert char array to string object
		ImageName.erase(remove(ImageName.begin(), ImageName.end(), '#'), ImageName.end()); // remove # from string


		// Receive the image size in bytes
		char recv_ImageSize[15];
		int recv_ImageSize_recvByte;
		if ((recv_ImageSize_recvByte = recv(client_socket, recv_ImageSize, sizeof(recv_ImageSize), 0)) < 0)
		{
			MessageBox::Show("Error : Image Size couldn't received ");
		}
		string ImageSize(recv_ImageSize); // convert char array to string object
		ImageSize.erase(remove(ImageSize.begin(), ImageSize.end(), '#'), ImageSize.end()); // remove # from string
		int imageSize = stoi(ImageSize); // char to int conversion
		// --


		// Variables
		int totalPacketSize = 9 + 10240 + 9;
		int TCP_PacketNumber = 0;
		int packetSize = 20480;
		int localChecksum = 0;
		int TCP_Checksum = 0;

		int TCP_BytesReceived = 0;
		int TCP_TotalBytesReceived = 0;
		int TCP_TotalPacketNumber = imageSize / packetSize + ((imageSize % packetSize > 0) ? 1 : 0);

		char buffer_PacketNumber[6];
		char buffer_ImageData[20480];
		char buffer_Checksum[5];
		// --
		int useless;

		memset((void*)&buffer_PacketNumber[0], 0, sizeof(buffer_PacketNumber));
		memset((void*)&buffer_ImageData[0], 0, sizeof(buffer_ImageData));
		memset((void*)&buffer_Checksum[0], 0, sizeof(buffer_Checksum));

		std::string TimeStamp = getTimeStamp();
		String^ Str_TimeStamp = gcnew String(TimeStamp.data());

		// file crate at the path
		FILE* IMAGE;

		string filePath = FolderName + "//" + TimeStamp + ImageName;
		String^ Str_ImageName = Str_TimeStamp + gcnew String(ImageName.data());
		String^ Str_FolderName = gcnew String(FolderName.data());

		IncomingData(Str_FolderName, TCP_TotalPacketNumber, TCP_PacketNumber);


		fopen_s(&IMAGE, filePath.c_str(), "wb");
		if (IMAGE == nullptr)
		{
			break;
			exit(11);
		}
		// --

		while (true)
		{
			IncomingData(Str_FolderName, TCP_TotalPacketNumber, TCP_PacketNumber);

			localChecksum = 0;
			TCP_TotalBytesReceived = 0;

			if (TCP_TotalPacketNumber == TCP_PacketNumber)
			{
				break;
			}

			if ((useless = recv(client_socket, buffer_PacketNumber, sizeof(buffer_PacketNumber), 0)) < 0)
			{
				MessageBox::Show("Error : Image Packet Number ");
			}

			while (packetSize > TCP_TotalBytesReceived)
			{
				if ((TCP_BytesReceived = recv(client_socket, &buffer_ImageData[TCP_TotalBytesReceived], sizeof(buffer_ImageData) - TCP_TotalBytesReceived, 0)) < 0)
				{
					MessageBox::Show("Error : Image Data ");
				}
				TCP_TotalBytesReceived += TCP_BytesReceived;
			}


			if ((useless = recv(client_socket, buffer_Checksum, sizeof(buffer_Checksum), 0)) < 0)
			{
				MessageBox::Show("Error : Image Checksum ");
			}




			TCP_PacketNumber = atoi(buffer_PacketNumber);
			TCP_Checksum = atoi(buffer_Checksum);


			for (int i = 0; i < packetSize; i++)
			{
				uint8_t eachByteValue = buffer_ImageData[i];
				localChecksum += eachByteValue;
			}
			localChecksum = localChecksum % 256;

			if (TCP_Checksum == localChecksum)
			{
				send(client_socket, "ACK", sizeof("ACK"), 0);
			}
			else
			{
				send(client_socket, "NCK", sizeof("NCK"), 0);
			}



			fwrite(buffer_ImageData, sizeof(char), sizeof(buffer_ImageData), IMAGE);
		}

		fclose(IMAGE);
		



		//MessageBox::Show(Str_FolderName);

		if (FolderName == "imagesMap")
		{ 
			String^ picturepath1 = "imagesMap\\" + Str_ImageName;
			pictureBox_Map->Image = Image::FromFile(picturepath1);

			//MessageBox::Show("[Map]" + picturepath1);
		}
		else if (FolderName == "imagesCV")
		{
			if(comboBox_Pictures->FindString(Str_ImageName) != 0 )
			{
				comboBox_Pictures->Items->Add(Str_ImageName);
				comboBox_Pictures->Text = Str_ImageName;
			}

			String^ picturepath2 = "imagesCV\\" + Str_ImageName;
			pictureBox_Cam->Image = Image::FromFile(picturepath2);

			//MessageBox::Show("[Cam]" + picturepath2);
		}

		ResetIncomingTextBox();


	}
}
