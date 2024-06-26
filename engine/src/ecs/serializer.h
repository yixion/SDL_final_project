#pragma once
#include "entity.h"
#include "helpers/yaml.h"
#include "components/common.h"
#include "components/physics.h"
#include "components/graphics.h"
#include "components/behaviour.h"


namespace fuse::ecs {
    struct serializer {
        FUSE_INLINE serializer(registry *reg) : _registry(reg) {}

        // deserialize all entities
        FUSE_INLINE void deserialize(const YAML::Node nodes){
            
            // clear registry
            _registry->clear();

            // deserialize all entities
            for(auto node:nodes) {
                ecs::entity e(_registry);  // create a entity 
                deserialize_info(node, e);
                deserialize_transform(node, e);
                // deserialize_rigidbody(node, e);
                // deserialize_collider(node, e);
                // deserialize_sprite(node, e);
                // deserialize_animation(node, e);
                // deserialize_text(node, e);
                // deserialize_script(node, e);
            }
        }

        // serialize all entities
        FUSE_INLINE void serialize(YAML::Emitter& em) {
            em << YAML::Key << "entities" << YAML::Value << YAML::BeginSeq;
            for(auto& e: _registry->view<ecs::info_component>()) {
                ecs::entity entity(e, _registry);
                
                em << YAML::BeginMap;
                serialize_info(em, entity);
                serialize_transform(em, entity);
                // serialize_rigidbody(em, entity);
                // serialize_collider(em, entity);
                // serialize_sprite(em, entity);
                // serialize_animation(em, entity);
                // serialize_text(em, entity);
                // serialize_script(em, entity);
                em << YAML::EndMap;
            }
            em << YAML::EndSeq;
        }

        // serialize info_component
        FUSE_INLINE void serialize_info(YAML::Emitter& em, entity& e){
            if(e.has_component<ecs::info_component>()) {
                auto& i = e.get_component<ecs::info_component>();
                em << YAML::Key << "info_component";
                em << YAML::BeginMap;
                em << YAML::Key << "uuid" << YAML::Value << i.uuid;
                em << YAML::Key << "name" << YAML::Value << i.name;
                em << YAML::Key << "tag" << YAML::Value << i.tag;
                em << YAML::EndMap;
            }
        }

        // deserialize info_component
        FUSE_INLINE void deserialize_info(YAML::Node node, entity& e) {
            if(auto data = node["info_component"]) {
                auto& i = e.add_component<ecs::info_component>();
                i.uuid = data["uuid"].as<uuid64>();
                i.name = data["name"].as<std::string>();
                i.tag = data["tag"].as<std::string>();
            }
        }

        // serialize transform_component
        FUSE_INLINE void serialize_transform(YAML::Emitter& em, entity& e){
            if(e.has_component<ecs::transform_component>()) {
                auto& t = e.get_component<ecs::transform_component>();
                em << YAML::Key << "transform_component";
                em << YAML::BeginMap;
                em << YAML::Key << "translate" << YAML::Value << YAML::Flow << YAML::BeginSeq << t.translate.x << t.translate.y << YAML::EndSeq;
                em << YAML::Key << "scale" << YAML::Value << YAML::Flow << YAML::BeginSeq << t.scale.x << t.scale.y << YAML::EndSeq;
                em << YAML::Key << "rotation" << YAML::Value << t.rotation;
                em << YAML::EndMap;
            }
        }

        // deserialize transform_component
        FUSE_INLINE void deserialize_transform(YAML::Node node, entity& e) {
            if(auto data = node["transform_component"]) {
                auto& t = e.add_component<ecs::transform_component>();
                t.translate = data["translate"].as<vec2f>();
                t.scale = data["scale"].as<vec2f>();
                t.rotation = data["rotation"].as<float>();
            }
        }

        // serialize rigidbody_component
        FUSE_INLINE void serialize_rigidbody(YAML::Emitter& em, entity& e) {
            if(e.has_component<ecs::rigidbody_component>()) {
                auto& r = e.get_component<ecs::rigidbody_component>();
                em << YAML::Key << "rigidbody_component";
                em << YAML::BeginMap;
                em << YAML::Key << "gravity" << YAML::Value << r.body.gravity_scale;
                em << YAML::Key << "velocity" << YAML::Value << r.body.velocity;
                em << YAML::Key << "disabled" << YAML::Value << r.disabled;
                em << YAML::Key << "force" << YAML::Value << r.body.force;
                em << YAML::EndMap;
            }
        }

        // deserialize rigidbody_component
        FUSE_INLINE void deserialize_rigidbody(YAML::Node node, entity& e) {
            if(auto data = node["rigidbody_component"]) {
                auto& r = e.add_component<ecs::rigidbody_component>();
                r.body.gravity_scale = data["gravity"].as<float>();
                r.body.velocity = data["velocity"].as<vec2f>();
                r.disabled = data["disabled"].as<bool>();
                r.body.force = data["force"].as<vec2f>();
            }
        }

