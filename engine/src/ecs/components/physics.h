#pragma once
#include "physics/rigidbody2.h"

namespace fuse::ecs
{
    
  struct rigidbody_component{
    FUSE_INLINE rigidbody_component() = default;
    bool disabled = false;
    rigidbody2 body;
  };
} // namespace fuse::ecs
