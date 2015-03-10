#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <boost/thread.hpp>

using std::auto_ptr;
using boost::mutex;

class Singleton
{
public:
    static Singleton& GetInstance();

private:
    Singleton(){}
    ~Singleton(){}

    // Use auto_ptr to make sure that the allocated memory for instance
    // will be released when program exits (after main() ends).
    static auto_ptr<Singleton> s_instance;
    friend class auto_ptr<Singleton>;

    Singleton(const Singleton&);
    Singleton& operator =(const Singleton&);
};


template <typename T>
class ISingleton
{
public:
    static T& GetSingleton()
    {
        static  mutex s_mutex;
        if (s_instance.get() == NULL)
        {
            mutex::scoped_lock lock(s_mutex);
            if (s_instance.get() == NULL)
            {
                s_instance.reset(new T());
            }
            // 'lock' will be destructed now. 's_mutex' will be unlocked.
        }
        return *s_instance;
    }

    static T* GetSingletonPtr()
    {
        static mutex s_mutex;
        if (s_instance.get() == NULL)
        {
            mutex::scoped_lock lock(s_mutex);
            if (s_instance.get() == NULL)
            {
                s_instance.reset(new T());
            }
            // 'lock' will be destructed now. 's_mutex' will be unlocked.
        }
        return s_instance.get();
    }
protected:
    ISingleton() { }
    ~ISingleton() { }

    // Use auto_ptr to make sure that the allocated memory for instance
    // will be released when program exits (after main() ends).
    static auto_ptr<T> s_instance;

private:
    ISingleton(const Singleton&);
    ISingleton& operator =(const ISingleton&);
};

template <typename T>
auto_ptr<T> ISingleton<T>::s_instance;

#endif // SINGLETON_H
