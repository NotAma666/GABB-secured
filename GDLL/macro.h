#pragma once
//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <stdio.h>
#include "clock_gettime.h"
#include "macro_instructions.h"

void cout(std::wstring ctx);
void cout(std::string ctx);

bool match(std::string a, std::string b) {
	for (unsigned int i = 0; i < a.length(); i++) if (a[i] >= 0x61 && a[i] <= 0x7A) a[i] = toupper(a[i]);
	for (unsigned int i = 0; i < b.length(); i++) if (b[i] >= 0x61 && b[i] <= 0x7A) b[i] = toupper(b[i]);
	return a == b;
}

unsigned int ReadLines(std::string filename, std::vector<std::string> &result) {
	std::fstream ifs(filename, std::ios::in); //| std::ios::ate
	if (ifs.good()) {

		std::vector<std::string> vbuff;
		std::string buff;

		while (!ifs.eof()) {
			std::getline(ifs, buff);
			vbuff.push_back(buff);
		}

		ifs.close();
		result = vbuff;

		return vbuff.size();
	}
	return 0;
}

struct def_funct {
	std::string text;
	int nums;
};

struct var {
	std::string name;
	int value;
};

struct def_pair {
	int beg, mid, mid2, end;
	bool breakable;
};

struct macro_pair {
	int layer;
	int type;
	int beginline;
	std::vector<int> middlelines;
	int endline;
};

int max_funct_defs = 23;
def_funct function_definitions[23] = {
	{ "MOUSE_MOVE", 2 },         //0
	{ "MOUSE_DOWN", 3 },         //1
	{ "MOUSE_UP", 3 },           //2
	{ "KEY_DOWN", 2 },           //3
	{ "KEY_UP", 2 },             //4
	{ "SLEEP", 1 },              //5
	{ "SET", 2 },                //6
	{ "SET", 4 },                //7
	{ "VAR", 1 },                //8
	{ "VAR", 2 },                //9
	{ "DO", 0 },                 //10
	{ "WHILE", 3 },              //11
	{ "ENDWHILE", 0 },           //12
	{ "IF", 3 },                 //13
	{ "ELSEIF", 3 },             //14
	{ "ELSE", 0 },               //15
	{ "ENDIF", 0 },              //16
	{ "CONTINUE", 0 },           //17
	{ "RETURN", 0 },             //18
	{ "BREAK", 0 },              //19
	{ "OVERWRITE_LIMIT", 1 },    //20
	{ "DEBUG", 1 },              //21
	{ "WRITE", -1 }              //22
};

int max_pair_defs = 3;
def_pair pair_definitions[3] = {
	{ 10, -1, -1, 11, true }, //DO .. WHILE
	{ 11, -1, -1, 12, true }, //WHILE .. ENDWHILE
	{ 13, 14, 15, 16, false } //IF .. ELSEIF .. ELSE .. ENDIF
};

class MacroController {
private:
	std::vector<std::string> errors;
	int mode = 0; // 0 - test, 1 - execute;
	int limit = 10000, limit_counter = 0;
	int last_line = 0, current_line = 0, current_layer = 0;

	bool debug_mode = false, last_line_changed = false;
	std::vector<std::string> debug_lines;

	HWND target_hwnd;
	DWORD target_pid;

	std::vector<std::vector<std::string> > Script;
	std::vector<macro_pair> Pairs;
	std::vector<var> virtual_vars;
	//time, etc
	long time_offset = gettime();

public:


	void Loop();
	void MOUSE_MOVE(std::string x, std::string y);
	void MOUSE_DOWN(std::string button, std::string x, std::string y);
	void MOUSE_UP(std::string button, std::string x, std::string y);
	void KEY_DOWN(std::string type, std::string code);
	void KEY_UP(std::string type, std::string code);
	void SLEEP(std::string ms);
	void SET(std::string name, std::string newval);
	void SET(std::string name, std::string stat_a, std::string stat_b, std::string stat_c);
	void VAR(std::string name);
	void VAR(std::string name, std::string default_val);
	void DO();
	void WHILE(std::string stat_a, std::string stat_b, std::string stat_c);
	void ENDWHILE();
	void IF(std::string stat_a, std::string stat_b, std::string stat_c);
	void ELSEIF(std::string stat_a, std::string stat_b, std::string stat_c);
	void ELSE();
	void ENDIF();
	void CONTINUE();
	void RETURN();
	void BREAK();
	void OVERWRITE_LIMIT(std::string limit);
	void DEBUG(std::string state);
	void WRITE(std::vector<std::string> text);

