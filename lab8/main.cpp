#import <iostream>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <string>

using namespace std;

void chronometer(int maxDurationSeconds) {
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
}

int main() {


    //chronometer(60);
    showMessageWithDelay("msg", 2, 10);
    return 0;
}