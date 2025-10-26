#include "MovableLink.h"
#include <iostream>
#include <cmath>

// r - длина звена
MovableLink::MovableLink(int id, int prev_id, double r, double pitch, double yaw, double roll)
    : id_(id), prev_id_(prev_id), r_(r), pitch_(pitch), yaw_(yaw), roll_(roll)
{
    assert(id_ > 0 && "id must be positive");
    assert(prev_id_ >= 0 && "prev_id can't be negative");
    assert(r_ > 0 && "r must be positive");
}

int MovableLink::getId() const { 
    return id_; 
}

int MovableLink::getPrevId() const { 
    return prev_id_; 
}

double MovableLink::getR() const { 
    return r_; 
}

std::pair<double, double> MovableLink::getDirection() const { 
    return std::make_pair(pitch_, yaw_);
}

void MovableLink::setDirection(double new_pitch, double new_yaw, double new_roll) { 
    pitch_ = new_pitch;
    yaw_ = new_yaw;
    roll_ = new_roll;
}

void MovableLink::changeDirection(double d_pitch, double d_yaw, double d_roll) { 
    pitch_ += d_pitch;
    yaw_ += d_yaw;
    roll_ += d_roll;
}

// виртуальный метод для вывода информации
void MovableLink::printInfo() const {
    std::cout << "Link " << id_
              << " (prev=" << prev_id_
              << ") length=" << r_
              << ") dir=(" << pitch_ << ", " << yaw_ << ", " << roll_ << ") rad\n";
}
