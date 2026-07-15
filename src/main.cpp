#include "core/include/ZE/FH/Core/thread.h"
#include "../include/ZE/FH/Config.h"
#include <memory>




namespace ZE::FH::Main {
  void start()
  {
  
    std::unique_ptr<ZE::FH::IConfig> appConfig = std::make_unique<ZE::FH::Config>("config.ini");

    
  }

   
}



int main (int argc, char *argv[]) {
  
  ZE::FH::Main::start();
  return 0;
}
