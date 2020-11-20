/* date = November 20th 2020 6:52 pm */
#ifndef MATHS_H
#define MATHS_H

#define PI 3.1415926535897

/* Vectors and Matrices types/functions */

struct Vec2{
    float x, y;
};

Vec2 InitVec2(float x, float y){
    Vec2 v2 = {x, y};
    return v2;
};
#define Vec2(x, y) InitVec2(x, y)

Vec2 operator+(Vec2 a, Vec2 b){
    Vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

b32 operator==(Vec2 a, Vec2 b){
    b32 result = 0;
    if(a.x == b.x && a.y == b.y) result = 1;
    return result;
}

struct Vec3{
    union{
        struct{
            float x, y, z;
        };
        struct{
            float r, g, b;
        };
    };
};

Vec3 InitVec3(float x, float y, float z){
    Vec3 v3 = {x, y, z};
    return v3;
}
#define Vec3(x, y, z) InitVec3(x, y, z)

Vec3 NormaliseVec3(Vec3 vec3){
    f32 length = sqrt((vec3.x * vec3.x) + (vec3.y * vec3.y) + (vec3.z * vec3.z));
    Vec3 final = Vec3((vec3.x / length), (vec3.y / length), (vec3.z / length));
    return final;
}

struct Vec4{
    union{
        struct{
            float x, y, z, w;
        };
        struct{
            float r, g, b, a;
        };
    };
};

Vec4 InitVec4(float x, float y, float z, float w){
    Vec4 v4 = {x, y, z, w};
    return v4;
};
#define Vec4(x, y, z, w) InitVec4(x, y, z, w)

//NOTE: Use column major, so [column][row]

struct Mat4{
    float elements[4][4];
};

Mat4 InitMat4(){
    Mat4 mat4 = {};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            mat4.elements[i][j] = 0;
        }
    }
    return mat4;
}
#define Mat4() InitMat4()

Mat4 InitMat4Identity(){
    Mat4 mat4 = {};
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(i == j){
                mat4.elements[i][j] = 1;
            }else{
                mat4.elements[i][j] = 0;
            }
        }
    }
    return mat4;
};
#define Mat4Identity() InitMat4Identity()

/* Translates a mat4 by a Vector3.
              // (1, 0, 0, x)
// (0, 1, 0, y)
// (0, 0, 1, z)
// (0, 0, 0, 1)
*/
void Mat4Translate(Mat4 *source, Vec3 amount){
    source->elements[3][0] = amount.x;
    source->elements[3][1] = amount.y;
    source->elements[3][2] = amount.z;
}

/* Translates a mat4 by a Vector3.
// (x, 0, 0, 0)
// (0, y, 0, 0)
// (0, 0, z, 0)
// (0, 0, 0, 1)
*/
void Mat4Scale(Mat4 *source, Vec3 amount){
    source->elements[0][0] = amount.x;
    source->elements[1][1] = amount.y;
    source->elements[2][2] = amount.z;
}

/* Creates an orthographic matrix.
https://en.wikipedia.org/wiki/Orthographic_projection
*/
Mat4 CreateOrthographicMat4(f32 left, f32 right, f32 bottom, f32 top, f32 near_, f32 far_){
    Mat4 mat4 = Mat4();
    mat4.elements[0][0] =  2.0f / (right-left);
    mat4.elements[1][1] =  2.0f / (top-bottom);
    mat4.elements[2][2] = -2.0f / (far_-near_);
    mat4.elements[3][0] = -((right+left) / (right-left));
    mat4.elements[3][1] = -((top+bottom) / (top-bottom));
    mat4.elements[3][2] = -((far_+near_)/(far_-near_));
    mat4.elements[3][3] =  1.0f;
    
    return mat4;
}

/* Creates a projection matrix */
Mat4 CreateProjectionMat4(f32 fov, f32 aspect, f32 near_, f32 far_){
    Mat4 mat4 = Mat4();
    mat4.elements[0][0] = 1.f / tanf(fov * (PI / 360.f));
    mat4.elements[1][1] = aspect / tanf(fov * (PI / 360.f));
    mat4.elements[2][3] = -1.f;
    mat4.elements[2][2] = (near_ + far_) / (near_ - far_);
    mat4.elements[3][2] = (2.f * near_ * far_) / (near_ - far_);
    mat4.elements[3][3] = 0.f;
    return mat4;
}

/* Multiplies a mat4 by mat4. */
Mat4 operator*(Mat4 a, Mat4 b){
    Mat4 c = {0};
    
    for(int j = 0; j < 4; ++j)
    {
        for(int i = 0; i < 4; ++i)
        {
            c.elements[i][j] = (a.elements[0][j]*b.elements[i][0] +
                                a.elements[1][j]*b.elements[i][1] +
                                a.elements[2][j]*b.elements[i][2] +
                                a.elements[3][j]*b.elements[i][3]);
        }
    }
    
    return c;
}

/* Multiplies a vec4 by mat4. */
Vec4 operator*(Mat4 a, Vec4 b){
	Vec4 result = {{0.0f, 0.0f, 0.0f, 0.0f}};
	result.x = (a.elements[0][0] * b.x) + (a.elements[1][0] * b.y) + (a.elements[2][0] * b.z) + (a.elements[3][0] * b.w );
	result.y = (a.elements[0][1] * b.x) + (a.elements[1][1] * b.y) + (a.elements[2][1] * b.z) + (a.elements[3][1] * b.w );
	result.z = (a.elements[0][2] * b.x) + (a.elements[1][2] * b.y) + (a.elements[2][2] * b.z) + (a.elements[3][2] * b.w );
	result.w = (a.elements[0][3] * b.x) + (a.elements[1][3] * b.y) + (a.elements[2][3] * b.z) + (a.elements[3][3] * b.w );
	return result;
}

b32 operator==(Vec4 a, Vec4 b){
    if(a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w) return 1;
    else{
        return 0;
    }
}

#endif //TYPES_H

