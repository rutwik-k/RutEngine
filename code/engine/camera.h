/* date = November 21st 2020 11:39 am */
#ifndef CAMERA_H
#define CAMERA_H

#define CAMERA_SPEED 20

struct Camera{
    Vec3 pos;
    Vec3 velocity;
    Vec3 front;
    Vec3 up;
    Vec3 right;
    
    Vec3 direction;
    
    f32 yaw = 90.0f;
    f32 pitch = 0.0f;
    
    b32 moving;
};

#endif //CAMERA_H
