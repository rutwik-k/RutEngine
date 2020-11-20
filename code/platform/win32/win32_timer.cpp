internal void Win32TimerInit(Win32Timer *timer){
    timer->sleep_is_granular = (timeBeginPeriod(1) == TIMERR_NOERROR);
    QueryPerformanceFrequency(&timer->performance_counter_frequency);
}

internal void Win32TimerBegin(Win32Timer *timer){
    QueryPerformanceCounter(&timer->begin_frame);
}

internal void Win32TimerEnd(Win32Timer *timer, Platform platform){
    QueryPerformanceCounter(&timer->end_frame);
    i64 desired_frame_counts = (i64)(timer->performance_counter_frequency.QuadPart / platform.target_fps);
    i64 frame_count = timer->end_frame.QuadPart - timer->begin_frame.QuadPart;
    i64 counts_to_wait = desired_frame_counts - frame_count;
    
    LARGE_INTEGER begin_wait_time_data;
    LARGE_INTEGER end_wait_time_data;
    QueryPerformanceCounter(&begin_wait_time_data);
    
    while(counts_to_wait > 0)
    {
        if(timer->sleep_is_granular)
        {
            DWORD milliseconds_to_sleep = (DWORD)(1000.0 * ((f64)(counts_to_wait) / timer->performance_counter_frequency.QuadPart));
            if(milliseconds_to_sleep > 1)
            {
                --milliseconds_to_sleep;
                Sleep(milliseconds_to_sleep);
            }
        }
        
        QueryPerformanceCounter(&end_wait_time_data);
        counts_to_wait -= end_wait_time_data.QuadPart - begin_wait_time_data.QuadPart;
        begin_wait_time_data = end_wait_time_data;
    }
    
    
    timer->ms_per_frame =(((f32)end_wait_time_data.QuadPart - (f32)timer->begin_frame.QuadPart)*1000) / (f32)timer->performance_counter_frequency.QuadPart;
}