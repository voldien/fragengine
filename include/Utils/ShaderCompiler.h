#ifndef _FRAG_CORE_SHADER_COMPILER_H_
#define _FRAG_CORE_SHADER_COMPILER_H_ 1
#include"../Def.h"
#include"../Renderer/Shader.h"
#include"../Core/Ref.h"

namespace fragview{
	
	class FVDECLSPEC ShaderCompiler{
	public:
		class CompilerOptions : UIDObject {
			const char *name;
			const char *value;
		};

		class CompilerSources{
			Ref<IO> vertex;
			Ref<IO> fragment;
			Ref<IO> geometry;
			Ref<IO> tesselation;
		};

		std::vector<Ref<Shader>> CompilePermutation(Ref<IRenderer>& renderer,  std::vector<CompilerOptions>& options);
	};
} 
#endif