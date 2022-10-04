#include"CommandView.h"
#include "Controller.h"

int main(int argc, char* argv[]){
    
    CommandModel cm(3);
    CommandView cv(cm.get_ref_store());
    Controller ctrl(&cm);
    ctrl.start();

    return 0;
}