	int CallByID(int ID, std::vector<std::string> params);
	void SetMode(int mode);

	bool isError();
	std::vector<std::string> GetError(bool clear = false);
	void ClearError();
	void AddError(std::string err);

	bool isDebug();
	bool isDebugMode();
	std::vector<std::string> GetDebug(bool clear = false);
	void ClearDebug();
	void AddDebug(std::string dbg);

	bool IsVarName(std::string ctx);

	void ClearVVars() { this->virtual_vars.clear(); }
	bool VVarExists(std::string name_);
	int GetVVar(std::string name_);
	bool SetVVar(std::string name_, std::string value_);
	void CreateVVar(std::string name_, std::string value_);

	void ClearScript(std::vector<std::string> &Lines);
	bool PrepareForInterpreter(std::vector<std::string> input, std::vector<std::vector<std::string> > &result);
	bool PerformTestRun();

	void ResetLineChangeBuffer() { this->last_line_changed = false; }
	bool LineChangeBuffer() { return this->last_line_changed; }

	void SetCurrentLine(int line) { this->last_line_changed = true; this->last_line = this->current_line; this->current_line = line; }
	void ResetCurrentLine() { this->current_line = 0; this->last_line = 0; }
	int GetCurrentLine() { return this->current_line; }
	int GetLastLine() { return this->last_line; }
	void SetCurrentLayer(int val) { this->current_layer = val; }
	int GetCurrentLayer() { return this->current_layer; }

	void DebugMode(bool enabled) { this->debug_mode = enabled; }

	void AssignPairs(std::vector<macro_pair> pairs_) { this->Pairs = pairs_; }

	void AssignScript(std::vector<std::vector<std::string> > script_) { this->Script = script_; }
	std::vector<std::vector<std::string> > GetScript() { return this->Script; }
	unsigned int GetScriptSize() { return this->Script.size(); }
	std::vector<std::string> GetScriptLine(int line) { if (line < (int)Script.size() && line >= 0) return this->Script[line]; return {}; }

	void SetDelay(int mil) { this->time_offset = gettime() + mil; }
	bool isReady() { return this->time_offset - gettime() <= 0; }
	int GetDelay() { int tm = this->time_offset - gettime(); return tm < 0 ? 0 : tm; }

	int Step();
};

void MacroController::Loop() {

}

int MacroController::CallByID(int ID, std::vector<std::string> params) {

	if (function_definitions[ID].nums != -1 && ((int)params.size() < function_definitions[ID].nums)) return -1;
	switch (ID) {
	case 0:
		this->MOUSE_MOVE(params[0], params[1]);
		break;
	case 1:
		this->MOUSE_DOWN(params[0], params[1], params[2]);
		break;
	case 2:
		this->MOUSE_UP(params[0], params[1], params[2]);
		break;
	case 3:
		this->KEY_DOWN(params[0], params[1]);
		break;
	case 4:
		this->KEY_UP(params[0], params[1]);
		break;
	case 5:
		this->SLEEP(params[0]);
		break;
	case 6:
		this->SET(params[0], params[1]);
		break;
	case 7:
		this->SET(params[0], params[1], params[2], params[3]);
		break;
	case 8:
		this->VAR(params[0]);
		break;
	case 9:
		this->VAR(params[0], params[1]);
		break;
	case 10:
		this->DO();
		break;
	case 11:
		this->WHILE(params[0], params[1], params[2]);
		break;
	case 12:
		this->ENDWHILE();
		break;
	case 13:
		this->IF(params[0], params[1], params[2]);
		break;
	case 14:
		this->ELSEIF(params[0], params[1], params[2]);
		break;
	case 15:
		this->ELSE();
		break;
	case 16:
		this->ENDIF();
		break;
	case 17:
		this->CONTINUE();
		break;
	case 18:
		this->RETURN();
		break;
	case 19:
		this->BREAK();
		break;
	case 20:
		this->OVERWRITE_LIMIT(params[0]);
		break;
	case 21:
		this->DEBUG(params[0]);
		break;
	case 22:
		this->WRITE(params);
		break;
	default:
		return -2;
	}

	if (this->isError()) return 0;

	if (this->isDebug()) {
		std::vector<std::string> const dbg = GetDebug(1);
		for (unsigned int i = 0; i < dbg.size(); i++) cout(dbg[i]);
	}
	return 1;
}

