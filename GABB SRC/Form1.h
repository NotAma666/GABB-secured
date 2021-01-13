#pragma once
#include <msclr\marshal_cppstd.h>
#include "../GDLL/client_lib.h"
#include <codecvt>
#include <fstream>

std::vector<std::pair<std::string, std::vector<std::string>>> saveData;
std::wstring savePath = L"";

std::vector<std::pair<int, std::vector<std::string>>> windowData;

std::vector<std::pair<int, std::pair<bool, std::string>>> SpammerInstances;
int selected_spammer_instance = -1;
int selected_spammer_id = -1;

std::pair<std::vector<std::pair<int, std::string>>, std::vector<int>> spammerData;
std::vector<int> spammerTargets;
bool spammerRefreshing = false;

std::vector<ACCUSER> userData;
bool accountAdding = false;
int accountEditing = -1;


std::wstring s2ws(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
	return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converterX;
	return converterX.to_bytes(wstr);
}

USERDATA uData;

void toClipboard(const std::string &s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size());
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

namespace GABB {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: W tym miejscu dodaj kod konstruktora
			//
		}

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::Panel^  Footer;
	private: System::Windows::Forms::Timer^  engineEventTimer;
	private: System::Windows::Forms::Label^  labelServerVersion;
	private: System::Windows::Forms::Label^  labelServerState;
	private: System::Windows::Forms::Panel^  panelServerState;
private: System::Windows::Forms::Panel^  panelServerAcc;
private: System::Windows::Forms::Label^  labelServerAccType;
private: System::Windows::Forms::Label^  labelServerAccName;
private: System::Windows::Forms::Label^  labelServerAccExp;
private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
private: System::Windows::Forms::TabPage^  tabSettings;
private: System::Windows::Forms::Panel^  panel2;
private: System::Windows::Forms::Panel^  panel3;
private: System::Windows::Forms::Panel^  panel1;
private: System::Windows::Forms::TextBox^  textBox2;
private: System::Windows::Forms::TextBox^  textBox1;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::TabPage^  tabLogs;
private: System::Windows::Forms::TextBox^  Logs;
private: System::Windows::Forms::TabPage^  tabDecoder;
private: System::Windows::Forms::CheckBox^  checkBoxSaveCopy;
private: System::Windows::Forms::CheckBox^  checkBoxSave;
private: System::Windows::Forms::ListBox^  listBoxSaveTitle;
private: System::Windows::Forms::ListBox^  listBoxSaveContent;
private: System::Windows::Forms::TextBox^  textBoxSavePath;
private: System::Windows::Forms::Button^  buttonDecode;
private: System::Windows::Forms::TabPage^  tabSpammer;
private: System::Windows::Forms::TextBox^  textBoxSpammerTextNew;
private: System::Windows::Forms::TextBox^  textBoxSpammerIntervalMessage;
private: System::Windows::Forms::TextBox^  textBoxSpammerIntervalLetter;
private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::CheckBox^  checkBoxSpammerState;
private: System::Windows::Forms::CheckBox^  checkBoxSpammerNoshift;
private: System::Windows::Forms::CheckBox^  checkBoxSpammerRandom;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::ListBox^  listBoxSpammerText;
private: System::Windows::Forms::CheckBox^  checkBoxSpammerWindowsAll;
private: System::Windows::Forms::CheckedListBox^  checkedListBoxSpammerWindows;
private: System::Windows::Forms::TabPage^  tabAccounts;
private: System::Windows::Forms::Panel^  panelAccountsEdit;
private: System::Windows::Forms::Button^  buttonAccountEditRandom;
private: System::Windows::Forms::Button^  buttonAccountEditCANCEL;
private: System::Windows::Forms::Button^  buttonAccountEditOK;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  labelAccountEdit;
private: System::Windows::Forms::TextBox^  textBoxAccountsCreateName;
private: System::Windows::Forms::TextBox^  textBoxAccountsCreateMAC;
private: System::Windows::Forms::Button^  buttonAccountsEdit;
private: System::Windows::Forms::Button^  buttonAccountsAdd;
private: System::Windows::Forms::Button^  buttonAccountsUnban;
private: System::Windows::Forms::Button^  buttonAccountsDelete;
private: System::Windows::Forms::Button^  buttonAccountsSet;
private: System::Windows::Forms::TextBox^  textBoxAccountsCurrent;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::ListBox^  listBoxAccounts;
private: System::Windows::Forms::TabPage^  tabWindows;
private: System::Windows::Forms::CheckBox^  checkBoxWindowsMB;
private: System::Windows::Forms::CheckBox^  checkBoxWindowsMBAll;
private: System::Windows::Forms::Button^  buttonWindowsCaptchaSolve;
private: System::Windows::Forms::Button^  buttonWindowsSH;
private: System::Windows::Forms::Button^  buttonWindowsBTF;
private: System::Windows::Forms::Button^  buttonWindowsClose;
private: System::Windows::Forms::Button^  buttonWindowsOpen;
private: System::Windows::Forms::ListBox^  listBoxWindows;
private: System::Windows::Forms::TabPage^  tabMain;
private: System::Windows::Forms::Panel^  panelLoginForm;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::TextBox^  textBoxLoginName;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::Button^  buttonLoginOk;
private: System::Windows::Forms::TextBox^  textBoxLoginPass;
private: System::Windows::Forms::Label^  labelMainVersionLatest;
private: System::Windows::Forms::Label^  labelLoginError;
private: System::Windows::Forms::Button^  buttonLoginALOGOUT;
private: System::Windows::Forms::Label^  labelServerState2;
private: System::Windows::Forms::Label^  labelMainVersion;
private: System::Windows::Forms::Button^  buttonLinkYT;
private: System::Windows::Forms::Button^  buttonLinkDiscord;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  labelLoginAName;
private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Label^  labelLoginAType;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  labelLoginAExp;
private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::TextBox^  textBox4;
private: System::Windows::Forms::TextBox^  textBox3;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::ListBox^  listBoxSpammerInstances;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Button^  buttonSpammerInstanceRm;

private: System::Windows::Forms::Button^  buttonSpammerInstanceAdd;
private: System::Windows::Forms::CheckBox^  checkBoxSpammerEnableAll;
private: System::Windows::Forms::Label^  labelUnbannerTimer;
private: System::Windows::Forms::TabPage^  tabMacro;

