
namespace ZE::Core {
  class IThread {
    public:
        virtual ~IThread() = default;
        
        // Pure virtual function - must be implemented by derived classes
        virtual void run() = 0;
        virtual void stop() = 0;
    };

    // Concrete Implementation
    class Thread : public IThread {
    public:
        void run() override;
        void stop() override;
    };
  
}