std::vector<int> GetDefinition(std::string param_1, int &length) {
	std::vector<int> pos;
	for (int i = 0; i < max_funct_defs; i++) {
		if (match(function_definitions[i].text, param_1) && (function_definitions[i].nums == length || function_definitions[i].nums == -1)) {
			pos.clear();
			pos.push_back(i);
			length = -1;
			return pos;
		}
		else if (function_definitions[i].text == param_1) {
			pos.push_back(function_definitions[i].nums * -1);
		}
	}
	length = 0;
	return pos;
}

int main()
{
	cout("Hello world!");

	std::vector<std::string> Bytes;

	if (!ReadLines("instructions.txt", Bytes)) {
		std::cout << "File is empty or doesn't exists!" << std::endl;
		_getch();
		return 1;
	}

	MacroController * MACRO = new MacroController();

	std::vector<std::vector<std::string> > commands;

	if (!MACRO->PrepareForInterpreter(Bytes, commands)) {
		std::vector<std::string> errors = MACRO->GetError();
		for (unsigned int i = 0; i < errors.size(); i++) std::cout << errors[i] << std::endl;
		_getch();
		return 1;
	}

	if (MACRO->isDebug()) {
		std::vector<std::string> dbg = MACRO->GetDebug(1);
		for (unsigned int i = 0; i < dbg.size(); i++) std::cout << dbg[i] << std::endl;
	}

	if (!MACRO->PerformTestRun()) {
		std::vector<std::string> errors = MACRO->GetError();
		for (unsigned int i = 0; i < errors.size(); i++) std::cout << errors[i] << std::endl;
	}


	std::cout << "Code end!" << std::endl;




	/*for( unsigned int i = 0; i < commands.size(); i++ ) {
			for( unsigned int j = 0; j < commands[i].size(); j++ ) std::cout << commands[i][j] << " ";
			std::cout << std::endl;
	}*/





	_getch();

	return 0;
}

void MacroController::SetMode(int mode_) {
	this->mode = mode_;
}

void MacroController::ClearScript(std::vector<std::string> &Lines) {
	for (unsigned int i = 0; i < Lines.size(); i++) {
		int posbuf;
		if ((posbuf = Lines[i].find(';')) < (int)Lines[i].length()) Lines[i] = Lines[i].substr(0, posbuf);
		for (int j = Lines[i].length() - 1; j >= 0; j--)
			if (Lines[i][j] != ' ' && (int)Lines[i][j] != 9) {
				if (j == Lines[i].length() - 1) break;
				Lines[i] = Lines[i].substr(0, j + 1);
				break;
			}

		for (int j = 0; j < (int)Lines[i].length(); j++)
			if (Lines[i][j] != ' ' && (int)Lines[i][j] != 9) {
				if (j == 0) break;
				Lines[i] = Lines[i].substr(j, Lines[i].length());
				break;
			}
	}
}

