#include <windows.h>
#include <stdio.h>

int main() {
    // Step 1: Load kernel32.dll dynamically
    HINSTANCE hDll = LoadLibrary("kernel32.dll");
    if (hDll == NULL) {
        printf("Error loading kernel32.dll: %ld\n", GetLastError());
        return 1;
    }

    // Step 2: Get the address of the 'GetTickCount' function
    typedef DWORD (WINAPI *GetTickCountFunc)();
    GetTickCountFunc GetTickCount = (GetTickCountFunc)GetProcAddress(hDll, "GetTickCount");

    if (GetTickCount == NULL) {
        printf("Error finding GetTickCount: %ld\n", GetLastError());
        FreeLibrary(hDll);
        return 1;
    }

    // Step 3: Call the GetTickCount function
    DWORD tickCount = GetTickCount();
    
    // Convert milliseconds to human-readable format (hours, minutes, seconds)
    DWORD hours = tickCount / 3600000; // 1 hour = 3600000 milliseconds
    DWORD minutes = (tickCount % 3600000) / 60000; // 1 minute = 60000 milliseconds
    DWORD seconds = (tickCount % 60000) / 1000; // 1 second = 1000 milliseconds
    DWORD milliseconds = tickCount % 1000; // Remainder in milliseconds

    // Step 4: Print the result in a human-readable format
    printf("The system has been running for %lu hours, %lu minutes, %lu seconds, and %lu milliseconds.\n",
           hours, minutes, seconds, milliseconds);

    // Step 5: Free the DLL
    FreeLibrary(hDll);
    return 0;
}
