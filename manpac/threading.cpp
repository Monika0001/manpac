#include <iostream>
#include <thread>
#include <windows.h>

// First function to run on a separate thread
void function1()
{
    SetThreadAffinityMask(GetCurrentThread(), 1);
    for (int i = 0; i < 500; i++)
    {
        std::cout << "Function 1 is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Second function to run on a separate thread
void function2()
{
    SetThreadAffinityMask(GetCurrentThread(), 2);
    for (int i = 0; i < 500; i++)
    {
        std::cout << "Function 2 is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

int main()
{
    // Create two thread objects and start them
    std::thread thread1(function1);
    std::thread thread2(function2);

    // Wait for the threads to finish
    thread1.join();
    thread2.join();

    // Threads are now closed
    std::cout << "Threads are closed" << std::endl;

    return 0;
}