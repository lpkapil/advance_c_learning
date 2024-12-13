#include <windows.h>

int main() {
    // Step 1: Load user32.dll dynamically
    HINSTANCE hDll = LoadLibrary("user32.dll");
    if (hDll == NULL) {
        printf("Error loading user32.dll: %ld\n", GetLastError());
        return 1;
    }

    // Step 2: Get the address of the 'MessageBoxA' function
    typedef int (WINAPI *MessageBoxAFunc)(HWND, LPCSTR, LPCSTR, UINT);
    MessageBoxAFunc MessageBoxA = (MessageBoxAFunc)GetProcAddress(hDll, "MessageBoxA");

    if (MessageBoxA == NULL) {
        printf("Error loading MessageBoxA: %ld\n", GetLastError());
        FreeLibrary(hDll);
        return 1;
    }

    // Step 3: Call the MessageBoxA function
    MessageBoxA(NULL, "Hello from the DLL!", "Test Message", MB_OK);

    // Step 4: Free the DLL
    FreeLibrary(hDll);
    return 0;
}
