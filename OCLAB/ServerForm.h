#include <iostream>
#include <winsock2.h>
#include <stdint.h>
#include <string>
#include <fstream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
#pragma once


namespace OCLAB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ ServerForm
	/// </summary>
	public ref class ServerForm : public System::Windows::Forms::Form
	{
	public:
		ServerForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~ServerForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Label^ nLabel;
	private: System::Windows::Forms::NumericUpDown^ Numeric_n;
	private: System::Windows::Forms::ListBox^ listBox_n;
	private: System::Windows::Forms::Button^ Ok_button;

	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;


	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		   /// содержимое этого метода с помощью редактора кода.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->nLabel = (gcnew System::Windows::Forms::Label());
			   this->Numeric_n = (gcnew System::Windows::Forms::NumericUpDown());
			   this->listBox_n = (gcnew System::Windows::Forms::ListBox());
			   this->Ok_button = (gcnew System::Windows::Forms::Button());
			   this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Numeric_n))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // nLabel
			   // 
			   this->nLabel->AutoSize = true;
			   this->nLabel->Font = (gcnew System::Drawing::Font(L"Times New Roman", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->nLabel->Location = System::Drawing::Point(5, 12);
			   this->nLabel->Name = L"nLabel";
			   this->nLabel->Size = System::Drawing::Size(69, 15);
			   this->nLabel->TabIndex = 0;
			   this->nLabel->Text = L"¬ведите n:";
			   // 
			   // Numeric_n
			   // 
			   this->Numeric_n->Location = System::Drawing::Point(80, 11);
			   this->Numeric_n->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			   this->Numeric_n->Name = L"Numeric_n";
			   this->Numeric_n->Size = System::Drawing::Size(120, 20);
			   this->Numeric_n->TabIndex = 1;
			   // 
			   // listBox_n
			   // 
			   this->listBox_n->FormattingEnabled = true;
			   this->listBox_n->Location = System::Drawing::Point(8, 37);
			   this->listBox_n->Name = L"listBox_n";
			   this->listBox_n->Size = System::Drawing::Size(153, 342);
			   this->listBox_n->TabIndex = 2;
			   // 
			   // Ok_button
			   // 
			   this->Ok_button->Location = System::Drawing::Point(206, 11);
			   this->Ok_button->Name = L"Ok_button";
			   this->Ok_button->Size = System::Drawing::Size(41, 20);
			   this->Ok_button->TabIndex = 3;
			   this->Ok_button->Text = L"OK";
			   this->Ok_button->UseVisualStyleBackColor = true;
			   this->Ok_button->Click += gcnew System::EventHandler(this, &ServerForm::Ok_button_Click);
			   // 
			   // backgroundWorker1
			   // 
			   this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ServerForm::backgroundWorker1_DoWork);
			   // 
			   // ServerForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(400, 400);
			   this->Controls->Add(this->Ok_button);
			   this->Controls->Add(this->listBox_n);
			   this->Controls->Add(this->Numeric_n);
			   this->Controls->Add(this->nLabel);
			   this->Name = L"ServerForm";
			   this->Text = L"ServerForm";
			   this->Load += gcnew System::EventHandler(this, &ServerForm::ServerForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Numeric_n))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	int n = 0;
	int i = 0;
	bool onclicked = false;
	SOCKET sListen;
	SOCKET newConnection;
	
	

	private: System::Void ServerForm_Load(System::Object^ sender, System::EventArgs^ e) {
		backgroundWorker1->RunWorkerAsync();
	}

	private: System::Void Ok_button_Click(System::Object^ sender, System::EventArgs^ e) {
		n = (int)this->Numeric_n->Value;	
		onclicked = true;
		this->Ok_button->Enabled = false;
	}

	private: System::Void OCLAB::ServerForm::Add_n(int k)
	{
		listBox_n->Items->Add(k);
	}

	private: System::Void OCLAB::ServerForm::Disconnect()
	{
		std::string message = "Client ";
		message += std::to_string(newConnection);
		message += " disconnected!";
		String^ new_message = gcnew System::String(message.c_str());

		listBox_n->Items->Add(new_message);
	}

	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		std::ofstream logs;
		logs.open("E:\\VisualStudioProjects\\OCLAB\\OCLAB\\Log.txt");
		WSAData wsaData;
		WORD DLLVersion = MAKEWORD(2, 1);
		if (WSAStartup(DLLVersion, &wsaData) != 0) {
			MessageBox::Show("Error!", "Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			this->Close();
		}
		SOCKADDR_IN addr;
		int size_of_addr = sizeof(addr);
		// информаци€ об адресе сокета  
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(1111);
		addr.sin_family = AF_INET;
		// прослушивание
		sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);
		
		while (true) {
			
			newConnection = accept(sListen, (SOCKADDR*)&addr, &size_of_addr);
			if (newConnection == 0) {
				MessageBox::Show("Error!", "Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				this->Close();
			}
			MessageBox::Show("Connection successful!", "OK!", MessageBoxButtons::OK, MessageBoxIcon::None);
			logs << "Connection successful" << std::endl;
			while(!onclicked){}
			for (i; i <= n; i++) {
				int g = i;
				if (send(newConnection, (char*)&g, sizeof(g), NULL) == SOCKET_ERROR) {
					Disconnect();
					logs << "Client " << newConnection << " disconnect" << std::endl;
					break;
				}
				this->listBox_n->Invoke(gcnew Action<int>(this, &ServerForm::Add_n), i);
				logs << i << std::endl;
				listBox_n->TopIndex = listBox_n->Items->Count - 1;
				Sleep(200);
			}

			if (i >= n) {
				MessageBox::Show("Task completed!", "OK!", MessageBoxButtons::OK, MessageBoxIcon::None);
				logs << "Task completed!" << std::endl;
				break;
			}
		}
		
	}
	
};
}
