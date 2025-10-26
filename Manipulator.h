#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "MovableLink.h"
#include "Gripper.h"
#include "Camera.h"
#include <map>
#include <vector>
#include <tuple>
#include <iostream>

// класс манипулятора для управления всеми звеньями
class Manipulator {
private:
    std::map<int, MovableLink*> links_; // хранение всех звеньев по номеру

public:
    // деструктор 
    ~Manipulator();

    // добавление звена в манипулятор
    void addLink(MovableLink* link);

    // получение звена по ID
    MovableLink* getLink(int id) const;

    // управление углами звеньев
    void setDirection(int id, double new_pitch, double new_yaw, double new_roll);

    // методы для захватов
    void openGripper(int id, double angle);
    void closeGripper(int id);

    // методы для камер
    void takePhoto(int id);

    // вычисление позиции звена в глобальной системе координат
    std::tuple<double, double, double> calculatePosition(int id) const;

    // вывод структуры манипулятора
    void printStructure() const;

private:
    // проверка столкновений между звеньями
    bool checkCollision(const std::vector<int>& chain, size_t current_index, 
                       double x, double y, double z) const;
};

#endif // MANIPULATOR_H
