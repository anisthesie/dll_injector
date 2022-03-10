#include "dll_inject.h"

int main(int argc, char** argv) {
    if(argc < 3) {
        printf("Usage: dllinject <pid> <DLL path>");
        return -1;
    }
    int processName = atoi(argv[1]);
    char* dllPath = argv[2];
    inject(processName, dllPath);
    return 0;
}
