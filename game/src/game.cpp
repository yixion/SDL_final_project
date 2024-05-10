#include <core/entry.h>

fuse::app_config fuse::create_application(){
    fuse::app_config config;
    config.version = "0.0.1";
    config.title = "Flight game 2024";
    config.height = 480;
    config.width = 560;
    return config;
}