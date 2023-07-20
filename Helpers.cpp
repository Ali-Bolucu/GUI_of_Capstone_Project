#include "MyForm.h"

#include <stdio.h>
#include <iostream>


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;


void InterfaceCapstone::MyForm::IsConnected(bool status)
{
    String^ result;

    if (status)
    {
        textBox_Connection_Status->Text = "Connected to Server";
        textBox_Connection_Status->BackColor = Color::Green;
    }
    else
    {
        textBox_Connection_Status->Text = "Error";
        textBox_Connection_Status->BackColor = Color::Red;
    }

}

void InterfaceCapstone::MyForm::IsDisconnected(bool status)
{
    String^ result;

    if (status)
    {
        textBox_Connection_Status->Text = "Disconnected from Server";
        textBox_Connection_Status->BackColor = Color::LightGreen;
    }
    else
    {
        textBox_Connection_Status->Text = "Error";
        textBox_Connection_Status->BackColor = Color::Red;
    }

}

void InterfaceCapstone::MyForm::IsSubscribed(bool status)
{
    String^ result;

    if (status)
    {
        Textbox_Subscribe_Status->Text = "Successful";
        Textbox_Subscribe_Status->BackColor = Color::MediumSeaGreen;
    }
    else
    {
        Textbox_Subscribe_Status->Text = "Failure";
        Textbox_Subscribe_Status->BackColor = Color::Red;
    }

}


void InterfaceCapstone::MyForm::IncomingData(String^ FolderName, int TCP_TotalPacketNumber, int TCP_PacketNumber)
{
    if (FolderName == "imagesCV")
    {
        textBox_Incoming_Image->Text = "Incoming :  " + TCP_TotalPacketNumber + "/" + TCP_PacketNumber;
        textBox_Incoming_Image->BackColor = Color::Red;

    }
    else if (FolderName == "imagesMap")
    {
        textBox_Incoming_Map->Text = "Incoming:  " + TCP_TotalPacketNumber + "/" + TCP_PacketNumber;;
        textBox_Incoming_Map->BackColor = Color::Red;

    }
}


void InterfaceCapstone::MyForm::ResetIncomingTextBox()
{

    textBox_Incoming_Image->ResetText();
    textBox_Incoming_Image->BackColor = Color::Green;

    textBox_Incoming_Map->ResetText();
    textBox_Incoming_Map->BackColor = Color::Green;

}


void InterfaceCapstone::MyForm::ResetImagesList()
{

    comboBox_Pictures->Items->Clear();
    comboBox_Pictures->ResetText();

}

std::string InterfaceCapstone::MyForm::getTimeStamp()
{

    // Generate TimeStamp
    std::time_t currentTime = std::time(nullptr);  // Get current time
    std::tm* localTime = std::localtime(&currentTime);  // Convert to local time
    char newName[30];
    std::strftime(newName, sizeof(newName), "%Y%m%d_%H.%M.%S_", localTime);  // Format the time as desired

    return std::string(newName);

}