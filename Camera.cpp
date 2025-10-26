#include "Camera.h"
#include <iostream>
#include <cassert>

// Конструктор с дополнительными параметрами для камеры
Camera::Camera(int id, int prev_id, double r, double pitch, double yaw, double roll, double fov)
    : MovableLink(id, prev_id, r, pitch, yaw, roll),
      fov_(fov) 
    {
        assert(fov_ > 0 && "fov must be positive");
        assert(id_ > 0 && "id must be positive");
        assert(prev_id_ >= 0 && "prev_id can't be negative");
        assert(r_ > 0 && "r must be positive");
    }

void Camera::take_a_photo() {
    std::cout << "Camera " << id_ << " took a photo of mechanism" << std::endl;
}

// переопределение метода вывода информации
void Camera::printInfo() const {
    std::cout << "Camera " << id_
              << " (prev=" << prev_id_
              << ") length=" << r_
              << ") dir=(" << pitch_ << ", " << yaw_ << ", " << roll_ << ") rad"
              << " fov=" << fov_ << " rad\n";
}
