#pragma once

using RVA = unsigned int;
// public: class gsl::span<class gsl::not_null<class Actor * __ptr64>,-1>
// __cdecl BlockSource::fetchEntities(enum ActorType,class AABB const &
// __ptr64,class Actor const * __ptr64) __ptr64
constexpr RVA MSSYM_MD5_21a49b5175e9c00856ce77825b121141 = 0x00A18070;

namespace SymHook {

    // [ԭ��] public: virtual class Vec3 const & __ptr64 __cdecl
    // Actor::getPos(void)const __ptr64 [����] ?getPos@Actor@@UEBAAEBVVec3@@XZ
    constexpr RVA MSSYM_B1QA6getPosB1AA5ActorB2AAE12UEBAAEBVVec3B2AAA2XZ =
        0x00554A80;
}  // namespace SymHook
