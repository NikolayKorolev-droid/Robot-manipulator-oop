#include "Gripper.h"
#include <iostream>
#include <cassert>

// direction - направление центра захвата (рад). Угол между рукой и стержнем звена
// open_angle - угол раскрытия (рад). Угол между центральной осью руки и каждым из трех захватов 
// (т.к. раскрытие руки происходит симметрично)
Gripper::Gripper(int id, int prev_id, double r, double pitch, double yaw, double roll, double open_angle)
    : MovableLink(id, prev_id, r, pitch, yaw, roll),
      open_angle_(open_angle) 
    {
        assert(open_angle_ >= 0 && "open angle can't be negative");
        assert(id_ > 0 && "id must be positive");
        assert(prev_id_ >= 0 && "prev id can't be negative");
        assert(r_ > 0 && "r must be positive");
    }

// геттеры 
double Gripper::getOpenAngle() const {
    return open_angle_;
}

// открытие захвата на заданный угол
void Gripper::open(double angle) {
    open_angle_ = angle;
}

// закрытие захвата
void Gripper::close() {
    open_angle_ = 0.0;
}

// поменять угол раскрытия захвата (метод open это начальные условия, а данный метод
// меняет угол "в реальном времени")
void Gripper::changeOpenAngle(double d_angle){
    open_angle_ += d_angle;
    if (open_angle_ < 0.0) {
        open_angle_ = 0.0;
    }
}

// переопределение метода вывода информации
void Gripper::printInfo() const {
    std::cout << "Gripper " << id_
              << " (prev=" << prev_id_
              << ") length=" << r_
              << ") dir=(" << pitch_ << ", " << yaw_ << ", " << roll_ << ") rad"
              << " open_angle=" << open_angle_ << " rad\n";
}
