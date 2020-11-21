void AudioPlaySamples(Platform *platform){
    local_persist float t = 0;
    i16 tone_volume = 3000;
    int tone_hz = 256;
    //printf("%i\n", buffer->samples_per_second);
    int wave_period = platform->samples_per_sec/tone_hz;
    
    i16 *sample_out = (i16 *)platform->samples;
    for(int sample_index = 0; sample_index < platform->sample_count; sample_index++){
        float sine = sinf(t);
        i16 sample_value = (i16)(sine * tone_volume);
        *sample_out++ = sample_value;
        *sample_out++ = sample_value;
        
        t += 2*3.14159265*1.0f/(float)wave_period;
    }
}