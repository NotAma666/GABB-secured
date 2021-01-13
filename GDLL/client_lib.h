#pragma once
#include <vector>
#include <string>


struct ACCUSER {
	ACCUSER(int ID_, std::string Name_, std::string MAC_) : id(ID_), name(Name_), mac(MAC_) {}
	int id;
	std::string name, mac;
};

struct USERDATA {
	bool logged_in = false, server = false, connected = false, connecting = false, update = true;
	std::string version = "0.0.0", latest = "0.0.0", username = "", expire_time = "", sid = "";
	int acctype = 0;
	int theme = 0;
};

struct SETTINGS {
	int MBINTER = 1, SPAMINTER = 1, MACROINTER = 1, EVENTINTER = 10;
};

namespace GABBE {

	void __declspec(dllexport) Init();
	void __declspec(dllexport) UpdateTimer(int timid, int value);
	void __declspec(dllexport) UpdateSettings();
	void __declspec(dllexport) SolveCaptcha();

	void __declspec(dllexport) KeepSessionUp();
	void __declspec(dllexport) LogIn(std::string login_, std::string pass_);
	void __declspec(dllexport) LogOut();
	USERDATA __declspec(dllexport) GetUser();

	void __declspec(dllexport) OpenInBrowser(std::string link);
	std::string __declspec(dllexport) LinkDC();
	std::string __declspec(dllexport) LinkYT();


	std::vector<std::pair<int, std::wstring>> __declspec(dllexport) EventLoop();

	std::wstring __declspec(dllexport) GetPath(std::string title);

	std::vector<std::pair<int, std::vector<std::string>>> __declspec(dllexport) GetWindows();

	void __declspec(dllexport) NewWindow();
	void __declspec(dllexport) CloseWindow(int id);
	void __declspec(dllexport) bringToFront(int id);
	void __declspec(dllexport) changeVisibility(int id);

	std::vector<ACCUSER> __declspec(dllexport) GetAccounts();

	std::string __declspec(dllexport) GetRandomMAC();
	std::string __declspec(dllexport) GetCurrentAccount();
	void __declspec(dllexport) NewAccount(std::string name, std::string mac);
	void __declspec(dllexport) SetAccountRandom();
	void __declspec(dllexport) SetAccount(int id);
	void __declspec(dllexport) EditAccount(int id, std::string name, std::string mac);
	void __declspec(dllexport) DeleteAccount(int id);

	std::vector<std::pair<std::string, std::vector<std::string>>> __declspec(dllexport) decodeFile(std::wstring path);
	void __declspec(dllexport) decodeSetFilter(bool filter);

	bool __declspec(dllexport) MBState(int id);
	bool __declspec(dllexport) MBState(int id, bool set);
	bool __declspec(dllexport) MBStateAll(bool set);

	void __declspec(dllexport) SpammerAddInstance();
	void __declspec(dllexport) SpammerRemoveInstance(int InstanceID);
	std::vector<std::pair<int, std::pair<bool, std::string>>> __declspec(dllexport) SpammerGetInstances();

	void __declspec(dllexport) SpammerNoshift(bool enabled);
	void __declspec(dllexport) SpammerState(int InstanceID, bool enabled);
	void __declspec(dllexport) SpammerStateAll(bool enabled);
	void __declspec(dllexport) SpammerRandom(int InstanceID, bool enabled);
	void __declspec(dllexport) SpammerAddText(int InstanceID, std::string ctx);
	void __declspec(dllexport) SpammerDelText(int InstanceID, int SpammerID);
	void __declspec(dllexport) SpammerSetIds(int InstanceID, std::vector<int> targets);
	void __declspec(dllexport) SpammerSetInter(int InstanceID, int word, int letter);
	std::pair<std::vector<std::pair<int, std::string>>, std::vector<int>> __declspec(dllexport) SpammerGet(int InstanceID);
	std::vector<int> __declspec(dllexport) SpammerGetDesc(int InstanceID);

	void __declspec(dllexport) MacroAddInstance();
	void __declspec(dllexport) MacroRemoveInstance(int InstanceID);
	void __declspec(dllexport) MacroSetIds(int InstanceID, std::vector<int> targets);
	std::vector<std::pair<int, std::string>> __declspec(dllexport) MacroGetList();
	std::pair<std::vector<std::pair<std::string, std::string>>, std::vector<int>> __declspec(dllexport) MacroGetInstance(int InstanceID);
	std::vector<std::pair<int, std::string>> __declspec(dllexport) MacroGetVariables(int InstanceID);

	void __declspec(dllexport) SetTheme(int id);
	int __declspec(dllexport) GetTheme();

	void __declspec(dllexport) Close();
}