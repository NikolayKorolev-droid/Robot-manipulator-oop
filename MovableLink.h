#ifndef MOVABLELINK_H
#define MOVABLELINK_H

#include <iostream>
#include <cassert>
#include <utility>

// базовый класс для подвижного звена робота-манипулятора
class MovableLink {
protected:
    int id_;           // номер текущего звена
    int prev_id_;      // номер предыдущего звена (0, если нет)
    double r_;     // длина звена
    double pitch_;   // тангаж относительно предыдущего (либо основанию робота, если id = 1)
    double yaw_;  // рысканье относ пред (либо <...>)
    double roll_; // крен относ пред (либо <...>)
    // ось z направлена вдоль предыдущего звена, ось х и у - см. Readme

public:
    MovableLink(int id, int prev_id, double r, double pitch, double yaw, double roll);
    
    // виртуальный деструктор для корректного наследования
    virtual ~MovableLink() = default;

    int getId() const;
    int getPrevId() const;
    double getR() const;
    std::pair<double, double> getDirection() const;

    
    void setDirection(double new_pitch, double new_yaw, double new_roll);
    void changeDirection(double d_pitch, double d_yaw, double d_roll);

    // виртуальный метод для вывода информации (может быть переопределен в наследниках)
    virtual void printInfo() const;
};

#endif // MOVABLELINK_H
