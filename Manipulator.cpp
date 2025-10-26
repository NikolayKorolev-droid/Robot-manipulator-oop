#include "Manipulator.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <algorithm>

#define M_PI 3.14159265358979323846

// деструктор (пробегается по всем парам в links_ и удаляет их)
Manipulator::~Manipulator() {
    for (auto& p : links_)
        delete p.second;
}

// добавление звена в манипулятор
void Manipulator::addLink(MovableLink* link) {
    int id = link->getId();
    if (links_.count(id)) {
        std::cerr << "Link with id " << id << " already exists!\n";
        return;
    }
    links_[id] = link;
}

// получение звена по ID
MovableLink* Manipulator::getLink(int id) const {
    auto it = links_.find(id);
    if (it != links_.end()) {
        return it->second;
    }
    return nullptr;
}

// управление углами звеньев
void Manipulator::setDirection(int id, double new_pitch, double new_yaw, double new_roll) {
    assert(links_.count(id) && "link with this id doesn't exist");
    links_[id]->setDirection(new_pitch, new_yaw, new_roll);
}

// открытие захвата
void Manipulator::openGripper(int id, double angle) {
    Gripper* g = dynamic_cast<Gripper*>(links_[id]);
    if (g)
        g->open(angle);
    else
        std::cerr << "Link " << id << " is not a gripper!\n";
}

// закрытие захвата
void Manipulator::closeGripper(int id) {
    Gripper* g = dynamic_cast<Gripper*>(links_[id]);
    if (g)
        g->close();
    else
        std::cerr << "Link " << id << " is not a gripper!\n";
}

// сделать фото
void Manipulator::takePhoto(int id) {
    Camera* c = dynamic_cast<Camera*>(links_[id]);
    if (c)
        c->take_a_photo();
    else
        std::cerr << "Link " << id << " is not a camera!\n";
}

// вычисление позиции звена в глобальной системе координат
// 1. roll не влияет на позицию (в нашем роботе для упрощения стержни вращаются так, что не влияют на другие стержни)
// 2. координаты звена n: (x_n, y_n, z_n)[абс] = (x_{n-1}, y_{n-1}, z_{n-1})[абс] + (r_n*cos(yaw)*sin(pitch), r_n*sin(yaw)*sin(pitch), r_n*cos(pitch))
// где [абс] - координаты в глобальной системе координат
// 3. представим, что первое звено прикреплено к блоку управления, причем понятно, что pitch(id=1)<=pi/2, yaw(id=1)<=pi/2, см. картинку в readme; 
// в то время как pitch(id>1), yaw(id>1) - любые с условием, что звенья не сталкиваются друг с другом. Этот блок управления - ноль в глобальной системе координат. 
// Тогда по формуле выше (x_{1}, y_{1}, z_{1})[абс] = (r{n}*cos(yaw)sin(pitch), r{n}*sin(yaw)sin(pitch), r{n}*cos(pitch)). 
// 4. Далее с помощью for находим координаты всех звеньев вплоть до n-го
std::tuple<double, double, double> Manipulator::calculatePosition(int id) const {
    assert(links_.count(id) && "link with this id doesn't exist");
    
    // соберем все звенья от блока управления до нужного звена
    std::vector<int> chain;
    int current_id = id;
    while (current_id != 0 && links_.count(current_id)) {
        chain.push_back(current_id);
        current_id = links_.at(current_id)->getPrevId();
    }
    
    // если цепочка неполная, возвращаем ошибку
    if (current_id != 0) {
        std::cerr << "Incomplete chain to link " << id << std::endl;
        return std::make_tuple(0.0, 0.0, 0.0);
    }
    
    // перевернем цепочку, чтобы идти от корня к нужному звену
    std::reverse(chain.begin(), chain.end());
    
    // координаты блока управления 
    double x = 0.0, y = 0.0, z = 0.0;
    
    // вычислим координаты каждого звена в цепочке вплоть до нужного
    for (size_t i = 0; i < chain.size(); ++i) {
        const MovableLink* link = links_.at(chain[i]);
        double r = link->getR();
        auto direction = link->getDirection();
        double pitch = direction.first;
        double yaw = direction.second;
        
        // проверим ограничения для первого звена
        if (chain[i] == 1) {
            if (pitch > M_PI/2 || yaw > M_PI/2) {
                std::cerr << "Pitch and yaw can't be greater than pi/2: pitch=" << pitch 
                         << ", yaw=" << yaw << std::endl;
                return std::make_tuple(0.0, 0.0, 0.0);
            }
        }
        
        // вычислим относительные координаты текущего звена
        double dx = r * cos(yaw) * sin(pitch);
        double dy = r * sin(yaw) * sin(pitch);
        double dz = r * cos(pitch);
        
        // отсюда найдем абсолютные координаты
        x += dx;
        y += dy;
        z += dz;
        
        // проверим столкновения с предыдущими звеньями (кроме первого)
        if (i > 0) {
            if (!checkCollision(chain, i, x, y, z)) {
                std::cerr << "Collision detected for link " << chain[i] 
                         << " at position (" << x << ", " << y << ", " << z << ")" << std::endl;
                return std::make_tuple(0.0, 0.0, 0.0);
            }
        }
    }
    
    return std::make_tuple(x, y, z);
}

// проверка столкновений: проверяем, что новое звено не пересекается
// с предыдущими звеньями в цепочке
bool Manipulator::checkCollision(const std::vector<int>& chain, size_t current_index, 
                                 double x, double y, double z) const {
    
    // получим координаты текущего звена
    double current_x = x;
    double current_y = y;
    double current_z = z;
    
    // проверим столкновения с предыдущими звеньями в цепочке
    for (size_t i = 0; i < current_index; ++i) {
        // вычислим координаты предыдущего звена
        double prev_x = 0.0, prev_y = 0.0, prev_z = 0.0;
        for (size_t j = 0; j <= i; ++j) {
            const MovableLink* link = links_.at(chain[j]);
            double r = link->getR();
            auto direction = link->getDirection();
            double pitch = direction.first;
            double yaw = direction.second;
            
            double dx = r * cos(yaw) * sin(pitch);
            double dy = r * sin(yaw) * sin(pitch);
            double dz = r * cos(pitch);
            
            prev_x += dx;
            prev_y += dy;
            prev_z += dz;
        }
        
        // проверим расстояние между звеньями
        double distance = sqrt(pow(current_x - prev_x, 2) + 
                              pow(current_y - prev_y, 2) + 
                              pow(current_z - prev_z, 2));
        
        // если расстояние слишком мало, считаем это столкновением
        if (distance < 0.1) { // минимальное расстояние между звеньями (по факту проверяем лишь то, что звенья не сомкнулись в цикл)
            return false;
        }
    }
    
    return true;
}

// вывод структуры манипулятора
void Manipulator::printStructure() const {
    std::cout << "\n--- Manipulator Structure ---\n";
    for (auto& pair : links_) {
        int id = pair.first;
        MovableLink* link = pair.second;
        link->printInfo();
    }
    std::cout << "------------------------------\n";
}
