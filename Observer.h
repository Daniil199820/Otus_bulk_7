#pragma once
#include<vector>

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
public:
    void addObserver(Observer* observer){
        _observers.push_back(observer);
    }

    void notifyUpdate(){
        for(unsigned int i=0;i<_observers.size();++i){
            _observers[i]->update();
        }
    }
private:
    std::vector<Observer*>_observers;    
};