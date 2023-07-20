#pragma once

#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <iostream>

namespace InterfaceCapstone {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			Control::CheckForIllegalCrossThreadCalls = false;
			ThreadSubscribe = gcnew Thread ( gcnew ThreadStart (this, &InterfaceCapstone::MyForm::TCP_Subscribe));

			SOCKET client_socket = NULL;
			
		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Thread^ ThreadSubscribe;
		SOCKET client_socket;


	private: System::Windows::Forms::Button^ button_Connect;
	private: System::Windows::Forms::TextBox^ textBox_Connection_Status;


	private: System::Windows::Forms::ComboBox^ comboBox_Pictures;
	private: System::Windows::Forms::Button^ button_Set_Subscribe;







	private: System::Windows::Forms::Button^ button_Disconnect;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox_TCP_Port;

	private: System::Windows::Forms::TextBox^ textBox_TCP_IP_Addr;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox_Map;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::PictureBox^ pictureBox_Cam;
	private: System::Windows::Forms::TextBox^ Textbox_Subscribe_Status;
	private: System::Windows::Forms::TextBox^ textBox_Incoming_Map;

	private: System::Windows::Forms::TextBox^ textBox_Incoming_Image;
	private: System::Windows::Forms::Button^ button_Set_Unsubscribe;










