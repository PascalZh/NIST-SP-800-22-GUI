#include "framework.h"
#include "log.h"
#include <stdarg.h>

extern HWND hEdit;

char* convert_newline(char* input) {
	size_t input_len = strlen(input);
	size_t output_len = 0;
	size_t i = 0, j = 0;
	char* output = NULL;
	for (i = 0; i < input_len; i++) {
		if (input[i] == '\n') {
			output_len++;
		}
		output_len++;
	}
	output_len++; // add space for null terminator
	output = (char*)malloc(output_len);
	if (output == NULL) {
		return NULL;
	}
	memset(output, 0, output_len);
	for (i = 0, j = 0; i < input_len; i++, j++) {
		if (input[i] == '\n') {
			output[j++] = '\r';
		}
		output[j] = input[i];
	}
	output[j] = '\0';
	return output;
}
extern "C" {


	void mylog(const char* msg)
	{
		static WCHAR szBuffer[1024 * 512];
		static size_t end = 0;

		// Convert WChar to Multibyte
		DWORD dBufSize = MultiByteToWideChar(CP_OEMCP, 0, msg, -1, NULL, 0);
		WCHAR* dBuf = new WCHAR[dBufSize];
		memset(dBuf, 0, dBufSize);
		int nRet = MultiByteToWideChar(CP_OEMCP, 0, msg, -1, dBuf, dBufSize);

		for (size_t i = 0; i < dBufSize - 1; i++) {
			if (end + i >= 1024 * 512) {
				break;
			}
			if (dBuf[i] == L'\n') {
				szBuffer[end + i] = L'\r';
				end++;
				szBuffer[end + i] = L'\n';
			}
			else {
				szBuffer[end + i] = dBuf[i];
			}
		}
		end += dBufSize - 1;

		//SetWindowText(hEdit, szBuffer);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)szBuffer);

		int len = GetWindowTextLength(hEdit);
		SendMessage(hEdit, EM_SETSEL, len, len);
		SendMessage(hEdit, EM_SCROLLCARET, 0, 0);

		delete[] dBuf;
	}

	int mylog_printf(const char* fmt, ...)
	{
		static char buf[1024 * 128];
		va_list args;
		va_start(args, fmt);
		int result = vsprintf(buf, fmt, args);
		va_end(args);

		mylog(buf);
		return result;
	}

}