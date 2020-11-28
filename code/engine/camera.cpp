internal void CameraUpdate(Camera *camera){
    camera->velocity = Vec3(0, 0, 0);
    
    if(app.platform->left_mouse_down){
        camera->yaw   += app.platform->cursor_dx * 0.1f;
        camera->pitch -= app.platform->cursor_dy * 0.1f;
    }
    if(camera->pitch > 90.0f) camera->pitch = 90.0f;
    if(camera->pitch < -90.0f) camera->pitch = -90.0f;
    
    camera->direction.x = cosf(ToRadians(camera->yaw)) * cosf(ToRadians(camera->pitch));
    camera->direction.y = sinf(ToRadians(camera->pitch));
    camera->direction.z = sinf(ToRadians(camera->yaw)) * cosf(ToRadians(camera->pitch));
    
    camera->front = NormaliseVec3(camera->direction);
    
    if(app.platform->key_down[KEY_W]){
        camera->target_pos = camera->pos - Vec3(camera->front.x * CAMERA_SPEED * app.platform->dt, camera->front.y * CAMERA_SPEED * app.platform->dt,
                                                camera->front.z * CAMERA_SPEED * app.platform->dt);
    }
    if(app.platform->key_down[KEY_A]){
        camera->target_pos = camera->pos + NormaliseVec3(Vec3Cross(camera->front, camera->up)) * CAMERA_SPEED * app.platform->dt;
    }
    if(app.platform->key_down[KEY_S]){
        camera->target_pos = camera->pos + Vec3(camera->front.x * CAMERA_SPEED * app.platform->dt, camera->front.y * CAMERA_SPEED * app.platform->dt,
                                                camera->front.z * CAMERA_SPEED * app.platform->dt);
    }
    if(app.platform->key_down[KEY_D]){
        camera->target_pos = camera->pos - NormaliseVec3(Vec3Cross(camera->front, camera->up)) * CAMERA_SPEED * app.platform->dt;
    }
    if(app.platform->key_down[KEY_SPACE]){
        camera->target_pos = camera->pos + Vec3(camera->up.x * CAMERA_SPEED * app.platform->dt, camera->up.y * CAMERA_SPEED * app.platform->dt,
                                                camera->up.z * CAMERA_SPEED * app.platform->dt);
    }
    if(app.platform->key_down[KEY_SHIFT]){
        camera->target_pos = camera->pos - Vec3(camera->up.x * CAMERA_SPEED * app.platform->dt, camera->up.y * CAMERA_SPEED * app.platform->dt,
                                                camera->up.z * CAMERA_SPEED * app.platform->dt);
    }
    
    camera->pos = Vec3Lerp(camera->pos, camera->target_pos, 0.1f);
}