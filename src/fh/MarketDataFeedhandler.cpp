#include <iostream>
#include <ostream>
#include <thread>

#include "ZE/Core/thread.h"
#include "ZE/FH/Config.h"
#include "ZE/FH/MarketDataFeedHandler.h"

namespace ZE::FH::Main
{

    struct P
    {
        int no;
    };

    using fn = int(*)(P);
    int process(P p)
    {
            std::cout << p.no << std::endl;
        return p.no;
    }
    void MarketDataFeedHandler::start()
    {
        struct P p;
        p.no = 10;
        std::string t = "T1";
        ZE::Core::Thread<fn,P> thread(t, 7, process, p);
        thread.start();

        struct P p2;
        p2.no = -1;
        std::string t2 = "T2";
        ZE::Core::Thread<fn,P> thread2(t2, 8, process, p2);
        thread2.start();

        std::this_thread::sleep_for(std::chrono::seconds(3));
        // thread.stop();
        // ZE::FH::Config config("app.conf");
        // std::unique_ptr<ZE::FH::IConfig> appConfig = std::make_unique<ZE::FH::Config>("app.conf");

        // sample 4 thread t1 => downstream( ws connection ) , t2 => logging, t3 => upstream, t4 = time measure ya analytics ( like in fxp2 stopwatch)

    }
} // namespace ZE::FH::Main

