#include "ZE/FH/MarketDataFeedHandler.h"
#include <memory>
#include "ZE/Core/thread.h"
#include "ZE/FH/Config.h"

namespace ZE::FH::Main
{
    void MarketDataFeedHandler::start()
    {
        ZE::FH::Config config("app.conf");
        // std::unique_ptr<ZE::FH::IConfig> appConfig = std::make_unique<ZE::FH::Config>("app.conf");
    }
} // namespace ZE::FH::Main

