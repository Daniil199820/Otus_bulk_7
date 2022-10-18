#include"CommandView.h"
#include "Controller.h"
//another branch
int main(int argc, char* argv[]){
    std::unique_ptr<CommandModel> cm;
    
    if(argc>1){
        cm = std::make_unique<CommandModel>(std::stoul(argv[1]));
    }
    else{
        cm = std::make_unique<CommandModel>(3);
    }
    CommandView cv(cm->get_ref_store());
    Controller ctrl(std::move(cm));
    ctrl.start();

    return 0;
}