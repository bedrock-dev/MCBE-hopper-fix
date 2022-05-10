

#ifndef TRAPDOOR_ACTOR_H
#define TRAPDOOR_ACTOR_H

#include <string>
#include <vector>

//#include "commands/CommandNode.h"
#include "../graphics/Vec3.h"
#include "../../hook/SymHook.h"
#include "../../lib/mod.h"

namespace trapdoor {
    class Actor {
       public:
        class Actor& operator=(class Actor const&) = delete;
        Actor(class Actor const&) = delete;
        Actor() = delete;
        //获取头部坐标
        Vec3* getPos() {
            return SYM_CALL(
                Vec3 * (*)(void*),
                SymHook::MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ,
                this);
        }
    };
}  // namespace trapdoor
#endif
