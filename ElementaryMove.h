#ifndef ELEMENTARYMOVE_H
#define ELEMENTARYMOVE_H

#include "Manipulator.h"

// класс элементарного движения одного звена
class ElementaryMove {
private:
    int link_id_;       // звено, которое двигается
    double target_pitch_; // конечный тангаж
    double target_yaw_; // конечное рысканье
    double target_roll_; // конечный крен
    bool valid_;        // валидность движения

public:
    ElementaryMove(int link_id, double target_pitch, double target_yaw, double target_roll);

    // проверка валидности движения по сути реализована уже в Manipulator, и нет смысла добавлять еще одну

    // выполнение движения на манипуляторе
    void execute(Manipulator& manip);
};

#endif // ELEMENTARYMOVE_H
