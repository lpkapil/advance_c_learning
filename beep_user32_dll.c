#include <windows.h>
#include <stdio.h>

int main() {
    // Load user32.dll dynamically (although it's already loaded by default, this is for demonstration)
    HINSTANCE hDll = LoadLibrary("user32.dll");
    if (hDll == NULL) {
        printf("Error loading user32.dll: %ld\n", GetLastError());
        return 1;
    }

    // Get the address of the MessageBeep function
    typedef BOOL (WINAPI *MessageBeepFunc)(UINT);
    MessageBeepFunc MessageBeepPtr = (MessageBeepFunc)GetProcAddress(hDll, "MessageBeep");
    if (MessageBeepPtr == NULL) {
        printf("Error finding MessageBeep function: %ld\n", GetLastError());
        FreeLibrary(hDll);
        return 1;
    }

    // Play a simple beep
    if (MessageBeepPtr(MB_OK)) {
        printf("Beep played successfully.\n");
    } else {
        printf("Error occurred while playing beep: %ld\n", GetLastError());
    }

    // Free the DLL
    FreeLibrary(hDll);
    return 0;
}
