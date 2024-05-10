#pragma once
/*
  The only requirement for using precompile header is that 
  we must include the pch.h header file in all .cpp-files of the engine
*/


namespace fuse {
  struct app_config {
    int width = 0;
    int height = 0;       
    std::string title;
    std::string scene;
    std::string version;
  };

  // will be defined in game.exe
  app_config create_application();

  FUSE_API void run_application(const app_config&);  
}