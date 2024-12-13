#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void download_file(const char *url) {
    // Extract file extension from URL
    const char *filename = strrchr(url, '/');  // Find last '/' to extract filename
    if (filename) {
        filename++; // Skip the '/' character
    } else {
        filename = "downloaded_file";  // Default filename if URL has no '/'
    }

    // Prepare the PowerShell command to download the file
    char command[1024];
    snprintf(command, sizeof(command),
             "powershell -Command \"Invoke-WebRequest -Uri '%s' -OutFile '%s'\"",
             url, filename);

    // Execute the command
    if (system(command) == 0) {
        printf("Download completed successfully. File saved as %s.\n", filename);
    } else {
        printf("Download failed.\n");
    }
}

int main() {
    char url[512];

    // Get URL input from the user
    printf("Enter the URL to download: ");
    fgets(url, sizeof(url), stdin);

    // Remove the newline character at the end of the URL
    url[strcspn(url, "\n")] = 0;

    // Call the function to download the file
    download_file(url);

    return 0;
}
