
#ifndef _MESH_FILTER_H_
#define _MESH_FILTER_H_ 1
#include <Core/SmartReference.h>
#include"Mesh.h"

namespace fragview {

	class FVDECLSPEC MeshFilter : public SmartReference {
	public:
		MeshFilter(void);
		~MeshFilter(void);

	//	void setMesh(Mesh* mesh);
	//	Mesh* getMesh(void)const{return this->mesh;}

	private:
	//	Mesh* mesh;
	};
}

#endif
