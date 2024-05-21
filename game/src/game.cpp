#include <core/entry.h>

fuse::app_config fuse::create_application(){
    fuse::app_config config;
    config.version = "0.0.1";
    config.title = "Flight game 2024";
    config.height = 500;
    config.width = 380;
    return config;
}