#include <iostream>
#include <cmath>
#include "MovableLink.h"
#include "Gripper.h"
#include "Camera.h"
#include "Manipulator.h"
#include "ElementaryMove.h"
#include "Movement.h"
#include "Tests.h"

#define PI 3.14159265358979323846

int main() {
    std::cout << "=== Robot Manipulator System ===" << std::endl;
    
    // создание и тестирование базового звена
    MovableLink link2(2, 1, 1.0, 0.0, 0.0, 0.0);
    link2.printInfo();

    link2.setDirection(1.0, 0.0, 0.0);
    link2.printInfo();

    link2.changeDirection(0.5, 0.0, 0.0);
    link2.printInfo();

    // запуск тестов
    runTests();

    // создание манипулятора и добавление звеньев
    Manipulator robot;

    robot.addLink(new MovableLink(1, 0, 1.0, 0.0, 0.0, 0.0));
    robot.addLink(new MovableLink(2, 1, 1.0, 0.0, 0.0, 0.0));
    robot.addLink(new Gripper(3, 2, 1.0, 0.0, 0.0, 0.0, 0.2));
    robot.addLink(new MovableLink(4, 3, 1.0, 0.0, 0.0, 0.0));
    robot.addLink(new Camera(5, 4, 0.5, 0.2, 0.0, 0.0, PI / 4));

    robot.printStructure();

    // проверка функционала захвата
    robot.openGripper(3, 0.5);
    robot.closeGripper(3);

    // проверка функционала камеры
    robot.takePhoto(5);

    // создаем движение
    Movement movement;
    movement.addMove(ElementaryMove(2, PI / 4, 0.0, 0.0));
    movement.addMove(ElementaryMove(3, PI / 6, 0.0, 0.0));
    movement.executeAll(robot);

    robot.printStructure();

    // вычисляем положение конца звена 3
    auto position = robot.calculatePosition(3);
    double x = std::get<0>(position);
    double y = std::get<1>(position);
    double z = std::get<2>(position);
    std::cout << "End of link 3 at (" << x << ", " << y << ", " << z << ")" << std::endl;

    return 0;
}
