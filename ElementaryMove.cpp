#include "ElementaryMove.h"
#include <iostream>

ElementaryMove::ElementaryMove(int link_id, double target_pitch, double target_yaw, double target_roll)
    : link_id_(link_id), target_pitch_(target_pitch), target_yaw_(target_yaw), target_roll_(target_roll), valid_(true) {}


// выполнение движения на манипуляторе
void ElementaryMove::execute(Manipulator& manip) {
    manip.setDirection(link_id_, target_pitch_, target_yaw_, target_roll_);
}
