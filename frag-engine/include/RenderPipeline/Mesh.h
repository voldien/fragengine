#ifndef _FRAG_CORE_MESH_H_
#define _FRAG_CORE_MESH_H_ 1
#include<Core/SmartReference.h>

namespace fragengine {

	class FVDECLSPEC Mesh : public SmartReference {
	public:
		Mesh();
		Mesh(const Mesh& mesh);
		~Mesh();

		Mesh getSubMesh(int index);
		unsigned int getNumSubMesh() const;

	//
	//	Vector3 getVertex(unsigned int index)const;					/* Vertex [Index] */
	//
	//	void setVertex(unsigned int index, const Vector3& vertex);
	//
	//	Vector3* getVertexBundle();						/* Vertexs Bundle */
	//
	//	Vector2 getUV(unsigned int index)const;						/* Get UV [Index] */
	//
	//	Vector2* getUVBundle();							/* Get UV Bundle Data*/
	//
	//	Vector3 getNormal(unsigned int index)const;					/* Get Normal[Index] */
	//
	//	Vector3* getNormalBundle();						/* Get Normal Bundle Data. */
	//
	//	Vector3 getTangent(unsigned int index)const;					/* Get Tanget[Index] */
	//
	//	Vector3* getTangentBundle();						/* Get Tanget Bundle Data. */
	//
	//	Vector3  getBiNormal(unsigned int index)const;					/* Get BiNormal[Index] */
	//
	//	Vector3*  getBiNormalBundle();						/* Get BiNormal Bundle Data. */
	//
	//	Vector3  getBitTangent(unsigned int index)const;				/* Get BitTangent[Index] */
	//
	//	Vector3*  getBitTangentBundle();					/* Get BitTangent Bundle Data. */
	//
	//	void* getVBOBuffer()const;
	//
	//	void  reverseCulling();								// Reverse Indices. Reversing CullingFace
	//
	//	void  computeBBox();								// ReCalculate Bounding Box
	//
	//	void  reNormal();									// ReCalculate Normal
	//
	//	void  reTangent();									// ReCalculate Tangent
	//
	//	/**/
	//	void combindMesh(unsigned int num,Mesh** mesh);
	//
	//
	//	/**/
	//	void setMeshFlag(unsigned int flag);
	//	unsigned int getMeshFlag()const{return this->SupportFlag;}
	//

	public:
	//	static Mesh* findMesh(const std::string& pathName);
	//	static Mesh* findMesh(const char* meshName);
	};
} // namespace fragengine
#endif