#pragma once
#include <myo/myo.hpp>
#include "myo.h"

namespace Elechanics {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::IO;

	/// <summary>
	/// Summary for TCPclient
	/// </summary>
	public ref class TCPclient : public System::Windows::Forms::Form
	{
	
	
	private: System::Windows::Forms::Button^  button3;
	private: TcpClient^ client;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::Button^  Up;
	private: System::Windows::Forms::Button^  Stop;
	private: System::Windows::Forms::Button^  Right;
	private: System::Windows::Forms::Button^  Down;
	private: System::Windows::Forms::Button^  Left;


	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::Button^  Myo;
	private: NetworkStream^ stream;

	public:
		TCPclient(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~TCPclient()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->Up = (gcnew System::Windows::Forms::Button());
			this->Stop = (gcnew System::Windows::Forms::Button());
			this->Right = (gcnew System::Windows::Forms::Button());
			this->Down = (gcnew System::Windows::Forms::Button());
			this->Left = (gcnew System::Windows::Forms::Button());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->Myo = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(300, 92);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(66, 20);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Send";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &TCPclient::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(10, 92);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(284, 20);
			this->textBox1->TabIndex = 1;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(96, 12);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(108, 20);
			this->textBox2->TabIndex = 2;
			this->textBox2->Text = L"192.168.4.1";
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(96, 38);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(108, 20);
			this->textBox3->TabIndex = 3;
			this->textBox3->Text = L"80";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(10, 64);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(108, 22);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Connect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &TCPclient::button2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(61, 15);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(20, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"IP:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(61, 41);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(29, 13);
			this->label2->TabIndex = 6;
			this->label2->Text = L"Port:";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(141, 64);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(104, 22);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Disconnect";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &TCPclient::button3_Click);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(10, 118);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(284, 97);
			this->textBox4->TabIndex = 8;
			// 
			// Up
			// 
			this->Up->Location = System::Drawing::Point(428, 43);
			this->Up->Name = L"Up";
			this->Up->Size = System::Drawing::Size(45, 43);
			this->Up->TabIndex = 9;
			this->Up->Text = L"Up";
			this->Up->UseVisualStyleBackColor = true;
			this->Up->Click += gcnew System::EventHandler(this, &TCPclient::button4_Click);
			// 
			// Stop
			// 
			this->Stop->Location = System::Drawing::Point(428, 92);
			this->Stop->Name = L"Stop";
			this->Stop->Size = System::Drawing::Size(45, 42);
			this->Stop->TabIndex = 10;
			this->Stop->Text = L"Stop";
			this->Stop->UseVisualStyleBackColor = true;
			this->Stop->Click += gcnew System::EventHandler(this, &TCPclient::button5_Click);
			// 
			// Right
			// 
			this->Right->Location = System::Drawing::Point(479, 94);
			this->Right->Name = L"Right";
			this->Right->Size = System::Drawing::Size(46, 40);
			this->Right->TabIndex = 11;
			this->Right->Text = L"Right";
			this->Right->UseVisualStyleBackColor = true;
			this->Right->Click += gcnew System::EventHandler(this, &TCPclient::button6_Click);
			// 
			// Down
			// 
			this->Down->Location = System::Drawing::Point(428, 140);
			this->Down->Name = L"Down";
			this->Down->Size = System::Drawing::Size(45, 43);
			this->Down->TabIndex = 12;
			this->Down->Text = L"Down";
			this->Down->UseVisualStyleBackColor = true;
			this->Down->Click += gcnew System::EventHandler(this, &TCPclient::button7_Click);
			// 
			// Left
			// 
			this->Left->Location = System::Drawing::Point(375, 91);
			this->Left->Name = L"Left";
			this->Left->Size = System::Drawing::Size(47, 42);
			this->Left->TabIndex = 13;
			this->Left->Text = L"Left";
			this->Left->UseVisualStyleBackColor = true;
			this->Left->Click += gcnew System::EventHandler(this, &TCPclient::button8_Click);
			// 
			// Myo
			// 
			this->Myo->Location = System::Drawing::Point(301, 159);
			this->Myo->Name = L"Myo";
			this->Myo->Size = System::Drawing::Size(65, 24);
			this->Myo->TabIndex = 14;
			this->Myo->Text = L"Myo";
			this->Myo->UseVisualStyleBackColor = true;
			this->Myo->Click += gcnew System::EventHandler(this, &TCPclient::Myo_Click);
			// 
			// TCPclient
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(538, 222);
			this->Controls->Add(this->Myo);
			this->Controls->Add(this->Left);
			this->Controls->Add(this->Down);
			this->Controls->Add(this->Right);
			this->Controls->Add(this->Stop);
			this->Controls->Add(this->Up);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->KeyPreview = true;
			this->Name = L"TCPclient";
			this->Text = L"TCPclient";
			this->Load += gcnew System::EventHandler(this, &TCPclient::TCPclient_Load);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TCPclient::TCPclient_KeyPress);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void TCPclient_Load(System::Object^  sender, System::EventArgs^  e) {
	}

// Send button
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		// Translate the passed message into ASCII and store it as a Byte array. 
		/*Get the byte array of the message and send it to the stream*/
		array<Byte>^data = System::Text::Encoding::ASCII->GetBytes(textBox1->Text);
		stream->Write(data, 0, data->Length);
		textBox4->AppendText("Message: " + textBox1->Text + "\r\n");
		textBox1->Clear();
	}
// Connect Button
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

	/*Parse IP & port info and connect to client, the stream has global scope so that other funcs can use
	Note the usage of BGW is just for realtime display of received messages*/
	client = gcnew TcpClient(textBox2->Text,Int32::Parse(textBox3->Text));
	stream = client->GetStream();
	textBox4->AppendText("Connected to: " + textBox2->Text + ":" + textBox3->Text + "\r\n");
}

// Disconnect Button
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
	/*Disconnect from client, close stream first then TCP connection
	NOTE: this is the Disconnect button, not to be confused with server stop(below)*/
	textBox4->AppendText("Disconnected \r\n");
	stream->Close();
	client->Close();
}
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
	array<Byte>^data = System::Text::Encoding::ASCII->GetBytes("1");
	stream->Write(data, 0, data->Length);
	textBox4->AppendText("Message: 1\r\n");
}
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
	array<Byte>^data = System::Text::Encoding::ASCII->GetBytes("4");
	stream->Write(data, 0, data->Length);
	textBox4->AppendText("Message: 4\r\n");
}
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
	array<Byte>^data = System::Text::Encoding::ASCII->GetBytes("2");
	stream->Write(data, 0, data->Length);
	textBox4->AppendText("Message: 2\r\n");
}
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
	array<Byte>^data = System::Text::Encoding::ASCII->GetBytes("5");
	stream->Write(data, 0, data->Length);
	textBox4->AppendText("Message: 5\r\n");
}
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
	array<Byte>^data = System::Text::Encoding::ASCII->GetBytes("3");
	stream->Write(data, 0, data->Length);
	textBox4->AppendText("Message: 3\r\n");
}
private: System::Void TCPclient_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {

	array<Byte>^data;
	switch (e->KeyChar)
	{
	case 'w':
		data = System::Text::Encoding::ASCII->GetBytes("1");
		stream->Write(data, 0, data->Length);
		textBox4->AppendText("Message: 1\r\n");
	break;
	case 's':
		data = System::Text::Encoding::ASCII->GetBytes("2");
		stream->Write(data, 0, data->Length);
		textBox4->AppendText("Message: 2\r\n");
	break;
	case 'x':
		data = System::Text::Encoding::ASCII->GetBytes("3");
		stream->Write(data, 0, data->Length);
		textBox4->AppendText("Message: 3\r\n");
		break;
	case 'a':
		data = System::Text::Encoding::ASCII->GetBytes("4");
		stream->Write(data, 0, data->Length);
		textBox4->AppendText("Message: 4\r\n");
		break;
	case 'd':
		data = System::Text::Encoding::ASCII->GetBytes("5");
		stream->Write(data, 0, data->Length);
		textBox4->AppendText("Message: 5\r\n");
		break;
	}
}
private: System::Void Myo_Click(System::Object^  sender, System::EventArgs^  e) {
	
	myo::Hub hub("com.example.hello-myo");
	textBox4->AppendText("Attempting to find a Myo...\r\n");
	myo::Myo* myo = hub.waitForMyo(10000);
	if (!myo) {
		textBox4->AppendText("Unable to find a Myo!");
		Application::Exit();
	}
	textBox4->AppendText("Connected to a Myo armband! \r\n");
	DataCollector collector;
	hub.addListener(&collector);
	
	while (1) {
		hub.run(1000);
		array<Byte>^data;
		if (collector.currentPose == myo::Pose::rest || collector.pitch_w < 2)
		{
			data = System::Text::Encoding::ASCII->GetBytes("2");
			stream->Write(data, 0, data->Length);
			textBox4->AppendText("Message: 2\r\n");
		}
		else if (collector.currentPose == myo::Pose::fist && collector.pitch_w > 13)
		{
			data = System::Text::Encoding::ASCII->GetBytes("3");
			stream->Write(data, 0, data->Length);
			textBox4->AppendText("Message: 3\r\n");
		}
		else if (collector.currentPose == myo::Pose::fist && collector.pitch_w > 2 && collector.pitch_w < 9)
		{
			data = System::Text::Encoding::ASCII->GetBytes("1");
			stream->Write(data, 0, data->Length);
			textBox4->AppendText("Message: 1\r\n");
		}
		else if (collector.currentPose == myo::Pose::fist && (collector.roll_w >11))
		{ 
			data = System::Text::Encoding::ASCII->GetBytes("5");
			stream->Write(data, 0, data->Length);				// right is 5
			textBox4->AppendText("Message: 5\r\n");
		}
		else if (collector.currentPose == myo::Pose::fist && (collector.roll_w <10))
		{
			data = System::Text::Encoding::ASCII->GetBytes("4");
			stream->Write(data, 0, data->Length);				// left is 4
			textBox4->AppendText("Message: 4\r\n");
		}
		else if (collector.currentPose == myo::Pose::fingersSpread)
		{
			break;
			Application::Exit();
		}
	}
	
}
};
}
