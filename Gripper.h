#ifndef GRIPPER_H
#define GRIPPER_H

#include "MovableLink.h"

// наследник MovableLink
class Gripper : public MovableLink {
private:
    double open_angle_;  // угол раскрытия (рад)

public:
    Gripper(int id, int prev_id, double r, 
            double pitch, double yaw, double roll, double open_angle);

    //так как Захват уже отнаследовал все геттеры Подвижного звена, осталось 
    //добавить геттеры угла ее раскрытия
    double getOpenAngle() const;

    // методы управления захватом
    void open(double angle);
    void close();
    void changeOpenAngle(double d_angle);

    // переопределение метода вывода информации
    void printInfo() const override;
};

#endif // GRIPPER_H
