# Most Excellent Game Engine (MEGEngine)
A personal development project to learn about game development, engine design, and to improve software development skills. Rendering system wraps OpenGL but plans for the future are to replace this with Vulkan.

## Requirements
These dependencies are wrapped by MEGEngine so the user doesn't have to interact directly with the libraries. They can be swapped out in future if necessary without affecting the MEGEngine interface. Wherever possible, these dependencies have been kept out of header files so their classes and types are not accessible to a MEGEngine user, but MEGEngine functionality is dependent on them.
- OpenGL
    The graphics engine - this must be installed separately
- GLAD
    Loads references to OpenGL functions in memory for use at runtime
- GLFW
    Handles windows and OpenLG context. Via windows it handles inputs etc.
- GLM
    Maths library. Contains the actual implementation of maths operations.
- JSON
    Library for reading and writing json data. Currently used for persistent settings via json files
- STB
    Library for loading images. Used within the renderer for textures and materials

## Build & Install
To configure and build the MEGEngine library, create a ```build``` dir and run cmake from there:
```bash
mkdir build && cd build
cmake .. # configure the cmake project, giving '..' (proj root dir) as the src dir
make # build all targets covered by the configuration
```

You can add optional flags to the ```cmake ..``` command to build example games and unit tests:
```bash
cmake .. -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON
```
These flags are ```OFF``` by default. By enabling these flags, you will see the unit test target and game targets get built when you run the ```make``` command.

If you are going to install the library, you should also add the flag to specify it should be built in release mode ```-DCMAKE_BUILD_TYPE=Release```.

After building the library, you can install it system-wide using the install command:
```bash
sudo make install
```
If you don't want to install system-wide, you can drop the ```sudo``` from the start.

You can now link the library to your game projects:
```cmake
find_package(MEGEngine REQUIRED)
```

And you can include the MEGEngine headers:
```cpp
#include <MEGEngine/Core.h>
#include <MEGEngine/Core/Application.h> // although this would already be included by the line above
#include <MEGEngine/Math.h>
```
