#ifndef _FRAG_CORE_SHADER_COMPILER_H_
#define _FRAG_CORE_SHADER_COMPILER_H_ 1
#include"../Def.h"
#include"../Renderer/Shader.h"
#include"../Core/Ref.h"
#include<map>
#include<vector>

namespace fragview{

	/**
	 * 
	 */
	class FVDECLSPEC ShaderCompiler{
	public:
		class CompilerOption : UIDObject {
			public:
			unsigned int type;
			const char *name;
			const char *value;
		};

		class CompilerSources {
		public:
			Ref<IO> vertex;
			Ref<IO> fragment;
			Ref<IO> geometry;
			Ref<IO> tessellationControl;
			Ref<IO> tessellationEvolution;
			Ref<IO> compute;
		};

		class ShaderResult : UIDObject {
		public:
			Ref<Shader> shader;
			CompilerOption option;
		};

		class CompilerOptionSet {
			public:
			std::vector<CompilerOption> option;
		};

		std::map<long int, ShaderResult>
		CompilePermutation(Ref<IRenderer> &renderer, CompilerSources* references, const CompilerOptionSet &optionset);
	};
} 
#endif