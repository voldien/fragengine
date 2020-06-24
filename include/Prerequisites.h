/**
    FrameView for rendering shaders in screen space.
    Copyright (C) 2018  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _CORE_PREREQUISITES_H_
#define _CORE_PREREQUISITES_H_ 1
#include"audio/Prerequisites.h"
#include"physic/Prerequisites.h"
#include"Renderer/Prerequisites.h"

namespace fragview {

	/*  Core.   */
	class FileNotify;
	class IConfig;
	class Object;

	class IScheduler;

	/*  IO  */
	class IO;
	class FileIO;
	class ZipFileIO;
	class BufferIO;
	class FileAccess;
	class ASync;
	class GZFileIO;
	class ZipFile;
	class IFileSystem;
	class FileSystem;

	class Hash;
	class Random;
	class Base64;
	class Base32;
	class Base16;
	/*  Network.    */
	class IP;
	class NetSocket;
	
	/**
	 *
	 */
	class Scene;
	class SandBoxSubScene;
	class RenderPipeline;

	/**
	 *
	 */
	class Node;
	class Camera;
	class Frustum;
	class Light;
	/**
	 *
	 */
	class TargetNode;

	class IRenderPipelineBase;
	class RenderPipelineBase;
	class RenderPipelineSandBox;
	class Mesh;
	class MeshFilter;
	class ParticleSystem;
	class Renderer;

	class Font;
	class FontFactory;

	class VideoFactory;
	class VideoTexture;
}


#endif
