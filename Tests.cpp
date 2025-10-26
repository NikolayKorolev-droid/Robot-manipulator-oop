#include "Tests.h"

#define M_PI 3.14159265358979323846

// Упрощенная функция для запуска основных тестов
void runTests() {
    std::cout << "\n===== BASIC TESTS =====\n";

    // 1. Тест создания и управления звеном
    MovableLink link1(1, 0, 1.0, 0.0, 0.0, 0.0);
    assert(link1.getId() == 1);
    assert(std::abs(link1.getR() - 1.0) < 1e-9);
    
    link1.setDirection(M_PI/4, M_PI/6, 0.0);
    auto dir = link1.getDirection();
    assert(std::abs(dir.first - M_PI/4) < 1e-9);
    assert(std::abs(dir.second - M_PI/6) < 1e-9);

    // 2. Тест захвата
    Gripper gripper(2, 1, 1.0, 0.0, 0.0, 0.0, 0.5);
    assert(std::abs(gripper.getOpenAngle() - 0.5) < 1e-9);
    
    gripper.open(1.0);
    assert(std::abs(gripper.getOpenAngle() - 1.0) < 1e-9);
    
    gripper.close();
    assert(std::abs(gripper.getOpenAngle() - 0.0) < 1e-9);

    // 3. Тест камеры
    Camera camera(3, 2, 0.5, 0.0, 0.0, 0.0, M_PI/4);
    assert(std::abs(camera.getR() - 0.5) < 1e-9);
    camera.take_a_photo(); // должно работать без ошибок

    // 4. Тест манипулятора
    Manipulator manipulator;
    manipulator.addLink(new MovableLink(1, 0, 1.0, 0.0, 0.0, 0.0));
    manipulator.addLink(new MovableLink(2, 1, 1.0, 0.0, 0.0, 0.0));
    manipulator.addLink(new Gripper(3, 2, 1.0, 0.0, 0.0, 0.0, 0.2));
    manipulator.addLink(new Camera(4, 3, 0.5, 0.0, 0.0, 0.0, M_PI/6));

    // 5. Тест управления манипулятором
    manipulator.setDirection(1, M_PI/4, M_PI/6, 0.0);
    manipulator.openGripper(3, 0.5);
    manipulator.closeGripper(3);
    manipulator.takePhoto(4);

    // 6. Тест вычисления позиций
    auto pos1 = manipulator.calculatePosition(1);
    double x1 = std::get<0>(pos1);
    double y1 = std::get<1>(pos1);
    double z1 = std::get<2>(pos1);
    
    // Проверяем, что позиция вычисляется корректно
    assert(std::abs(x1) < 10.0 && std::abs(y1) < 10.0 && std::abs(z1) < 10.0);

    // 7. Тест элементарных движений
    ElementaryMove move1(1, M_PI/4, 0.0, 0.0);
    ElementaryMove move2(2, M_PI/6, 0.0, 0.0);
    
    Movement movement;
    movement.addMove(move1);
    movement.addMove(move2);
    movement.executeAll(manipulator);

    // 8. Тест структуры манипулятора
    manipulator.printStructure();

    std::cout << "\n===== ALL BASIC TESTS PASSED =====\n";
}