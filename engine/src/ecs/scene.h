#pragma once
#include "ecs/systems/sprite_renderer_system.h"
#include "ecs/systems/text_renderer_system.h"
#include "ecs/systems/frame_animation_system.h"
namespace fuse::ecs {
  struct scene {

    FUSE_INLINE scene(SDL_Renderer* rd): _renderer(rd) {
      register_system<ecs::frame_animation_system>();
      register_system<ecs::sprite_renderer_system>();
      register_system<ecs::text_renderer_system>();
    }

    FUSE_INLINE ~scene() {
      for (auto& s : _systems) { FUSE_DELETE(s); }
      _registry.clear();
      _systems.clear();
    }

    FUSE_INLINE ecs::entity add_entity(const std::string& name) {
      auto entity = ecs::entity(&_registry);
      entity.add_component<info_component>().name = name;
      entity.add_component<transform_component>();
      return entity;
    }

    FUSE_INLINE void update(float dt) {
      //set the color of the renderer to white
      SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
      for (auto& sys : _systems) { sys->update(dt); }
    }

    FUSE_INLINE void start(){
      //load texture
      auto sprite = _assets.load_texture("assets/test.png","test",_renderer);
      auto f1 = _assets.load_texture("assets/fly1.png","f1",_renderer);
      auto f2 = _assets.load_texture("assets/fly2.png","f2",_renderer);
      //load texture asset
      auto font = _assets.load_font("assets/font.ttf", "ft", 30);
      //create entity
      ecs::entity entity1 = add_entity("player");
      ecs::entity entity2 = add_entity("text");
      ecs::entity entity3 = add_entity("plane");

      //add animation asset
      auto animation = _assets.add<animation_asset>("fight");
      animation->instance.frames.push_back(f1->id);
      animation->instance.frames.push_back(f2->id);
      animation->instance.speed = 300;
      
      //add sprite component
      auto& a = entity3.add_component<ecs::animation_component>();
      a.animation = animation->id;
      entity1.add_component<ecs::sprite_component>().sprite = sprite->id;
      auto& tx = entity2.add_component<ecs::text_component>();
      tx.text = "This is a text!";
      tx.font = font->id;
      for(auto& sys:_systems){sys->start();}
      
    }

    template <typename T>
    FUSE_INLINE void register_system() {
      FUSE_STATIC_ASSERT(std::is_base_of<ecs::system, T>::value);
      auto new_system = new T();
      new_system->prepare(&_registry, _renderer, &_assets);
      this->_systems.push_back(new_system);
    }

    private:
      std::vector<ecs::system*> _systems;
      SDL_Renderer* _renderer = NULL;
      ecs::registry _registry;
      asset_registry _assets;
    };
}

