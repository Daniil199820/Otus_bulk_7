#include"CommandView.h"
#include "Controller.h"

int main(int argc, char* argv[]){
    CommandModel* cm;
    
    if(argc>1){
        cm = new CommandModel(std::stoul(argv[1]));
    }
    else{
        cm = new CommandModel(3);
    }
    CommandView cv(cm->get_ref_store());
    Controller ctrl(cm);
    ctrl.start();

    return 0;
}