bool MacroController::PrepareForInterpreter(std::vector<std::string> input, std::vector<std::vector<std::string> > &result) {
	MacroController::ClearScript(input);
	this->ClearError();
	result.clear();

	std::string v1;
	bool error = true;
	std::vector<std::string> empty;
	for (unsigned int i = 0; i < input.size(); i++) {
		result.push_back(empty);
		v1 = "";
		for (unsigned int j = 0; j <= input[i].length(); j++) {
			if (j == input[i].size() || input[i][j] == ' ' || (int)input[i][j] == 9) {
				result[i].push_back(v1);
				v1 = "";
			}
			else v1 += input[i][j];
		}
	}
	std::string v2;
	int v3;
	std::vector<int> v4;
	for (unsigned int i = 0; i < result.size(); i++) {
		if (result[i][0].length() == 0) continue;
		v2 = result[i][0];
		v3 = result[i].size() - 1;
		v4 = GetDefinition(v2, v3);
		if (v4.size() <= 0) {
			this->AddError(std::string("invalid command at line " + std::to_string(i + 1) + ", [" + result[i][0] + "]"));
			if (error) error = false;
		}
		else if (!v3) {
			std::string amounts = "";
			for (int j = 0; j < (int)v4.size(); j++) {
				amounts += std::to_string(v4[j] * -1);
				if (j < (int)v4.size() - 3) amounts += ", ";
				else if (j == (int)v4.size() - 2) amounts += " or ";
			}
			this->AddError(std::string("invalid amount of parameters at line " + std::to_string(i + 1) + ", [" + result[i][0]
				+ "]. Expected " + amounts + ", got " + std::to_string(result[i].size() - 1)));
			if (error) error = false;
		}
		else result[i][0] = std::to_string(v4[0]);

	}

	if (!error) return error;

	if (result.size() > 0 && result[0].size() == 2 && result[0][0] == "21" && atoi(result[0][1].c_str()) > 0) this->DebugMode(1);

	int layer = 0;
	std::vector<macro_pair> pairs;
	for (unsigned int i = 0; i < result.size(); i++) {
		if (result[i].size() == 1 && result[i][0].length() == 0) continue;

		int ptr = atoi(result[i][0].c_str());
		if (ptr >= 0 && ptr < max_funct_defs) {
			for (int z = 0; z < max_pair_defs; z++) {
				if (ptr == pair_definitions[z].beg) {
					bool brek = false;
					for (unsigned int x = 0; x < pairs.size(); x++) {
						if ((pairs[x].type == 0 && pairs[x].endline == i) ||
							(pairs[x].type == 1 && pairs[x].beginline == i)) {
							brek = true;
							continue;
						}
					}
					if (brek) continue;
					macro_pair vPair;
					vPair.beginline = i;
					vPair.endline = -1;
					vPair.type = z;
					vPair.layer = layer;
					pairs.push_back(vPair);
					layer++;
				}
				else if (ptr != -1 && (ptr == pair_definitions[z].mid || ptr == pair_definitions[z].mid2)) {
					for (int x = pairs.size() - 1; x >= 0; x--) {
						if (pairs[x].layer == layer - 1 && pairs[x].type == z) {
							pairs[x].middlelines.push_back(i);
							break;
						}
					}
				}
				else if (ptr == pair_definitions[z].end) {
					for (int x = pairs.size() - 1; x >= 0; x--) {
						if (pairs[x].layer <= layer - 1 && pairs[x].type == z && pairs[x].endline == -1) {
							pairs[x].endline = i;
							layer--;
							break;
						}
					}
				}
			}
		}
	}

	for (unsigned int i = 0; i < pairs.size(); i++) {
		if (pairs[i].endline == -1) {
			this->AddError("Couldn't find matching [" + function_definitions[pair_definitions[pairs[i].type].end].text + "] for [" +
				function_definitions[pair_definitions[pairs[i].type].beg].text + "] at line [" + std::to_string(pairs[i].beginline + 1) + "].");
			if (error) error = false;
		}
	}

	if (this->isDebugMode()) {
		for (unsigned int i = 0; i < pairs.size(); i++) {
			std::string sbuf = std::to_string(i) + ":\n  Begin: " + std::to_string(pairs[i].beginline + 1) + "\n  Mid:\n";
			for (unsigned int j = 0; j < pairs[i].middlelines.size(); j++) sbuf += "      " + std::to_string(pairs[i].middlelines[j] + 1) + "\n";
			sbuf += "  End: " + std::to_string(pairs[i].endline + 1) + "\n  Layer: " + std::to_string(pairs[i].layer) + "\n  Type: " + std::to_string(pairs[i].type) + "\n\n";
			this->AddDebug(sbuf);
		}
	}

	if (error) {
		this->AssignPairs(pairs);
		this->AssignScript(result);
	}

	this->ClearVVars();

	return error;
}

bool MacroController::PerformTestRun() {
	std::vector<std::vector<std::string>> commands = this->GetScript();
	this->ClearError();
	this->SetMode(0);
	this->ResetCurrentLine();


	while (this->Step()) {
		if (this->isDebug()) {
			std::vector<std::string> dbg = this->GetDebug(1);
			for (unsigned int i = 0; i < dbg.size(); i++) std::cout << "   " << dbg[i] << std::endl;
		}
		if (this->isError()) {
			std::vector<std::string> err = this->GetError(1);
			for (unsigned int i = 0; i < err.size(); i++) std::cout << err[i] << std::endl;
			break;
		}
		Sleep(this->GetDelay());
		if (this->isDebugMode()) {
			std::cout << "-> " << this->GetCurrentLine() << " " << this->GetCurrentLayer() << std::endl;
			std::cout << "   " << gettime() << std::endl;
			Sleep(500);
		}
	}



	this->SetMode(1);
	return this->isError();
}

void MacroController::MOUSE_MOVE(std::string x_, std::string y_) {
	if (this->isDebugMode()) this->AddDebug("MOUSE_MOVE");
	this->AddError("Function [MOUSER_MOVE] is DEPRECATED. Use [MOUSE_DOWN] or [MOUSE_UP] with <button>, <x> and <y> parameters instead.");
}

