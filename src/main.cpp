
#include "ZE/FH/MarketDataFeedHandler.h"

int main (int argc, char *argv[])
{
    ZE::FH::Main::MarketDataFeedHandler fh = ZE::FH::Main::MarketDataFeedHandler();
    fh.start();
    return 0;
}
