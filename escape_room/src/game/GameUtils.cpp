#include "GameUtils.h"

bool CheckDistanceLimit(GameObject& ob1, GameObject& ob2)
{
    if (glm::distance(ob1.GetPosition(), ob2.GetPosition()) <= MAX_PICK_DIST)
        return true;
    return false;
}
