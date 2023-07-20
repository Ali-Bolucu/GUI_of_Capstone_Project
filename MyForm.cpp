#include "MyForm.h"

#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <thread>



#include <msclr/marshal.h>



using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

[STAThread]
void main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    InterfaceCapstone::MyForm form;
    Application::Run(% form);
}
 

void InterfaceCapstone::MyForm::button_Connect_click(System::Object^ sender, System::EventArgs^ e)
{   
    bool status = TCP_Connect();
    IsConnected(status);

    ResetImagesList();
}

void InterfaceCapstone::MyForm::button_Disconnect_click(System::Object^ sender, System::EventArgs^ e)
{
    bool status = TCP_Disconnect();
    IsDisconnected(status);

    ResetImagesList();
}

void InterfaceCapstone::MyForm::comboBox_Pictures_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
    String^ ImageName = comboBox_Pictures->SelectedItem->ToString();
    String^ ImagePath = "imagesCV\\" + ImageName;

    delete pictureBox_Cam->Image;
    pictureBox_Cam->Image = Image::FromFile(ImagePath);

}





void InterfaceCapstone::MyForm::button_Set_Subscribe_click(System::Object^ sender, System::EventArgs^ e)
{
    ThreadSubscribe = gcnew Thread(gcnew ThreadStart(this, &InterfaceCapstone::MyForm::TCP_Subscribe));
    ThreadSubscribe->Start();

    button_Connect->Enabled = false;
    button_Disconnect->Enabled = false;
}

void InterfaceCapstone::MyForm::button_Set_Unsubscribe_click(System::Object^ sender, System::EventArgs^ e)
{
    bool status = TCP_Disconnect();
    IsDisconnected(status);

    ThreadSubscribe->Abort();
    ThreadSubscribe->Join();

    button_Connect->Enabled = true;
    button_Disconnect->Enabled = true;

}

