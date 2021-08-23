#pragma once
#include "Observer.h"
#include <string>

class LoadingBar : public Observer
{
    private:
        std::string processName;
        unsigned int tasksSize;
        unsigned int tasksCompleted;
        void DisplayProgress();
    public:
        LoadingBar(std::string processName, int tasksSize);
        void reportCompletedTask();
        virtual void OnNotify();
};