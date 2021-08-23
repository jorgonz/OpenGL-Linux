#pragma once
#include <vector>
#include "Observer.h"

class Subject
{
    private:
        std::vector<Observer*> Observers;

    public:
        Subject();
        void AddObserver(Observer* observer);
        void RemoveObserver(Observer* observer);
        void Notify();
};