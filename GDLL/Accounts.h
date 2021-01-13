#pragma once
#include <string>
#include <vector>
#include "registry.h"

void cout(std::wstring ctx);
namespace Safety {
	std::string RandomKey(int length, int table);
}

std::wstring s2ws(const std::string &s) {
	return std::wstring(s.begin(), s.end());
}

std::string toUpperA(std::string text) {
	for (unsigned int i = 0; i < text.length(); i++) if (text[i] >= 97 && text[i] <= 122) text[i] -= 32;
	return text;
}

/*std::wstring s2ws(const std::string& str) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converterX;
	return converterX.from_bytes(str);
}*/

std::string ws2s(const std::wstring& wstr) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> converterX;
	return converterX.to_bytes(wstr);
}

int HexCharToInt(char HexChar) {
	std::string chars = "0123456789abcdefABCDEF";
	size_t posX = chars.find(HexChar);
	return posX == std::string::npos ? 0 : (posX > 15 ? posX - 6 : posX);
}

std::string IntToHex(int INT) {
	std::stringstream stream;
	stream << std::hex << INT;
	return std::string(stream.str());
}

int Multiply(int number, int times) {
	int result = 1;
	for (int i = 0; i < times; i++) result = result * number;
	return result;
}

struct ACCUSER;

class ACCMGR {
public:
	ACCMGR(std::string savedata = "");
	bool findMKey();

	void setRegAccount(int ID);
	void setRegAccountRandom();
	void setRegKeys(std::pair<std::string, std::string> keys);

	std::string getRegAccount();

	void editAccount(int ID, std::string MAC, std::string Name = "");
	void addAccount(std::string MAC, std::string name = "");
	void loadAccounts(std::string savedata);
	std::string toString();

	ACCUSER * getAccount(int ID);
	std::string getAccounts(); 
	std::vector<ACCUSER> getVAccounts();

	void delAccount(int ID);

	int freeID();

	std::string KeyAToMAC(std::string key);
	std::pair<std::string, std::string> MACToKeys(std::string MAC);

	inline bool isChanged() { return this->changed ? !(this->changed = false) : false; }
	inline bool isInitialised() { return this->initialised; }
	inline std::string RandomMAC() { return toUpperA(Safety::RandomKey(12, 3)); }
private:
	std::vector<ACCUSER> items;
	bool changed = false;
	bool initialised = false;
	std::wstring aKey = L"", aValue1 = L"", aValue2 = L"", aMKey = L"";
};

ACCMGR::ACCMGR(std::string savedata) {
	srand((unsigned int)time(NULL));
	std::wstring data = FindKey(HKEY_CURRENT_USER, L"", true);
	if (!data.length()) return;

	std::vector<std::wstring> values = FindKeyAll(HKEY_CURRENT_USER, data, false);
	if (values.size() < 2) return;

	this->aKey = data;
	this->aValue1 = values[0];
	this->aValue2 = values[1];

	if (savedata.length()) this->loadAccounts(savedata);
	this->initialised = true;
}

bool ACCMGR::findMKey() {
	std::wstring key = L"";
	HKEY HK = NULL;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft", 0, KEY_READ | KEY_WOW64_32KEY, &HK) == ERROR_SUCCESS) {
		key = FindKey(HK, L"", true);
		RegCloseKey(HK);
	}
	if (!key.length() && RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft", 0, KEY_READ | KEY_WOW64_64KEY, &HK) == ERROR_SUCCESS) {
		key = FindKey(HK, L"", true);
		RegCloseKey(HK);
	}
	if (!key.length()) return false;
	this->aMKey = key;
	return true;
}

