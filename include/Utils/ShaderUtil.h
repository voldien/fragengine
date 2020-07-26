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
#ifndef _FRAGVIEW_SHADERUTIL_H_
#define _FRAGVIEW_SHADERUTIL_H_ 1
#include "../Core/IO/IO.h"
#include "../Core/Ref.h"
#include"../Renderer/IRenderer.h"


namespace fragview {
	
	/**
	 *
	 */
	class FVDECLSPEC ShaderUtil {
	private:
		/*	*/
		typedef struct default_texture_location_t {
			const char *texname;    /*  */
			int loc;                /*  */
		} DefaultTextureLocation;	//TODO relocate to to the engine.

		typedef struct uniform_location_t{
			const char *texname; /*  */
			int loc;			 /*  */
		} UniformLocation;

		typedef struct shaderObject {
			const char *buf;
			unsigned long size;
			ShaderLanguage language;
			ShaderDesc::ShaderCodeType type;
		} ShaderObject;

		typedef struct ShaderObjectDesc_t{
			std::vector<Ref<IO>> &source;
			ShaderLanguage language;
			ShaderDesc::ShaderCodeType type;
		} ShaderObjectDesc;

		public:

			// TODO relocate and .
			static void
			loadFragmentProgramPipeline(IO *fragIO, ShaderLanguage language, IRenderer *renderer,
										ProgramPipeline **pshader);

		static void
		loadProgramPipeline(const ShaderObject *vshader, const ShaderObject *fshader, const ShaderObject *gshader,
		                    const ShaderObject *tcshader,
		                    const ShaderObject *teshader, IRenderer *renderer, ProgramPipeline **pshader);

		static void
		loadShader(const char *source, const int size, ShaderType type, IRenderer *renderer, Shader **pshader,
		           ShaderLanguage language = GLSL, unsigned int dataType = 0);

		static void loadShader(const Ref<IO> &io, ShaderType, Ref<IRenderer> &renderer, ShaderLanguage language, Shader **shader);
		static void loadProgram(const Ref<IO> &io, Ref<IRenderer> &renderer, ShaderLanguage language, Shader **shader);
		static void loadProgram(
			ShaderObjectDesc *vertex,
			ShaderObjectDesc *fragment,
			ShaderObjectDesc *geometry,
			ShaderObjectDesc *tesseC,
			ShaderObjectDesc *tesseT,
			ShaderObjectDesc *compute,
			Ref<IRenderer> &renderer, ShaderLanguage language, Shader **shader);
		//static void loadProgram(const )

		static void loadProgram(IO *io, IRenderer *renderer, Shader **pShader, unsigned int format);
		static void loadProgram(const void* pData, long int nBytes, IRenderer *renderer, Shader **pShader, unsigned int format);

		//TODO rename the IRENDER to ICompute
		//TODO rename to program
		static void loadComputeShader(const Ref<IO> &computeIO, Ref<IRenderer> & renderer, ProgramPipeline **programPipeline);
		//static void loadComputeShader(const Ref<IO> &computeIO, Ref<IRenderer> &*renderer, ProgramPipeline **programPipeline);
		static void loadComputeShader(const char *pData, long int nBytes, IRenderer *renderer, ProgramPipeline **programPipeline);

		/*	*/
		static void
		loadComputeShaderSource(ShaderObject *shaderDesc, IRenderer *renderer, ProgramPipeline **programPipeline);

		//TODO relocate to be part of the zip!
		static void loadDisplayShader(IRenderer *renderer, ProgramPipeline **pProgramPipeline);


		static ShaderDesc::ShaderCodeType getCodeType(
				const char *filePath);    /*  Determine if shader is binary or source file based on the file basename.    */
		static ShaderLanguage getFileLanguage(
				const char *filePath);            /*  Determine what shader language based on the file basename.  */
		static ShaderType getShaderType(const char *filePath);                  /*  */

		/**
		 *
		 * @param programPipeline
		 */
		//TODO relocate to the engine.
		static void defaultUniformMap(ProgramPipeline *programPipeline);

		static std::vector<UniformLocation> getShaderUniformAttributes(void);

		//TODO resolve and act as a helper function.
		static void copyUniform(Ref<Shader> &shader);
		static void pastUniform(Ref<Shader> &shader);
	};
}

#endif