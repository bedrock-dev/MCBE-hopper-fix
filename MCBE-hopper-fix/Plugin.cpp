#include "pch.h"
#include <EventAPI.h>
#include <LLAPI.h>
#include <gsl/gsl>
#include "FMT/chrono.h"
#include "FMT/color.h"
#include "FMT/core.h"
#include "FMT/os.h"
#include "FMT/format.h"
namespace {
    constexpr uint64_t ITEM_ENTITY = 64u;

    int getRand(int size) {
        return rand() % size;
    }
}

//fix hopper
THook(
    gsl::span<gsl::not_null<void*>>*,
    "?fetchEntities@BlockSource@@QEAA?AV?$span@V?$not_null@PEAVActor@@@gsl@@$0?0@gsl@@V?$span@V?$not_null@PEBVActor@@@gsl@@$0?0@3@AEBVAABB@@_N@Z",
    void* bs,
    void* a2,
    uint64_t type,
    void* a4
) {
    if (type != ITEM_ENTITY)return original(bs, a2, type, a4);
    auto list = original(bs, a2, type, a4);
    if (list->size() < 2)return list;
    auto random = getRand(list->size());
    std::swap(list->operator[](0), list->operator[](random));
    return list;
}

void PluginInit() {
    fmt::print(fmt::format("[{:%H:%M:%S} Info][MCBE-hopper-fix] Loaded\n", fmt::localtime(_time64(0))));
}