struct TextureCounter{
    u32 value;
} counter;

struct Texture{
    i32 w, h, ch;
    GLuint id;
    u32 count;
};

internal Texture LoadTexture(char *filename, i32 filtering_option, i32 format, b32 flip_image){
    Texture texture = {};
    stbi_set_flip_vertically_on_load(flip_image);
    u8 *texture_data = stbi_load(filename, &texture.w, &texture.h, &texture.ch, 0);
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filtering_option);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filtering_option);
    if(texture_data){
        glTexImage2D(GL_TEXTURE_2D, 0, format, texture.w, texture.h, 0, format, GL_UNSIGNED_BYTE, texture_data);
    }else{
        OutputDebugString("Failed to load texture\n");
        printf("Failed to load texture\n");
    }
    texture.count = counter.value;
    counter.value++;
    stbi_image_free(texture_data);
    return texture;
}