//1. get vertex, normal and index count
//2. alloc vertex and normal array
//3. fill vertex and normal array with values
//4. fill data array with vertices and normals pointed by indices
ParsedOBJ ParseOBJFile(char *string){
    ParsedOBJ parsed_obj = {};
    parsed_obj.file = platform.PlatformReadEntireFileToString(string);
    u32 vertex_count = 0;
    u32 normal_count = 0;
    u32  index_count = 0;
    for(int i = 0; i < parsed_obj.file.bytes; i++){
        if(parsed_obj.file.data[i] == 'v' && i != parsed_obj.file.bytes - 1){
            if(parsed_obj.file.data[i + 1] == ' '){
                vertex_count++;
            }
            if(parsed_obj.file.data[i + 1] == 'n'){
                normal_count++;
            }
        }
        if(parsed_obj.file.data[i] == 'f'){
            u32 line_index = i;
            while(parsed_obj.file.data[line_index] != '\n'){
                if(parsed_obj.file.data[line_index] == ' '){
                    index_count++;
                }
                line_index++;
            }
        }
    }
    f32 *vertices = (f32 *)MemoryArenaAllocate(&app.permanent_arena, vertex_count * sizeof(f32));
    f32 *normals = (f32 *)MemoryArenaAllocate(&app.permanent_arena, normal_count * sizeof(f32));
    parsed_obj.data = (f32 *)MemoryArenaAllocate(&app.permanent_arena, index_count * sizeof(f32));
    
    for(int i = 0; i < parsed_obj.file.bytes; i++){
        if(parsed_obj.file.data[i] == 'v' && i != parsed_obj.file.bytes - 1){
            if(parsed_obj.file.data[i + 1] == ' '){
                
            }
            if(parsed_obj.file.data[i + 1] == 'n'){
                
            }
        }
        if(parsed_obj.file.data[i] == 'f'){
            u32 line_index = i;
            while(parsed_obj.file.data[line_index] != '\n'){
                if(parsed_obj.file.data[line_index] == ' '){
                    
                }
                
            }
        }
    }
    
    
    return parsed_obj;
}