#ifndef LIGHTPUZZLE_MIRROR_H
#define LIGHTPUZZLE_MIRROR_H

#include "Direction.h"
#include <Eigen/Dense>

namespace lightpuzzle
{
    class Mirror
    {
    private:
        Direction mDirection;
        Eigen::Vector2d mNormalDirection;
    public:
        explicit Mirror(Direction direction);
        
        /**
         * @brief Redirects beam from input direction to output direction
         * 
         * @param input 
         * @return Direction 
         */
        Direction redirect(Direction input);

    };
}

#endif
