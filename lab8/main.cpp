#include <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>
#include <windows.h>

using namespace std;

typedef struct fparam {
    int maxDuration;
    int duration;
    string msg;
}fparam, *pfparam;

/*void chronometer(int maxDurationSeconds) {
    int currentDurationSeconds = 0;
    while (currentDurationSeconds <= maxDurationSeconds) {
        cout<<currentDurationSeconds<<" seconds passed"<<endl;
        currentDurationSeconds++;
        this_thread::sleep_for (chrono::seconds(1));
    }
}
void showMessageWithDelay(string msg, int delaySeconds, int maxDurationSeconds) {
    int currentDurationSeconds = 0;
    while (currentDurationSeconds <= maxDurationSeconds) {
        if (currentDurationSeconds % delaySeconds == 0 && currentDurationSeconds != 0)
            cout<<msg<<currentDurationSeconds<<endl;
        currentDurationSeconds++;
        this_thread::sleep_for (chrono::seconds(1));
    }
}*/
DWORD WINAPI  chronometer(LPVOID lpParam) {
    pfparam params = (pfparam) lpParam;
    int maxDurationSeconds = params->maxDuration;
    int currentDurationSeconds = 0;
    while (currentDurationSeconds <= maxDurationSeconds) {
        cout<<currentDurationSeconds<<" seconds passed"<<endl;
        currentDurationSeconds++;
        Sleep(1000);
    }
    return 0;
}
DWORD WINAPI  showMessageWithDelay(LPVOID lpParam) {
    pfparam params = (pfparam) lpParam;
    int maxDurationSeconds = params->maxDuration;
    int delaySeconds = params->duration;
    string msg = params->msg;
    int currentDurationSeconds = 0;
    while (currentDurationSeconds <= maxDurationSeconds) {
        if (currentDurationSeconds % delaySeconds == 0 && currentDurationSeconds != 0)
            cout<<msg<<endl;
        currentDurationSeconds++;
        Sleep(1000);
    }
}


int main() {
    /*chronometer(60);
    showMessageWithDelay("msg", 2, 10);*/

    const int FUNC_NUM = 3;

    HANDLE  hThreadArray[FUNC_NUM];
    DWORD   dwThreadIdArray[FUNC_NUM];
    pfparam params[FUNC_NUM];

    params[0] = (pfparam) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(fparam));
    params[1] = (pfparam) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(fparam));
    params[2] = (pfparam) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(fparam));
    /*params[0]->duration = 60;*/
    params[0]->maxDuration = 60;
    /*params[0]->msg =*/
    params[1]->duration = 5;
    params[1]->maxDuration = 60;
    params[1]->msg = "i am a message";
    params[2]->duration = 7;
    params[2]->maxDuration = 60;
    params[2]->msg = "another message";

    hThreadArray[0] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size
            chronometer,       // thread function name
            params[0],          // argument to thread function
            CREATE_SUSPENDED,                      // use default creation flags
            &dwThreadIdArray[0]);
    hThreadArray[1] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size
            showMessageWithDelay,       // thread function name
            params[1],          // argument to thread function
            CREATE_SUSPENDED,                      // use default creation flags
            &dwThreadIdArray[1]);
    hThreadArray[2] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size
            showMessageWithDelay,       // thread function name
            params[2],          // argument to thread function
            CREATE_SUSPENDED,                      // use default creation flags
            &dwThreadIdArray[2]);

    ResumeThread(hThreadArray[0]);
    ResumeThread(hThreadArray[1]);
    ResumeThread(hThreadArray[2]);

    WaitForMultipleObjects(3, hThreadArray, TRUE, INFINITE);


    return 0;
}