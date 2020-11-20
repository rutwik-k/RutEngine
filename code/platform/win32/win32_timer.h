/* date = November 20th 2020 7:12 pm */

#ifndef WIN32_TIMER_H
#define WIN32_TIMER_H

struct Win32Timer{
    b32 sleep_is_granular;
    
    LARGE_INTEGER performance_counter_frequency;
    LARGE_INTEGER begin_frame;
    LARGE_INTEGER end_frame;
    
    f32 ms_per_frame;
};

#endif //WIN32_TIMER_H
