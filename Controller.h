#pragma once

#include "Model.h"

class Controller{
public:
   inline Controller(CommandModel* mdl);

   inline void start();
private:
    CommandModel* mdl;
};