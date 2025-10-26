#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "ElementaryMove.h"
#include "Manipulator.h"
#include <vector>

// класс для управления последовательностью движений
class Movement {
private:
    std::vector<ElementaryMove> moves_; // последовательность элементарных движений

public:
    // добавление элементарного движения в последовательность
    void addMove(const ElementaryMove& move);

    // выполнение всех движений в последовательности
    void executeAll(Manipulator& manip);

    // поиск последнего звена в манипуляторе
    int findLastLinkId(const Manipulator& manip) const;
};

#endif // MOVEMENT_H
