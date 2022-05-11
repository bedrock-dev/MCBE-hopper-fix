//
// Created by xhy on 2020/8/24.
//
#ifndef TRAPDOOR_AABB_H
#define TRAPDOOR_AABB_H

#include "BlockPos.h"
#include "Vec3.h"

namespace trapdoor {

    struct AABB {
        Vec3 min{};
        Vec3 max{};

        AABB(Vec3 _p1, Vec3 _p2) {
            min = _p1;
            max = _p2;
        }

        Vec3 getCenter() const { return (min + max) * 0.5; }
        float getVolume() const { return abs((min - max).volume()); }
        void grow(Vec3 a) {
            min = min - a;
            max = max + a;
        }
    };

    struct BoundingBox {
        BlockPos minPos;
        BlockPos maxPos;

        inline BlockPos getCenter() const {
            return {(minPos.x + maxPos.x) / 2, (minPos.y + maxPos.y) / 2,
                    (minPos.z + maxPos.z) / 2};
        }

        AABB getSpawnArea() const {
            int x = (this->maxPos.x - this->minPos.x + 1) / 2 + this->minPos.x;
            int z =
                (this->maxPos.z - this->minPos.z + 1) / 2 + this->minPos.z + 1;
            Vec3 minPoint{x, minPos.y, z - 1};
            Vec3 maxPoint{x + 1, maxPos.y + 1, z};
            return {minPoint, maxPoint};
        }

        AABB toAABB() const {
            return {minPos.toVec3(), maxPos.toVec3() + Vec3(1, 1, 1)};
        }

        bool operator<(const BoundingBox& rhs) const {
            if (minPos < rhs.minPos)
                return true;
            if (rhs.minPos < minPos)
                return false;
            return maxPos < rhs.maxPos;
        }
    };
}  // namespace trapdoor
typedef trapdoor::AABB AABB;
typedef trapdoor::BoundingBox BoundingBox;
#endif  // TRAPDOOR_AABB_H
