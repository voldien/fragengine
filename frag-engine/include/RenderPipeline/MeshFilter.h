
#ifndef _MESH_FILTER_H_
#define _MESH_FILTER_H_ 1
#include <Core/SmartReference.h>
#include"Mesh.h"

namespace fragengine {

	class FVDECLSPEC MeshFilter : public SmartReference {
	public:
		MeshFilter();
		~MeshFilter();

	//	void setMesh(Mesh* mesh);
	//	Mesh* getMesh()const{return this->mesh;}

	private:
	//	Mesh* mesh;
	};
}

#endif