void MacroController::MOUSE_DOWN(std::string button_, std::string x_, std::string y_) {
	COORD pp;
	pp.X = atoi(x_.c_str());
	pp.Y = atoi(y_.c_str());
	int btn = atoi(button_.c_str());
	if (btn < 0 || btn > 2) {
		this->AddDebug("Button < 0 || > 2. Button = 0.");
		btn = 0;
	}
	if (this->isDebugMode()) this->AddDebug("MOUSE_DOWN " + std::to_string(btn) + " at " + std::to_string(pp.X) + ", " + std::to_string(pp.Y) + ".");

	//code

}

void MacroController::MOUSE_UP(std::string button_, std::string x_, std::string y_) {
	COORD pp;
	pp.X = atoi(x_.c_str());
	pp.Y = atoi(y_.c_str());
	int btn = atoi(button_.c_str());
	if (btn < 0 || btn > 2) {
		this->AddDebug("Button < 0 || > 2. Button = 0.");
		btn = 0;
	}
	if (this->isDebugMode()) this->AddDebug("MOUSE_UP " + std::to_string(btn) + " at " + std::to_string(pp.X) + ", " + std::to_string(pp.Y) + ".");

	//code

}

void MacroController::KEY_DOWN(std::string type, std::string code) {
	if (this->isDebugMode()) this->AddDebug("KEY_DOWN " + type + " " + code);

	if (type == "CHAR") {

		//write char
	}
	else if (type == "VKEY") {
		if (code.length() != 2 || HexCharToInt(code[0]) == -1 || HexCharToInt(code[1]) == -1) {
			this->AddError("Invalid argument in [KEY_DOWN], line: " + std::to_string(this->GetCurrentLine()) + ". Expected 2 hexadecimal chars (eg. <FF>) got <" + code + ">.");
			return;
		}

		//write vkey
	}
	else this->AddError("Invalid argument in [KEY_DOWN], line: " + std::to_string(this->GetCurrentLine()) + ". Expected <CHAR/VKEY> got <" + type + ">.");

}

void MacroController::KEY_UP(std::string type, std::string code) {
	if (this->isDebugMode()) this->AddDebug("KEY_UP " + type + " " + code);

}

void MacroController::SLEEP(std::string ms) {
	if (this->isDebugMode()) this->AddDebug("SLEEP");
	if (this->mode > 0) this->SetDelay(this->GetVVar(ms));
}

void MacroController::SET(std::string name, std::string newval) {
	this->SetVVar(name, newval);
	if (this->isDebugMode()) this->AddDebug("SET " + name + " to " + std::to_string(this->GetVVar(name)) + ".");
}

void MacroController::SET(std::string name, std::string stat_a, std::string stat_b, std::string stat_c) {
	if (stat_b == "+")
		this->SetVVar(name, std::to_string(this->GetVVar(stat_a) + this->GetVVar(stat_c)));
	else if (stat_b == "-")
		this->SetVVar(name, std::to_string(this->GetVVar(stat_a) - this->GetVVar(stat_c)));
	else if (stat_b == "*")
		this->SetVVar(name, std::to_string(this->GetVVar(stat_a) * this->GetVVar(stat_c)));
	else if (stat_b == "/") {
		if (this->GetVVar(stat_c) == 0) {
			this->AddError("Trying to divide by 0 in line " + std::to_string(this->GetCurrentLine()));
			return;
		}
		this->SetVVar(name, std::to_string(this->GetVVar(stat_a) / this->GetVVar(stat_c)));
	}
	else {
		this->AddError("Undefined parameter <" + stat_b + "> on line " + std::to_string(this->GetCurrentLine()) + " [SET]");
		return;
	}
	if (this->isDebugMode()) this->AddDebug("SET " + name + " to " + std::to_string(this->GetVVar(name)) + ".");
}

void MacroController::VAR(std::string name) {
	if (this->isDebugMode()) this->AddDebug("VAR " + name);
	if (!this->SetVVar(name, "")) {
		this->AddError("An error occurred while creating [" + name + "] [VAR].");
	}
}

void MacroController::VAR(std::string name, std::string default_val) {
	if (!this->SetVVar(name, default_val)) {
		this->AddError("An error occurred while creating [" + name + "] [VAR].");
		return;
	}
	if (this->isDebugMode()) this->AddDebug("VAR" + name + " " + std::to_string(this->GetVVar(name)));
}

void MacroController::DO() {
	if (this->isDebugMode()) this->AddDebug("DO");
	this->SetCurrentLayer(this->GetCurrentLayer() + 1);

}

