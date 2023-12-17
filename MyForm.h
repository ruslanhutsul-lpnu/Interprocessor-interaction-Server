#pragma once
//
//#undef UNICODE
//#define WIN32_LEAN_AND_MEAN
#include "Server.h"
#include <msclr/marshal_cppstd.h>
#include <Windows.h>
#include <sstream>

#include <thread>
#include <chrono>
#include <vector>


//
//#define DEFAULT_BUFLEN 512
//#define DEFAULT_PORT "27015"

namespace WFtry2 {

	using namespace System::Threading;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;
	using namespace System::Runtime::InteropServices;
	using namespace System::IO;
	using namespace msclr::interop;
	//using namespace std;
	using namespace System::Timers;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	/// 

	


	public ref class MyForm : public System::Windows::Forms::Form
	{

	private: List<SOCKET>^ moderSockets = gcnew List<SOCKET>();
	private: Server^ server;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Panel^ panel2;


	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Button^ button_deleteChatHistory;

	private: System::Windows::Forms::Label^ label2;

	private:
		// Остання отримана відповідь від сервера
		String^ lastReceivedMessage;
		// Таймер для перевірки сервера

	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ User;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Access;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Time;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Customer;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Message;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;

	private: System::ComponentModel::IContainer^ components;


		   System::Timers::Timer^ serverCheckTimer;
	private: System::Timers::Timer^ timer;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::Label^ label3;

		   String^ filePath = "UserData.txt";
		   String^ filePathChat = "ChatData.txt"; 
		   String^ filePathIncoming = "IncomingData.txt";

	/*C:\\Users\\Admin\\Desktop\\Нова папка\\*/

	public:
		MyForm(void)
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
		~MyForm()
		{
		}
	
		   

	
	
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		
		//this->Load += gcnew EventHandler(this, &MyForm::MyForm_Load);
		//////
		//serverCheckTimer = gcnew System::Timers::Timer();
		//serverCheckTimer->Interval = 1000; // Інтервал в мілісекундах (тут 1000 мс = 1 с)
		//serverCheckTimer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &MyForm::OnTimerTick);
		//serverCheckTimer->AutoReset = true; // Щоб таймер автоматично перезапускався після інтервалу
		//serverCheckTimer->Enabled = true;
		/////

		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button_deleteChatHistory = (gcnew System::Windows::Forms::Button());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->User = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Access = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->Time = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Customer = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Message = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->timer = (gcnew System::Timers::Timer());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timer))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(186, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(109, 19);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Active users";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(188)), static_cast<System::Int32>(static_cast<System::Byte>(227)),
				static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->panel2->Controls->Add(this->richTextBox1);
			this->panel2->Controls->Add(this->pictureBox2);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Location = System::Drawing::Point(203, 319);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(519, 253);
			this->panel2->TabIndex = 5;
			// 
			// richTextBox1
			// 
			this->richTextBox1->Location = System::Drawing::Point(57, 54);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(384, 170);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(179, 17);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(24, 31);
			this->pictureBox2->TabIndex = 4;
			this->pictureBox2->TabStop = false;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(84)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->label2->Location = System::Drawing::Point(209, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(92, 19);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Messages";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(165, 46);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(25, 36);
			this->pictureBox1->TabIndex = 6;
			this->pictureBox1->TabStop = false;
			// 
			// button_deleteChatHistory
			// 
			this->button_deleteChatHistory->Location = System::Drawing::Point(329, 578);
			this->button_deleteChatHistory->Name = L"button_deleteChatHistory";
			this->button_deleteChatHistory->Size = System::Drawing::Size(241, 27);
			this->button_deleteChatHistory->TabIndex = 7;
			this->button_deleteChatHistory->Text = L"Delete chat history in file";
			this->button_deleteChatHistory->UseVisualStyleBackColor = true;
			this->button_deleteChatHistory->Click += gcnew System::EventHandler(this, &MyForm::button_deleteChatHistory_Click);
			// 
			// dataGridView1
			// 
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->User, this->Access });
			this->dataGridView1->Location = System::Drawing::Point(76, 83);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->ReadOnly = true;
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(304, 215);
			this->dataGridView1->TabIndex = 8;
			// 
			// User
			// 
			this->User->HeaderText = L"User";
			this->User->MinimumWidth = 6;
			this->User->Name = L"User";
			this->User->ReadOnly = true;
			this->User->Width = 125;
			// 
			// Access
			// 
			this->Access->HeaderText = L"Access";
			this->Access->MinimumWidth = 6;
			this->Access->Name = L"Access";
			this->Access->ReadOnly = true;
			this->Access->Width = 125;
			// 
			// dataGridView2
			// 
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				this->Time, this->Customer,
					this->Message
			});
			this->dataGridView2->Location = System::Drawing::Point(416, 83);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->ReadOnly = true;
			this->dataGridView2->RowHeadersWidth = 51;
			this->dataGridView2->RowTemplate->Height = 24;
			this->dataGridView2->Size = System::Drawing::Size(427, 215);
			this->dataGridView2->TabIndex = 10;
			// 
			// Time
			// 
			this->Time->HeaderText = L"Time";
			this->Time->MinimumWidth = 6;
			this->Time->Name = L"Time";
			this->Time->ReadOnly = true;
			this->Time->Width = 125;
			// 
			// Customer
			// 
			this->Customer->HeaderText = L"Customer";
			this->Customer->MinimumWidth = 6;
			this->Customer->Name = L"Customer";
			this->Customer->ReadOnly = true;
			this->Customer->Width = 125;
			// 
			// Message
			// 
			this->Message->HeaderText = L"Message";
			this->Message->MinimumWidth = 6;
			this->Message->Name = L"Message";
			this->Message->ReadOnly = true;
			this->Message->Width = 125;
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 1000;
			this->timer->SynchronizingObject = this;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(549, 46);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(205, 19);
			this->label3->TabIndex = 11;
			this->label3->Text = L"Message for processing";
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(519, 46);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(24, 31);
			this->pictureBox3->TabIndex = 12;
			this->pictureBox3->TabStop = false;
			// 
			// MyForm
			// 
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(190)), static_cast<System::Int32>(static_cast<System::Byte>(204)),
				static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->ClientSize = System::Drawing::Size(896, 612);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->button_deleteChatHistory);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->panel2);
			this->Font = (gcnew System::Drawing::Font(L"Century Gothic", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Name = L"MyForm";
			this->Text = L"Server";
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->timer))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

			this->Load += gcnew EventHandler(this, &MyForm::MyForm_Load);
			System::Timers::Timer^ timer = gcnew System::Timers::Timer();
			timer->Interval = 1000; // інтервал в мілісекундах
			timer->Elapsed += gcnew ElapsedEventHandler(this, &MyForm::OnTimerTick);
			timer->AutoReset = true; // встановлення автоматичного перезапуску таймера
			timer->Enabled = true;
		}
