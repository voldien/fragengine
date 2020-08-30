## FragView ##
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Travis Build Status](https://travis-ci.org/voldien/fragview.svg?branch=master)](https://travis-ci.org/voldien/fragview)

The *Fragview* software program for creating and experiment with shaders such as *glsl*/*spirv*/*s*/*opencl-c*. Where it support both sandbox for 2D canvas, similar to GLSL Sandbox. In Addition it support 3D models view for visuallie the effect on the 

 Whereas *fragview* will allow much greater flexibility and not only be limit to a single
shader language. Where both fragment and compute shader is support for the sandbox. Whereas the _world view_  will support
for using Geometry and tessellation.

## Examples
### Simple Fragment shader
The following example will load the wave GLSL fragment shader. Where gamma correction is enabled with the *srgb*. Additionally
The default framebuffer alpha channel is enabled. Finally, the OpenGL rendering API is specified.
```
fragview -f samples/glsl/wave.frag --renderer-opengl --alpha --srgb
```
### Compute Shader
```
fragview -f samples/glsl/wave.frag --renderer-opengl --alpha --srgb
```

##  Dependencies ##
This softwared uses both the *FragCore* and *FragEngine* library.


## License
This project is licensed under the GPL+3 License - see the [LICENSE](LICENSE) file for details