void MacroController::WHILE(std::string stat_a, std::string stat_b, std::string stat_c) {
	if (this->isDebugMode()) this->AddDebug("WHILE");
	for (unsigned int i = 0; i < this->Pairs.size(); i++) {
		if (Pairs[i].type != 0 && Pairs[i].type != 1) continue;
		if (Pairs[i].type == 0 && Pairs[i].endline == this->GetCurrentLine()) {

			bool tru = false;
			if (stat_b == "==")
				tru = this->GetVVar(stat_a) == this->GetVVar(stat_c);
			else if (stat_b == "<")
				tru = this->GetVVar(stat_a) < this->GetVVar(stat_c);
			else if (stat_b == "<=")
				tru = this->GetVVar(stat_a) <= this->GetVVar(stat_c);
			else if (stat_b == ">")
				tru = this->GetVVar(stat_a) > this->GetVVar(stat_c);
			else if (stat_b == ">=")
				tru = this->GetVVar(stat_a) >= this->GetVVar(stat_c);
			else if (stat_b == "!=")
				tru = this->GetVVar(stat_a) != this->GetVVar(stat_c);
			else {
				this->AddError("Error at line " + std::to_string(this->GetCurrentLine()) + " in [IF]. Invalid argument " + stat_b + ". Expected ==, <, <=, >, >= or != .");
				return;
			}

			if (tru) SetCurrentLine(Pairs[i].beginline);
			else this->SetCurrentLayer(this->GetCurrentLayer() - 1);
			return;
		}
		else if (Pairs[i].beginline == this->GetCurrentLine()) {
			if (this->GetCurrentLayer() < Pairs[i].layer + 1) this->SetCurrentLayer(this->GetCurrentLayer() + 1);

			bool tru = false;
			if (stat_b == "==")
				tru = this->GetVVar(stat_a) == this->GetVVar(stat_c);
			else if (stat_b == "<")
				tru = this->GetVVar(stat_a) < this->GetVVar(stat_c);
			else if (stat_b == "<=")
				tru = this->GetVVar(stat_a) <= this->GetVVar(stat_c);
			else if (stat_b == ">")
				tru = this->GetVVar(stat_a) > this->GetVVar(stat_c);
			else if (stat_b == ">=")
				tru = this->GetVVar(stat_a) >= this->GetVVar(stat_c);
			else if (stat_b == "!=")
				tru = this->GetVVar(stat_a) != this->GetVVar(stat_c);
			else {
				this->AddError("Error at line " + std::to_string(this->GetCurrentLine()) + " in [IF]. Invalid argument " + stat_b + ". Expected ==, <, <=, >, >= or != .");
				return;
			}

			if (!tru) {
				SetCurrentLine(Pairs[i].endline);
				this->SetCurrentLayer(this->GetCurrentLayer() - 1);
			}
			return;
		}
	}
}

void MacroController::ENDWHILE() {
	if (this->isDebugMode()) this->AddDebug("ENDWHILE");
	for (unsigned int i = 0; i < this->Pairs.size(); i++) {
		if (Pairs[i].type == 1 && Pairs[i].endline == this->GetCurrentLine()) {
			SetCurrentLine(Pairs[i].beginline);
			return;
		}
	}

}

void MacroController::IF(std::string stat_a, std::string stat_b, std::string stat_c) {
	if (this->isDebugMode()) this->AddDebug("IF " + stat_a + " " + stat_b + " " + stat_c);
	for (unsigned int i = 0; i < this->Pairs.size(); i++) {
		if (this->Pairs[i].type == 2 && this->Pairs[i].beginline == this->GetCurrentLine()) {

			bool tru = false;
			if (stat_b == "==")
				tru = this->GetVVar(stat_a) == this->GetVVar(stat_c);
			else if (stat_b == "<")
				tru = this->GetVVar(stat_a) < this->GetVVar(stat_c);
			else if (stat_b == "<=")
				tru = this->GetVVar(stat_a) <= this->GetVVar(stat_c);
			else if (stat_b == ">")
				tru = this->GetVVar(stat_a) > this->GetVVar(stat_c);
			else if (stat_b == ">=")
				tru = this->GetVVar(stat_a) >= this->GetVVar(stat_c);
			else if (stat_b == "!=")
				tru = this->GetVVar(stat_a) != this->GetVVar(stat_c);
			else {
				this->AddError("Error at line " + std::to_string(this->GetCurrentLine()) + " in [IF]. Invalid argument " + stat_b + ". Expected ==, <, <=, >, >= or != .");
				return;
			}

			if (!tru) {
				if (Pairs[i].middlelines.size() > 0 && Pairs[i].middlelines[0] > this->GetCurrentLine()) {
					this->SetCurrentLine(Pairs[i].middlelines[0]);
					this->SetCurrentLayer(Pairs[i].layer + 1);
					return;
				}
				else this->SetCurrentLine(Pairs[i].endline);
			}
			else {
				this->SetCurrentLayer(Pairs[i].layer + 1);
				return;
			}
		}
	}
}

