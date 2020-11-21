struct Win32Sound{
    LPDIRECTSOUNDBUFFER sound_buffer;
    DSBUFFERDESC sound_buffer_desc;
    LPDIRECTSOUND direct_sound;
};

void Win32InitSound(HWND hwnd, Win32Sound *win32_sound){
    if(SUCCEEDED(DirectSoundCreate(0, &win32_sound->direct_sound, 0))){
        if(SUCCEEDED(win32_sound->direct_sound->SetCooperativeLevel(hwnd, DSSCL_PRIORITY))){
            DSBUFFERDESC primary_buffer_desc = {};
            primary_buffer_desc.dwSize = sizeof(primary_buffer_desc);
            primary_buffer_desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
            LPDIRECTSOUNDBUFFER primary_buffer;
            if(SUCCEEDED(win32_sound->direct_sound->CreateSoundBuffer(&primary_buffer_desc, &primary_buffer, 0))){
                WAVEFORMATEX wave_format = {};
                wave_format.wFormatTag = WAVE_FORMAT_PCM;
                wave_format.nChannels = platform.channels;
                wave_format.nSamplesPerSec = platform.samples_per_sec;
                wave_format.wBitsPerSample = 16;
                wave_format.nBlockAlign = (wave_format.nChannels * wave_format.wBitsPerSample) / 8;
                wave_format.nAvgBytesPerSec = wave_format.nSamplesPerSec * wave_format.nBlockAlign;
                wave_format.cbSize = 0;
                
                
                win32_sound->sound_buffer_desc.dwSize = sizeof(win32_sound->sound_buffer_desc);
                win32_sound->sound_buffer_desc.dwFlags = 0;
                win32_sound->sound_buffer_desc.dwBufferBytes = platform.samples_per_sec * platform.bytes_per_sample;
                win32_sound->sound_buffer_desc.dwReserved = 0;
                win32_sound->sound_buffer_desc.lpwfxFormat = &wave_format;
                
                if(SUCCEEDED(win32_sound->direct_sound->CreateSoundBuffer(&win32_sound->sound_buffer_desc, &win32_sound->sound_buffer, 0))){
                    OutputDebugString("Created Win32 Sound Buffer\n");
                }
            }
        }
    }
}

void Win32ClearSoundBuffer(Win32Sound *win32_sound){
    VOID *region_1;
    DWORD region_1_size;
    
    VOID *region_2;
    DWORD region_2_size;
    if(SUCCEEDED(win32_sound->sound_buffer->Lock(0, win32_sound->sound_buffer_desc.dwBufferBytes, &region_1, &region_1_size, &region_2, &region_2_size, 0))){
        i8 *sample_out = (i8 *)region_1;
        for(int i = 0; i < region_1_size; i++){
            *sample_out++ = 0;
        }
        sample_out = (i8 *) region_2;
        for(int i = 0; i < region_2_size; i++){
            *sample_out++ = 0;
        }
        
        win32_sound->sound_buffer->Unlock(region_1, region_1_size, region_2, region_2_size);
    }
};

/*
void Win32FillSoundBuffer(Win32Sound *win32_sound, void *samples){
    VOID *region_1;
    DWORD region_1_size;
    
    VOID *region_2;
    DWORD region_2_size;
    if(SUCCEEDED(win32_sound->sound_buffer->Lock(0, win32_sound->sound_buffer_desc.dwBufferBytes, &region_1, &region_1_size, &region_2, &region_2_size, 0))){
        i16 *sample_out = (i16 *)region_1;
        int wavelength = 48000/256;
        f32 t = 0.0f;
        f32 sin_value;
        for(int i = 0; i < region_1_size / (2 * sizeof(i16)); i++){
            sin_value = sinf(t);
            i16 another_thing = sin_value * 3000.0f;
            //L
            *sample_out++ = another_thing;
            //R
            *sample_out++ = another_thing;
            t += 2*PI*1.0f/wavelength;
        }
        
        win32_sound->sound_buffer->Unlock(region_1, region_1_size, region_2, region_2_size);
    }
    
    win32_sound->sound_buffer->Play(0, 0, DSBPLAY_LOOPING);
}
*/