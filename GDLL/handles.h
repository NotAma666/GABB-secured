#pragma once
#include <string>
#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <Shlwapi.h>
#include <winternl.h>

#pragma comment(lib,"ntdll.lib")

//#define NT_SUCCESS(x) ((x) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH 0xc0000004

#define SystemHandleInformation 16
#define ObjectBasicInformation 0
#define ObjectNameInformation 1
#define ObjectTypeInformation 2

typedef NTSTATUS(NTAPI *_NtQuerySystemInformation)(
	ULONG SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);
typedef NTSTATUS(NTAPI *_NtDuplicateObject)(
	HANDLE SourceProcessHandle,
	HANDLE SourceHandle,
	HANDLE TargetProcessHandle,
	PHANDLE TargetHandle,
	ACCESS_MASK DesiredAccess,
	ULONG Attributes,
	ULONG Options
	);
typedef NTSTATUS(NTAPI *_NtQueryObject)(
	HANDLE ObjectHandle,
	ULONG ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);

/*typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;*/

typedef struct _SYSTEM_HANDLE
{
	ULONG ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, *PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION
{
	ULONG HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE
{
	NonPagedPool,
	PagedPool,
	NonPagedPoolMustSucceed,
	DontUseThisType,
	NonPagedPoolCacheAligned,
	PagedPoolCacheAligned,
	NonPagedPoolCacheAlignedMustS
} POOL_TYPE, *PPOOL_TYPE;

typedef struct _OBJECT_TYPE_INFORMATION
{
	UNICODE_STRING Name;
	ULONG TotalNumberOfObjects;
	ULONG TotalNumberOfHandles;
	ULONG TotalPagedPoolUsage;
	ULONG TotalNonPagedPoolUsage;
	ULONG TotalNamePoolUsage;
	ULONG TotalHandleTableUsage;
	ULONG HighWaterNumberOfObjects;
	ULONG HighWaterNumberOfHandles;
	ULONG HighWaterPagedPoolUsage;
	ULONG HighWaterNonPagedPoolUsage;
	ULONG HighWaterNamePoolUsage;
	ULONG HighWaterHandleTableUsage;
	ULONG InvalidAttributes;
	GENERIC_MAPPING GenericMapping;
	ULONG ValidAccess;
	BOOLEAN SecurityRequired;
	BOOLEAN MaintainHandleCount;
	USHORT MaintainTypeList;
	POOL_TYPE PoolType;
	ULONG PagedPoolUsage;
	ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;


//for getting an address of a procedure in memory
PVOID GetLibraryProcAddress(std::string LibraryName, std::string ProcName)
{
	return GetProcAddress(GetModuleHandleA(LibraryName.c_str()), ProcName.c_str());
}

std::wstring PathTarget(std::wstring path)
{
	std::wstring buffer = L"";
	for (int i = path.length() - 1; i >= 0; i--)
	{
		if (path[i] == '\\' || path[i] == '/') break;
		else buffer = path[i] + buffer;
	}
	return buffer;
}

int EnumerateHandles(DWORD PID, HANDLE ProcessHandle)
{

	_NtQuerySystemInformation NtQuerySystemInformation = (_NtQuerySystemInformation)GetLibraryProcAddress("ntdll.dll", "NtQuerySystemInformation");
	if (NtQuerySystemInformation == NULL) return GetLastError();
	_NtDuplicateObject NtDuplicateObject = (_NtDuplicateObject)GetLibraryProcAddress("ntdll.dll", "NtDuplicateObject");
	if (NtDuplicateObject == NULL) return GetLastError();
	_NtQueryObject NtQueryObject = (_NtQueryObject)GetLibraryProcAddress("ntdll.dll", "NtQueryObject");
	if (NtQueryObject == NULL) return GetLastError();
	NTSTATUS Status;
	PSYSTEM_HANDLE_INFORMATION HandleInfo;
	DWORD HandleInfoSize = 0x10000;
	//HANDLE ProcessHandle;
	ULONG i;

	//ProcessHandle = OpenProcess( PROCESS_DUP_HANDLE, false, PID );
	//if( ProcessHandle == NULL ) cout( GetLastError() );
	HandleInfo = (PSYSTEM_HANDLE_INFORMATION)malloc(HandleInfoSize);

	while ((Status = NtQuerySystemInformation(SystemHandleInformation, HandleInfo, HandleInfoSize, 0) == STATUS_INFO_LENGTH_MISMATCH))
	{
		HandleInfo = (PSYSTEM_HANDLE_INFORMATION)realloc(HandleInfo, HandleInfoSize *= 2);
	}

	if (!NT_SUCCESS(Status))
	{
		free(HandleInfo);
		return GetLastError();
	}

	for (i = 0; i < HandleInfo->HandleCount; i++)
	{
		SYSTEM_HANDLE Handle = HandleInfo->Handles[i];
		HANDLE DupHandle = 0;
		POBJECT_TYPE_INFORMATION ObjectTypeInfo;
		LPVOID ObjectNameInfo;
		UNICODE_STRING ObjectName;
		ULONG ReturnLength;

		if (Handle.ProcessId != PID) {
			continue;
		}
		
		
		if (!SUCCEEDED(NtDuplicateObject(ProcessHandle, (HANDLE)Handle.Handle, GetCurrentProcess(), &DupHandle, 0, 0, 0))) continue;
		ObjectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(0x1000);
		NtQueryObject(DupHandle, ObjectTypeInformation, ObjectTypeInfo, 0x1000, 0);

		if ((int)Handle.GrantedAccess == 0x0012019F) {
			free(ObjectTypeInfo);
			CloseHandle(DupHandle);
			continue;
		}

		//Query fail
		ObjectNameInfo = malloc(0x1000);
		if (!NT_SUCCESS(NtQueryObject(DupHandle, ObjectNameInformation, ObjectNameInfo, 0x1000, &ReturnLength))) {
			ObjectNameInfo = realloc(ObjectNameInfo, ReturnLength);
			if (!NT_SUCCESS(NtQueryObject(DupHandle, ObjectNameInformation, ObjectNameInfo, ReturnLength, NULL))) {
				free(ObjectTypeInfo);
				free(ObjectNameInfo);
				CloseHandle(DupHandle);
				continue;
			}
		}

		ObjectName = *(PUNICODE_STRING)ObjectNameInfo;
		std::wstring ObjectBuffer = ObjectTypeInfo->Name.Buffer;
		if (ObjectBuffer.find(L"Mutant") != std::wstring::npos && ObjectName.Length && PathTarget(ObjectName.Buffer) == L"Growtopia") {
			DuplicateHandle(ProcessHandle, (HANDLE)Handle.Handle, NULL, NULL, 0, 1, DUPLICATE_CLOSE_SOURCE);
			free(ObjectTypeInfo);
			free(ObjectNameInfo);
			CloseHandle(DupHandle);
			continue;
		}
		free(ObjectTypeInfo);
		free(ObjectNameInfo);
		CloseHandle(DupHandle);
	}
	free(HandleInfo);
	return 0;
}

HWND h_HWND = NULL;
BOOL CALLBACK EnumWindowsProcMyGt(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);

	if (lpdwProcessId != lParam) return true;
	char buff[255];

	if (!IsWindowVisible(hwnd)) return true;

	GetWindowTextA(hwnd, (LPSTR)buff, 254);
	if (std::string(buff).find("Growtopia") != std::string::npos)
	{
		h_HWND = hwnd;
		return false;
	}

	return true;
}

HWND EnumWindowsMyGt(DWORD PID)
{
	h_HWND = NULL;
	EnumWindows(EnumWindowsProcMyGt, PID);
	return h_HWND;
}