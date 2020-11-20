internal void Win32DisplayError(char *title, char *info){
    MessageBoxA(0, (LPCSTR)info, (LPCSTR)title, MB_OK);
}