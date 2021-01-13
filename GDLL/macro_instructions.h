//#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <sstream>

int HexCharToInt(char HexChar); /*{
	std::string chars = "0123456789abcdef";
	int posX = chars.find(HexChar);
	return posX == std::string::npos ? -1 : posX;
}*/

std::string IntToHex(int INT); /*{
	std::stringstream stream;
	stream << std::hex << INT;
	return std::string(stream.str());
}*/

void SimulateVKWrite(SHORT vk, bool down) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0; // hardware scan code for key
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = vk;
	ip.ki.dwFlags = down ? 0 : KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}

void SimulateWrite(std::string ctx) {
    INPUT ip;
    HKL currentKBL = GetKeyboardLayout(0);

    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    bool shifted;
    for (unsigned int i = 0; i < ctx.length(); i++) {
        shifted = false;
		SHORT vk = VkKeyScanExA(ctx[i], currentKBL);
        if (HIBYTE(vk) & 1) {
            shifted = true;
        }

		ip.ki.dwFlags = 0;
		if (shifted) {
			ip.ki.wVk = VK_SHIFT;
			SendInput(1, &ip, sizeof(INPUT));
		}

		ip.ki.wVk = LOBYTE(vk);
		SendInput(1, &ip, sizeof(INPUT));
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
		SendInput(1, &ip, sizeof(INPUT));

		if (shifted) {
			ip.ki.wVk = VK_SHIFT;
			SendInput(1, &ip, sizeof(INPUT));
		}
		
        for (int j = 0; j < 2; j++) {
            if( j == 0 ) ip.ki.dwFlags = 0;
            else ip.ki.dwFlags = KEYEVENTF_KEYUP;

            if (j != 0) {
                ip.ki.wVk = LOBYTE(vk);
                SendInput(1, &ip, sizeof(INPUT));
            }

			if (shifted) { //shift
				ip.ki.wVk = VK_SHIFT;
				SendInput(1, &ip, sizeof(INPUT));
			}

            if (j == 0) {
                ip.ki.wVk = LOBYTE(vk);
                SendInput(1, &ip, sizeof(INPUT));
                Sleep(10);
            }
        }
    }
}
