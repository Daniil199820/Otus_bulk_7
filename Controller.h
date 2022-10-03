#pragma once

#include "Model.h"

class Controller{
public:
    Controller(CommandModel* mdl);

    void start();
private:
    CommandModel* mdl;
};