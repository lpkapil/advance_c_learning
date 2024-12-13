#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void delete_exe_files_except_self(const char *directory, const char *selfPath) {
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;

    // Prepare the search pattern to find all files with .exe extension
    char searchPattern[MAX_PATH];
    snprintf(searchPattern, sizeof(searchPattern), "%s\\*.exe", directory);

    // Find the first .exe file
    hFind = FindFirstFile(searchPattern, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No .exe files found in the directory.\n");
        return;
    }

    // Iterate over all files and delete them
    do {
        // Skip directories
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            // Construct full path to the file
            char filePath[MAX_PATH];
            snprintf(filePath, sizeof(filePath), "%s\\%s", directory, findFileData.cFileName);

            // Check if the file is the same as the current executable (self)
            if (strcmp(filePath, selfPath) == 0) {
                printf("Skipping own executable: %s\n", filePath);
                continue; // Skip deleting the executable itself
            }

            // Try to delete the file
            if (DeleteFile(filePath)) {
                printf("Deleted: %s\n", filePath);
            } else {
                printf("Failed to delete: %s\n", filePath);
            }
        }
    } while (FindNextFile(hFind, &findFileData) != 0);

    // Close the find handle
    FindClose(hFind);
}

int main() {
    char currentDir[MAX_PATH];
    char selfPath[MAX_PATH];

    // Get the current working directory
    if (GetCurrentDirectory(MAX_PATH, currentDir) == 0) {
        printf("Error getting current directory.\n");
        return 1;
    }

    // Get the path of the running executable
    if (GetModuleFileName(NULL, selfPath, MAX_PATH) == 0) {
        printf("Error getting executable file path.\n");
        return 1;
    }

    printf("Deleting all .exe files in the directory: %s\n", currentDir);

    // Call function to delete .exe files except the executable itself
    delete_exe_files_except_self(currentDir, selfPath);

    return 0;
}
