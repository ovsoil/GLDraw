#include "Singleton.h"

auto_ptr<Singleton> Singleton::s_instance;

Singleton& Singleton::GetInstance()
{
//    static QMutex s_mutex;
    if (s_instance.get() == NULL)
    {
//        QMutexLocker lock(&s_mutex);
        if (s_instance.get() == NULL)
        {
            s_instance.reset(new Singleton());
        }
        // 'lock' will be destructed now. 's_mutex' will be unlocked.
    }
    return *s_instance;
}