void MacroController::ELSEIF(std::string stat_a, std::string stat_b, std::string stat_c) {
	if (this->isDebugMode()) this->AddDebug("ELSEIF " + stat_a + " " + stat_b + " " + stat_c);
	for (unsigned int i = 0; i < this->Pairs.size(); i++) {
		if (this->Pairs[i].type == 2) {

			bool tru = false;
			int line = this->GetCurrentLine();
			for (unsigned int x = 0; x <= Pairs[i].middlelines.size(); x++) {
				if (Pairs[i].middlelines[x] == line) {
					tru = true;
					break;
				}
			}
			if (!tru) continue;

			if (this->GetLastLine() == line - 1) {
				this->SetCurrentLine(this->Pairs[i].endline);
				return;
			}

			tru = false;
			if (stat_b == "==")
				tru = this->GetVVar(stat_a) == this->GetVVar(stat_c);
			else if (stat_b == "<")
				tru = this->GetVVar(stat_a) < this->GetVVar(stat_c);
			else if (stat_b == "<=")
				tru = this->GetVVar(stat_a) <= this->GetVVar(stat_c);
			else if (stat_b == ">")
				tru = this->GetVVar(stat_a) > this->GetVVar(stat_c);
			else if (stat_b == ">=")
				tru = this->GetVVar(stat_a) >= this->GetVVar(stat_c);
			else if (stat_b == "!=")
				tru = this->GetVVar(stat_a) != this->GetVVar(stat_c);
			else {
				this->AddError("Error at line " + std::to_string(this->GetCurrentLine()) + " in [IF]. Invalid argument " + stat_b + ". Expected ==, <, <=, >, >= or != .");
				return;
			}

			if (!tru) {
				for (unsigned int x = 0; x <= Pairs[i].middlelines.size(); x++) {
					if (Pairs[i].middlelines[x] > line) {
						this->SetCurrentLine(Pairs[i].middlelines[x]);
						return;
					}
				}
				this->SetCurrentLine(Pairs[i].endline);
				return;
			}
			return;
		}
	}
}

void MacroController::ELSE() {
	if (this->isDebugMode()) this->AddDebug("ELSE");
	for (unsigned int i = 0; i < this->Pairs.size(); i++) {
		if (this->Pairs[i].type == 2) {

			bool tru = false;
			int line = this->GetCurrentLine();
			for (unsigned int x = 0; x <= Pairs[i].middlelines.size(); x++) {
				if (Pairs[i].middlelines[x] == line) {
					tru = true;
					break;
				}
			}
			if (!tru) continue;

			if (this->GetLastLine() == line - 1) {
				this->SetCurrentLine(Pairs[i].endline);
				return;
			}
			return;
		}
	}
}

void MacroController::ENDIF() {
	if (this->isDebugMode()) this->AddDebug("ENDIF");
	for (unsigned int i = 0; i < this->Pairs.size(); i++)
		if (this->Pairs[i].type == 2 && this->Pairs[i].endline == this->GetCurrentLine()) {
			this->SetCurrentLayer(Pairs[i].layer);
			return;
		}
}

void MacroController::CONTINUE() {
	if (this->isDebugMode()) this->AddDebug("CONTINUE");
	for (unsigned int i = 0; i < Pairs.size(); i++) {
		if (!pair_definitions[Pairs[i].type].breakable) continue;

		int line = this->GetCurrentLine();
		if ((Pairs[i].beginline > line && Pairs[i].endline < this->GetCurrentLine()) || Pairs[i].layer > this->GetCurrentLayer()) continue;
		this->SetCurrentLine(Pairs[i].beginline);
		return;
	}

}

void MacroController::RETURN() {
	if (this->isDebugMode()) this->AddDebug("RETURN");
	this->SetCurrentLine(this->GetScriptSize());
}

void MacroController::BREAK() {
	if (this->isDebugMode()) this->AddDebug("BREAK");
	for (unsigned int i = 0; i < Pairs.size(); i++) {
		if (!pair_definitions[Pairs[i].type].breakable) continue;

		int line = this->GetCurrentLine();
		if ((Pairs[i].beginline > line || Pairs[i].endline < line) || Pairs[i].layer > this->GetCurrentLayer()) continue;
		this->SetCurrentLine(Pairs[i].endline + 1);
		this->SetCurrentLayer(Pairs[i].layer);
		return;
	}
}