#pragma endregion
	
		void MyForm_Load(Object^ sender, EventArgs^ e) {
			try {
				server = gcnew Server();
				
				// Запускаємо сервер у окремому потоці
				Thread^ serverThread = gcnew Thread(gcnew ThreadStart(server, &Server::StartServer));
				serverThread->IsBackground = true; // Щоб при закритті форми припинити роботу сервера
				serverThread->Start();
				ServerLoadChat();
				ReadIncomingMessageFromFile();
			}
			catch (Exception^ e) {
				MessageBox::Show("Сталася помилка2222 : {0}", e->Message);
				
			}
			
			
		}

		void OnTimerTick(System::Object^ source, System::Timers::ElapsedEventArgs^ e) {

			for each (SOCKET clientSocket in server->ClientSockets) {
				int index = GetIndexOfSocket(server->ClientSockets, clientSocket);
				
				String^ receivedMessage = server->ReceiveData(clientSocket);
				if (receivedMessage == "disconnect") {
					/*MessageBox::Show(Convert::ToString(index));*/
					DeleteFromList(index);
					/*MessageBox::Show(Convert::ToString(index));*/
					moderSockets->RemoveAt(index);
					continue;
				}

				/*Console::WriteLine("Сталася помилка11111: {0}", receivedMessage);*/

				// Process the received message here
				if (!(receivedMessage == ""))
				{
					/*MessageBox::Show("server " + receivedMessage);*/
					CheckMessenge(clientSocket, receivedMessage);
				}
				

				// Update the text box with each received message
				/*String^ messageToShow = gcnew String(receivedMessage);
				textBox1->Invoke(gcnew Action<String^>(this, &MyForm::UpdateTextBox), messageToShow);*/
			}
		}

		int GetIndexOfSocket(List<SOCKET>^ socketList, SOCKET clientSocket) {
			for (int i = 0; i < socketList->Count; i++) {
				if (socketList[i] == clientSocket) {
					return i; // Повертаємо індекс, якщо знайдено співпадіння
				}
			}
			return -1; // Якщо не знайдено співпадінь
		}


		// Метод для оновлення текстового поля з іншого потока (через Invoke)
		void UpdateTextBox(String^ message) {
			/*textBox1->Text = message;*/
		}

		private: int CheckMessenge(SOCKET client, String^ messenge) {
			array<String^>^ words = messenge->Split(' ');
			/*MessageBox::Show(messenge);*/
			if (words[0] == "SIGN")
			{
				if (!IsUserInFile(words[1], words[2])) {
					PrintToFile(words[1], words[2], words[3]);
					server->SendData(client, "SIGN the account registered succes");
				}
				else {
					server->SendData(client, "SIGN the account successfully registered");
				}
			}
			else if (words[0] == "LOGIN")
			{
				try {
					if (IsLogIn(client, words[1], words[2], words[3])) {
						if (IsModer(words[1], words[2]))
						{
							String^ managedString = "LOGIN moder " + words[1] + " " + words[2]; // Ваш String^
							marshal_context context;
							const char* charStr = context.marshal_as<const char*>(managedString);
							server->SendData(client, charStr);
							Sleep(1000);
							moderSockets->Add(client);
							AddToList(words[1], words[2], true);
							DataGriedToModer(client);
							ClientLoadChat(client);
						}
						else {
							String^ managedString = "LOGIN true " + words[1] + " " + words[2]; // Ваш String^
							marshal_context context;
							const char* charStr = context.marshal_as<const char*>(managedString);
							server->SendData(client, charStr);
							AddToList(words[1], words[2], false);
							ClientLoadChat(client);
							
						}
							


					}
					
				}		
				catch (std::exception ex) {
					MessageBox::Show(Convert::ToString(ex.what()));
					server->SendData(client, ex.what());
				}

			}
			else if (words[0] == "MESSAGE")
			{
				///*MessageBox::Show(messenge);*/
				//textBox2->Text = messenge;
				/*server->SendData(client, "ok");*/
				PrintIncomingMessageToFile(messenge);
				dataGridView2->Rows->Add(words[1] + " " + words[2], words[3] + " " + words[4], JoinWordsFromIndex(words, 5));

				for each (SOCKET moderSocket in moderSockets) {

					String^ managedString = "UPDATE " + words[1] + " " + words[2] + " " + words[3] + " " + words[4] + " " + JoinWordsFromIndex(words, 5);
					marshal_context context;
					const char* charStr = context.marshal_as<const char*>(managedString);

					server->SendData(moderSocket, charStr);
				}
			}
			else if (words[0] == "ACCEPT") {

				String^ toFile = words[1] + " " + words[2] + "\n" + words[3] + " " + words[4] + ": " + JoinWordsFromIndex(words, 5) + "\n";
				PrintMessageToFile(toFile);
				richTextBox1->Text += toFile;
				DeleteMessageFromList(words[1] + " " + words[2]);
				DataGriedToFile();
				marshal_context context;
				String^ str = "MESSAGE " + toFile;
				const char* charStr = context.marshal_as<const char*>(str);

				/*MessageBox::Show(str);*/
		
				for each (SOCKET clientSocket in server->ClientSockets) {
					server->SendData(clientSocket, charStr);
				}
			}
			else if (words[0] == "REJECT") {
				/*MessageBox::Show(messenge);*/
				DeleteMessageFromList(words[1] + " " + words[2]);
				DataGriedToFile();
				marshal_context context;

				const char* charStr = context.marshal_as<const char*>(messenge);

					server->SendData(client, charStr);
				
			}

			return 1;
		}

		void PrintIncomingMessageToFile(String^ message) {
			try {
				array<String^>^ words = message->Split(' ');
				StreamWriter^ writer = gcnew StreamWriter(filePathIncoming, true);

				// Рядок, який будемо записувати
				String^ textToWrite = words[1] + " " + words[2] + " " + words[3] + " " + words[4] + " " + JoinWordsFromIndex(words, 5);

				// Записуємо рядок у файл
				writer->WriteLine(textToWrite);

				// Закриваємо файл
				writer->Close();

				/*MessageBox::Show("Інформацію успішно записано у файл.");*/
			}
			catch (Exception^ e) {
				/*MessageBox::Show("Сталася помилка: {0}", e->Message);*/

			}
		}
		void ReadIncomingMessageFromFile() {
			try {
				StreamReader^ reader = gcnew StreamReader(filePathIncoming);

				while (!reader->EndOfStream) {
					String^ line = reader->ReadLine();
					array<String^>^ words = line->Split(' ');
					dataGridView2->Rows->Add(words[0] + " " + words[1], words[2] + " " + words[3], JoinWordsFromIndex(words, 4));

				}

				// Закриваємо файл
				reader->Close();
			}
			catch (Exception^ e) {
				/*MessageBox::Show("Сталася помилка: {0}", e->Message);*/

			}
			

		}
		

		private: void DataGriedToModer(SOCKET moder) {
			if (dataGridView2->Rows->Count == 0)
				return;
			// Оголошення String^ для зберігання даних
			String^ dataAsString = "";

			// Проходимо по всіх рядках у dataGridView1
			for each (DataGridViewRow ^ row in dataGridView2->Rows) {
				if (row->IsNewRow) continue; 


				for each (DataGridViewCell ^ cell in row->Cells) {

					dataAsString += cell->Value->ToString() + " ";
				}

				dataAsString += "\n";
			}
			dataAsString = "LOAD " + dataAsString;
			marshal_context context;
			const char* charStr = context.marshal_as<const char*>(dataAsString);
			
			server->SendData(moder, charStr);
		}

			   private: void DataGriedToFile() {
				   if (dataGridView2->Rows->Count == 0)
					   return;
				   // Оголошення String^ для зберігання даних
				   String^ dataAsString = "";

				   // Проходимо по всіх рядках у dataGridView1
				   for each (DataGridViewRow ^ row in dataGridView2->Rows) {
					   if (row->IsNewRow) continue;


					   for each (DataGridViewCell ^ cell in row->Cells) {

						   dataAsString += cell->Value->ToString() + " ";
					   }

					   dataAsString += "\n";
				   }

				  /* MessageBox::Show("Інформацію успішно записано у файл." + dataAsString);*/

				   try {
					   /*MessageBox::Show("Інформацію успішно записано у файл.");*/
					   /*array<String^>^ words = message->Split(' ');*/
					   StreamWriter^ writer = gcnew StreamWriter(filePathIncoming);

					  

					   /*MessageBox::Show("Інформацію успішно записано у файл." + dataAsString);*/

					   // Записуємо рядок у файл
					   writer->WriteLine(dataAsString);

					   // Закриваємо файл
					   writer->Close();

					   /*MessageBox::Show("Інформацію успішно записано у файл.");*/
				   }
				   catch (Exception^ e) {
					   /*MessageBox::Show("Сталася помилка: {0}", e->Message);*/

				   }
			   }

		private: void AddToList(String^ surname, String^ name, bool access) {
			String^ moder = "Default";
			if (access)
				moder = "Moder";
			dataGridView1->Rows->Add(surname + " " + name, moder);

		}
		private: void DeleteFromList(int index) {
			/*MessageBox::Show(Convert::ToString(index));
			MessageBox::Show(Convert::ToString(server->ClientSockets->Count));*/
			if(server->ClientSockets->Count == 0)
				dataGridView1->Rows->Clear();

			// Перевірка на вірність індексу перед видаленням
			if (index >= 0 && index < dataGridView1->Rows->Count) {
				dataGridView1->Rows->RemoveAt(index); // Видаляємо рядок за вказаним індексом
				dataGridView1->Refresh(); // Оновлюємо DataGridView, щоб відобразити зміни
				/*for (int i = 0; i < dataGridView1->Rows->Count; ++i) {
					Console::WriteLine("Індекс рядка {0}: {1}", i, dataGridView1->Rows[i]->Cells[0]->Value);
				}*/

				
			}
		}
		private: void DeleteMessageFromList(String^ time) {
			// Перевірка на вірність індексу перед видаленням
			for (int i = 0; i < dataGridView2->Rows->Count; i++) {
				/*MessageBox::Show(dataGridView2->Rows[i]->Cells[0]->Value->ToString() + "   " + time);*/

				if (dataGridView2->Rows[i]->Cells[0]->Value->ToString() == time) {
					dataGridView2->Rows->RemoveAt(i);
				}
			}

		}

		String^ JoinWordsFromIndex(array<String^>^ words, int startIndex) {
			if (startIndex >= words->Length) {
				return ""; // Повернути порожній рядок, якщо початковий індекс виходить за межі масиву
			}

			String^ result = "";
			for (int i = startIndex; i < words->Length; i++) {
				result += words[i] + " ";
			}

			return result->Trim(); // Повертаємо рядок, обрізаючи останній пробіл за допомогою Trim()
		}


		private: bool IsUserInFile(String^ surname, String^ name) {
			try {

				StreamReader^ reader = gcnew StreamReader(filePath);

				while (!reader->EndOfStream) {
					String^ line = reader->ReadLine();
					array<String^>^ words = line->Split(' ');
					if (surname == words[0] && name == words[1])
					{
						reader->Close();
						return true;
					}

				}

				// Закриваємо файл
				reader->Close();

				return false;
			}
			catch (Exception^ e) {
				Console::WriteLine("Сталася помилка11111: {0}", e->Message);
			}
		}
			private: bool IsLogIn(SOCKET client, String^ surname, String^ name, String^ password) {
				try {

					StreamReader^ reader = gcnew StreamReader(filePath);

					while (!reader->EndOfStream) {
						String^ line = reader->ReadLine();
						array<String^>^ words = line->Split(' ');
						if (surname == words[0] && name == words[1])
						{
							if (password == words[2])
							{
								reader->Close();
								return true;
							}
							else {
								reader->Close();
								server->SendData(client, "LOGIN Incorrect password");
								throw std::exception("LOGIN Incorrect password");
								/*MessageBox::Show("Неправильний пароль");*/
								return false;
							}
						}

					}

					// Закриваємо файл
					reader->Close();
					server->SendData(client, "LOGIN There is no user with the same last name and first name");
					throw std::exception("LOGIN There is no user with the same last name and first name");
					/*MessageBox::Show("Користувача з таким самим прізвищем та ім'ям нема");*/
					return false;
				}
				catch (Exception^ e) {
					Console::WriteLine("Сталася помилка2222: {0}", e->Message);
				}
			}

				   private: bool IsModer(String^ surname, String^ name) {
					   try {

						   StreamReader^ reader = gcnew StreamReader(filePath);

						   while (!reader->EndOfStream) {
							   String^ line = reader->ReadLine();
							   array<String^>^ words = line->Split(' ');
							   if (surname == words[0] && name == words[1])
							   {
								   if (words->Length == 4)
								   {
									   reader->Close();
									   return true;
								   }
								   else {
									   reader->Close();

									   return false;
								   }
							   }

						   }

						   // Закриваємо файл
						   reader->Close();
						   /* server->SendData("LOGIN There is no user with the same last name and first name");*/
							/*MessageBox::Show("Користувача з таким самим прізвищем та ім'ям нема");*/
						   return false;
					   }
					   catch (Exception^ e) {
						   Console::WriteLine("Сталася помилка2222: {0}", e->Message);
					   }
				   }

		private: void PrintToFile(String^ surname, String^ name, String^ password)
		{
			try {

				StreamWriter^ writer = gcnew StreamWriter(filePath, true);

				// Рядок, який будемо записувати
				String^ textToWrite = surname + " " + name + " " + password;

				// Записуємо рядок у файл
				writer->WriteLine(textToWrite);

				// Закриваємо файл
				writer->Close();

				MessageBox::Show("Інформацію успішно записано у файл.");
			}
			catch (Exception^ e) {
				MessageBox::Show("Сталася помилка: {0}", e->Message);

			}

		}

			   private: void ServerLoadChat() {
				   try {

					   StreamReader^ reader = gcnew StreamReader(filePathChat);

					   while (!reader->EndOfStream) {
						   String^ line = reader->ReadLine();
						   richTextBox1->Text += line + "\n";

					   }

					   // Закриваємо файл
					   reader->Close();
					   
				   }
				   catch (Exception^ e) {
					   Console::WriteLine("Сталася помилка2222: {0}", e->Message);
				   }
			   }

				private: void ClientLoadChat(SOCKET client) {
					marshal_context context;
					String^ str = "LOADCHAT " + richTextBox1->Text;
					const char* charStr = context.marshal_as<const char*>(str);
					
					server->SendData(client, charStr);
					
				}


			   private: void PrintMessageToFile(String^ message)
			   {
				   try {

					   StreamWriter^ writer = gcnew StreamWriter(filePathChat, true);


					   // Записуємо рядок у файл
					   writer->WriteLine(message);

					   // Закриваємо файл
					   writer->Close();

					/*   MessageBox::Show("Інформацію успішно записано у файл.");*/
				   }
				   catch (Exception^ e) {
					   MessageBox::Show("Сталася помилка: {0}", e->Message);

				   }

			   }





		private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
		}
		
private: System::Void button_deleteChatHistory_Click(System::Object^ sender, System::EventArgs^ e) {
	try {

		StreamWriter^ writer = gcnew StreamWriter(filePathChat, false);
		/*ServerLoadChat();*/

		// Записуємо рядок у файл
		writer->WriteLine("");

		// Закриваємо файл
		writer->Close();
		ServerLoadChat();

		/*   MessageBox::Show("Інформацію успішно записано у файл.");*/
	}
	catch (Exception^ e) {
		MessageBox::Show("Сталася помилка: {0}", e->Message);

	}
}
//private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
//}
};
}
