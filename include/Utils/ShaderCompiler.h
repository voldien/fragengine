#ifndef _FV_SHADER_COMPILER_H_
#define _FV_SHADER_COMPILER_H_ 1
#include"../Def.h"
#include"../Renderer/Shader.h"

namespace fragview{
	class ShaderCompiler{
	public:
		class CompilerOptions{
			const char *name;
			const char *value;
		};
		

		std::vector<Ref<Shader>> CompilePermutation(void);
	};
} 
#endif