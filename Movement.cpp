#include "Movement.h"
#include <iostream>

// добавление элементарного движения в последовательность
void Movement::addMove(const ElementaryMove& move) {
    moves_.push_back(move);
}

// выполнение всех движений в последовательности
void Movement::executeAll(Manipulator& manip) {
    std::cout << "\nExecuting movement sequence...\n";
    for (auto& m : moves_)
        m.execute(manip);
    
    // найдем последнее звено в манипуляторе
    int lastLinkId = findLastLinkId(manip);
    if (lastLinkId != -1) {
        // тогда вычисляем итоговое положение последнего звена
        auto position = manip.calculatePosition(lastLinkId);
        double x = std::get<0>(position);
        double y = std::get<1>(position);
        double z = std::get<2>(position);
        std::cout << "Position of " << lastLinkId << " link is (" 
                 << x << ", " << y << ", " << z << ")\n";
    }
    
    std::cout << "Movement finished.\n";
}

// поиск последнего звена в манипуляторе
int Movement::findLastLinkId(const Manipulator& manip) const {
    int maxId = -1;
    
    // пройдем по всем звеньям и найдем максимальный ID
    // используем printStructure для получения информации о звеньях
    // это не идеальное решение, но работает без изменения Manipulator
    for (int id = 1; id <= 1000; ++id) { // вряд ли звеньев будет больше в нашем роботе
        try {
            manip.calculatePosition(id); // пробуем вычислить позицию
            if (id > maxId) {
                maxId = id;
            }
        } catch (...) {
            // если не удалось вычислить позицию, значит звена с таким ID нет
            break;
        }
    }
    
    return maxId;
}
