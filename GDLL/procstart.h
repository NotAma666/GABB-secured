#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#define MAX_PIPE_BUFSIZE 4096

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#include "safety.h"


namespace PROCESS {
	bool Initialised = false;
	bool bit32 = true;

	void Init() {
		BOOL btt;
		bool procread = IsWow64Process(GetCurrentProcess(), &btt);
		bit32 = !btt;
		Initialised = procread;
	}

	struct pipeSet {
		HANDLE g_hChildStd_OUT_Rd = NULL;
		HANDLE g_hChildStd_OUT_Wr = NULL;
		HANDLE g_hChildStd_ERR_Rd = NULL;
		HANDLE g_hChildStd_ERR_Wr = NULL;
	};

	bool CreateChildProcess(wchar_t * command, pipeSet &pipes);
	std::string ReadFromPipe(pipeSet &pipes);

	std::string SystemCommand(std::wstring cmd) {
		pipeSet pipes;
		SECURITY_ATTRIBUTES sa;
		//printf("\n->Start of parent execution.\n");
		// Set the bInheritHandle flag so pipe handles are inherited.
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = TRUE;
		sa.lpSecurityDescriptor = NULL;
		// Create a pipe for the child process's STDERR.
		if (!CreatePipe(&(pipes.g_hChildStd_ERR_Rd), &(pipes.g_hChildStd_ERR_Wr), &sa, 0)) {
			return Safety::InsertKey("0 -1", "prockey64", 11);
		}
		// Ensure the read handle to the pipe for STDERR is not inherited.
		if (!SetHandleInformation(pipes.g_hChildStd_ERR_Rd, HANDLE_FLAG_INHERIT, 0)) {
			return Safety::InsertKey("0 -2", "prockey64", 11);
		}
		// Create a pipe for the child process's STDOUT.
		if (!CreatePipe(&(pipes.g_hChildStd_OUT_Rd), &(pipes.g_hChildStd_OUT_Wr), &sa, 0)) {
			return Safety::InsertKey("0 -3", "prockey64", 11);
		}
		// Ensure the read handle to the pipe for STDOUT is not inherited
		if (!SetHandleInformation(pipes.g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0)) {
			return Safety::InsertKey("0 -4", "prockey64", 11);
		}
		// Create the child process.
		wchar_t * comm = new wchar_t[cmd.length() + 1];
		for (unsigned int i = 0; i <= cmd.length(); i++) {
			if (i != cmd.length()) comm[i] = cmd[i];
			else comm[i] = '\0';
		}
		if (!CreateChildProcess(comm, pipes)) {
			return Safety::InsertKey("0 -5", "prockey64", 11);
		}

		// Read from pipe that is the standard output for child process.
		std::string result = ReadFromPipe(pipes);

		CloseHandle(pipes.g_hChildStd_ERR_Rd);
		CloseHandle(pipes.g_hChildStd_OUT_Rd);

		return result;
	}

	bool CreateChildProcess(wchar_t * command, pipeSet &pipes) {
		PROCESS_INFORMATION piProcInfo;
		STARTUPINFO siStartInfo;
		bool bSuccess = FALSE;

		ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));

		ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
		siStartInfo.cb = sizeof(STARTUPINFO);
		siStartInfo.hStdError = pipes.g_hChildStd_ERR_Wr;
		siStartInfo.hStdOutput = pipes.g_hChildStd_OUT_Wr;
		siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

		bSuccess = CreateProcess(NULL, command, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &siStartInfo, &piProcInfo);

		CloseHandle(piProcInfo.hProcess);
		CloseHandle(piProcInfo.hThread);
		CloseHandle(pipes.g_hChildStd_ERR_Wr);
		CloseHandle(pipes.g_hChildStd_OUT_Wr);
		if (!bSuccess) return 0;
		return 1;
	}

	std::string ReadFromPipe(pipeSet &pipes) {
		DWORD dwRead;
		CHAR chBuf[MAX_PIPE_BUFSIZE];
		bool bSuccess = FALSE;
		std::string out = "", err = "";
		for (;;) {
			bSuccess = ReadFile(pipes.g_hChildStd_OUT_Rd, chBuf, MAX_PIPE_BUFSIZE, &dwRead, NULL);
			if (!bSuccess || dwRead == 0) break;
			out += std::string(chBuf, dwRead);
		}
		dwRead = 0;
		for (;;) {
			bSuccess = ReadFile(pipes.g_hChildStd_ERR_Rd, chBuf, MAX_PIPE_BUFSIZE, &dwRead, NULL);
			if (!bSuccess || dwRead == 0) break;
			err += std::string(chBuf, dwRead);
		}
		if (out.length() == 0) return err;
		return out;
	}
}
std::vector<std::string> Destroy(std::string ctx, std::string delimiter);

std::pair<bool, int> ReadMemoryInt(std::wstring title, std::wstring moduleName, DWORD base_offset, std::vector<DWORD> offset) {
	if (!PROCESS::Initialised) { PROCESS::Init(); if (!PROCESS::Initialised) { cout("PROCESS namespace was not initialised! Failed to read!"); return { 0, 11 }; } }
	std::string ctx = ws2s(title) + "\\\n" +
		ws2s(moduleName) + "\\\n" +
		std::to_string(base_offset) + "\\\n";
	for (unsigned int i = 0; i < offset.size(); i++) ctx += std::to_string(offset[i]) + "\\\n";

	std::string resline = Safety::RemoveKey(PROCESS::SystemCommand((PROCESS::bit32 ? L"memscan32.exe " : L"memscan64.exe ") + s2ws(Safety::InsertKey(ctx, "prockey64", 13))), "prockey64", 11) + " ";
	std::vector<std::string> res = Destroy(resline, " ");
	cout((PROCESS::bit32 ? "memscan32.exe " : "memscan64.exe ") + ctx);
	if (res.size() >= 2) cout(res[0] + " " + res[1]);
	return ((res.size() >= 2) ? std::pair<bool, int>{ atoi(res[0].c_str()), atoi(res[1].c_str()) } : std::pair<bool, int>{0, 10});
}