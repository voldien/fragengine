# FragView
[![Travis Build Status](https://travis-ci.org/voldien/fragview.svg?branch=master)](https://travis-ci.org/voldien/fragview)

Fragment view software program for creating and experiment with shaders with *glsl*/*spirv*/*s*/*opencl-c*.

## Features
* Realtime file modification.
* Dynamic Rendering interface for multiple rendering API.
* Session Configuration

## Motivation
Based on the [https://github.com/voldien/glslview](glslview) program. That support OpenGL sandbox with realtime
modification of fragment shader. Whereas *fragview* will allow much greater flexibility and not only be limit to a single
shader language. Where both fragment and compute shader is support for the sandbox. Whereas the _world view_  will support
for using Geometry and tessellation.

## Installation
The software can be easily installed with invoking the following command.
```bash
mkdir build && cd build
cmake ..
cmake --build .
make install
```

## Examples
The following example will load the wave GLSL fragment shader. Where gamma correction is enabled with the *srgb*. Additionally
The default framebuffer alpha channel is enabled. Finally, the OpenGL rendering API is specified.
```
fragview -f samples/glsl/wave.frag --renderer-opengl --alpha --srgb
```

 Dependencies 
----------------
In order to compile the program, the following Debian packages is required.

```bash
apt install libyaml-dev libjson-c-dev libxml2-dev libsdl2-dev libglew-dev libvulkan-dev libgl1-mesa-dev opencl-headers libzip-dev libfswatch-dev libfreeimage-dev libavcodec-dev libavfilter-dev libavformat-dev  libassimp-dev libfreetype6-dev 
```

```bash
apt install libopenal-dev libalut-dev libbullet-dev
```

```bash
apt install libgtk-3-dev
```
External libraries library dependencies.
```bash
sudo apt install check libsubunit-dev
```
Tool dependencies.
```bash
apt install zip gzip libgtest-dev 
```

## License
This project is licensed under the GPL+3 License - see the [LICENSE](LICENSE) file for details