void MacroController::OVERWRITE_LIMIT(std::string new_limit) {
	if (this->isDebugMode()) this->AddDebug("OVERWRITE_LIMIT");
	int nlim = atoi(new_limit.c_str());
	if (nlim > 0) this->limit = nlim;
	else this->AddError("Limit must be bigger than 0. Current value: " + std::to_string(nlim));
}

void MacroController::DEBUG(std::string state) {
	this->AddDebug("DEBUG " + state);
	this->DebugMode(atoi(state.c_str()) > 0);
}

void MacroController::WRITE(std::vector<std::string> text) {
	std::string txt = "";
	for (unsigned int i = 0; i < text.size(); i++) {
		txt += text[i];
		if (i < text.size() - 1) txt += " ";
	}

	if (this->isDebugMode()) this->AddDebug("WRITE " + txt);

	if (txt.length() == 0) {
		this->AddError("Error in line " + std::to_string(this->GetCurrentLine()) + " in [WRITE]. Text can't be empty!");
		return;
	}
}


bool MacroController::isError() {
	return this->errors.size() > 0;
}

std::vector<std::string> MacroController::GetError(bool clear) {
	std::vector<std::string> temp = this->errors;
	if (clear) this->errors.clear();
	return temp;
}

void MacroController::ClearError() {
	this->errors.clear();
}

void MacroController::AddError(std::string err) {
	this->errors.push_back(err);
}

bool MacroController::isDebug() {
	return this->debug_lines.size() > 0;
}

bool MacroController::isDebugMode() {
	return this->debug_mode;
}

std::vector<std::string> MacroController::GetDebug(bool clear) {
	std::vector<std::string> temp = this->debug_lines;
	if (clear) this->debug_lines.clear();
	return temp;
}

void MacroController::ClearDebug() {
	this->debug_lines.clear();
}

void MacroController::AddDebug(std::string err) {
	this->debug_lines.push_back(err);
}

bool MacroController::IsVarName(std::string ctx) {
	if (ctx.length() >= 1 && ctx[0] < 0x30 || ctx[0] > 0x39) return true; return false;
}

bool MacroController::VVarExists(std::string name_) {
	if (!this->IsVarName(name_)) {
		this->AddError("[" + name_ + "] is not a valid [VAR] name.");
		return false;
	}
	for (unsigned int i = 0; i < this->virtual_vars.size(); i++)
		if (this->virtual_vars[i].name == name_) { return true; }
	return false;
}

int MacroController::GetVVar(std::string name_) {
	if (!this->IsVarName(name_)) {
		return atoi(name_.c_str());
	}
	if (!this->VVarExists(name_)) {
		this->AddError("[" + name_ + "] is NOT defined.");
		return 0;
	}
	for (unsigned int i = 0; i < this->virtual_vars.size(); i++)
		if (this->virtual_vars[i].name == name_) { return this->virtual_vars[i].value; }
	return 0;
}

bool MacroController::SetVVar(std::string name_, std::string value_) {
	if (!this->IsVarName(name_)) {
		this->AddError("[" + name_ + "] is not a valid [VAR] name.");
		return false;
	}
	int val = this->IsVarName(value_) ? GetVVar(value_) : atoi(value_.c_str());
	for (unsigned int i = 0; i < this->virtual_vars.size(); i++)
		if (this->virtual_vars[i].name == name_) {
			this->virtual_vars[i].value = val;
			return true;
		}
	var temp; temp.name = name_; temp.value = val;
	this->virtual_vars.push_back(temp);
	return true;
}

int MacroController::Step() {
	if (!this->isReady()) return 1;
	int lineID = 0;
	std::vector< std::string > line;
	while ((line.size() <= 0 || line[0].length() <= 0) && (lineID < (int)this->GetScriptSize())) {
		lineID = this->GetCurrentLine();
		line = this->GetScriptLine(lineID);
		if (line.size() <= 0 || line[0].length() <= 0) this->SetCurrentLine(lineID + 1);
	}
	this->ResetLineChangeBuffer();
	if (line.size() <= 0 || line[0].length() <= 0) return 0;
	this->limit_counter++;

	int functionID = atoi(line[0].c_str());
	line.erase(line.begin());
	this->CallByID(functionID, line);

	if (!this->LineChangeBuffer()) this->SetCurrentLine(this->GetCurrentLine() + 1);

	if (this->isError()) return -1;
	return 1;
}