void ACCMGR::setRegKeys(std::pair<std::string, std::string> keys) {
	if(!this->initialised) return;
	if(!RegKeySetValueBinary(HKEY_CURRENT_USER, this->aKey, this->aValue1, keys.first) || 
		!RegKeySetValueBinary(HKEY_CURRENT_USER, this->aKey, this->aValue2, keys.second)) {
		cout(L"Inserting device keys failed!");
		return;
	}
	std::string Rguid = Safety::RandomKey(36, 3);
	Rguid[8] = '-'; Rguid[13] = '-'; Rguid[18] = '-'; Rguid[23] = '-';
	RegKeySetValueRegSz(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Cryptography", L"MachineGuid", s2ws(Rguid));
	if (this->aMKey.length() || this->findMKey()) RegDeleteKey(HKEY_CURRENT_USER, std::wstring(L"Software\\Microsoft\\" + this->aMKey).c_str());
	this->changed = true;
}

void ACCMGR::setRegAccount(int ID) {
	ACCUSER * u = this->getAccount(ID);
	if (u == NULL) return;
	this->setRegKeys(this->MACToKeys(u->mac));
}

void ACCMGR::setRegAccountRandom() {
	this->setRegKeys(this->MACToKeys(this->RandomMAC()));
}

std::string ACCMGR::getRegAccount() {
	if (this->aKey == L"") return "";
	std::wstring key;
	RegKeyGetValueBinary(HKEY_CURRENT_USER, this->aKey, this->aValue1, key, key, key);
	if(!key.length()) return "";
	return this->KeyAToMAC(ws2s(key));
}

void ACCMGR::addAccount(std::string MAC, std::string name) {
	for (unsigned int i = 0; i < this->items.size(); i++) if (this->items[i].mac == MAC) return;
	this->items.push_back({ this->freeID(), name, MAC });
	this->changed = true;
}

void ACCMGR::editAccount(int ID, std::string MAC, std::string Name) {
	for (unsigned int i = 0; i < this->items.size(); i++) {
		if (this->items[i].id == ID) {
			this->items[i].mac = MAC;
			this->items[i].name = Name;
			this->changed = true;
			return;
		}
	}
}

void ACCMGR::loadAccounts(std::string savedata) {
	if (!savedata.length()) return;
	this->items.clear();

	std::size_t pos, a, b;
	while ((pos = savedata.find("\\|")) != std::string::npos) {
		if ((a = savedata.find("a|")) < pos && (b = savedata.find("b|")) < pos && a < b) {
			this->addAccount(savedata.substr(a + 2, b - a - 2), savedata.substr(0, a));
		}
		savedata = savedata.substr(pos + 2);
	}
	this->changed = true;
}

std::string ACCMGR::toString() {
	std::string ctx;
	for (unsigned int i = 0; i < this->items.size(); i++) ctx += this->items[i].name + "a|" + this->items[i].mac + "b|\\|";
	return ctx;
}

ACCUSER * ACCMGR::getAccount(int ID) {
	for (unsigned int i = 0; i < this->items.size(); i++) if (this->items[i].id == ID) return &this->items[i];
	return NULL;
}

std::string ACCMGR::getAccounts() {
	std::string buffer = "";
	for (unsigned int i = 0; i < this->items.size(); i++) buffer += this->items[i].name + "a|" + this->items[i].mac + "b|\\|";
	return buffer;
}

std::vector<ACCUSER> ACCMGR::getVAccounts() {
	return this->items;
}

void ACCMGR::delAccount(int ID) {
	for (unsigned int i = 0; i < this->items.size(); i++) {
		if (items[i].id == ID) {
			items.erase(items.begin() + i);
			this->changed = true;
			return;
		}
	}
}

int ACCMGR::freeID() {
	int id = 1;
	while (this->getAccount(id) != NULL) { id++; }
	return id;
}

std::string ACCMGR::KeyAToMAC(std::string key) {
	if (key.length() != 36) return "";
	std::string result = "";
	unsigned char val;
	for (int i = 0; i < 17; i++) {
		if (i % 3 == 2) continue;

		val = HexCharToInt(key[i * 2]) * 16 + HexCharToInt(key[(i * 2) + 1]);

		result += IntToHex((unsigned char)((val >= 0x1f && val <= 0x34) ? (val - (21 + i)) : (val - (238 + i))));
	}
	return toUpperA(result);
}

std::pair<std::string, std::string> ACCMGR::MACToKeys(std::string MAC) {
	std::string Rkeya = "", Rkeyb = "";
	if (MAC.length() != 12) return { "", "" };
	unsigned char values[18];
	for (int i = 0; i < 17; i++) values[i] = 238 + i;
	values[17] = 0;
	int id = 0;
	int hex;
	for (int i = 0; i < 17; i++) {
		if (i % 3 == 2) {
			values[i] += 10;
			continue;
		}
		if ((hex = HexCharToInt(MAC[id])) < 10) values[i] += hex;
		else values[i] -= (217 - hex);
		id++;
	}

	std::string result = "";
	for (int i = 0; i < 18; i++) {
		std::string addi = IntToHex((unsigned char)values[i]);
		result += addi.length() % 2 == 1 ? '0' + addi : addi;
	}
	Rkeya = result;


	int sum = 0;
	for (int i = 0; i < 18; i++) if (i % 3 != 2) sum += values[i];

	int altems[6] = { 4, 3, 7, 6, 4, 4 };
	int offsets[12] = { -1, -1, -1, -1, -1, -1, 8, 7, 5, 4, 2, 1 };

	for (int i = 0; i < (int)MAC.length(); i++) {
		int mass = HexCharToInt(MAC[i]);
		if (mass == 0) continue;
		if (mass >= 10) {
			altems[5] += mass - 7;
			altems[4] -= 1;
			altems[3] -= 2;
		}
		else if (offsets[i] != -1 && mass > offsets[i]) {
			altems[5] += mass - 6;
			altems[4] -= 5;
			altems[3] -= 2;
		}
		else altems[5] += mass;
	}

	int val = 0;
	for (int i = 5; i >= 0; i--) val += (altems[i] * (Multiply(10, 5 - i)));
	for (int i = 5; i > 0; i--) {
		altems[i] = val % 10;
		val -= val % 10;
		val /= 10;
	}
	altems[0] = val;

	char spacer = '3';
	std::string HASH2 = "";

	for (int i = 0; i < 6; i++) HASH2 += spacer + std::to_string(altems[i]);
	HASH2 += "00";
	Rkeyb = HASH2;
	return { Rkeya, Rkeyb };
}