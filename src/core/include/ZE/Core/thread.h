
#include <atomic>
#include <bits/this_thread_sleep.h>
#include <chrono>
#include <exception>
#include <iostream>
#include <pthread.h>
#include <sched.h>
#include <string>
namespace ZE::Core {
    class IThread {

        
        virtual void init() = 0;
        virtual void start() = 0;
        virtual void run() = 0;
        virtual void stop() = 0;

    };

    // Concrete Implementation
    template<typename F, typename P>
    class Thread : public IThread {
    private:
        std::string& m_thread_name;
        int m_cpu_id;
        pthread_t m_thread{};
        pthread_attr_t m_thread_attr{};
        F m_func;
        P m_params;
        std::atomic<bool> m_stop = false;
        std::chrono::time_point<std::chrono::steady_clock> last_execution_time;

        // Static thread entry point
        static void* threadEntryPoint(void* arg)
        {
            Thread* self = static_cast<Thread*>(arg);
            self->poll();
            return nullptr;
        }

    public:
        void init() override;
        void start() override;
        void run() override;
        Thread(std::string &thread_name, const int &cpu_id, F func, P params);
        void stop() override;
        void poll();

        void printInfo(const std::string &msg) const;
        ~Thread();
    };

    // Template implementation
    template<typename F, typename P>
    Thread<F, P>::Thread(std::string &thread_name, const int &cpu_id, F func, P params )
        : m_thread_name(thread_name), m_cpu_id(cpu_id), m_func(func), m_params(params)
    {
        Thread<F, P>::init();
    }

    template<typename F, typename P>
    void Thread<F, P>::init()
    {
        // Initialize thread attributes
        pthread_attr_init(&m_thread_attr);
        printInfo("Thread initialized");
    }

    template<typename F, typename P>
    void Thread<F, P>::start()
    {
        if(pthread_create(&m_thread, &m_thread_attr, threadEntryPoint, this) != 0)
        {
            std::cout << "Thread creation failed\n";
            return;
        }

        // Set affinity AFTER thread creation using the thread ID
        cpu_set_t cpu_set;
        CPU_ZERO(&cpu_set);
        CPU_SET(m_cpu_id, &cpu_set);

        if (pthread_setaffinity_np(m_thread, sizeof(cpu_set_t), &cpu_set) != 0)
        {
            std::cout << "Error setting affinity\n";
        }
    }

    template<typename F, typename P>
    void Thread<F, P>::stop()
    {
        m_stop = true;
        pthread_join(m_thread, nullptr);
        printInfo("Thread stopped");
    }

    template<typename F, typename P>
    void Thread<F, P>::run()
    {
        m_func(m_params);
        last_execution_time = std::chrono::steady_clock::now();
    }

    template<typename F, typename P>
    void Thread<F, P>::poll()
    {
        if (!m_stop)
        {
            this->Thread<F, P>::run();
            auto currTime = std::chrono::steady_clock::now();
            if (currTime - last_execution_time < std::chrono::seconds(1))
            {
                std::this_thread::sleep_for(std::chrono::seconds(1) + last_execution_time - currTime);
            }
            this->Thread<F, P>::poll();
        }
    }

    template<typename F, typename P>
    Thread<F, P>::~Thread()
    {
        this->Thread<F, P>::stop();
    }

    template<typename F, typename P>
    void Thread<F, P>::printInfo(const std::string& msg) const
    {
        std::cout << "Thread: " << m_thread_name << " " << msg << "\n";
    }

}
