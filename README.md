# Final Project: Air Fight

This is a game where an airplane flies through obstacles and attempts to get to the final point. The game will terminate when the airplane collides with boundaries or obstacles.

## Languages Used
- C
- C++

## Environment Construction

1. **Download SDL**: Functions for creating windows and reading the keyboard info. [SDL Release 2.30.3](https://github.com/libsdl-org/SDL/releases/tag/release-2.30.3).
2. **Download SDL_image**: For loading images. [SDL_image Library](https://wiki.libsdl.org/SDL2/Libraries#sdl_image).
3. **Download SDL_ttf**: For generating fonts. [SDL_ttf Library](https://wiki.libsdl.org/SDL2/Libraries#sdl_ttf).
4. **Download SDL_mixer**: For adding background music. [SDL_mixer Library](https://wiki.libsdl.org/SDL2/Libraries#sdl_mixer).
5. **Compile Using VSCode and CMake**: Set up your development environment with Visual Studio Code and CMake for compiling the project.

## Game Engine

### Assets
- **Graphics**: Visual elements of the game.
- **Audio**: Sound effects and background music.
- **Fonts**: Text rendering.
- **Registers**: Keeps track of game assets.

### Core
- **Controls**: Manages keyboard inputs and outputs.
- **UID Storage**: Stores unique identifiers for game objects.
- **Game Loop**: Continuously loops the game if not terminated.

### ECS (Entity Component System)
- **Behavior Control**: Manages the behavior of game objects.
- **common.h**: Stores information and position of objects.
- **physics.h**: Handles the logic of object physics.
- **graphics.h**: Manages rendering of graphics, audio, and fonts.

### Windows
- **Libraries**: Contains the SDL systems libraries.
- **Logic Implementation**: Implements the game logic mentioned above.

### Script Language
- **Object Behavior**: Instantiates the behavior of objects on the screen.

## Compilation and Setup
1. Ensure all necessary SDL libraries are downloaded and properly linked in your development environment.
2. Use CMake to configure and generate build files.
3. Compile the project using Visual Studio Code.

## To Run the Game
1. Ensure all assets (graphics, audio, fonts) are in the correct directories.
2. Press F5 to start the game and press A to change the color of the plane
3. Use spacebar to control the airplane and navigate through obstacles.
4. The game will terminate if the airplane collides with any boundaries or obstacles.
