
#ifndef FRAGVIEW_MODELIMPORT_H_
#define FRAGVIEW_MODELIMPORT_H_ 1
#include "TargetNode.h"

namespace fragview {
/**
 *
 */
	class ShaderModelImporter {
	public:
		ShaderModelImporter(IRenderer *renderer);

		TargetNode *createTargetModel(int argc, const char **argv);

	private:
		IRenderer *renderer;
	};
}
#endif