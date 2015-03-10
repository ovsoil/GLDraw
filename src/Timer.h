#ifndef OL_TIMER_H
#define OL_TIMER_H

#include <ctime>
#include <limits>
#include <sys/time.h>

namespace OL{

class Timer
{
public:
    Timer() { _start_time = std::clock(); } // postcondition: elapsed()==0
    //         Timer( const timer& src );      // post: elapsed()==src.elapsed()
    //        ~Timer(){}
    //  timer& operator=( const timer& src );  // post: elapsed()==src.elapsed()
    void   restart() {
        _start_time = std::clock();
         //cout << _start_time << endl;
    } // post: elapsed()==0

    double elapsed() const                  // return elapsed time in seconds
    {
        int now_time = std::clock();
        //cout << now_time << endl;
        //cout << CLOCKS_PER_SEC << endl;
        return  double(now_time - _start_time) / CLOCKS_PER_SEC;
    }

    double elapsed_max() const   // return estimated maximum value for elapsed()
        // Portability warning: elapsed_max() may return too high a value on systems
        // where std::clock_t overflows or resets at surprising values.
    {
        return (double((std::numeric_limits<std::clock_t>::max)())
                - double(_start_time)) / double(CLOCKS_PER_SEC); 
    }

    double elapsed_min() const            // return minimum value for elapsed()
    { return double(1)/double(CLOCKS_PER_SEC); }

private:
    std::clock_t _start_time;
}; // Timer

//Linux Timer
class LTimer
{
public:
    LTimer()
    {
        gettimeofday(&_tv_beg, NULL);
    }

    void restart() { gettimeofday(&_tv_beg, NULL); }

    double elapsed() const                  // return elapsed time in seconds
    {
        struct timeval tv;
        int ret = gettimeofday(&tv, NULL);
        if(ret)
        {
            perror("gettimeofday");
            return -1;
        }
        else
        {
            //cout << _tv_beg.tv_sec << "s," << _tv_beg.tv_usec << "us" << endl;
            //cout << tv.tv_sec << "s," << tv.tv_usec << "us" << endl;
            double elapsed_seconds = (tv.tv_sec - _tv_beg.tv_sec) > 0 ?
                (tv.tv_sec - _tv_beg.tv_sec) + (1000000.0 - _tv_beg.tv_usec + tv.tv_usec) / 1000000.0 : 
                (tv.tv_usec - _tv_beg.tv_usec) / 1000000.0;
            return elapsed_seconds;
        }
    }
private:
    struct timeval _tv_beg;
}; // LTimer

//glut Timer
//class GlutTimer
//{
//public:
//    GlutTimer()
//    {
//	    time_beg = glutGet( GLUT_ELAPSED_TIME );
//    }
//
//    void restart()
//    {
//	    time_beg = glutGet( GLUT_ELAPSED_TIME );
//    }
//
//    double elapsed() const                  // return elapsed time in seconds
//    {
//	    return glutGet( GLUT_ELAPSED_TIME ) - time_beg;
//    }
//private:
//    int time_beg;
//}; // glut Timer

} // namespace OL

#endif  // OL_TIMER_H
