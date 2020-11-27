/* date = November 26th 2020 6:48 pm */
#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

struct ParsedOBJ{
    //currently, this will just hold vertices and normals, and default white colour
    float *data;
    
    FileContents file;
};

#endif //OBJ_PARSER_H
