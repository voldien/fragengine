#ifndef _FRAG_CORE_MESH_H_
#define _FRAG_CORE_MESH_H_ 1
#include"../Core/SmartReference.h"

namespace fragview {

	class FVDECLSPEC Mesh : public SmartReference {
	public:
		Mesh(void);
		Mesh(const Mesh& mesh);
		~Mesh(void);


	//
	//	Vector3 getVertex(unsigned int index)const;					/* Vertex [Index] */
	//
	//	void setVertex(unsigned int index, const Vector3& vertex);
	//
	//	Vector3* getVertexBundle(void);						/* Vertexs Bundle */
	//
	//	Vector2 getUV(unsigned int index)const;						/* Get UV [Index] */
	//
	//	Vector2* getUVBundle(void);							/* Get UV Bundle Data*/
	//
	//	Vector3 getNormal(unsigned int index)const;					/* Get Normal[Index] */
	//
	//	Vector3* getNormalBundle(void);						/* Get Normal Bundle Data. */
	//
	//	Vector3 getTangent(unsigned int index)const;					/* Get Tanget[Index] */
	//
	//	Vector3* getTangentBundle(void);						/* Get Tanget Bundle Data. */
	//
	//	Vector3  getBiNormal(unsigned int index)const;					/* Get BiNormal[Index] */
	//
	//	Vector3*  getBiNormalBundle(void);						/* Get BiNormal Bundle Data. */
	//
	//	Vector3  getBitTangent(unsigned int index)const;				/* Get BitTangent[Index] */
	//
	//	Vector3*  getBitTangentBundle(void);					/* Get BitTangent Bundle Data. */
	//
	//	void* getVBOBuffer(void)const;
	//
	//	void  reverseCulling(void);								// Reverse Indices. Reversing CullingFace
	//
	//	void  computeBBox(void);								// ReCalculate Bounding Box
	//
	//	void  reNormal(void);									// ReCalculate Normal
	//
	//	void  reTangent(void);									// ReCalculate Tangent
	//
	//	/**/
	//	void combindMesh(unsigned int num,Mesh** mesh);
	//
	//
	//	/**/
	//	void setMeshFlag(unsigned int flag);
	//	unsigned int getMeshFlag(void)const{return this->SupportFlag;}
	//

	public:
	//	static Mesh* findMesh(const std::string& pathName);
	//	static Mesh* findMesh(const char* meshName);
	};
}
#endif