        // serialize collider_component
        FUSE_INLINE void serialize_collider(YAML::Emitter& em, entity& e) {
            auto& c = e.get_component<ecs::collider_component>();
            em << YAML::Key << "collider_component";
            em << YAML::BeginMap;
            em << YAML::Key << "width" << YAML::Value << c.collider.w;
            em << YAML::Key << "height" << YAML::Value << c.collider.h;
            em << YAML::Key << "disabled" << YAML::Value << c.disabled;
            em << YAML::EndMap;
        }

        // deserialize collider_component
        FUSE_INLINE void deserialize_collider(YAML::Node node, entity& e) {
            if(auto data = node["collider_component"]) {
                auto& c = e.add_component<ecs::collider_component>();
                c.collider.w = data["width"].as<float>();
                c.collider.h = data["height"].as<float>();
                c.disabled = data["disabled"].as<bool>();
            }
        }

        // serialize sprite_component
        FUSE_INLINE void serialize_sprite(YAML::Emitter& em, entity& e) {
            auto& s = e.get_component<ecs::sprite_component>();
            em << YAML::Key << "sprite_component";
            em << YAML::BeginMap;
            em << YAML::Key << "sprite" << YAML::Value << s.sprite;
            em << YAML::Key << "flip" << YAML::Value << s.flip;
            em << YAML::EndMap;
        }

        // deserialize sprite_component
        FUSE_INLINE void deserialize_sprite(YAML::Node node, entity& e) {
            if(auto data = node["sprite_component"]) {
                auto& s = e.add_component<ecs::sprite_component>();
                s.sprite = data["sprite"].as<asset_id>();
                s.flip = (SDL_RendererFlip)data["flip"].as<int>();
            }
        }

        // serialize animation_component
        FUSE_INLINE void serialize_animation(YAML::Emitter& em, entity& e) {
            if(e.has_component<ecs::animation_component>()) {
                auto& a = e.get_component<ecs::animation_component>();
                em << YAML::Key << "animation_component";
                em << YAML::BeginMap;
                em << YAML::Key << "animations" << YAML::Value << a.animation;
                em << YAML::Key << "flip" << YAML::Value << (int)a.flip;
                em << YAML::EndMap;
            }
        }

        // deserialize animation_component
        FUSE_INLINE void deserialize_animation(YAML::Node node, entity& e) {
            if(auto data = node["animation_component"]) {
                auto& a = e.add_component<ecs::animation_component>();
                a.animation = data["animations"].as<asset_id>();
                a.flip = (SDL_RendererFlip)data["flip"].as<int>();
            }
        }

        // serialize text_component
        FUSE_INLINE void serialize_text(YAML::Emitter& em, entity& e) {
            if(e.has_component<ecs::text_component>()) {
                auto& t = e.get_component<ecs::text_component>();
                em << YAML::Key << "text_component";
                em << YAML::BeginMap;
                em << YAML::Key << "R" << YAML::Value << t.color.r;
                em << YAML::Key << "G" << YAML::Value << t.color.g;
                em << YAML::Key << "B" << YAML::Value << t.color.b;
                em << YAML::Key << "A" << YAML::Value << t.color.a;
                em << YAML::Key << "text" << YAML::Value << t.text;
                em << YAML::Key << "font" << YAML::Value << t.font;
                em << YAML::Key << "flip" << YAML::Value << t.flip;
                em << YAML::EndMap;
            }
        }

        // derialize text_component
        FUSE_INLINE void deserialize_text(YAML::Node node, entity& e) {
            if(auto data = node["text_component"]) {
                auto& t = e.add_component<ecs::text_component>();
                t.color.r = data["R"].as<uint8_t>();
                t.color.g = data["G"].as<uint8_t>();
                t.color.b = data["B"].as<uint8_t>();
                t.color.a = data["A"].as<uint8_t>();
                t.text = data["text"].as<std::string>();
                t.font = data["font"].as<asset_id>();
                t.flip = (SDL_RendererFlip)data["flip"].as<int>();
            }
        }

        // serialize script_component
        FUSE_INLINE void serialize_script(YAML::Emitter& em, entity& e) {
            if(e.has_component<ecs::script_component>()) {
                auto& s = e.get_component<ecs::script_component>();
                em << YAML::Key << "script_component";
                em << YAML::BeginMap;
                em << YAML::Key << "name" << YAML::Value << s.name;
                em << YAML::EndMap;
            }
        }

        // derialize script_component
        FUSE_INLINE void deserialize_script(YAML::Node node, entity& e) {
            if(auto data = node["script_component"]) {
                auto& s = e.add_component<ecs::script_component>();
                s.name = data["name"].as<std::string>();

                if(!s.name.compare("player_controller")) {
                    s.bind<player_controller>();
                }
                else if(!s.name.compare("scrolling_ground")) {
                    s.bind<scrolling_ground>();
                }
                else if(!s.name.compare("pipe_spawner")) {
                    s.bind<pipe_spawner>();
                }
            }
        }



    private:
        registry* _registry = NULL;
    };
}
