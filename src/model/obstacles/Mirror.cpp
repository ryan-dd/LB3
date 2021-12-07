#include "Mirror.h"

namespace lightpuzzle
{
    Mirror::Mirror(Direction direction):
        mDirection(direction),
        mNormalDirection(toVector(getNormal(direction)))
    {
    }

    Eigen::Vector2d Mirror::redirect(Direction input)
    {
        auto inputVec = toVector(input);
        return inputVec - 2*(inputVec.dot(mNormalDirection))*mNormalDirection;
    }
}

