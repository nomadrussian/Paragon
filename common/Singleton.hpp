#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <cassert>
#include <typeinfo>

#include <util/Log.hpp>

template <typename T>
class Singleton
{
protected:
    static inline T* instance = nullptr;

public:
    static void init()
    {
        if (instance == nullptr)
        {
            instance = new T();
        }
        else
        {
            log_warning(std::string("Attempting to instantiate ") + typeid(T).name() + std::string(" when it has been already instantiated"));
        }
    }

    static void shutdown()
    {
        if (instance != nullptr)
        {
            delete instance;
            instance = nullptr;
        }
        else
        {
            log_warning(std::string("Attempting to shutdown ") + typeid(T).name() + std::string(" when it has no instance"));
        }
    }

    static T& getInstance()
    {
        assert(instance != nullptr && "Singleton has not been instantiated");
        return *instance;
    }

protected:
    Singleton()
    {
        log_debug(std::string("Singleton ") + typeid(T).name() + std::string(" has been created"));
    }

    virtual ~Singleton()
    {
        log_debug(std::string("Singleton ") + typeid(T).name() + std::string(" has been destroyed"));
    }

private:
    Singleton& operator=(const Singleton&) = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    Singleton(Singleton&&) = delete;
};

#endif // SINGLETON_HPP
