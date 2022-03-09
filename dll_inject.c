#include "dll_inject.h"

void inject(int pid, char* dll_path){
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processId);
    if(!process) {
        printf("Could not open process with pid: %d \n", pid);
        return;
    }

    HMODULE kernel32_module = GetModuleHandle(L"kernel32.dll");
    if(!kernel32_module) {
        printf("Could not find kernel32.dll in process memory.");
        return;
    }

    DWORD LoadLibraryA_addr = GetProcAddress(kernel32_module, "LoadLibraryA");
    if(!LoadLibraryA_addr) {
        printf("Could not get LoadLibraryA address. \n");
        return;
    }
    LPVOID dllpath_addr = VirtualAllocEx(process, NULL, sizeof(dll_path), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    WriteProcessMemory(process, dllpath_addr, dllPath, sizeof(dll_path), 0);
    HANDLE remoteThread = CreateRemoteThread(process, NULL, NULL, (LPTHREAD_START_ROUTINE) LoadLibraryA_addr, dllpath_addr, NULL, NULL);
    if(!remoteThread) {
        printf("Creating remote thread failed \n" );
        return;
    }
    WaitForSingleObject(remoteThread, INT_MAX);
    VirtualFreeEx(process, dllpath_addr, sizeof(dllPath), MEM_FREE);
}