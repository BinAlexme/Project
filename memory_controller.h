//
// Created by Админ on 24.10.2022.
//

#ifndef PROJECT1_MEMORY_CONTROLLER_H
#define PROJECT1_MEMORY_CONTROLLER_H
#include "include.h"

class memory_controller {
public:
    memory_controller() : memory_controller("Counter-Strike: Global Offensive - Direct3D 9"){}
    memory_controller(const CHAR* name);
    DWORD process_id;
    HWND hwnd;
    HANDLE handle;
    void setNewWindow(const CHAR* name);
    uintptr_t GetModuleBaseAddress(const char *module_name);
    template<typename t> t RPM(DWORD address) {
        t buffer;
        ReadProcessMemory(handle, (LPCVOID)address, &buffer, sizeof(t), nullptr);
        return buffer;
    }

    template<typename t> void WPM(DWORD address, t value) {
        WriteProcessMemory(handle, (LPVOID)address, &value, sizeof(t), nullptr);
    }
};


#endif //PROJECT1_MEMORY_CONTROLLER_H
