#ifndef CAMERA_H
#define CAMERA_H

#include "MovableLink.h"

// наследник MovableLink
class Camera : public MovableLink {
private:
    double fov_;         // угол раствора, то есть обзора (field of view). orientation - это по сути тангаж, рысканье и крен, поэтому его не добавил

public:
    // конструктор с дополнительными параметрами для камеры
    Camera(int id, int prev_id, double r, double pitch, double yaw, double roll, double fov);

    // снимок
    void take_a_photo();

    // переопределение метода вывода информации
    void printInfo() const override;
};

#endif // CAMERA_H
