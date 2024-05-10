#pragma once
#include "math/vec2.h"
#include "dispatcher.h"

namespace fuse::inputs
{
    struct mouse_state{
        std::bitset<7> buttons={0};
        vec2f offset, wheel;
    };
    FUSE_API const vec2f& mouse_offset();
    FUSE_API const vec2f& mouse_wheel();
    FUSE_API bool is_button(int);
    
    FUSE_API void initialize(SDL_Window*);
    FUSE_API dispatcher* get_dispatcher();
    FUSE_API void dispatch_evnets();
    FUSE_API bool is_key(int);
} // namespace fuse::inputs