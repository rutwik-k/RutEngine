void Win32FreeFile(void *data){
    if(data){
        VirtualFree(data, 0, MEM_RELEASE);
    }
}

/* note - could turn this into a struct if we ever needed to know the size of the file. */
void *Win32ReadEntireFileToString(char *filename){
    SetCurrentDirectory("..\\data\\");
    HANDLE file_handle;
    char *data;
    if((file_handle = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0)) != INVALID_HANDLE_VALUE){
        DWORD file_size = GetFileSize(file_handle, 0);
        if(file_size){
            data = (char *)VirtualAlloc(0, file_size + 1, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
            if(data){
                DWORD bytes_read;
                if(ReadFile(file_handle,(void *) data, file_size, &bytes_read, 0) && (file_size == bytes_read)){
                    //null terminator
                    data[file_size] = '\0';
                }else{
                    Win32FreeFile(data);
                }
            }
        }
        CloseHandle(file_handle);
    }else{
        char filename_to_print[256];
        wsprintf(filename_to_print, "Couldn't load file %s\n", filename);
        Win32DisplayError("Error loading file", filename_to_print);
    }
    return data;
}

//havent tested lol
b32 Win32WriteToFile(char *filename, u64 data_size, void *data){
    b32 result = 0;
    HANDLE file_handle;
    if((file_handle = CreateFileA(filename, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0)) != INVALID_HANDLE_VALUE){
        DWORD bytes_written;
        if(WriteFile(file_handle, data, data_size, &bytes_written, 0)){
            //file read successfully
            result = (bytes_written == data_size);
        }
        else{
            
        }
        CloseHandle(file_handle);
    }
    return result;
}