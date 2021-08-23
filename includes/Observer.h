#pragma once

class Observer
{
    public:
        virtual ~Observer() {};
        virtual void OnNotify() = 0;
};