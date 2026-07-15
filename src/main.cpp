#include <memory>
#include "../include/ZE/FH/Config.h"
#include "core/include/ZE/FH/Core/thread.h"


namespace ZE::FH::Main
{
    void start() { std::unique_ptr<ZE::FH::IConfig> appConfig = std::make_unique<ZE::FH::Config>("config.ini"); }


} // namespace ZE::FH::Main


int main(int argc, char *argv[])
{

    ZE::FH::Main::start();
    return 0;
}
