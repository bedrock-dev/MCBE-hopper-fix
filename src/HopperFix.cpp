//
// Created by xhy on 2020/11/27.
//

#include "../hook/SymHook.h"
#include "../lib/mod.h"
#include "gsl"

namespace {
    constexpr uint64_t ITEM_ENTITY = 64u;

    int getRand(int size) {
        return rand() % size;
    }
}

//THook(
//        void*,
//        MSSYM_B2QUA9getItemAtB1AA6HopperB2AAE17IEAAPEAVItemActorB2AAE15AEAVBlockSourceB2AAA8AEBVVec3B3AAAA1Z,
//        void *hopper, void *blockSource, void * position
//) {
//    hopperWorking = true;
//    auto *item = original(hopper, blockSource, position);
//    hopperWorking = false;
//    return item;
//}


//fix hopper
THook(

        gsl::span<gsl::not_null<void *>>*,
        MSSYM_MD5_21a49b5175e9c00856ce77825b121141,
        void *bs,
        void *a2,
        uint64_t type, void * a4
) {
    if (type != ITEM_ENTITY)return original(bs, a2, type, a4);
    auto list = original(bs, a2, type, a4);
    if (list->size() < 2)return list;
    auto random = getRand(list->size());
    std::swap(list->operator[](0), list->operator[](random));
    return list;
}