private: System::Windows::Forms::TextBox^  textBox6;
private: System::Windows::Forms::TextBox^  textBox5;
private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::CheckBox^  checkBox1;
private: System::Windows::Forms::CheckedListBox^  checkedListBox1;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Button^  buttonMacroBrowse;
private: System::Windows::Forms::Button^  buttonMacroInstanceRm;
private: System::Windows::Forms::Button^  buttonMacroInstanceAdd;
private: System::Windows::Forms::ListBox^  listBoxMacroInstanceVariables;
private: System::Windows::Forms::ListBox^  listBoxMacroInstances;
private: System::Windows::Forms::CheckBox^  checkBox2;
private: System::Windows::Forms::CheckBox^  checkBox3;
	private: System::ComponentModel::IContainer^  components;
	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->Footer = (gcnew System::Windows::Forms::Panel());
			this->panelServerAcc = (gcnew System::Windows::Forms::Panel());
			this->labelServerAccType = (gcnew System::Windows::Forms::Label());
			this->labelServerAccName = (gcnew System::Windows::Forms::Label());
			this->labelServerAccExp = (gcnew System::Windows::Forms::Label());
			this->labelServerVersion = (gcnew System::Windows::Forms::Label());
			this->labelServerState = (gcnew System::Windows::Forms::Label());
			this->panelServerState = (gcnew System::Windows::Forms::Panel());
			this->engineEventTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->tabSettings = (gcnew System::Windows::Forms::TabPage());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->tabLogs = (gcnew System::Windows::Forms::TabPage());
			this->Logs = (gcnew System::Windows::Forms::TextBox());
			this->tabDecoder = (gcnew System::Windows::Forms::TabPage());
			this->checkBoxSaveCopy = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSave = (gcnew System::Windows::Forms::CheckBox());
			this->listBoxSaveTitle = (gcnew System::Windows::Forms::ListBox());
			this->listBoxSaveContent = (gcnew System::Windows::Forms::ListBox());
			this->textBoxSavePath = (gcnew System::Windows::Forms::TextBox());
			this->buttonDecode = (gcnew System::Windows::Forms::Button());
			this->tabSpammer = (gcnew System::Windows::Forms::TabPage());
			this->checkBoxSpammerEnableAll = (gcnew System::Windows::Forms::CheckBox());
			this->listBoxSpammerInstances = (gcnew System::Windows::Forms::ListBox());
			this->textBoxSpammerTextNew = (gcnew System::Windows::Forms::TextBox());
			this->textBoxSpammerIntervalMessage = (gcnew System::Windows::Forms::TextBox());
			this->textBoxSpammerIntervalLetter = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->checkBoxSpammerState = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSpammerNoshift = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxSpammerRandom = (gcnew System::Windows::Forms::CheckBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->buttonSpammerInstanceRm = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->buttonSpammerInstanceAdd = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->listBoxSpammerText = (gcnew System::Windows::Forms::ListBox());
			this->checkBoxSpammerWindowsAll = (gcnew System::Windows::Forms::CheckBox());
			this->checkedListBoxSpammerWindows = (gcnew System::Windows::Forms::CheckedListBox());
			this->tabAccounts = (gcnew System::Windows::Forms::TabPage());
			this->labelUnbannerTimer = (gcnew System::Windows::Forms::Label());
			this->panelAccountsEdit = (gcnew System::Windows::Forms::Panel());
			this->buttonAccountEditRandom = (gcnew System::Windows::Forms::Button());
			this->buttonAccountEditCANCEL = (gcnew System::Windows::Forms::Button());
			this->buttonAccountEditOK = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labelAccountEdit = (gcnew System::Windows::Forms::Label());
			this->textBoxAccountsCreateName = (gcnew System::Windows::Forms::TextBox());
			this->textBoxAccountsCreateMAC = (gcnew System::Windows::Forms::TextBox());
			this->buttonAccountsEdit = (gcnew System::Windows::Forms::Button());
			this->buttonAccountsAdd = (gcnew System::Windows::Forms::Button());
			this->buttonAccountsUnban = (gcnew System::Windows::Forms::Button());
			this->buttonAccountsDelete = (gcnew System::Windows::Forms::Button());
			this->buttonAccountsSet = (gcnew System::Windows::Forms::Button());
			this->textBoxAccountsCurrent = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->listBoxAccounts = (gcnew System::Windows::Forms::ListBox());
			this->tabWindows = (gcnew System::Windows::Forms::TabPage());
			this->checkBoxWindowsMB = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxWindowsMBAll = (gcnew System::Windows::Forms::CheckBox());
			this->buttonWindowsCaptchaSolve = (gcnew System::Windows::Forms::Button());
			this->buttonWindowsSH = (gcnew System::Windows::Forms::Button());
			this->buttonWindowsBTF = (gcnew System::Windows::Forms::Button());
			this->buttonWindowsClose = (gcnew System::Windows::Forms::Button());
			this->buttonWindowsOpen = (gcnew System::Windows::Forms::Button());
			this->listBoxWindows = (gcnew System::Windows::Forms::ListBox());
			this->tabMain = (gcnew System::Windows::Forms::TabPage());
			this->panelLoginForm = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBoxLoginName = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->buttonLoginOk = (gcnew System::Windows::Forms::Button());
			this->textBoxLoginPass = (gcnew System::Windows::Forms::TextBox());
			this->labelMainVersionLatest = (gcnew System::Windows::Forms::Label());
			this->labelLoginError = (gcnew System::Windows::Forms::Label());
			this->buttonLoginALOGOUT = (gcnew System::Windows::Forms::Button());
			this->labelServerState2 = (gcnew System::Windows::Forms::Label());
			this->labelMainVersion = (gcnew System::Windows::Forms::Label());
			this->buttonLinkYT = (gcnew System::Windows::Forms::Button());
			this->buttonLinkDiscord = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->labelLoginAName = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->labelLoginAType = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->labelLoginAExp = (gcnew System::Windows::Forms::Label());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabMacro = (gcnew System::Windows::Forms::TabPage());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkedListBox1 = (gcnew System::Windows::Forms::CheckedListBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->buttonMacroBrowse = (gcnew System::Windows::Forms::Button());
			this->buttonMacroInstanceRm = (gcnew System::Windows::Forms::Button());
			this->buttonMacroInstanceAdd = (gcnew System::Windows::Forms::Button());
			this->listBoxMacroInstanceVariables = (gcnew System::Windows::Forms::ListBox());
			this->listBoxMacroInstances = (gcnew System::Windows::Forms::ListBox());
			this->Footer->SuspendLayout();
			this->panelServerAcc->SuspendLayout();
			this->tabSettings->SuspendLayout();
			this->tabLogs->SuspendLayout();
			this->tabDecoder->SuspendLayout();
			this->tabSpammer->SuspendLayout();
			this->tabAccounts->SuspendLayout();
			this->panelAccountsEdit->SuspendLayout();
			this->tabWindows->SuspendLayout();
			this->tabMain->SuspendLayout();
			this->panelLoginForm->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabMacro->SuspendLayout();
			this->SuspendLayout();
			// 
			// Footer
			// 
			this->Footer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(24)), static_cast<System::Int32>(static_cast<System::Byte>(24)),
				static_cast<System::Int32>(static_cast<System::Byte>(28)));
			this->Footer->Controls->Add(this->panelServerAcc);
			this->Footer->Controls->Add(this->labelServerVersion);
			this->Footer->Controls->Add(this->labelServerState);
			this->Footer->Controls->Add(this->panelServerState);
			this->Footer->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->Footer->Location = System::Drawing::Point(0, 392);
			this->Footer->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Footer->Name = L"Footer";
			this->Footer->Size = System::Drawing::Size(840, 31);
			this->Footer->TabIndex = 1;
			// 
			// panelServerAcc
			// 
			this->panelServerAcc->Controls->Add(this->labelServerAccType);
			this->panelServerAcc->Controls->Add(this->labelServerAccName);
			this->panelServerAcc->Controls->Add(this->labelServerAccExp);
			this->panelServerAcc->Location = System::Drawing::Point(154, 1);
			this->panelServerAcc->Name = L"panelServerAcc";
			this->panelServerAcc->Size = System::Drawing::Size(584, 30);
			this->panelServerAcc->TabIndex = 7;
			// 
			// labelServerAccType
			// 
			this->labelServerAccType->AutoSize = true;
			this->labelServerAccType->ForeColor = System::Drawing::Color::White;
			this->labelServerAccType->Location = System::Drawing::Point(3, 14);
			this->labelServerAccType->Name = L"labelServerAccType";
			this->labelServerAccType->Size = System::Drawing::Size(79, 16);
			this->labelServerAccType->TabIndex = 6;
			this->labelServerAccType->Text = L"Account type:";
			// 
			// labelServerAccName
			// 
			this->labelServerAccName->AutoSize = true;
			this->labelServerAccName->ForeColor = System::Drawing::Color::White;
			this->labelServerAccName->Location = System::Drawing::Point(3, 0);
			this->labelServerAccName->Name = L"labelServerAccName";
			this->labelServerAccName->Size = System::Drawing::Size(77, 16);
			this->labelServerAccName->TabIndex = 6;
			this->labelServerAccName->Text = L"Logged in as: ";
			// 
			// labelServerAccExp
			// 
			this->labelServerAccExp->AutoSize = true;
			this->labelServerAccExp->ForeColor = System::Drawing::Color::White;
			this->labelServerAccExp->Location = System::Drawing::Point(163, 14);
			this->labelServerAccExp->Name = L"labelServerAccExp";
			this->labelServerAccExp->Size = System::Drawing::Size(111, 16);
			this->labelServerAccExp->TabIndex = 6;
			this->labelServerAccExp->Text = L"Premium expiration: ";
			// 
			// labelServerVersion
			// 
			this->labelServerVersion->ForeColor = System::Drawing::Color::White;
			this->labelServerVersion->Location = System::Drawing::Point(724, 14);
			this->labelServerVersion->Name = L"labelServerVersion";
			this->labelServerVersion->Size = System::Drawing::Size(108, 15);
			this->labelServerVersion->TabIndex = 5;
			this->labelServerVersion->Text = L"0.0.0";
			this->labelServerVersion->TextAlign = System::Drawing::ContentAlignment::BottomRight;
			// 
			// labelServerState
			// 
			this->labelServerState->AutoSize = true;
			this->labelServerState->ForeColor = System::Drawing::Color::White;
			this->labelServerState->Location = System::Drawing::Point(54, 12);
			this->labelServerState->Name = L"labelServerState";
			this->labelServerState->Size = System::Drawing::Size(76, 16);
			this->labelServerState->TabIndex = 4;
			this->labelServerState->Text = L"Disconnected";
			// 
			// panelServerState
			// 
			this->panelServerState->BackColor = System::Drawing::Color::Red;
			this->panelServerState->Location = System::Drawing::Point(4, 3);
			this->panelServerState->Name = L"panelServerState";
			this->panelServerState->Size = System::Drawing::Size(44, 25);
			this->panelServerState->TabIndex = 3;
			// 
			// engineEventTimer
			// 
			this->engineEventTimer->Enabled = true;
			this->engineEventTimer->Interval = 10;
			this->engineEventTimer->Tick += gcnew System::EventHandler(this, &Form1::engineEventTimer_Tick);
			// 
			// tabSettings
			// 
			this->tabSettings->BackColor = System::Drawing::Color::Black;
			this->tabSettings->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabSettings.BackgroundImage")));
			this->tabSettings->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabSettings->Controls->Add(this->panel2);
			this->tabSettings->Controls->Add(this->panel3);
			this->tabSettings->Controls->Add(this->panel1);
			this->tabSettings->Controls->Add(this->textBox2);
			this->tabSettings->Controls->Add(this->textBox4);
			this->tabSettings->Controls->Add(this->textBox3);
			this->tabSettings->Controls->Add(this->textBox1);
			this->tabSettings->Controls->Add(this->label16);
			this->tabSettings->Controls->Add(this->label1);
			this->tabSettings->Controls->Add(this->label15);
			this->tabSettings->Controls->Add(this->label18);
			this->tabSettings->Controls->Add(this->label17);
			this->tabSettings->Controls->Add(this->label14);
			this->tabSettings->ForeColor = System::Drawing::Color::White;
			this->tabSettings->Location = System::Drawing::Point(4, 44);
			this->tabSettings->Name = L"tabSettings";
			this->tabSettings->Size = System::Drawing::Size(832, 344);
			this->tabSettings->TabIndex = 7;
			this->tabSettings->Text = L"Settings";
			// 
			// panel2
			// 
			this->panel2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel2.BackgroundImage")));
			this->panel2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Location = System::Drawing::Point(8, 252);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(200, 87);
			this->panel2->TabIndex = 2;
			this->panel2->Click += gcnew System::EventHandler(this, &Form1::panel2_Click);
			// 
			// panel3
			// 
			this->panel3->BackColor = System::Drawing::Color::Black;
			this->panel3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Location = System::Drawing::Point(420, 252);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(200, 87);
			this->panel3->TabIndex = 2;
			this->panel3->Click += gcnew System::EventHandler(this, &Form1::panel3_Click);
			// 
			// panel1
			// 
			this->panel1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"panel1.BackgroundImage")));
			this->panel1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Location = System::Drawing::Point(214, 252);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(200, 87);
			this->panel1->TabIndex = 2;
			this->panel1->Click += gcnew System::EventHandler(this, &Form1::panel1_Click);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(268, 141);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(134, 26);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"100";
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(268, 76);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(134, 26);
			this->textBox4->TabIndex = 1;
			this->textBox4->Text = L"1";
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &Form1::textBox4_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(268, 45);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(134, 26);
			this->textBox3->TabIndex = 1;
			this->textBox3->Text = L"1";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &Form1::textBox3_TextChanged);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(268, 13);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(134, 26);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"1";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(10, 80);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(0, 22);
			this->label16->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(10, 227);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(144, 22);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Background Image:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::Transparent;
			this->label15->Location = System::Drawing::Point(10, 144);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(252, 22);
			this->label15->TabIndex = 0;
			this->label15->Text = L"Event thread interval (max 1000):";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->BackColor = System::Drawing::Color::Transparent;
			this->label18->Location = System::Drawing::Point(10, 79);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(170, 22);
			this->label18->TabIndex = 0;
			this->label18->Text = L"Macro thread interval:";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->BackColor = System::Drawing::Color::Transparent;
			this->label17->Location = System::Drawing::Point(10, 48);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(209, 22);
			this->label17->TabIndex = 0;
			this->label17->Text = L"Multiboxing thread interval:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->BackColor = System::Drawing::Color::Transparent;
			this->label14->Location = System::Drawing::Point(10, 16);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(194, 22);
			this->label14->TabIndex = 0;
			this->label14->Text = L"Spammer thread interval:";
			// 
			// tabLogs
			// 
			this->tabLogs->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(24)), static_cast<System::Int32>(static_cast<System::Byte>(24)),
				static_cast<System::Int32>(static_cast<System::Byte>(28)));
			this->tabLogs->Controls->Add(this->Logs);
			this->tabLogs->Location = System::Drawing::Point(4, 44);
			this->tabLogs->Name = L"tabLogs";
			this->tabLogs->Size = System::Drawing::Size(832, 344);
			this->tabLogs->TabIndex = 5;
			this->tabLogs->Text = L"Logs";
			// 
			// Logs
			// 
			this->Logs->AcceptsReturn = true;
			this->Logs->AcceptsTab = true;
			this->Logs->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->Logs->Dock = System::Windows::Forms::DockStyle::Fill;
			this->Logs->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->Logs->ForeColor = System::Drawing::Color::White;
			this->Logs->Location = System::Drawing::Point(0, 0);
			this->Logs->Multiline = true;
			this->Logs->Name = L"Logs";
			this->Logs->ReadOnly = true;
			this->Logs->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->Logs->Size = System::Drawing::Size(832, 344);
			this->Logs->TabIndex = 0;
			// 
			// tabDecoder
			// 
			this->tabDecoder->AllowDrop = true;
			this->tabDecoder->BackColor = System::Drawing::Color::Black;
			this->tabDecoder->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabDecoder.BackgroundImage")));
			this->tabDecoder->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabDecoder->Controls->Add(this->checkBoxSaveCopy);
			this->tabDecoder->Controls->Add(this->checkBoxSave);
			this->tabDecoder->Controls->Add(this->listBoxSaveTitle);
			this->tabDecoder->Controls->Add(this->listBoxSaveContent);
			this->tabDecoder->Controls->Add(this->textBoxSavePath);
			this->tabDecoder->Controls->Add(this->buttonDecode);
			this->tabDecoder->Location = System::Drawing::Point(4, 44);
			this->tabDecoder->Name = L"tabDecoder";
			this->tabDecoder->Size = System::Drawing::Size(832, 344);
			this->tabDecoder->TabIndex = 4;
			this->tabDecoder->Text = L"Decoder";
			this->tabDecoder->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::tabDecoder_DragDrop);
			this->tabDecoder->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::tabDecoder_DragEnter);
			// 
			// checkBoxSaveCopy
			// 
			this->checkBoxSaveCopy->AutoSize = true;
			this->checkBoxSaveCopy->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSaveCopy->ForeColor = System::Drawing::Color::White;
			this->checkBoxSaveCopy->Location = System::Drawing::Point(270, 47);
			this->checkBoxSaveCopy->Name = L"checkBoxSaveCopy";
			this->checkBoxSaveCopy->Size = System::Drawing::Size(260, 26);
			this->checkBoxSaveCopy->TabIndex = 5;
			this->checkBoxSaveCopy->Text = L"Copy selected item to clipboard";
			this->checkBoxSaveCopy->UseVisualStyleBackColor = false;
			// 
			// checkBoxSave
			// 
			this->checkBoxSave->AutoSize = true;
			this->checkBoxSave->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSave->Checked = true;
			this->checkBoxSave->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSave->Cursor = System::Windows::Forms::Cursors::Default;
			this->checkBoxSave->ForeColor = System::Drawing::Color::White;
			this->checkBoxSave->Location = System::Drawing::Point(12, 47);
			this->checkBoxSave->Name = L"checkBoxSave";
			this->checkBoxSave->Size = System::Drawing::Size(166, 26);
			this->checkBoxSave->TabIndex = 4;
			this->checkBoxSave->Text = L"Use password filter";
			this->checkBoxSave->UseVisualStyleBackColor = false;
			this->checkBoxSave->CheckedChanged += gcnew System::EventHandler(this, &Form1::checkBoxSave_CheckedChanged);
			// 
			// listBoxSaveTitle
			// 
			this->listBoxSaveTitle->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxSaveTitle->ForeColor = System::Drawing::Color::White;
			this->listBoxSaveTitle->FormattingEnabled = true;
			this->listBoxSaveTitle->ItemHeight = 22;
			this->listBoxSaveTitle->Location = System::Drawing::Point(8, 81);
			this->listBoxSaveTitle->Name = L"listBoxSaveTitle";
			this->listBoxSaveTitle->Size = System::Drawing::Size(256, 246);
			this->listBoxSaveTitle->TabIndex = 3;
			this->listBoxSaveTitle->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBoxSaveTitle_SelectedIndexChanged);
			// 
			// listBoxSaveContent
			// 
			this->listBoxSaveContent->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxSaveContent->ForeColor = System::Drawing::Color::White;
			this->listBoxSaveContent->FormattingEnabled = true;
			this->listBoxSaveContent->ItemHeight = 22;
			this->listBoxSaveContent->Location = System::Drawing::Point(270, 81);
			this->listBoxSaveContent->Name = L"listBoxSaveContent";
			this->listBoxSaveContent->Size = System::Drawing::Size(549, 246);
			this->listBoxSaveContent->TabIndex = 2;
			this->listBoxSaveContent->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBoxSaveContent_SelectedIndexChanged);
			// 
			// textBoxSavePath
			// 
			this->textBoxSavePath->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxSavePath->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBoxSavePath->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->textBoxSavePath->ForeColor = System::Drawing::Color::White;
			this->textBoxSavePath->Location = System::Drawing::Point(123, 10);
			this->textBoxSavePath->Name = L"textBoxSavePath";
			this->textBoxSavePath->Size = System::Drawing::Size(696, 26);
			this->textBoxSavePath->TabIndex = 1;
			// 
			// buttonDecode
			// 
			this->buttonDecode->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonDecode->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonDecode->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->buttonDecode->ForeColor = System::Drawing::Color::White;
			this->buttonDecode->Location = System::Drawing::Point(8, 6);
			this->buttonDecode->Name = L"buttonDecode";
			this->buttonDecode->Size = System::Drawing::Size(109, 35);
			this->buttonDecode->TabIndex = 0;
			this->buttonDecode->Text = L"Decode";
			this->buttonDecode->UseVisualStyleBackColor = false;
			this->buttonDecode->Click += gcnew System::EventHandler(this, &Form1::buttonDecode_Click);
			// 
			// tabSpammer
			// 
			this->tabSpammer->BackColor = System::Drawing::Color::Black;
			this->tabSpammer->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabSpammer.BackgroundImage")));
			this->tabSpammer->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabSpammer->Controls->Add(this->checkBoxSpammerEnableAll);
			this->tabSpammer->Controls->Add(this->listBoxSpammerInstances);
			this->tabSpammer->Controls->Add(this->textBoxSpammerTextNew);
			this->tabSpammer->Controls->Add(this->textBoxSpammerIntervalMessage);
			this->tabSpammer->Controls->Add(this->textBoxSpammerIntervalLetter);
			this->tabSpammer->Controls->Add(this->label10);
			this->tabSpammer->Controls->Add(this->label9);
			this->tabSpammer->Controls->Add(this->checkBoxSpammerState);
			this->tabSpammer->Controls->Add(this->checkBoxSpammerNoshift);
			this->tabSpammer->Controls->Add(this->checkBoxSpammerRandom);
			this->tabSpammer->Controls->Add(this->label11);
			this->tabSpammer->Controls->Add(this->label19);
			this->tabSpammer->Controls->Add(this->label8);
			this->tabSpammer->Controls->Add(this->buttonSpammerInstanceRm);
			this->tabSpammer->Controls->Add(this->button4);
			this->tabSpammer->Controls->Add(this->buttonSpammerInstanceAdd);
			this->tabSpammer->Controls->Add(this->button3);
			this->tabSpammer->Controls->Add(this->listBoxSpammerText);
			this->tabSpammer->Controls->Add(this->checkBoxSpammerWindowsAll);
			this->tabSpammer->Controls->Add(this->checkedListBoxSpammerWindows);
			this->tabSpammer->Location = System::Drawing::Point(4, 44);
			this->tabSpammer->Name = L"tabSpammer";
			this->tabSpammer->Size = System::Drawing::Size(832, 344);
			this->tabSpammer->TabIndex = 3;
			this->tabSpammer->Text = L"Spammer";
			// 
			// checkBoxSpammerEnableAll
			// 
			this->checkBoxSpammerEnableAll->AutoSize = true;
			this->checkBoxSpammerEnableAll->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSpammerEnableAll->ForeColor = System::Drawing::Color::White;
			this->checkBoxSpammerEnableAll->Location = System::Drawing::Point(213, 239);
			this->checkBoxSpammerEnableAll->Name = L"checkBoxSpammerEnableAll";
			this->checkBoxSpammerEnableAll->Size = System::Drawing::Size(46, 26);
			this->checkBoxSpammerEnableAll->TabIndex = 11;
			this->checkBoxSpammerEnableAll->Text = L"All";
			this->checkBoxSpammerEnableAll->UseVisualStyleBackColor = false;
			this->checkBoxSpammerEnableAll->Click += gcnew System::EventHandler(this, &Form1::checkBoxSpammerEnableAll_Click);
			// 
			// listBoxSpammerInstances
			// 
			this->listBoxSpammerInstances->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxSpammerInstances->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->listBoxSpammerInstances->ForeColor = System::Drawing::Color::White;
			this->listBoxSpammerInstances->FormattingEnabled = true;
			this->listBoxSpammerInstances->ItemHeight = 18;
			this->listBoxSpammerInstances->Location = System::Drawing::Point(8, 70);
			this->listBoxSpammerInstances->Name = L"listBoxSpammerInstances";
			this->listBoxSpammerInstances->Size = System::Drawing::Size(261, 166);
			this->listBoxSpammerInstances->TabIndex = 10;
			this->listBoxSpammerInstances->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBoxSpammerInstances_SelectedIndexChanged);
			// 
			// textBoxSpammerTextNew
			// 
			this->textBoxSpammerTextNew->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxSpammerTextNew->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->textBoxSpammerTextNew->ForeColor = System::Drawing::Color::White;
			this->textBoxSpammerTextNew->Location = System::Drawing::Point(275, 70);
			this->textBoxSpammerTextNew->Name = L"textBoxSpammerTextNew";
			this->textBoxSpammerTextNew->Size = System::Drawing::Size(340, 23);
			this->textBoxSpammerTextNew->TabIndex = 9;
			// 
			// textBoxSpammerIntervalMessage
			// 
			this->textBoxSpammerIntervalMessage->Location = System::Drawing::Point(156, 275);
			this->textBoxSpammerIntervalMessage->Name = L"textBoxSpammerIntervalMessage";
			this->textBoxSpammerIntervalMessage->Size = System::Drawing::Size(100, 26);
			this->textBoxSpammerIntervalMessage->TabIndex = 7;
			this->textBoxSpammerIntervalMessage->Text = L"3000";
			this->textBoxSpammerIntervalMessage->TextChanged += gcnew System::EventHandler(this, &Form1::textBoxSpammerIntervalMessage_TextChanged);
			// 
			// textBoxSpammerIntervalLetter
			// 
			this->textBoxSpammerIntervalLetter->Location = System::Drawing::Point(156, 307);
			this->textBoxSpammerIntervalLetter->Name = L"textBoxSpammerIntervalLetter";
			this->textBoxSpammerIntervalLetter->Size = System::Drawing::Size(100, 26);
			this->textBoxSpammerIntervalLetter->TabIndex = 7;
			this->textBoxSpammerIntervalLetter->Text = L"30";
			this->textBoxSpammerIntervalLetter->TextChanged += gcnew System::EventHandler(this, &Form1::textBoxSpammerIntervalMessage_TextChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->BackColor = System::Drawing::Color::Transparent;
			this->label10->ForeColor = System::Drawing::Color::White;
			this->label10->Location = System::Drawing::Point(28, 307);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(122, 22);
			this->label10->TabIndex = 8;
			this->label10->Text = L"letters interval:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Transparent;
			this->label9->ForeColor = System::Drawing::Color::White;
			this->label9->Location = System::Drawing::Point(15, 277);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(135, 22);
			this->label9->TabIndex = 8;
			this->label9->Text = L"message interval:";
			// 
			// checkBoxSpammerState
			// 
			this->checkBoxSpammerState->AutoSize = true;
			this->checkBoxSpammerState->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSpammerState->ForeColor = System::Drawing::Color::White;
			this->checkBoxSpammerState->Location = System::Drawing::Point(125, 239);
			this->checkBoxSpammerState->Name = L"checkBoxSpammerState";
			this->checkBoxSpammerState->Size = System::Drawing::Size(85, 26);
			this->checkBoxSpammerState->TabIndex = 6;
			this->checkBoxSpammerState->Text = L"Enabled";
			this->checkBoxSpammerState->UseVisualStyleBackColor = false;
			this->checkBoxSpammerState->Click += gcnew System::EventHandler(this, &Form1::checkBox1_Click);
			// 
			// checkBoxSpammerNoshift
			// 
			this->checkBoxSpammerNoshift->AutoSize = true;
			this->checkBoxSpammerNoshift->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSpammerNoshift->Checked = true;
			this->checkBoxSpammerNoshift->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxSpammerNoshift->ForeColor = System::Drawing::Color::White;
			this->checkBoxSpammerNoshift->Location = System::Drawing::Point(142, 35);
			this->checkBoxSpammerNoshift->Name = L"checkBoxSpammerNoshift";
			this->checkBoxSpammerNoshift->Size = System::Drawing::Size(127, 26);
			this->checkBoxSpammerNoshift->TabIndex = 6;
			this->checkBoxSpammerNoshift->Text = L"NoShift mode";
			this->checkBoxSpammerNoshift->UseVisualStyleBackColor = false;
			this->checkBoxSpammerNoshift->Click += gcnew System::EventHandler(this, &Form1::checkBoxSpammerNoshift_Click);
			// 
			// checkBoxSpammerRandom
			// 
			this->checkBoxSpammerRandom->AutoSize = true;
			this->checkBoxSpammerRandom->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSpammerRandom->ForeColor = System::Drawing::Color::White;
			this->checkBoxSpammerRandom->Location = System::Drawing::Point(19, 239);
			this->checkBoxSpammerRandom->Name = L"checkBoxSpammerRandom";
			this->checkBoxSpammerRandom->Size = System::Drawing::Size(85, 26);
			this->checkBoxSpammerRandom->TabIndex = 6;
			this->checkBoxSpammerRandom->Text = L"Random";
			this->checkBoxSpammerRandom->UseVisualStyleBackColor = false;
			this->checkBoxSpammerRandom->Click += gcnew System::EventHandler(this, &Form1::checkBoxSpammerRandom_Click);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->BackColor = System::Drawing::Color::Transparent;
			this->label11->ForeColor = System::Drawing::Color::White;
			this->label11->Location = System::Drawing::Point(617, 6);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(144, 22);
			this->label11->TabIndex = 5;
			this->label11->Text = L"Assigned windows:";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->BackColor = System::Drawing::Color::Transparent;
			this->label19->ForeColor = System::Drawing::Color::White;
			this->label19->Location = System::Drawing::Point(4, 6);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(150, 22);
			this->label19->TabIndex = 5;
			this->label19->Text = L"Spammer Instances:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Transparent;
			this->label8->ForeColor = System::Drawing::Color::White;
			this->label8->Location = System::Drawing::Point(271, 6);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(116, 22);
			this->label8->TabIndex = 5;
			this->label8->Text = L"Spammer text:";
			// 
			// buttonSpammerInstanceRm
			// 
			this->buttonSpammerInstanceRm->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonSpammerInstanceRm->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonSpammerInstanceRm->ForeColor = System::Drawing::Color::White;
			this->buttonSpammerInstanceRm->Location = System::Drawing::Point(41, 31);
			this->buttonSpammerInstanceRm->Name = L"buttonSpammerInstanceRm";
			this->buttonSpammerInstanceRm->Size = System::Drawing::Size(27, 33);
			this->buttonSpammerInstanceRm->TabIndex = 4;
			this->buttonSpammerInstanceRm->Text = L"-";
			this->buttonSpammerInstanceRm->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->buttonSpammerInstanceRm->UseVisualStyleBackColor = false;
			this->buttonSpammerInstanceRm->Click += gcnew System::EventHandler(this, &Form1::buttonSpammerInstanceRm_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(308, 31);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(27, 33);
			this->button4->TabIndex = 4;
			this->button4->Text = L"-";
			this->button4->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// buttonSpammerInstanceAdd
			// 
			this->buttonSpammerInstanceAdd->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonSpammerInstanceAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonSpammerInstanceAdd->ForeColor = System::Drawing::Color::White;
			this->buttonSpammerInstanceAdd->Location = System::Drawing::Point(8, 31);
			this->buttonSpammerInstanceAdd->Name = L"buttonSpammerInstanceAdd";
			this->buttonSpammerInstanceAdd->Size = System::Drawing::Size(27, 33);
			this->buttonSpammerInstanceAdd->TabIndex = 4;
			this->buttonSpammerInstanceAdd->Text = L"+";
			this->buttonSpammerInstanceAdd->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->buttonSpammerInstanceAdd->UseVisualStyleBackColor = false;
			this->buttonSpammerInstanceAdd->Click += gcnew System::EventHandler(this, &Form1::buttonSpammerInstanceAdd_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->ForeColor = System::Drawing::Color::White;
			this->button3->Location = System::Drawing::Point(275, 31);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(27, 33);
			this->button3->TabIndex = 4;
			this->button3->Text = L"+";
			this->button3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// listBoxSpammerText
			// 
			this->listBoxSpammerText->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxSpammerText->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->listBoxSpammerText->ForeColor = System::Drawing::Color::White;
			this->listBoxSpammerText->FormattingEnabled = true;
			this->listBoxSpammerText->ItemHeight = 18;
			this->listBoxSpammerText->Location = System::Drawing::Point(275, 99);
			this->listBoxSpammerText->Name = L"listBoxSpammerText";
			this->listBoxSpammerText->Size = System::Drawing::Size(340, 238);
			this->listBoxSpammerText->TabIndex = 3;
			// 
			// checkBoxSpammerWindowsAll
			// 
			this->checkBoxSpammerWindowsAll->AutoSize = true;
			this->checkBoxSpammerWindowsAll->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxSpammerWindowsAll->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->checkBoxSpammerWindowsAll->ForeColor = System::Drawing::Color::White;
			this->checkBoxSpammerWindowsAll->Location = System::Drawing::Point(621, 32);
			this->checkBoxSpammerWindowsAll->Name = L"checkBoxSpammerWindowsAll";
			this->checkBoxSpammerWindowsAll->Size = System::Drawing::Size(83, 22);
			this->checkBoxSpammerWindowsAll->TabIndex = 2;
			this->checkBoxSpammerWindowsAll->Text = L"Select all";
			this->checkBoxSpammerWindowsAll->UseVisualStyleBackColor = false;
			this->checkBoxSpammerWindowsAll->Click += gcnew System::EventHandler(this, &Form1::checkBoxSpammerWindowsAll_Click);
			// 
			// checkedListBoxSpammerWindows
			// 
			this->checkedListBoxSpammerWindows->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->checkedListBoxSpammerWindows->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->checkedListBoxSpammerWindows->ForeColor = System::Drawing::Color::White;
			this->checkedListBoxSpammerWindows->FormattingEnabled = true;
			this->checkedListBoxSpammerWindows->Location = System::Drawing::Point(621, 59);
			this->checkedListBoxSpammerWindows->Name = L"checkedListBoxSpammerWindows";
			this->checkedListBoxSpammerWindows->Size = System::Drawing::Size(198, 274);
			this->checkedListBoxSpammerWindows->TabIndex = 0;
			this->checkedListBoxSpammerWindows->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &Form1::checkedListBoxSpammerWindows_ItemCheck);
			// 
			// tabAccounts
			// 
			this->tabAccounts->BackColor = System::Drawing::Color::Black;
			this->tabAccounts->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabAccounts.BackgroundImage")));
			this->tabAccounts->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabAccounts->Controls->Add(this->labelUnbannerTimer);
			this->tabAccounts->Controls->Add(this->panelAccountsEdit);
			this->tabAccounts->Controls->Add(this->buttonAccountsEdit);
			this->tabAccounts->Controls->Add(this->buttonAccountsAdd);
			this->tabAccounts->Controls->Add(this->buttonAccountsUnban);
			this->tabAccounts->Controls->Add(this->buttonAccountsDelete);
			this->tabAccounts->Controls->Add(this->buttonAccountsSet);
			this->tabAccounts->Controls->Add(this->textBoxAccountsCurrent);
			this->tabAccounts->Controls->Add(this->label4);
			this->tabAccounts->Controls->Add(this->listBoxAccounts);
			this->tabAccounts->Location = System::Drawing::Point(4, 44);
			this->tabAccounts->Name = L"tabAccounts";
			this->tabAccounts->Size = System::Drawing::Size(832, 344);
			this->tabAccounts->TabIndex = 8;
			this->tabAccounts->Text = L"Devices";
			// 
			// labelUnbannerTimer
			// 
			this->labelUnbannerTimer->AutoSize = true;
			this->labelUnbannerTimer->BackColor = System::Drawing::Color::Transparent;
			this->labelUnbannerTimer->ForeColor = System::Drawing::Color::White;
			this->labelUnbannerTimer->Location = System::Drawing::Point(621, 322);
			this->labelUnbannerTimer->Name = L"labelUnbannerTimer";
			this->labelUnbannerTimer->Size = System::Drawing::Size(0, 22);
			this->labelUnbannerTimer->TabIndex = 6;
			// 
			// panelAccountsEdit
			// 
			this->panelAccountsEdit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(24)),
				static_cast<System::Int32>(static_cast<System::Byte>(24)), static_cast<System::Int32>(static_cast<System::Byte>(28)));
			this->panelAccountsEdit->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelAccountsEdit->Controls->Add(this->buttonAccountEditRandom);
			this->panelAccountsEdit->Controls->Add(this->buttonAccountEditCANCEL);
			this->panelAccountsEdit->Controls->Add(this->buttonAccountEditOK);
			this->panelAccountsEdit->Controls->Add(this->label7);
			this->panelAccountsEdit->Controls->Add(this->label6);
			this->panelAccountsEdit->Controls->Add(this->labelAccountEdit);
			this->panelAccountsEdit->Controls->Add(this->textBoxAccountsCreateName);
			this->panelAccountsEdit->Controls->Add(this->textBoxAccountsCreateMAC);
			this->panelAccountsEdit->Location = System::Drawing::Point(106, 48);
			this->panelAccountsEdit->Name = L"panelAccountsEdit";
			this->panelAccountsEdit->Size = System::Drawing::Size(628, 232);
			this->panelAccountsEdit->TabIndex = 5;
			this->panelAccountsEdit->Visible = false;
			// 
			// buttonAccountEditRandom
			// 
			this->buttonAccountEditRandom->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountEditRandom->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountEditRandom->ForeColor = System::Drawing::Color::White;
			this->buttonAccountEditRandom->Location = System::Drawing::Point(244, 182);
			this->buttonAccountEditRandom->Name = L"buttonAccountEditRandom";
			this->buttonAccountEditRandom->Size = System::Drawing::Size(139, 31);
			this->buttonAccountEditRandom->TabIndex = 3;
			this->buttonAccountEditRandom->Text = L"RANDOM";
			this->buttonAccountEditRandom->UseVisualStyleBackColor = false;
			this->buttonAccountEditRandom->Click += gcnew System::EventHandler(this, &Form1::buttonAccountEditRandom_Click);
			// 
			// buttonAccountEditCANCEL
			// 
			this->buttonAccountEditCANCEL->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountEditCANCEL->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountEditCANCEL->ForeColor = System::Drawing::Color::White;
			this->buttonAccountEditCANCEL->Location = System::Drawing::Point(99, 182);
			this->buttonAccountEditCANCEL->Name = L"buttonAccountEditCANCEL";
			this->buttonAccountEditCANCEL->Size = System::Drawing::Size(139, 31);
			this->buttonAccountEditCANCEL->TabIndex = 3;
			this->buttonAccountEditCANCEL->Text = L"CANCEL";
			this->buttonAccountEditCANCEL->UseVisualStyleBackColor = false;
			this->buttonAccountEditCANCEL->Click += gcnew System::EventHandler(this, &Form1::buttonAccountEditCANCEL_Click);
			// 
			// buttonAccountEditOK
			// 
			this->buttonAccountEditOK->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountEditOK->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountEditOK->ForeColor = System::Drawing::Color::White;
			this->buttonAccountEditOK->Location = System::Drawing::Point(389, 182);
			this->buttonAccountEditOK->Name = L"buttonAccountEditOK";
			this->buttonAccountEditOK->Size = System::Drawing::Size(139, 31);
			this->buttonAccountEditOK->TabIndex = 3;
			this->buttonAccountEditOK->Text = L"OK";
			this->buttonAccountEditOK->UseVisualStyleBackColor = false;
			this->buttonAccountEditOK->Click += gcnew System::EventHandler(this, &Form1::buttonAccountEditOK_Click);
			// 
			// label7
			// 
			this->label7->ForeColor = System::Drawing::Color::White;
			this->label7->Location = System::Drawing::Point(3, 127);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(620, 20);
			this->label7->TabIndex = 2;
			this->label7->Text = L"MAC:";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->ForeColor = System::Drawing::Color::White;
			this->label6->Location = System::Drawing::Point(3, 56);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(620, 20);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Name (just a descriptor for you):";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelAccountEdit
			// 
			this->labelAccountEdit->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 14));
			this->labelAccountEdit->ForeColor = System::Drawing::Color::White;
			this->labelAccountEdit->Location = System::Drawing::Point(3, 12);
			this->labelAccountEdit->Name = L"labelAccountEdit";
			this->labelAccountEdit->Size = System::Drawing::Size(620, 35);
			this->labelAccountEdit->TabIndex = 1;
			this->labelAccountEdit->Text = L"Editting Device";
			this->labelAccountEdit->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// textBoxAccountsCreateName
			// 
			this->textBoxAccountsCreateName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxAccountsCreateName->ForeColor = System::Drawing::Color::White;
			this->textBoxAccountsCreateName->Location = System::Drawing::Point(33, 79);
			this->textBoxAccountsCreateName->Name = L"textBoxAccountsCreateName";
			this->textBoxAccountsCreateName->Size = System::Drawing::Size(560, 26);
			this->textBoxAccountsCreateName->TabIndex = 0;
			this->textBoxAccountsCreateName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBoxAccountsCreateMAC
			// 
			this->textBoxAccountsCreateMAC->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxAccountsCreateMAC->ForeColor = System::Drawing::Color::White;
			this->textBoxAccountsCreateMAC->Location = System::Drawing::Point(33, 150);
			this->textBoxAccountsCreateMAC->Name = L"textBoxAccountsCreateMAC";
			this->textBoxAccountsCreateMAC->Size = System::Drawing::Size(560, 26);
			this->textBoxAccountsCreateMAC->TabIndex = 0;
			this->textBoxAccountsCreateMAC->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// buttonAccountsEdit
			// 
			this->buttonAccountsEdit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountsEdit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountsEdit->ForeColor = System::Drawing::Color::White;
			this->buttonAccountsEdit->Location = System::Drawing::Point(8, 208);
			this->buttonAccountsEdit->Name = L"buttonAccountsEdit";
			this->buttonAccountsEdit->Size = System::Drawing::Size(164, 33);
			this->buttonAccountsEdit->TabIndex = 4;
			this->buttonAccountsEdit->Text = L"EDIT";
			this->buttonAccountsEdit->UseVisualStyleBackColor = false;
			this->buttonAccountsEdit->Click += gcnew System::EventHandler(this, &Form1::buttonAccountsEdit_Click);
			// 
			// buttonAccountsAdd
			// 
			this->buttonAccountsAdd->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountsAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountsAdd->ForeColor = System::Drawing::Color::White;
			this->buttonAccountsAdd->Location = System::Drawing::Point(8, 247);
			this->buttonAccountsAdd->Name = L"buttonAccountsAdd";
			this->buttonAccountsAdd->Size = System::Drawing::Size(164, 33);
			this->buttonAccountsAdd->TabIndex = 4;
			this->buttonAccountsAdd->Text = L"ADD";
			this->buttonAccountsAdd->UseVisualStyleBackColor = false;
			this->buttonAccountsAdd->Click += gcnew System::EventHandler(this, &Form1::buttonAccountsAdd_Click);
			// 
			// buttonAccountsUnban
			// 
			this->buttonAccountsUnban->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountsUnban->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountsUnban->ForeColor = System::Drawing::Color::White;
			this->buttonAccountsUnban->Location = System::Drawing::Point(621, 286);
			this->buttonAccountsUnban->Name = L"buttonAccountsUnban";
			this->buttonAccountsUnban->Size = System::Drawing::Size(164, 33);
			this->buttonAccountsUnban->TabIndex = 4;
			this->buttonAccountsUnban->Text = L"UNBAN";
			this->buttonAccountsUnban->UseVisualStyleBackColor = false;
			this->buttonAccountsUnban->Click += gcnew System::EventHandler(this, &Form1::buttonAccountsUnban_Click);
			// 
			// buttonAccountsDelete
			// 
			this->buttonAccountsDelete->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountsDelete->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountsDelete->ForeColor = System::Drawing::Color::White;
			this->buttonAccountsDelete->Location = System::Drawing::Point(8, 286);
			this->buttonAccountsDelete->Name = L"buttonAccountsDelete";
			this->buttonAccountsDelete->Size = System::Drawing::Size(164, 33);
			this->buttonAccountsDelete->TabIndex = 4;
			this->buttonAccountsDelete->Text = L"DELETE";
			this->buttonAccountsDelete->UseVisualStyleBackColor = false;
			this->buttonAccountsDelete->Click += gcnew System::EventHandler(this, &Form1::buttonAccountsDelete_Click);
			// 
			// buttonAccountsSet
			// 
			this->buttonAccountsSet->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonAccountsSet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonAccountsSet->ForeColor = System::Drawing::Color::White;
			this->buttonAccountsSet->Location = System::Drawing::Point(8, 9);
			this->buttonAccountsSet->Name = L"buttonAccountsSet";
			this->buttonAccountsSet->Size = System::Drawing::Size(164, 33);
			this->buttonAccountsSet->TabIndex = 4;
			this->buttonAccountsSet->Text = L"SET";
			this->buttonAccountsSet->UseVisualStyleBackColor = false;
			this->buttonAccountsSet->Click += gcnew System::EventHandler(this, &Form1::buttonAccountsSet_Click);
			// 
			// textBoxAccountsCurrent
			// 
			this->textBoxAccountsCurrent->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxAccountsCurrent->ForeColor = System::Drawing::Color::White;
			this->textBoxAccountsCurrent->Location = System::Drawing::Point(574, 30);
			this->textBoxAccountsCurrent->Name = L"textBoxAccountsCurrent";
			this->textBoxAccountsCurrent->ReadOnly = true;
			this->textBoxAccountsCurrent->Size = System::Drawing::Size(245, 26);
			this->textBoxAccountsCurrent->TabIndex = 2;
			this->textBoxAccountsCurrent->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(574, 9);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(107, 18);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Current device:";
			// 
			// listBoxAccounts
			// 
			this->listBoxAccounts->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxAccounts->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->listBoxAccounts->ForeColor = System::Drawing::Color::White;
			this->listBoxAccounts->ItemHeight = 18;
			this->listBoxAccounts->Location = System::Drawing::Point(178, 9);
			this->listBoxAccounts->Name = L"listBoxAccounts";
			this->listBoxAccounts->Size = System::Drawing::Size(390, 310);
			this->listBoxAccounts->TabIndex = 0;
			// 
			// tabWindows
			// 
			this->tabWindows->BackColor = System::Drawing::Color::Black;
			this->tabWindows->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabWindows.BackgroundImage")));
			this->tabWindows->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabWindows->Controls->Add(this->checkBoxWindowsMB);
			this->tabWindows->Controls->Add(this->checkBoxWindowsMBAll);
			this->tabWindows->Controls->Add(this->buttonWindowsCaptchaSolve);
			this->tabWindows->Controls->Add(this->buttonWindowsSH);
			this->tabWindows->Controls->Add(this->buttonWindowsBTF);
			this->tabWindows->Controls->Add(this->buttonWindowsClose);
			this->tabWindows->Controls->Add(this->buttonWindowsOpen);
			this->tabWindows->Controls->Add(this->listBoxWindows);
			this->tabWindows->Location = System::Drawing::Point(4, 44);
			this->tabWindows->Name = L"tabWindows";
			this->tabWindows->Padding = System::Windows::Forms::Padding(3);
			this->tabWindows->Size = System::Drawing::Size(832, 344);
			this->tabWindows->TabIndex = 1;
			this->tabWindows->Text = L"Windows";
			// 
			// checkBoxWindowsMB
			// 
			this->checkBoxWindowsMB->AutoSize = true;
			this->checkBoxWindowsMB->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxWindowsMB->ForeColor = System::Drawing::Color::White;
			this->checkBoxWindowsMB->Location = System::Drawing::Point(6, 192);
			this->checkBoxWindowsMB->Name = L"checkBoxWindowsMB";
			this->checkBoxWindowsMB->Size = System::Drawing::Size(110, 26);
			this->checkBoxWindowsMB->TabIndex = 2;
			this->checkBoxWindowsMB->Text = L"MultiBoxing";
			this->checkBoxWindowsMB->UseVisualStyleBackColor = false;
			this->checkBoxWindowsMB->Click += gcnew System::EventHandler(this, &Form1::checkBoxWindowsMB_Click);
			// 
			// checkBoxWindowsMBAll
			// 
			this->checkBoxWindowsMBAll->AutoSize = true;
			this->checkBoxWindowsMBAll->BackColor = System::Drawing::Color::Transparent;
			this->checkBoxWindowsMBAll->ForeColor = System::Drawing::Color::White;
			this->checkBoxWindowsMBAll->Location = System::Drawing::Point(122, 192);
			this->checkBoxWindowsMBAll->Name = L"checkBoxWindowsMBAll";
			this->checkBoxWindowsMBAll->Size = System::Drawing::Size(46, 26);
			this->checkBoxWindowsMBAll->TabIndex = 2;
			this->checkBoxWindowsMBAll->Text = L"All";
			this->checkBoxWindowsMBAll->UseVisualStyleBackColor = false;
			this->checkBoxWindowsMBAll->Click += gcnew System::EventHandler(this, &Form1::checkBoxWindowsMB_Click_1);
			// 
			// buttonWindowsCaptchaSolve
			// 
			this->buttonWindowsCaptchaSolve->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonWindowsCaptchaSolve->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonWindowsCaptchaSolve->ForeColor = System::Drawing::Color::White;
			this->buttonWindowsCaptchaSolve->Location = System::Drawing::Point(8, 301);
			this->buttonWindowsCaptchaSolve->Name = L"buttonWindowsCaptchaSolve";
			this->buttonWindowsCaptchaSolve->Size = System::Drawing::Size(164, 33);
			this->buttonWindowsCaptchaSolve->TabIndex = 1;
			this->buttonWindowsCaptchaSolve->Text = L"SOLVE CAPTCHA";
			this->buttonWindowsCaptchaSolve->UseVisualStyleBackColor = false;
			this->buttonWindowsCaptchaSolve->Click += gcnew System::EventHandler(this, &Form1::buttonWindowsCaptchaSolve_Click);
			// 
			// buttonWindowsSH
			// 
			this->buttonWindowsSH->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonWindowsSH->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonWindowsSH->ForeColor = System::Drawing::Color::White;
			this->buttonWindowsSH->Location = System::Drawing::Point(8, 141);
			this->buttonWindowsSH->Name = L"buttonWindowsSH";
			this->buttonWindowsSH->Size = System::Drawing::Size(164, 33);
			this->buttonWindowsSH->TabIndex = 1;
			this->buttonWindowsSH->Text = L"SHOW / HIDE";
			this->buttonWindowsSH->UseVisualStyleBackColor = false;
			this->buttonWindowsSH->Click += gcnew System::EventHandler(this, &Form1::buttonWindowsSH_Click);
			// 
			// buttonWindowsBTF
			// 
			this->buttonWindowsBTF->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonWindowsBTF->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonWindowsBTF->ForeColor = System::Drawing::Color::White;
			this->buttonWindowsBTF->Location = System::Drawing::Point(8, 102);
			this->buttonWindowsBTF->Name = L"buttonWindowsBTF";
			this->buttonWindowsBTF->Size = System::Drawing::Size(164, 33);
			this->buttonWindowsBTF->TabIndex = 1;
			this->buttonWindowsBTF->Text = L"BRING TO FRONT";
			this->buttonWindowsBTF->UseVisualStyleBackColor = false;
			this->buttonWindowsBTF->Click += gcnew System::EventHandler(this, &Form1::buttonWindowsBTF_Click);
			// 
			// buttonWindowsClose
			// 
			this->buttonWindowsClose->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonWindowsClose->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonWindowsClose->ForeColor = System::Drawing::Color::White;
			this->buttonWindowsClose->Location = System::Drawing::Point(8, 63);
			this->buttonWindowsClose->Name = L"buttonWindowsClose";
			this->buttonWindowsClose->Size = System::Drawing::Size(164, 33);
			this->buttonWindowsClose->TabIndex = 1;
			this->buttonWindowsClose->Text = L"CLOSE";
			this->buttonWindowsClose->UseVisualStyleBackColor = false;
			this->buttonWindowsClose->Click += gcnew System::EventHandler(this, &Form1::buttonWindowsClose_Click);
			// 
			// buttonWindowsOpen
			// 
			this->buttonWindowsOpen->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonWindowsOpen->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonWindowsOpen->ForeColor = System::Drawing::Color::White;
			this->buttonWindowsOpen->Location = System::Drawing::Point(8, 24);
			this->buttonWindowsOpen->Name = L"buttonWindowsOpen";
			this->buttonWindowsOpen->Size = System::Drawing::Size(164, 33);
			this->buttonWindowsOpen->TabIndex = 1;
			this->buttonWindowsOpen->Text = L"OPEN";
			this->buttonWindowsOpen->UseVisualStyleBackColor = false;
			this->buttonWindowsOpen->Click += gcnew System::EventHandler(this, &Form1::buttonWindowsOpen_Click);
			// 
			// listBoxWindows
			// 
			this->listBoxWindows->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxWindows->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->listBoxWindows->ForeColor = System::Drawing::Color::White;
			this->listBoxWindows->FormattingEnabled = true;
			this->listBoxWindows->ItemHeight = 18;
			this->listBoxWindows->Location = System::Drawing::Point(178, 24);
			this->listBoxWindows->Name = L"listBoxWindows";
			this->listBoxWindows->Size = System::Drawing::Size(641, 310);
			this->listBoxWindows->TabIndex = 0;
			this->listBoxWindows->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::listBoxWindows_SelectedIndexChanged);
			// 
			// tabMain
			// 
			this->tabMain->BackColor = System::Drawing::Color::Black;
			this->tabMain->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabMain.BackgroundImage")));
			this->tabMain->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabMain->Controls->Add(this->panelLoginForm);
			this->tabMain->Controls->Add(this->labelMainVersionLatest);
			this->tabMain->Controls->Add(this->labelLoginError);
			this->tabMain->Controls->Add(this->buttonLoginALOGOUT);
			this->tabMain->Controls->Add(this->labelServerState2);
			this->tabMain->Controls->Add(this->labelMainVersion);
			this->tabMain->Controls->Add(this->buttonLinkYT);
			this->tabMain->Controls->Add(this->buttonLinkDiscord);
			this->tabMain->Controls->Add(this->label5);
			this->tabMain->Controls->Add(this->labelLoginAName);
			this->tabMain->Controls->Add(this->label13);
			this->tabMain->Controls->Add(this->labelLoginAType);
			this->tabMain->Controls->Add(this->label12);
			this->tabMain->Controls->Add(this->labelLoginAExp);
			this->tabMain->ForeColor = System::Drawing::SystemColors::ControlText;
			this->tabMain->Location = System::Drawing::Point(4, 44);
			this->tabMain->Name = L"tabMain";
			this->tabMain->Padding = System::Windows::Forms::Padding(3);
			this->tabMain->Size = System::Drawing::Size(832, 344);
			this->tabMain->TabIndex = 0;
			this->tabMain->Text = L"Main";
			// 
			// panelLoginForm
			// 
			this->panelLoginForm->BackColor = System::Drawing::Color::Transparent;
			this->panelLoginForm->Controls->Add(this->label2);
			this->panelLoginForm->Controls->Add(this->textBoxLoginName);
			this->panelLoginForm->Controls->Add(this->label3);
			this->panelLoginForm->Controls->Add(this->buttonLoginOk);
			this->panelLoginForm->Controls->Add(this->textBoxLoginPass);
			this->panelLoginForm->Location = System::Drawing::Point(9, 112);
			this->panelLoginForm->Name = L"panelLoginForm";
			this->panelLoginForm->Size = System::Drawing::Size(812, 168);
			this->panelLoginForm->TabIndex = 8;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->ForeColor = System::Drawing::Color::White;
			this->label2->Location = System::Drawing::Point(95, 9);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(54, 22);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Login:";
			// 
			// textBoxLoginName
			// 
			this->textBoxLoginName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxLoginName->ForeColor = System::Drawing::Color::White;
			this->textBoxLoginName->Location = System::Drawing::Point(138, 34);
			this->textBoxLoginName->MaxLength = 20;
			this->textBoxLoginName->Name = L"textBoxLoginName";
			this->textBoxLoginName->Size = System::Drawing::Size(530, 26);
			this->textBoxLoginName->TabIndex = 4;
			this->textBoxLoginName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(95, 66);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(81, 22);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Password:";
			// 
			// buttonLoginOk
			// 
			this->buttonLoginOk->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonLoginOk->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonLoginOk->ForeColor = System::Drawing::Color::White;
			this->buttonLoginOk->Location = System::Drawing::Point(324, 123);
			this->buttonLoginOk->Name = L"buttonLoginOk";
			this->buttonLoginOk->Size = System::Drawing::Size(156, 30);
			this->buttonLoginOk->TabIndex = 6;
			this->buttonLoginOk->Text = L"OK";
			this->buttonLoginOk->UseVisualStyleBackColor = false;
			this->buttonLoginOk->Click += gcnew System::EventHandler(this, &Form1::buttonLoginOk_Click);
			// 
			// textBoxLoginPass
			// 
			this->textBoxLoginPass->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBoxLoginPass->ForeColor = System::Drawing::Color::White;
			this->textBoxLoginPass->Location = System::Drawing::Point(138, 91);
			this->textBoxLoginPass->MaxLength = 30;
			this->textBoxLoginPass->Name = L"textBoxLoginPass";
			this->textBoxLoginPass->Size = System::Drawing::Size(530, 26);
			this->textBoxLoginPass->TabIndex = 5;
			this->textBoxLoginPass->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->textBoxLoginPass->UseSystemPasswordChar = true;
			// 
			// labelMainVersionLatest
			// 
			this->labelMainVersionLatest->AutoSize = true;
			this->labelMainVersionLatest->BackColor = System::Drawing::Color::Transparent;
			this->labelMainVersionLatest->ForeColor = System::Drawing::Color::White;
			this->labelMainVersionLatest->Location = System::Drawing::Point(8, 28);
			this->labelMainVersionLatest->Name = L"labelMainVersionLatest";
			this->labelMainVersionLatest->Size = System::Drawing::Size(139, 22);
			this->labelMainVersionLatest->TabIndex = 7;
			this->labelMainVersionLatest->Text = L"Latest: UNKNOWN";
			// 
			// labelLoginError
			// 
			this->labelLoginError->BackColor = System::Drawing::Color::Transparent;
			this->labelLoginError->ForeColor = System::Drawing::Color::Chartreuse;
			this->labelLoginError->Location = System::Drawing::Point(8, 283);
			this->labelLoginError->Name = L"labelLoginError";
			this->labelLoginError->Size = System::Drawing::Size(813, 54);
			this->labelLoginError->TabIndex = 6;
			this->labelLoginError->Text = L"Type login and password to new account\r\nif you don\'t have one yet.";
			this->labelLoginError->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// buttonLoginALOGOUT
			// 
			this->buttonLoginALOGOUT->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonLoginALOGOUT->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonLoginALOGOUT->ForeColor = System::Drawing::Color::White;
			this->buttonLoginALOGOUT->Location = System::Drawing::Point(336, 210);
			this->buttonLoginALOGOUT->Name = L"buttonLoginALOGOUT";
			this->buttonLoginALOGOUT->Size = System::Drawing::Size(156, 30);
			this->buttonLoginALOGOUT->TabIndex = 6;
			this->buttonLoginALOGOUT->Text = L"LOG OUT";
			this->buttonLoginALOGOUT->UseVisualStyleBackColor = false;
			this->buttonLoginALOGOUT->Click += gcnew System::EventHandler(this, &Form1::buttonLoginALOGOUT_Click);
			// 
			// labelServerState2
			// 
			this->labelServerState2->AutoSize = true;
			this->labelServerState2->BackColor = System::Drawing::Color::Transparent;
			this->labelServerState2->ForeColor = System::Drawing::Color::White;
			this->labelServerState2->Location = System::Drawing::Point(8, 50);
			this->labelServerState2->Name = L"labelServerState2";
			this->labelServerState2->Size = System::Drawing::Size(153, 22);
			this->labelServerState2->TabIndex = 2;
			this->labelServerState2->Text = L"Servers: Connecting";
			// 
			// labelMainVersion
			// 
			this->labelMainVersion->AutoSize = true;
			this->labelMainVersion->BackColor = System::Drawing::Color::Transparent;
			this->labelMainVersion->ForeColor = System::Drawing::Color::White;
			this->labelMainVersion->Location = System::Drawing::Point(8, 6);
			this->labelMainVersion->Name = L"labelMainVersion";
			this->labelMainVersion->Size = System::Drawing::Size(108, 22);
			this->labelMainVersion->TabIndex = 2;
			this->labelMainVersion->Text = L"Version: 0.0.0";
			// 
			// buttonLinkYT
			// 
			this->buttonLinkYT->BackColor = System::Drawing::Color::Transparent;
			this->buttonLinkYT->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonLinkYT.BackgroundImage")));
			this->buttonLinkYT->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->buttonLinkYT->Cursor = System::Windows::Forms::Cursors::Default;
			this->buttonLinkYT->FlatAppearance->BorderSize = 0;
			this->buttonLinkYT->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonLinkYT->Location = System::Drawing::Point(751, 6);
			this->buttonLinkYT->Name = L"buttonLinkYT";
			this->buttonLinkYT->Size = System::Drawing::Size(68, 68);
			this->buttonLinkYT->TabIndex = 0;
			this->buttonLinkYT->UseVisualStyleBackColor = false;
			this->buttonLinkYT->Click += gcnew System::EventHandler(this, &Form1::buttonLinkYT_Click);
			// 
			// buttonLinkDiscord
			// 
			this->buttonLinkDiscord->BackColor = System::Drawing::Color::Transparent;
			this->buttonLinkDiscord->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"buttonLinkDiscord.BackgroundImage")));
			this->buttonLinkDiscord->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->buttonLinkDiscord->Cursor = System::Windows::Forms::Cursors::Default;
			this->buttonLinkDiscord->FlatAppearance->BorderSize = 0;
			this->buttonLinkDiscord->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonLinkDiscord->Location = System::Drawing::Point(677, 6);
			this->buttonLinkDiscord->Name = L"buttonLinkDiscord";
			this->buttonLinkDiscord->Size = System::Drawing::Size(68, 68);
			this->buttonLinkDiscord->TabIndex = 0;
			this->buttonLinkDiscord->UseVisualStyleBackColor = false;
			this->buttonLinkDiscord->Click += gcnew System::EventHandler(this, &Form1::buttonLinkDiscord_Click);
			// 
			// label5
			// 
			this->label5->BackColor = System::Drawing::Color::Transparent;
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(64, 133);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(109, 22);
			this->label5->TabIndex = 9;
			this->label5->Text = L"Logged in as: ";
			this->label5->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// labelLoginAName
			// 
			this->labelLoginAName->AutoSize = true;
			this->labelLoginAName->BackColor = System::Drawing::Color::Transparent;
			this->labelLoginAName->ForeColor = System::Drawing::Color::GreenYellow;
			this->labelLoginAName->Location = System::Drawing::Point(174, 133);
			this->labelLoginAName->Name = L"labelLoginAName";
			this->labelLoginAName->Size = System::Drawing::Size(16, 22);
			this->labelLoginAName->TabIndex = 9;
			this->labelLoginAName->Text = L"-";
			// 
			// label13
			// 
			this->label13->BackColor = System::Drawing::Color::Transparent;
			this->label13->ForeColor = System::Drawing::Color::White;
			this->label13->Location = System::Drawing::Point(59, 155);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(114, 22);
			this->label13->TabIndex = 9;
			this->label13->Text = L"Account type: ";
			this->label13->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// labelLoginAType
			// 
			this->labelLoginAType->AutoSize = true;
			this->labelLoginAType->BackColor = System::Drawing::Color::Transparent;
			this->labelLoginAType->ForeColor = System::Drawing::Color::GreenYellow;
			this->labelLoginAType->Location = System::Drawing::Point(174, 155);
			this->labelLoginAType->Name = L"labelLoginAType";
			this->labelLoginAType->Size = System::Drawing::Size(16, 22);
			this->labelLoginAType->TabIndex = 9;
			this->labelLoginAType->Text = L"-";
			// 
			// label12
			// 
			this->label12->BackColor = System::Drawing::Color::Transparent;
			this->label12->ForeColor = System::Drawing::Color::White;
			this->label12->Location = System::Drawing::Point(69, 177);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(99, 22);
			this->label12->TabIndex = 9;
			this->label12->Text = L"Expire date: ";
			this->label12->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// labelLoginAExp
			// 
			this->labelLoginAExp->AutoSize = true;
			this->labelLoginAExp->BackColor = System::Drawing::Color::Transparent;
			this->labelLoginAExp->ForeColor = System::Drawing::Color::GreenYellow;
			this->labelLoginAExp->Location = System::Drawing::Point(174, 177);
			this->labelLoginAExp->Name = L"labelLoginAExp";
			this->labelLoginAExp->Size = System::Drawing::Size(16, 22);
			this->labelLoginAExp->TabIndex = 9;
			this->labelLoginAExp->Text = L"-";
			// 
			// tabControl1
			// 
			this->tabControl1->AllowDrop = true;
			this->tabControl1->Controls->Add(this->tabMain);
			this->tabControl1->Controls->Add(this->tabWindows);
			this->tabControl1->Controls->Add(this->tabAccounts);
			this->tabControl1->Controls->Add(this->tabSpammer);
			this->tabControl1->Controls->Add(this->tabMacro);
			this->tabControl1->Controls->Add(this->tabDecoder);
			this->tabControl1->Controls->Add(this->tabLogs);
			this->tabControl1->Controls->Add(this->tabSettings);
			this->tabControl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->tabControl1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->tabControl1->ItemSize = System::Drawing::Size(90, 40);
			this->tabControl1->Location = System::Drawing::Point(0, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(840, 392);
			this->tabControl1->SizeMode = System::Windows::Forms::TabSizeMode::Fixed;
			this->tabControl1->TabIndex = 3;
			this->tabControl1->Selecting += gcnew System::Windows::Forms::TabControlCancelEventHandler(this, &Form1::tabControl1_Selecting);
			// 
			// tabMacro
			// 
			this->tabMacro->BackColor = System::Drawing::Color::Black;
			this->tabMacro->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tabMacro.BackgroundImage")));
			this->tabMacro->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->tabMacro->Controls->Add(this->checkBox3);
			this->tabMacro->Controls->Add(this->checkBox2);
			this->tabMacro->Controls->Add(this->textBox6);
			this->tabMacro->Controls->Add(this->textBox5);
			this->tabMacro->Controls->Add(this->label21);
			this->tabMacro->Controls->Add(this->checkBox1);
			this->tabMacro->Controls->Add(this->checkedListBox1);
			this->tabMacro->Controls->Add(this->label20);
			this->tabMacro->Controls->Add(this->buttonMacroBrowse);
			this->tabMacro->Controls->Add(this->buttonMacroInstanceRm);
			this->tabMacro->Controls->Add(this->buttonMacroInstanceAdd);
			this->tabMacro->Controls->Add(this->listBoxMacroInstanceVariables);
			this->tabMacro->Controls->Add(this->listBoxMacroInstances);
			this->tabMacro->Location = System::Drawing::Point(4, 44);
			this->tabMacro->Name = L"tabMacro";
			this->tabMacro->Padding = System::Windows::Forms::Padding(3);
			this->tabMacro->Size = System::Drawing::Size(832, 344);
			this->tabMacro->TabIndex = 9;
			this->tabMacro->Text = L"Macro";
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->BackColor = System::Drawing::Color::Transparent;
			this->checkBox3->ForeColor = System::Drawing::Color::White;
			this->checkBox3->Location = System::Drawing::Point(430, 264);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(85, 26);
			this->checkBox3->TabIndex = 12;
			this->checkBox3->Text = L"Enabled";
			this->checkBox3->UseVisualStyleBackColor = false;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->BackColor = System::Drawing::Color::Transparent;
			this->checkBox2->ForeColor = System::Drawing::Color::White;
			this->checkBox2->Location = System::Drawing::Point(430, 300);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(78, 26);
			this->checkBox2->TabIndex = 12;
			this->checkBox2->Text = L"Repeat";
			this->checkBox2->UseVisualStyleBackColor = false;
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->textBox6->ForeColor = System::Drawing::Color::White;
			this->textBox6->Location = System::Drawing::Point(248, 303);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(176, 23);
			this->textBox6->TabIndex = 11;
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->textBox5->ForeColor = System::Drawing::Color::White;
			this->textBox5->Location = System::Drawing::Point(74, 36);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(458, 23);
			this->textBox5->TabIndex = 11;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->BackColor = System::Drawing::Color::Transparent;
			this->label21->ForeColor = System::Drawing::Color::White;
			this->label21->Location = System::Drawing::Point(617, 6);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(144, 22);
			this->label21->TabIndex = 10;
			this->label21->Text = L"Assigned windows:";
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->BackColor = System::Drawing::Color::Transparent;
			this->checkBox1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->checkBox1->ForeColor = System::Drawing::Color::White;
			this->checkBox1->Location = System::Drawing::Point(621, 32);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(83, 22);
			this->checkBox1->TabIndex = 9;
			this->checkBox1->Text = L"Select all";
			this->checkBox1->UseVisualStyleBackColor = false;
			// 
			// checkedListBox1
			// 
			this->checkedListBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->checkedListBox1->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->checkedListBox1->ForeColor = System::Drawing::Color::White;
			this->checkedListBox1->FormattingEnabled = true;
			this->checkedListBox1->Location = System::Drawing::Point(621, 59);
			this->checkedListBox1->Name = L"checkedListBox1";
			this->checkedListBox1->Size = System::Drawing::Size(198, 274);
			this->checkedListBox1->TabIndex = 8;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->BackColor = System::Drawing::Color::Transparent;
			this->label20->ForeColor = System::Drawing::Color::White;
			this->label20->Location = System::Drawing::Point(4, 6);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(126, 22);
			this->label20->TabIndex = 7;
			this->label20->Text = L"Macro Instances:";
			// 
			// buttonMacroBrowse
			// 
			this->buttonMacroBrowse->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonMacroBrowse->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonMacroBrowse->ForeColor = System::Drawing::Color::White;
			this->buttonMacroBrowse->Location = System::Drawing::Point(538, 31);
			this->buttonMacroBrowse->Name = L"buttonMacroBrowse";
			this->buttonMacroBrowse->Size = System::Drawing::Size(77, 33);
			this->buttonMacroBrowse->TabIndex = 5;
			this->buttonMacroBrowse->Text = L"Browse";
			this->buttonMacroBrowse->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->buttonMacroBrowse->UseVisualStyleBackColor = false;
			// 
			// buttonMacroInstanceRm
			// 
			this->buttonMacroInstanceRm->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonMacroInstanceRm->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonMacroInstanceRm->ForeColor = System::Drawing::Color::White;
			this->buttonMacroInstanceRm->Location = System::Drawing::Point(41, 31);
			this->buttonMacroInstanceRm->Name = L"buttonMacroInstanceRm";
			this->buttonMacroInstanceRm->Size = System::Drawing::Size(27, 33);
			this->buttonMacroInstanceRm->TabIndex = 5;
			this->buttonMacroInstanceRm->Text = L"-";
			this->buttonMacroInstanceRm->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->buttonMacroInstanceRm->UseVisualStyleBackColor = false;
			// 
			// buttonMacroInstanceAdd
			// 
			this->buttonMacroInstanceAdd->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->buttonMacroInstanceAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->buttonMacroInstanceAdd->ForeColor = System::Drawing::Color::White;
			this->buttonMacroInstanceAdd->Location = System::Drawing::Point(8, 31);
			this->buttonMacroInstanceAdd->Name = L"buttonMacroInstanceAdd";
			this->buttonMacroInstanceAdd->Size = System::Drawing::Size(27, 33);
			this->buttonMacroInstanceAdd->TabIndex = 6;
			this->buttonMacroInstanceAdd->Text = L"+";
			this->buttonMacroInstanceAdd->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->buttonMacroInstanceAdd->UseVisualStyleBackColor = false;
			// 
			// listBoxMacroInstanceVariables
			// 
			this->listBoxMacroInstanceVariables->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxMacroInstanceVariables->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->listBoxMacroInstanceVariables->ForeColor = System::Drawing::Color::White;
			this->listBoxMacroInstanceVariables->FormattingEnabled = true;
			this->listBoxMacroInstanceVariables->ItemHeight = 18;
			this->listBoxMacroInstanceVariables->Location = System::Drawing::Point(248, 70);
			this->listBoxMacroInstanceVariables->Name = L"listBoxMacroInstanceVariables";
			this->listBoxMacroInstanceVariables->Size = System::Drawing::Size(176, 220);
			this->listBoxMacroInstanceVariables->TabIndex = 0;
			// 
			// listBoxMacroInstances
			// 
			this->listBoxMacroInstances->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(36)), static_cast<System::Int32>(static_cast<System::Byte>(36)));
			this->listBoxMacroInstances->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 10));
			this->listBoxMacroInstances->ForeColor = System::Drawing::Color::White;
			this->listBoxMacroInstances->FormattingEnabled = true;
			this->listBoxMacroInstances->ItemHeight = 18;
			this->listBoxMacroInstances->Location = System::Drawing::Point(8, 70);
			this->listBoxMacroInstances->Name = L"listBoxMacroInstances";
			this->listBoxMacroInstances->Size = System::Drawing::Size(234, 256);
			this->listBoxMacroInstances->TabIndex = 0;
			// 
			// Form1
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(24)), static_cast<System::Int32>(static_cast<System::Byte>(24)),
				static_cast<System::Int32>(static_cast<System::Byte>(28)));
			this->ClientSize = System::Drawing::Size(840, 423);
			this->Controls->Add(this->tabControl1);
			this->Controls->Add(this->Footer);
			this->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Opacity = 0.97;
			this->Text = L"GABB";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Footer->ResumeLayout(false);
			this->Footer->PerformLayout();
			this->panelServerAcc->ResumeLayout(false);
			this->panelServerAcc->PerformLayout();
			this->tabSettings->ResumeLayout(false);
			this->tabSettings->PerformLayout();
			this->tabLogs->ResumeLayout(false);
			this->tabLogs->PerformLayout();
			this->tabDecoder->ResumeLayout(false);
			this->tabDecoder->PerformLayout();
			this->tabSpammer->ResumeLayout(false);
			this->tabSpammer->PerformLayout();
			this->tabAccounts->ResumeLayout(false);
			this->tabAccounts->PerformLayout();
			this->panelAccountsEdit->ResumeLayout(false);
			this->panelAccountsEdit->PerformLayout();
			this->tabWindows->ResumeLayout(false);
			this->tabWindows->PerformLayout();
			this->tabMain->ResumeLayout(false);
			this->tabMain->PerformLayout();
			this->panelLoginForm->ResumeLayout(false);
			this->panelLoginForm->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabMacro->ResumeLayout(false);
			this->tabMacro->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	msclr::interop::marshal_context context;
	private: System::Void SetImage(int id) {
		Image ^ img;
		switch (id) {
		default: img = this->panel1->BackgroundImage; break;
		case 1: img = this->panel2->BackgroundImage; break;
		case 2: img = this->panel3->BackgroundImage;
		}
		this->tabMain->BackgroundImage = img;
		this->tabWindows->BackgroundImage = img;
		this->tabAccounts->BackgroundImage = img;
		this->tabSpammer->BackgroundImage = img;
		this->tabDecoder->BackgroundImage = img; 
		this->tabMacro->BackgroundImage = img;
		this->tabSettings->BackgroundImage = img; 
		GABBE::SetTheme(id);
	}

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		GABBE::Init();
		std::fstream ifs("bckg.jpg", std::ios::in);
		if (ifs.good()) {
			Image ^ img = Image::FromFile("bckg.jpg");
			this->panel3->BackgroundImage = img;
			ifs.close();
		}
		SetImage(GABBE::GetTheme());
		RefreshDevices();
	}

	private: void cout(String^ ctx) {
		System::DateTime^ now = System::DateTime::Now;
		this->Logs->AppendText("[" + now->Hour + ":" + now->Minute + ":" + now->Second + "]: " + ctx + "\r\n");
		
	}

	private: void SaveDecode(String^ ctx) {
		this->listBoxSaveTitle->Items->Clear();
		this->listBoxSaveContent->Items->Clear();
		this->textBoxSavePath->Text = ctx;
		savePath = context.marshal_as<std::wstring>(ctx);
		saveData = GABBE::decodeFile(context.marshal_as<std::wstring>(ctx));

		for (unsigned int i = 0; i < saveData.size(); i++) {
			this->listBoxSaveTitle->Items->Add(gcnew String(saveData[i].first.c_str()));
		}
	}
			 
	private: void RefreshWindows() { //std::vector<std::pair<int, std::vector<std::string>>>
		spammerRefreshing = true;
		windowData = GABBE::GetWindows();
		this->listBoxWindows->Items->Clear();
		this->checkedListBoxSpammerWindows->Items->Clear();
		std::string buffer;
		bool allSelected = true;
		for (unsigned int i = 0; i < windowData.size(); i++) {
			buffer = "[" + std::to_string(windowData[i].first) + "]: ";
			for (unsigned int j = 0; j < windowData[i].second.size(); j++) {
				buffer += windowData[i].second[j] + (j != windowData[i].second.size() - 1 ? ", " : "");
				if (j == 0) this->checkedListBoxSpammerWindows->Items->Add(gcnew String(buffer.substr(0, buffer.length() - 2).c_str()));
			}
			this->listBoxWindows->Items->Add(gcnew String(buffer.c_str()));
			if (windowData[i].second.size() >= 4 && windowData[i].second[3] != "MB ON") allSelected = false;
		}
		this->checkBoxWindowsMBAll->Checked = allSelected;

		for (int i = 0; i < this->checkedListBoxSpammerWindows->Items->Count && i < (int)windowData.size(); i++) {
			for (unsigned int j = 0; j < spammerTargets.size(); j++) {
				if (windowData[i].first == spammerTargets[j]) {
					this->checkedListBoxSpammerWindows->SetItemChecked(i, 1);
					break;
				}
			}
		}
		spammerRefreshing = false;
	}

	private: void RefreshDevices() { //std::vector<int id, std::string name, mac>
		userData = GABBE::GetAccounts();
		this->listBoxAccounts->Items->Clear();
		std::string buffer;
		for (unsigned int i = 0; i < userData.size(); i++) {
			buffer = "[" + userData[i].name + "]: " + userData[i].mac;
			this->listBoxAccounts->Items->Add(gcnew String(buffer.c_str()));
		}
		this->textBoxAccountsCurrent->Text = gcnew String(GABBE::GetCurrentAccount().c_str());
	}

	private: void RefreshUser() {
		uData = GABBE::GetUser();

		this->labelServerState2->Text = "Servers: " + uData.server ? "UP" : "DOWN";
		this->labelServerState->Text = uData.connecting ? "Connecting" : ( uData.connected ? "Connected" : "Disconnected" );
		this->panelServerState->BackColor = uData.server ? (uData.connected ? Color::Lime : Color::Orange) : Color::Red;

		this->labelServerVersion->Text = gcnew String(uData.version.c_str());
		this->Text = "GABB v" + gcnew String(uData.version.c_str()) + " by Reiji Yoshikuro";
		this->labelMainVersion->Text = "Version: " + gcnew String(uData.version.c_str());
		this->labelMainVersionLatest->Text = "Latest: " + (uData.latest.length() ? gcnew String(uData.latest.c_str()) : "UNKNOWN");

		if (uData.username.length()) {
			this->panelServerAcc->Visible = true;
			this->labelServerAccName->Text = "Logged in as: " + gcnew String(uData.username.c_str());
			this->labelServerAccType->Text = "Account type: " + (uData.acctype > 0 ? (uData.acctype == 1 ? "Donator" : "Premium" ) : "Basic");
			this->labelServerAccExp->Text = "Expire date: " + gcnew String(uData.expire_time.c_str());

			this->panelLoginForm->Visible = false;
			this->labelLoginAName->Text = gcnew String(uData.username.c_str());
			this->labelLoginAType->Text = uData.acctype > 0 ? (uData.acctype == 1 ? "Donator" : "Premium") : "Basic";
			this->labelLoginAExp->Text = gcnew String(uData.expire_time.c_str());
		}
		else {
			this->panelServerAcc->Visible = false;
			this->panelLoginForm->Visible = true;
		}
	}

	private: void RefreshSpammerCurrent() {
		if (selected_spammer_id <= 0) return;

		spammerData = GABBE::SpammerGet(selected_spammer_id); //std::pair<std::vector<std::pair<int, std::string>>, std::vector<int>>
		this->listBoxSpammerText->Items->Clear();
		for (unsigned int i = 0; i < spammerData.first.size(); i++) this->listBoxSpammerText->Items->Add(gcnew String(spammerData.first[i].second.c_str()));

		checkboxspammerupdating = true;
		/*for (unsigned int i = 0; i < spammerData.second.size(); i++) {
			for (unsigned int j = 0; j < windowData.size() && j < this->checkedListBoxSpammerWindows->Items->Count; j++) {
				if(windowData[j].first == spammerData.second[i]) this->checkedListBoxSpammerWindows->SetItemChecked()
			}
			t += spammerData.second[i] + " ";
			this->checkedListBoxSpammerWindows->SetItemChecked(i, spammerData.second[i]);
		}*/
		spammerRefreshing = true;
		bool tru;
		for (unsigned int i = 0; i < windowData.size() && i < (unsigned int)this->checkedListBoxSpammerWindows->Items->Count; i++) {
			tru = false;
			for (unsigned int j = 0; j < spammerData.second.size(); j++) {
				if (windowData[i].first == spammerData.second[j]) { tru = true; break; }
			}
			this->checkedListBoxSpammerWindows->SetItemChecked(i, tru);
		}
		spammerRefreshing = false;

		std::vector<int> spammerDesc = GABBE::SpammerGetDesc(selected_spammer_id);
		if (spammerDesc.size() < 5) return;
		this->checkBoxSpammerState->Checked = spammerDesc[0];
		this->checkBoxSpammerRandom->Checked = spammerDesc[1];
		this->checkBoxSpammerNoshift->Checked = spammerDesc[2];
		this->textBoxSpammerIntervalMessage->Text = gcnew String(std::to_string(spammerDesc[3]).c_str());
		this->textBoxSpammerIntervalLetter->Text = spammerDesc[4].ToString();

	}

	private: void RefreshSpammerInstances() {
		int spammerID = selected_spammer_id;
		SpammerInstances = GABBE::SpammerGetInstances();
		this->listBoxSpammerInstances->Items->Clear();
		bool all = true;
		for (unsigned int i = 0; i < SpammerInstances.size(); i++) {
			if (all && !SpammerInstances[i].second.first) all = false;
			this->listBoxSpammerInstances->Items->Add(gcnew String( std::string(std::to_string(SpammerInstances[i].first) + (SpammerInstances[i].second.first ? ".[ON]:  " : ".[OFF]: ") + SpammerInstances[i].second.second).c_str() ));
		}
		this->checkBoxSpammerEnableAll->Checked = all;
		for (unsigned int i = 0; i < SpammerInstances.size() && i < (unsigned int)this->listBoxSpammerInstances->Items->Count; i++) if (SpammerInstances[i].first == spammerID) this->listBoxSpammerInstances->SelectedIndex = i;
	}

	bool logged_in = false;
	private: System::Void tabControl1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (!logged_in && (this->tabControl1->SelectedIndex != 0 && this->tabControl1->SelectedIndex != 6)) {
			//this->tabControl1->SelectedIndex = 0;
			cout("You are not logged in!");
		}
	}

	bool settings_update = false;
	private: System::Void engineEventTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		std::vector<std::pair<int, std::wstring>> query = GABBE::EventLoop();
		for (unsigned int i = 0; i < query.size(); i++) {
			switch (query[i].first) {
				default: {
					cout(gcnew String((L"Unhandled event[" + std::to_wstring(query[i].first) + L"]<" + query[i].second + L">").c_str()));
					break;
					}
				case 0: {
					exit(0);
					}
				case 1: {
					cout(gcnew String(query[i].second.c_str()));
					break;
					}
				case 2: {
					RefreshWindows();
					break;
					}
				case 3: {
					RefreshUser();
					break;
				}
				case 5: {
					RefreshDevices();
					break;
					}
				case 6: {
					this->labelUnbannerTimer->Text = "It took " + gcnew String(query[i].second.c_str()) + " ms";
				}
				case 10: {
					this->labelLoginError->ForeColor = Color::OrangeRed;
					this->labelLoginError->Text = gcnew String(query[i].second.c_str());
					break;
					}
				case 11: {
					this->labelLoginError->ForeColor = Color::Chartreuse;
					this->labelLoginError->Text = gcnew String(query[i].second.c_str());
					break;
					}
				case 21: {
					this->textBoxLoginPass->Text = "";
					break;
					}
				case 31: {
					if(selected_spammer_instance >= 0 && selected_spammer_instance < (int)SpammerInstances.size()) spammerData = GABBE::SpammerGet(SpammerInstances[selected_spammer_instance].first);
					break;
					}
				case 32: {
					RefreshSpammerInstances();
					break;
					}
				case 33: {
					RefreshSpammerCurrent();
					RefreshSpammerInstances();
					break;
					}

				case 40: {

					std::wstring t = query[i].second;
					std::size_t pos = 0;
					std::vector<std::wstring> numbs;
					while (1) {
						pos = t.find('|');
						if (pos == std::string::npos) break;
						numbs.push_back(t.substr(0, pos));
						t = t.substr(pos + 1);
					}
					settings_update = true;
					if (numbs.size() >= 4) {
						this->textBox2->Text = gcnew String(numbs[0].c_str());
						this->textBox4->Text = gcnew String(numbs[1].c_str());
						this->textBox3->Text = gcnew String(numbs[2].c_str());
						this->textBox1->Text = gcnew String(numbs[3].c_str());
					}
					settings_update = false;
					break;
				}

				case 41: {
					int z = atoi(ws2s(query[i].second).c_str());
					this->engineEventTimer->Interval = (z > 0 && z <= 1000) ? z : 100;
					break;
				}


				case 120: {
					this->checkBoxSpammerNoshift->Enabled = atoi(ws2s(query[i].second).c_str());
				}

				case 121: {
					//refresh spammer instances
				}
			}
		}

	}

	private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
		GABBE::Close();
	}

	private: System::Void buttonDecode_Click(System::Object^  sender, System::EventArgs^  e) {
		if(this->textBoxSavePath->Text->Length > 0) SaveDecode(this->textBoxSavePath->Text);
		else SaveDecode(gcnew String(GABBE::GetPath("MySave").c_str()));
	}
	private: System::Void tabDecoder_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		array<String^>^ paths = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop));
		for each (String^ path in paths) { SaveDecode(path); }
	}
	private: System::Void tabDecoder_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop)) e->Effect = DragDropEffects::Copy;
		else e->Effect = DragDropEffects::None;
	}
	private: System::Void listBoxSaveTitle_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxSaveTitle->SelectedIndex;
		if (id >= 0 && id < (int)saveData.size()) {
			this->listBoxSaveContent->Items->Clear();
			for (unsigned int i = 0; i < saveData[id].second.size(); i++) 
				this->listBoxSaveContent->Items->Add(gcnew String(saveData[id].second[i].c_str()));
		}
	}
	private: System::Void checkBoxSave_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		GABBE::decodeSetFilter(this->checkBoxSave->Checked);
		SaveDecode(gcnew String(savePath.c_str()));
	}
	private: System::Void listBoxSaveContent_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		if (this->listBoxSaveContent->SelectedIndex >= 0 && this->checkBoxSaveCopy->Checked) {
			toClipboard(context.marshal_as<std::string>(this->listBoxSaveContent->SelectedItem->ToString()));
		}
	}
	private: System::Void buttonWindowsOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::NewWindow();
	}
	private: System::Void buttonWindowsClose_Click(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxWindows->SelectedIndex;
		if (id >= 0 && id < (int)windowData.size()) GABBE::CloseWindow(windowData[id].first);
	}
	private: System::Void buttonWindowsBTF_Click(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxWindows->SelectedIndex;
		if (id >= 0 && id < (int)windowData.size()) GABBE::bringToFront(windowData[id].first);
	}
	private: System::Void buttonWindowsSH_Click(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxWindows->SelectedIndex;
		if (id >= 0 && id < (int)windowData.size()) GABBE::changeVisibility(windowData[id].first);
	}


	private: System::Void buttonAccountsSet_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->listBoxAccounts->SelectedIndex >= 0 && this->listBoxAccounts->SelectedIndex < (int)userData.size()) GABBE::SetAccount(userData[this->listBoxAccounts->SelectedIndex].id);
	}
	
	private: System::Void buttonAccountsDelete_Click(System::Object^  sender, System::EventArgs^  e) {
		if (accountAdding || accountEditing >= 0) return;
		if (this->listBoxAccounts->SelectedIndex >= 0 && this->listBoxAccounts->SelectedIndex < (int)userData.size()) GABBE::DeleteAccount(userData[this->listBoxAccounts->SelectedIndex].id);
	}

	private: System::Void buttonAccountsUnban_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::SetAccountRandom();
	}

	private: System::Void buttonAccountsAdd_Click(System::Object^  sender, System::EventArgs^  e) {
		if (accountAdding || accountEditing >= 0) return;
		accountAdding = true;
		this->textBoxAccountsCreateName->Text = "";
		this->textBoxAccountsCreateMAC->Text = gcnew String(GABBE::GetRandomMAC().c_str());
		this->panelAccountsEdit->Visible = true;
	}

	private: System::Void buttonAccountsEdit_Click(System::Object^  sender, System::EventArgs^  e) {
		if (accountAdding || accountEditing >= 0) return;
		int id = this->listBoxAccounts->SelectedIndex;
		if (id < 0 || id >= (int)userData.size()) return;
		accountEditing = userData[id].id;
		this->textBoxAccountsCreateName->Text = gcnew String(userData[id].name.c_str());
		this->textBoxAccountsCreateMAC->Text = gcnew String(userData[id].mac.c_str());
		this->panelAccountsEdit->Visible = true;
	}

	private: System::Void buttonAccountEditRandom_Click(System::Object^  sender, System::EventArgs^  e) {
		this->textBoxAccountsCreateMAC->Text = gcnew String(GABBE::GetRandomMAC().c_str());
	}

	private: System::Void buttonAccountEditOK_Click(System::Object^  sender, System::EventArgs^  e) {
		if (textBoxAccountsCreateMAC->TextLength != 12) {
			MessageBoxW(NULL, L"MAC must be 12 characters long", L"Error!", MB_OK | MB_ICONWARNING);
			return;
		}

		if (accountAdding) {
			GABBE::NewAccount(context.marshal_as<std::string>(this->textBoxAccountsCreateName->Text), context.marshal_as<std::string>(this->textBoxAccountsCreateMAC->Text));
			accountAdding = false;
		}
		else if (accountEditing != -1) {
			GABBE::EditAccount(accountEditing, context.marshal_as<std::string>(this->textBoxAccountsCreateName->Text), context.marshal_as<std::string>(this->textBoxAccountsCreateMAC->Text));
			accountEditing = -1;
		}
		this->panelAccountsEdit->Visible = false;
	}
	private: System::Void buttonAccountEditCANCEL_Click(System::Object^  sender, System::EventArgs^  e) {
		accountAdding = false;
		accountEditing = -1;
		this->panelAccountsEdit->Visible = false;
	}
	private: System::Void checkBoxWindowsMB_Click(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxWindows->SelectedIndex;
		if (id >= 0 && id < (int)windowData.size()) GABBE::MBState(windowData[id].first, this->checkBoxWindowsMB->Checked);
	}
	private: System::Void listBoxWindows_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxWindows->SelectedIndex;
		if (id < 0 || id >= (int)windowData.size()) {
			this->checkBoxWindowsMB->Enabled = false;
			this->checkBoxWindowsMB->Checked = false;
		}
		else {
			if (!this->checkBoxWindowsMB->Enabled) this->checkBoxWindowsMB->Enabled = true;
			this->checkBoxWindowsMB->Checked = GABBE::MBState(windowData[id].first);
		}
	}

	private: System::Void buttonLoginOk_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string login = context.marshal_as<std::string>(this->textBoxLoginName->Text);
		std::string pass = context.marshal_as<std::string>(this->textBoxLoginPass->Text);
		GABBE::LogIn(login, pass);
	}

	private: System::Void buttonLoginALOGOUT_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::LogOut();
	}
	private: System::Void checkBoxWindowsMB_Click_1(System::Object^  sender, System::EventArgs^  e) {
		GABBE::MBStateAll(this->checkBoxWindowsMBAll->Checked);
	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		if (this->textBoxSpammerTextNew->Text->Length) GABBE::SpammerAddText(selected_spammer_id, context.marshal_as<std::string>(this->textBoxSpammerTextNew->Text));
	}
	private: System::Void checkBoxSpammerRandom_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::SpammerRandom(selected_spammer_id, this->checkBoxSpammerRandom->Checked);
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		int id = this->listBoxSpammerText->SelectedIndex;
		if (id < 0 || id >= (int)spammerData.first.size()) return;
		GABBE::SpammerDelText(selected_spammer_id, spammerData.first[id].first);
	}
	private: System::Void textBoxSpammerIntervalMessage_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		GABBE::SpammerSetInter(selected_spammer_id, atoi(context.marshal_as<std::string>(this->textBoxSpammerIntervalMessage->Text).c_str()), atoi(context.marshal_as<std::string>(this->textBoxSpammerIntervalLetter->Text).c_str()));
	}
	private: System::Void checkBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::SpammerState(selected_spammer_id, this->checkBoxSpammerState->Checked);
	}

	bool checkboxspammerupdating = false;
	private: System::Void checkedListBoxSpammerWindows_ItemCheck(System::Object^  sender, System::Windows::Forms::ItemCheckEventArgs^  e) {
		if (!checkboxspammerupdating) {
			bool allChecked = true;
			for (int i = 0; i < this->checkedListBoxSpammerWindows->Items->Count; i++) {
				if (i == e->Index) {
					if(e->NewValue != CheckState::Checked) { allChecked = false; break; }
				}
				else if (!this->checkedListBoxSpammerWindows->GetItemChecked(i)) { allChecked = false; break; }
			}
			this->checkBoxSpammerWindowsAll->Checked = allChecked;
		}
		else if(e->Index == this->checkedListBoxSpammerWindows->Items->Count - 1) checkboxspammerupdating = false;
		
		if (spammerRefreshing) return;
		spammerTargets.clear();
		for (int i = 0; i < this->checkedListBoxSpammerWindows->Items->Count && i < (int)windowData.size(); i++) {
			if (i == e->Index) {
				if(e->NewValue == CheckState::Checked) spammerTargets.push_back(windowData[i].first);
			}
			else if (this->checkedListBoxSpammerWindows->GetItemChecked(i)) {
				spammerTargets.push_back(windowData[i].first);
			}
		}
		GABBE::SpammerSetIds(selected_spammer_id, spammerTargets);
	}
	private: System::Void checkBoxSpammerNoshift_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::SpammerNoshift(this->checkBoxSpammerNoshift->Checked);
	}
	private: System::Void checkBoxSpammerWindowsAll_Click(System::Object^  sender, System::EventArgs^  e) {
		checkboxspammerupdating = true;
		for (int i = 0; i < this->checkedListBoxSpammerWindows->Items->Count; i++) {
			this->checkedListBoxSpammerWindows->SetItemChecked(i, this->checkBoxSpammerWindowsAll->Checked);
		}
	}

	private: System::Void buttonLinkDiscord_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string lnk = GABBE::LinkDC();
		if(lnk.length()) GABBE::OpenInBrowser(lnk);
		else cout("Failed to retrieve link from server!");
	}
	private: System::Void buttonLinkYT_Click(System::Object^  sender, System::EventArgs^  e) {
		std::string lnk = GABBE::LinkYT();
		if (lnk.length()) GABBE::OpenInBrowser(lnk);
		else cout("Failed to retrieve link from server!");
	}
	private: System::Void buttonWindowsCaptchaSolve_Click(System::Object^  sender, System::EventArgs^  e) {
		GABBE::SolveCaptcha();
	}

	private: System::Void panel1_Click(System::Object^  sender, System::EventArgs^  e) {
		SetImage(0);
	}
	private: System::Void panel2_Click(System::Object^  sender, System::EventArgs^  e) {
		SetImage(1);
	}
	private: System::Void panel3_Click(System::Object^  sender, System::EventArgs^  e) {
		SetImage(2);
	}
	private: System::Void tabControl1_Selecting(System::Object^  sender, System::Windows::Forms::TabControlCancelEventArgs^  e) {
		int id = this->tabControl1->SelectedIndex;
		if (id != 0 && id < 6 && !uData.logged_in) {
			this->tabControl1->SelectedIndex = 6;
			cout("Login before accessing other tabs!");
		}
		if (id == 4) {
			this->tabControl1->SelectedIndex = 6;
			cout("Macro isn't ready yet!");
		}
	}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (settings_update) return;
		settings_update = true;
		int tt = atoi(context.marshal_as<std::string>(this->textBox1->Text).c_str());
		settings_update = false;
		GABBE::UpdateTimer(0, tt);
		GABBE::UpdateSettings();
	}
	private: System::Void textBox3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (settings_update) return;
		settings_update = true;
		int tt = atoi(context.marshal_as<std::string>(this->textBox3->Text).c_str());
		settings_update = false;
		GABBE::UpdateTimer(1, tt);
		GABBE::UpdateSettings();
	}
	private: System::Void textBox4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (settings_update) return;
		settings_update = true;
		int tt = atoi(context.marshal_as<std::string>(this->textBox4->Text).c_str());
		settings_update = false;
		GABBE::UpdateTimer(2, tt);
		GABBE::UpdateSettings();
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		if (settings_update) return;
		settings_update = true;
		int tt = atoi(context.marshal_as<std::string>(this->textBox2->Text).c_str());
		settings_update = false;
		GABBE::UpdateTimer(3, tt);
		GABBE::UpdateSettings();
	}


private: System::Void buttonSpammerInstanceAdd_Click(System::Object^  sender, System::EventArgs^  e) {
	GABBE::SpammerAddInstance();
}
private: System::Void buttonSpammerInstanceRm_Click(System::Object^  sender, System::EventArgs^  e) {
	if (selected_spammer_instance >= 0) GABBE::SpammerRemoveInstance(selected_spammer_id);
}
private: System::Void listBoxSpammerInstances_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	selected_spammer_instance = this->listBoxSpammerInstances->SelectedIndex;
	if (selected_spammer_instance >= 0 && selected_spammer_instance <= (int)SpammerInstances.size()) selected_spammer_id = SpammerInstances[selected_spammer_instance].first;
	else selected_spammer_id = -1;
	//cout(gcnew String(std::to_string(selected_spammer_instance).c_str()));
	RefreshSpammerCurrent();
}
private: System::Void checkBoxSpammerEnableAll_Click(System::Object^  sender, System::EventArgs^  e) {
	GABBE::SpammerStateAll(checkBoxSpammerEnableAll->Checked);
}

};
}
