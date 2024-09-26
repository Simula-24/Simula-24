#ifndef CORE_THREAD_H_
#define CORE_THREAD_H_

#include <core/types.h>
#include <core/stl/utility.h>
#include <core/stl/function.h>
#include <core/thread/mutex.h>

namespace simula24
{

///
/// @brief
///     This is what is passed to the OS create thread
///     function.
/// 
///     This expects p to be a pointer to an stl::function
///     of type void();
/// 
///     It will extract that function p and call it.
/// 
class dummy_thread_runner
{
public:
    static void* run(void* p)
    {
        auto* fn = static_cast<stl::function<void()>*>(p);
        (*fn)();
        return nullptr;
    }
};

///
/// @brief
///     Basic Thread class
/// 
///     This relies on the operating system's thread API
///     Specifically Window's Thread API and pthreads on *nix
///     Implementations are found in /platform/<name>/thread/thread.cpp
/// 
///     To use:
///     @code
///     simula24::thread mythread(myfunction, myargs...);    
///     mythread.join(); 
///     @endcode
/// 
///     Thread supports multiple arguments by hiding them inside of a lambda 
///     stored in @dummy
/// 
///     This dummy function is what @ref dummy_thread_runner will run
///     
///     
class thread
{
public:


    template<class T, class ...Args>
    explicit thread(T&& t, Args&&... args)
    {
        dummy = [=]() mutable {
            stl::forward<T>(t)(stl::forward<Args>(args)...);
            };
        start((void*)(&dummy_thread_runner::run), (void*)&dummy);
    }

    thread& operator=(thread&& other)
    {
        dummy = stl::move(other.dummy);
        m_thread = stl::move(other.m_thread);
        m_id = stl::move(other.m_id);
        return *this;
    }

    /// wait for this thread to finish
    void join();

    /// The TID for *this* thread
    size_t getId() const;

    const ThreadObject getNativeThreadObject() const
    {
        return m_thread;
    }

public:
    /// get thread id for caller
    static size_t getThreadID();


private:
    /// start a thread
    void start(void* function, void* args);

    /// native thread object
    ThreadObject m_thread;

    size_t m_id;
    /// dummy function. Holds a lambda that 
    /// calls the actual function
    stl::function<void()> dummy;
};

} // simula24


///
/// @brief
///     These macros are designed
///     to make creating threadsafe classes/functions
///     easier.
/// 
#define THREAD_SAFE_CLASS       simula24::Mutex __thread_safe_mutex__{};
#define THREAD_SAFE_FUNCTION    simula24::ScopedMutexLocker __mutex_locker__(__thread_safe_mutex__);

#endif // CORE_THREAD_H_