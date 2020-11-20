LRESULT CALLBACK Win32WindowProcedure(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param)
{
    LRESULT result = 0;
    
    if(msg == WM_CLOSE)
    {
        platform.should_quit = 1;
    }
    else if(msg == WM_DESTROY)
    {
        PostQuitMessage(0);
    }
    else if(msg == WM_SIZE)
    {
        
    }
    
    else if(msg == WM_LBUTTONDOWN)
    {
        if(!platform.left_mouse_down){
            platform.left_mouse_pressed = 1;
        }
        platform.left_mouse_down = 1;
    }
    
    else if(msg == WM_LBUTTONUP)
    {
        platform.left_mouse_down = 0;
        platform.left_mouse_pressed = 0;
    }
    
    else if(msg == WM_RBUTTONDOWN)
    {
        platform.right_mouse_down = 1;
    }
    
    else if(msg == WM_RBUTTONUP){
        platform.right_mouse_down = 0;
    }
    
    else if(msg == WM_KEYDOWN || msg == WM_KEYUP || msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP)
    {
        WPARAM key_code = w_param;
        LPARAM was_down = ((l_param & (1 << 30)) != 0); // shift left 30 bits
        LPARAM is_down  = ((l_param & (1 << 31)) == 0);
        
        u32 key_enum = 0; //holds the key enum
        
        if(key_code == 'A')
        {
            key_enum = KEY_A;
        }
        else if(key_code == 'B')
        {
            key_enum = KEY_B;
        }
        else if(key_code == 'C')
        {
            key_enum = KEY_C;
        }
        else if(key_code == 'D')
        {
            key_enum = KEY_D;
        }
        else if(key_code == 'E')
        {
            key_enum = KEY_E;
        }
        else if(key_code == 'F')
        {
            key_enum = KEY_F;
        }
        else if(key_code == 'G')
        {
            key_enum = KEY_G;
        }
        else if(key_code == 'H')
        {
            key_enum = KEY_H;
        }
        else if(key_code == 'I')
        {
            key_enum = KEY_I;
        }
        else if(key_code == 'J')
        {
            key_enum = KEY_J;
        }
        else if(key_code == 'K')
        {
            key_enum = KEY_K;
        }
        else if(key_code == 'L')
        {
            key_enum = KEY_L;
        }
        else if(key_code == 'M')
        {
            key_enum = KEY_M;
        }
        else if(key_code == 'N')
        {
            key_enum = KEY_N;
        }
        else if(key_code == 'O')
        {
            key_enum = KEY_O;
        }
        else if(key_code == 'P')
        {
            key_enum = KEY_P;
        }
        else if(key_code == 'Q')
        {
            key_enum = KEY_Q;
        }
        else if(key_code == 'R')
        {
            key_enum = KEY_R;
        }
        else if(key_code == 'S')
        {
            key_enum = KEY_S;
        }
        else if(key_code == 'T')
        {
            key_enum = KEY_T;
        }
        else if(key_code == 'U')
        {
            key_enum = KEY_U;
        }
        else if(key_code == 'V')
        {
            key_enum = KEY_V;
        }
        else if(key_code == 'W')
        {
            key_enum = KEY_W;
        }
        else if(key_code == 'X')
        {
            key_enum = KEY_X;
        }
        else if(key_code == 'Y')
        {
            key_enum = KEY_Y;
        }
        else if(key_code == 'Z')
        {
            key_enum = KEY_Z;
        }
        else if(key_code == '1'){
            key_enum = KEY_1;
        }
        else if(key_code == '2'){
            key_enum = KEY_2;
        }
        else if(key_code == '3'){
            key_enum = KEY_3;
        }
        else if(key_code == '4'){
            key_enum = KEY_4;
        }
        else if(key_code == VK_SPACE){
            key_enum = KEY_SPACE;
        }
        else if(key_code == VK_SHIFT){
            key_enum = KEY_SHIFT;
        }
        
        if(was_down != is_down)
        {
            platform.key_down[key_enum] = is_down;
        }
    }
    else
    {
        result = DefWindowProc(hwnd, msg, w_param, l_param);
    }
    return result;
}