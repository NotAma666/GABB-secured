#pragma once
#include <Windows.h>
#include <string>

HKL Layout = GetKeyboardLayout(NULL);
//`@$
std::string key_mapped_shifted = "~!@#$%^&*()_+{}|:\"<>?";
std::string key_mapped_tolower = "`1234567890-=[]\\;',./";
int key_mapped_base[21] = { 192, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 189, 187, 219, 221, 220, 186, 222, 188, 190, 191 };

WORD keymap(char c) {
	for (unsigned i = 0; i < key_mapped_shifted.size(); i++) if (key_mapped_shifted[i] == c) return MAKEWORD(key_mapped_base[i], 1);
	for (unsigned i = 0; i < key_mapped_tolower.size(); i++) if (key_mapped_tolower[i] == c) return MAKEWORD(key_mapped_base[i], 0);
	WORD vk = VkKeyScanExA(c, Layout);
	return vk;
}