	private:

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_Connect = (gcnew System::Windows::Forms::Button());
			this->textBox_Connection_Status = (gcnew System::Windows::Forms::TextBox());
			this->comboBox_Pictures = (gcnew System::Windows::Forms::ComboBox());
			this->button_Set_Subscribe = (gcnew System::Windows::Forms::Button());
			this->button_Disconnect = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox_TCP_Port = (gcnew System::Windows::Forms::TextBox());
			this->textBox_TCP_IP_Addr = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_Incoming_Map = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox_Map = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_Incoming_Image = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox_Cam = (gcnew System::Windows::Forms::PictureBox());
			this->Textbox_Subscribe_Status = (gcnew System::Windows::Forms::TextBox());
			this->button_Set_Unsubscribe = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Map))->BeginInit();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Cam))->BeginInit();
			this->SuspendLayout();
			// 
			// button_Connect
			// 
			this->button_Connect->Location = System::Drawing::Point(214, 14);
			this->button_Connect->Name = L"button_Connect";
			this->button_Connect->Size = System::Drawing::Size(80, 25);
			this->button_Connect->TabIndex = 0;
			this->button_Connect->Text = L"Connect";
			this->button_Connect->UseVisualStyleBackColor = true;
			this->button_Connect->Click += gcnew System::EventHandler(this, &MyForm::button_Connect_click);
			// 
			// textBox_Connection_Status
			// 
			this->textBox_Connection_Status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBox_Connection_Status->Location = System::Drawing::Point(230, 49);
			this->textBox_Connection_Status->Name = L"textBox_Connection_Status";
			this->textBox_Connection_Status->Size = System::Drawing::Size(161, 22);
			this->textBox_Connection_Status->TabIndex = 1;
			// 
			// comboBox_Pictures
			// 
			this->comboBox_Pictures->FormattingEnabled = true;
			this->comboBox_Pictures->Location = System::Drawing::Point(141, 19);
			this->comboBox_Pictures->Name = L"comboBox_Pictures";
			this->comboBox_Pictures->Size = System::Drawing::Size(224, 21);
			this->comboBox_Pictures->TabIndex = 3;
			this->comboBox_Pictures->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox_Pictures_SelectedIndexChanged);
			// 
			// button_Set_Subscribe
			// 
			this->button_Set_Subscribe->Location = System::Drawing::Point(648, 14);
			this->button_Set_Subscribe->Name = L"button_Set_Subscribe";
			this->button_Set_Subscribe->Size = System::Drawing::Size(100, 25);
			this->button_Set_Subscribe->TabIndex = 7;
			this->button_Set_Subscribe->Text = L"Subscribe";
			this->button_Set_Subscribe->UseVisualStyleBackColor = true;
			this->button_Set_Subscribe->Click += gcnew System::EventHandler(this, &MyForm::button_Set_Subscribe_click);
			// 
			// button_Disconnect
			// 
			this->button_Disconnect->Location = System::Drawing::Point(324, 14);
			this->button_Disconnect->Name = L"button_Disconnect";
			this->button_Disconnect->Size = System::Drawing::Size(80, 25);
			this->button_Disconnect->TabIndex = 8;
			this->button_Disconnect->Text = L"Disconnect";
			this->button_Disconnect->UseVisualStyleBackColor = true;
			this->button_Disconnect->Click += gcnew System::EventHandler(this, &MyForm::button_Disconnect_click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(17, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 13);
			this->label1->TabIndex = 10;
			this->label1->Text = L"IP Adress :";
			// 
			// textBox_TCP_Port
			// 
			this->textBox_TCP_Port->Location = System::Drawing::Point(81, 49);
			this->textBox_TCP_Port->Name = L"textBox_TCP_Port";
			this->textBox_TCP_Port->Size = System::Drawing::Size(100, 20);
			this->textBox_TCP_Port->TabIndex = 11;
			this->textBox_TCP_Port->Text = L"8079";
			// 
			// textBox_TCP_IP_Addr
			// 
			this->textBox_TCP_IP_Addr->Location = System::Drawing::Point(81, 23);
			this->textBox_TCP_IP_Addr->Name = L"textBox_TCP_IP_Addr";
			this->textBox_TCP_IP_Addr->Size = System::Drawing::Size(100, 20);
			this->textBox_TCP_IP_Addr->TabIndex = 12;
			this->textBox_TCP_IP_Addr->Text = L"20.203.172.10\r\n";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(17, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(32, 13);
			this->label2->TabIndex = 13;
			this->label2->Text = L"Port :";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox_Incoming_Map);
			this->groupBox1->Controls->Add(this->pictureBox_Map);
			this->groupBox1->Location = System::Drawing::Point(867, 119);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(636, 567);
			this->groupBox1->TabIndex = 14;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Map";
			// 
			// textBox_Incoming_Map
			// 
			this->textBox_Incoming_Map->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBox_Incoming_Map->ForeColor = System::Drawing::SystemColors::Info;
			this->textBox_Incoming_Map->Location = System::Drawing::Point(480, 19);
			this->textBox_Incoming_Map->Name = L"textBox_Incoming_Map";
			this->textBox_Incoming_Map->Size = System::Drawing::Size(150, 24);
			this->textBox_Incoming_Map->TabIndex = 17;
			// 
			// pictureBox_Map
			// 
			this->pictureBox_Map->Location = System::Drawing::Point(82, 89);
			this->pictureBox_Map->Name = L"pictureBox_Map";
			this->pictureBox_Map->Size = System::Drawing::Size(488, 457);
			this->pictureBox_Map->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_Map->TabIndex = 7;
			this->pictureBox_Map->TabStop = false;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox_Incoming_Image);
			this->groupBox2->Controls->Add(this->pictureBox_Cam);
			this->groupBox2->Controls->Add(this->comboBox_Pictures);
			this->groupBox2->Location = System::Drawing::Point(39, 119);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(620, 567);
			this->groupBox2->TabIndex = 15;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Images";
			// 
			// textBox_Incoming_Image
			// 
			this->textBox_Incoming_Image->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->textBox_Incoming_Image->ForeColor = System::Drawing::SystemColors::Info;
			this->textBox_Incoming_Image->Location = System::Drawing::Point(464, 19);
			this->textBox_Incoming_Image->Name = L"textBox_Incoming_Image";
			this->textBox_Incoming_Image->Size = System::Drawing::Size(150, 24);
			this->textBox_Incoming_Image->TabIndex = 17;
			// 
			// pictureBox_Cam
			// 
			this->pictureBox_Cam->Location = System::Drawing::Point(78, 89);
			this->pictureBox_Cam->Name = L"pictureBox_Cam";
			this->pictureBox_Cam->Size = System::Drawing::Size(452, 457);
			this->pictureBox_Cam->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox_Cam->TabIndex = 6;
			this->pictureBox_Cam->TabStop = false;
			// 
			// Textbox_Subscribe_Status
			// 
			this->Textbox_Subscribe_Status->BackColor = System::Drawing::SystemColors::Window;
			this->Textbox_Subscribe_Status->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->Textbox_Subscribe_Status->ForeColor = System::Drawing::SystemColors::WindowText;
			this->Textbox_Subscribe_Status->Location = System::Drawing::Point(676, 45);
			this->Textbox_Subscribe_Status->Name = L"Textbox_Subscribe_Status";
			this->Textbox_Subscribe_Status->Size = System::Drawing::Size(161, 22);
			this->Textbox_Subscribe_Status->TabIndex = 16;
			// 
			// button_Set_Unsubscribe
			// 
			this->button_Set_Unsubscribe->Location = System::Drawing::Point(783, 12);
			this->button_Set_Unsubscribe->Name = L"button_Set_Unsubscribe";
			this->button_Set_Unsubscribe->Size = System::Drawing::Size(100, 25);
			this->button_Set_Unsubscribe->TabIndex = 17;
			this->button_Set_Unsubscribe->Text = L"Stop Subscription";
			this->button_Set_Unsubscribe->UseVisualStyleBackColor = true;
			this->button_Set_Unsubscribe->Click += gcnew System::EventHandler(this, &MyForm::button_Set_Unsubscribe_click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1541, 725);
			this->Controls->Add(this->button_Set_Unsubscribe);
			this->Controls->Add(this->Textbox_Subscribe_Status);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->button_Set_Subscribe);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox_TCP_IP_Addr);
			this->Controls->Add(this->textBox_TCP_Port);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button_Disconnect);
			this->Controls->Add(this->textBox_Connection_Status);
			this->Controls->Add(this->button_Connect);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Map))->EndInit();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox_Cam))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		
#pragma endregion
	private: 




		//////////////////// MYFORM START ////////////////////
		void button_Connect_click(System::Object^ sender, System::EventArgs^ e);
		void button_Disconnect_click(System::Object^ sender, System::EventArgs^ e);

		void comboBox_Pictures_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);


		void button_Set_Subscribe_click(System::Object^ sender, System::EventArgs^ e);
		void button_Set_Unsubscribe_click(System::Object^ sender, System::EventArgs^ e);



		//////////////////// MYFORM END ////////////////////



		//////////////////// TCP START ////////////////////
		SOCKADDR_IN TCP_CreateSocket();

		bool TCP_Connect();
		bool TCP_Disconnect();

		void TCP_Subscribe();



		//////////////////// TCP END ////////////////////




		//////////////////// HELPERS START ////////////////////
		void IsConnected(bool status);
		void IsDisconnected(bool status);
		void IsSubscribed(bool status);

		void IncomingData(String^ FolderName, int TCP_TotalPacketNumber, int TCP_PacketNumber);

		void ResetIncomingTextBox();
		void ResetImagesList();
	
		std::string getTimeStamp();

		//////////////////// HELPERS END ////////////////////

};
}
