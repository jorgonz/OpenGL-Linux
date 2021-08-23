#include "includes/LoadingBar.h"
#include <iostream>
#include <math.h>

LoadingBar::LoadingBar(std::string processName, int tasksSize)
{
    this->processName = processName;
    this->tasksCompleted = 0;
    this->tasksSize = tasksSize;
    
    std::cout << "Loading " << processName << std::endl;
    DisplayProgress();
}

void LoadingBar::DisplayProgress()
{
    float progress = (static_cast<float>(this->tasksCompleted) / static_cast<float>(this->tasksSize));
    int progressBarWidth = 50;
    int currentPosition = progress * 50;
    char loadingBarChar;
    std::cout << "[";
    for(int i = 0; i < 50; i++)
    {
        if(i < currentPosition)
        {
            loadingBarChar = '=';
        }
        else if(i == currentPosition)
        {
            loadingBarChar = '>';
        }
        else
        {
            loadingBarChar = ' ';
        }

        std::cout << loadingBarChar;
    }
    std::cout << "] %" << trunc(progress * 100) << "\r";
    std::cout.flush();

    if(progress >= 1.0f)
    {
        std::cout << std::endl << "Loading Completed" << std::endl;
    }
}

void LoadingBar::reportCompletedTask()
{
    this->tasksCompleted++;
    this->DisplayProgress();
}

void LoadingBar::OnNotify()
{
    this->reportCompletedTask();
}