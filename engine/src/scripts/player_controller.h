#pragma once
#include "script_instance.h"

namespace fuse
{
    struct player_controller:script_instance{

        FUSE_INLINE void on_start(){
            FUSE_INFO("player_script started!");
        }

        FUSE_INLINE void on_collision(ecs::entity e){
            FUSE_INFO("colliding with: %d", e.id());
        }

        FUSE_INLINE void on_update(float dt){
            auto& t = get_component<ecs::transform_component>();
            
            if(inputs::is_key(SDL_SCANCODE_A)){
                t.translate.x -= (speed*dt);
            }

            if(inputs::is_key(SDL_SCANCODE_D)){
                t.translate.x += (speed*dt);
            }

            if(inputs::is_key(SDL_SCANCODE_W)){
                t.translate.y -= (speed *dt);
            }

            if(inputs::is_key(SDL_SCANCODE_S)){
                t.translate.y += (speed * dt);
            }
        }
        private:
            float speed = 300.0f;
    };
} // namespace fuse
