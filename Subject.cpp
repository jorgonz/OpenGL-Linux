#include "includes/Subject.h"

Subject::Subject() { }

void Subject::AddObserver(Observer* observer)
{
    this->Observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
    for(int i = 0; i < this->Observers.size(); i++)
    {
        if(observer == this->Observers[i])
        {
            this->Observers.erase(this->Observers.begin() + i);
        }
    }
}

void Subject::Notify()
{
    for(int i = 0; i < this->Observers.size(); i++)
    {
        this->Observers[i]->OnNotify();
    }
}