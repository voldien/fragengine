#include"ShaderModel/ShaderModelImporter.h"
#include<getopt.h>
#include<Utils/ShaderUtil.h>
#include<ShaderModel/ShaderModelImporter.h>

#include"Recast.h"
//#include"nanosvgrast.h"
//#include"xatlas.h"
//#include"Recast.h"

using namespace fragcore;
//extern const char* shortarg;
//extern struct option* longoptions;
TargetNode* ShaderModelImporter::createTargetModel(int argc, const char **argv) {
//
//
//	int c;
//	int index;
//	TargetNode* root = new TargetNode();
//	TargetNode* child = root;
//
//	/*  First pass. */
//	while( ( c = getopt_long(argc, (char *const *)argv, shortarg, longoptions, &index) ) != EOF){
//
//		switch(c){
//			case'f':
//				if(optarg){
//					ProgramPipeline* shader;
//
//					//ShaderUtil::loadFragmentProgramPipeline(optarg, this->renderer, &shader);
//
//					TargetNode* pchild = new TargetNode();
//					pchild->setProgramShader(shader);
//					child->addChild(pchild);
//					child = pchild;
//				}
//			case 'G':
//				break;
//			case 'T':
//				break;
//			case 'E':
//				break;
//			case 'H':
//				break;
//			default:
//				break;
//		}
//	}
//
//	/*	Reset getopt.	*/
//	optind = 0;
//	optopt = 0;
//	opterr = 0;

	return NULL;
}

ShaderModelImporter::ShaderModelImporter(IRenderer *renderer) {
	this->renderer = renderer;
}

