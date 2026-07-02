#include <iostream>
#include <windows.h>
#include <iomanip>

void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printHeader1() {
    std::cout << "--- System Resource Monitor ---" << std::endl;
}

void getMemoryUsage() {
    static DWORDLONG maxramused = 0;
    static DWORDLONG minramused = 0;

    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);

    DWORDLONG totalPhysMem = memInfo.ullTotalPhys / 1024 / 1024;
    DWORDLONG physMemUsed = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / 1024 / 1024;

    double usagePercent = (double)physMemUsed / (double)totalPhysMem * 100.0;

    if (physMemUsed > maxramused) maxramused = physMemUsed;
    if (minramused == 0 || physMemUsed < minramused) minramused = physMemUsed;

    setCursorPosition(0, 2);

    std::cout << "RAM Usage: " << std::fixed << std::setprecision(1) << usagePercent << "% ("
        << physMemUsed << " MB / " << totalPhysMem << " MB)    " << std::endl;
    std::cout << "Max RAM used: " << maxramused << " MB    " << std::endl;
    std::cout << "Min RAM used: " << minramused << " MB    " << std::endl;
}

int main() {
    printHeader1();
    while (true) {
        getMemoryUsage();
        Sleep(1000);
    }
    return 0;
}