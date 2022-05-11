//
// Created by xhy on 2020/11/27.
//

#include "../hook/SymHook.h"
#include "../lib/mod.h"
#include "../api/graphics/AABB.h"
#include "../api/entity/Actor.h"
#include "gsl"

typedef trapdoor::Actor Actor;

namespace {
    constexpr uint64_t ITEM_ENTITY = 64u;
    int getRand(int size) { return rand() % size; }
    float frac(float x) { return x - floor(x); }
}  // namespace

// THook(
//         void*,
//         MSSYM_B2QUA9getItemAtB1AA6HopperB2AAE17IEAAPEAVItemActorB2AAE15AEAVBlockSourceB2AAA8AEBVVec3B3AAAA1Z,
//         void *hopper, void *blockSource, void * position
//) {
//     hopperWorking = true;
//     auto *item = original(hopper, blockSource, position);
//     hopperWorking = false;
//     return item;
// }

// fix hopper
THook(gsl::span<gsl::not_null<Actor*>>*,
      MSSYM_MD5_21a49b5175e9c00856ce77825b121141,
      void* blockSource,
      void* a2,
      uint64_t type,
      AABB* aABB) {
    auto volume =
        abs((aABB->max.x - aABB->min.x) * (aABB->max.y - aABB->min.y) *
            (aABB->max.z - aABB->min.z));
    if (type != ITEM_ENTITY || volume < 0.9994f ||
        volume > 1.000001f)  // isn't hopper or hopper_minecart
        return original(blockSource, a2, type, aABB);

    if (abs(frac(aABB->min.y) - 0.625f) < 0.0001f &&
        abs(frac((aABB->max.x + aABB->min.x) / 2.0f) - 0.5f) < 0.0001f &&
        abs(frac((aABB->max.z + aABB->min.z) / 2.0f) - 0.5f) < 0.0001f) {
        // is hopper
        aABB->max.y += 0.375f;
    }
    aABB->min.x = aABB->min.x - 0.125f;
    aABB->min.z = aABB->min.z - 0.125f;
    aABB->max.x = aABB->max.x + 0.125f;
    aABB->max.z = aABB->max.z + 0.125f;
    auto list = original(blockSource, a2, type, aABB);
    // std::cout << list->size();
    if (list->size() > 0 && list->size() != static_cast<std::size_t>(-1)) {
        std::vector<Actor*> suckList;
        for (int i = 0; i < list->size(); i++) {
            auto item = list->operator[](i);
            auto pos = item->getPos();
            // std::cout << pos->x << ',' << pos->y << ',' << pos->z <<
            // std::endl;
            if (pos->x > aABB->min.x && pos->z > aABB->min.z &&
                pos->x < aABB->max.x && pos->z < aABB->max.z) {
                // std::cout << "true" << std::endl;
                suckList.push_back(list->operator[](i));
            }
        }

        if (suckList.size() > 1) {
            auto random = getRand(suckList.size());
            std::swap(suckList[0], suckList[random]);
        }

        auto mEntityList = (int64_t*)((char*)blockSource + 152);

        *((int64_t*)blockSource + 20) =
            *((int64_t*)blockSource + 19);  // clear list

        for (auto* i : suckList) {
            float** v39 = (float**)mEntityList[1];
            int64_t v52;
            *(int64_t*)&v52 = (int64_t)i;
            *v39 = (float*)i;
            mEntityList[1] += 8i64;
        }
        auto v44 = (int64_t*)*mEntityList;
        auto v45 = (int64_t*)mEntityList[1];
        auto v46 = (int64_t*)*mEntityList;
        int64_t* result;
        result = (int64_t*)a2;
        if ((int64_t*)*mEntityList == v45) {
        LABEL_69:
            auto v27 = v45 - v44;
            *result = v27;
        } else {
            while (*v46) {
                if (++v46 == v45)
                    goto LABEL_69;
            }
        }
        // std::cout << "hooked" << std::endl;
        return (gsl::span<gsl::not_null<Actor*>>*)result;
    }

    return list;
}
