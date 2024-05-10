#pragma once

namespace fuse
{
    FUSE_INLINE const uint32_t get_unique_typeid(){
        static uint32_t type = 1u;
        return type++;
    }
    //https://stackoverflow.com/questions/10535667/does-it-make-any-sense-to-use-inline-keyword-with-templates
    //ODR violations
        template<typename T> 
        FUSE_INLINE const uint32_t type_id(){
            static const uint32_t type = get_unique_typeid();
            return type;
        }
} // namespace fuse
