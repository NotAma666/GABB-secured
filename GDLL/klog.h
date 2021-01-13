#pragma once
#include <Windows.h>
#include <vector>
#include <string>

struct mouseButtonEvent {
	bool isDown;
	POINT pos;
	int key;
};

struct winpos {
	winpos() { this->clear(); }
	std::vector<std::pair<bool, unsigned int>> vKeys; //isPressed, vKey
	std::vector<mouseButtonEvent> mouseEvents; //isDown, pos, key
	POINT mouse_last_pos;
	bool mouse_l_button_state;
	bool mouse_r_button_state;
	short mouse_wheel_delta;
	bool is_absoulte = false;

	void clear() {
		vKeys.clear();
		mouseEvents.clear(); 
		GetCursorPos(&(this->mouse_last_pos));
		mouse_l_button_state = false;
		mouse_r_button_state = false;
		mouse_wheel_delta = 0;
	}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	winpos * posWnd = (winpos*)GetWindowLong(hwnd, GWLP_USERDATA);
	UINT dwSize;
	RAWINPUTDEVICE rid[2];
	RAWINPUT *buffer;

	switch (msg)
	{
	case WM_QUIT:
		PostQuitMessage(0);
		break;

	/*case WM_NCCREATE: {
		
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
		SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
	}*/

	case WM_CREATE: {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);//winpos * posWnd2 = (winpos*)lParam;
		//SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER);
		rid[0].usUsagePage = 0x01;
		rid[0].usUsage = 0x06;
		rid[0].dwFlags = RIDEV_INPUTSINK;
		rid[0].hwndTarget = hwnd;

		rid[1].usUsagePage = 0x01;
		rid[1].usUsage = 0x02;
		rid[1].dwFlags = RIDEV_INPUTSINK;
		rid[1].hwndTarget = hwnd;

		if (!RegisterRawInputDevices(rid, 2, sizeof(rid[0]))) {
			MessageBox(NULL, L"Registering raw input device failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
			return -1;
		}
		break;

	}
	case WM_INPUT: {
		if (posWnd == NULL) return 0;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
		buffer = (RAWINPUT*)HeapAlloc(GetProcessHeap(), 0, dwSize);

		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, buffer, &dwSize, sizeof(RAWINPUTHEADER)) == dwSize)
		{
			//cout(std::to_wstring(posWnd->mouse_last_pos.x));
			if (buffer->header.dwType == RIM_TYPEKEYBOARD)
			{
				if (buffer->data.keyboard.Message == WM_KEYDOWN) {
					posWnd->vKeys.push_back({ true, buffer->data.keyboard.VKey });
				}
				else if (buffer->data.keyboard.Message == WM_KEYUP) posWnd->vKeys.push_back({ false, buffer->data.keyboard.VKey });
			}
			else if (buffer->header.dwType == RIM_TYPEMOUSE) {
				//posWnd->mouse_last_pos = { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY };
				posWnd->is_absoulte = (buffer->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE);
				if (posWnd->is_absoulte) {
					posWnd->mouse_last_pos.x += buffer->data.mouse.lLastX;
					posWnd->mouse_last_pos.y += buffer->data.mouse.lLastY;
				}
				else GetCursorPos(&(posWnd->mouse_last_pos));
				
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) {
					posWnd->mouseEvents.push_back({ true, { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY }, 0 });
				}
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) {
					posWnd->mouseEvents.push_back({ false, { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY }, 0 });
				}
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) {
					posWnd->mouseEvents.push_back({ true, { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY }, 1 });
				}
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) {
					posWnd->mouseEvents.push_back({ false, { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY }, 1 });
				}
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) {
					posWnd->mouseEvents.push_back({ true, { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY }, 2 });
				}
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) {
					posWnd->mouseEvents.push_back({ false, { buffer->data.mouse.lLastX, buffer->data.mouse.lLastY }, 2 });
				}
				if (buffer->data.mouse.usButtonFlags & RI_MOUSE_WHEEL) {
					posWnd->mouseEvents.push_back({ false, { (short)buffer->data.mouse.usButtonData, 0 }, 3 });
				}

				//else MessageBox(NULL, std::wstring(L"ERR " + std::to_wstring(buffer->data.mouse.usButtonFlags)).c_str(), L"test", MB_OK);
			}
		}

		// free the buffer
		HeapFree(GetProcessHeap(), 0, buffer);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

/*void MSGLoop(MSG * msg) {
	while (GetMessage(msg, NULL, 0, 0) > 0) {
		TranslateMessage(msg);
		DispatchMessage(msg);
	}
}*/
	
/*class KLOG {
public:
	winpos * GetEvents() {
		return &(this->eventPos);
	}

	KLOG();
	inline bool isInitialised() { return this->init; }
private:
	const wchar_t * g_szClassName = L"MBWnd";
	HINSTANCE hInstance = GetModuleHandle(NULL);

	bool init = false;
	HWND hwnd;
	winpos eventPos;
};

KLOG::KLOG() {
	if (this->hInstance == NULL) return;
	WNDCLASSEX wc;
	//MSG msg;

	// register window class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = this->hInstance;
	wc.lpszClassName = this->g_szClassName;
	wc.cbClsExtra = 1;

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	// create message-only window
	this->hwnd = CreateWindowEx( 0, g_szClassName, NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, this->hInstance, &(this->eventPos));

	if (!this->hwnd) {
		MessageBox(NULL, (L"Window Creation Failed!: " + std::to_wstring(GetLastError())).c_str(), L"Error!", MB_ICONEXCLAMATION | MB_OK);
		UnregisterClassW(this->g_szClassName, this->hInstance);
		return;
	}
	SetClassLongPtr(this->hwnd, 1, (int)&(this->eventPos));

	//std::async(std::launch::async, MSGLoop, &msg);

	this->init = true;
}*/