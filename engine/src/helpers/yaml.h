#pragma once
#include "pch.h"
#include "math/vec2.h"
#include "yaml-cpp/yaml.h"

namespace YAML {

    // vec2f
    template <>
    struct convert<fuse::vec2f> {
        FUSE_INLINE static YAML::Node encode(const fuse::vec2f& rhs){
            YAML::Node node;
            node.push_back(rhs.x);
            node.push_back(rhs.y);
            node.SetStyle(YAML::EmitterStyle::Flow);
            return node;
        }

        FUSE_INLINE static bool decode(const YAML::Node &node, fuse::vec2f& rhs){
            if(!node.IsSequence() || node.size() != 2){
                return false;
            }
            rhs.x = node[0].as<float>();
            rhs.y = node[1].as<float>();
            return true;
        }
    };
    
    // stream operator
    FUSE_INLINE YAML::Emitter & operator << (YAML::Emitter & emitter, const fuse::vec2f &v) {
        emitter << YAML::EmitterStyle::Flow;
        emitter << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
        return emitter;
    }
}
