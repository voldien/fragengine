// #include"asset/AssetImporter.h"
// #include"RenderingInterface.h"
// #include"physic/PhysicInterface.h"
// #include"Debug.h"
// #include"Scene.h"
// #include"Renderer.h"
// #include"ZipFileSystem.h"

// #include<FreeImage.h>
// #include<zlib.h>
// #include<zip.h>
// #include<assimp/ai_assert.h>
// #include<assimp/Importer.hpp>
// #include<assimp/scene.h>
// #include<assimp/postprocess.h>
// #include<assimp/IOSystem.hpp>
// #include <StringUtil.h>
// #include <physic/PhysicDesc.h>
// #include <GeomtryUtil.h>

// using namespace Assimp;

// AssetImporter::AssetImporter(void){
// 	this->scene = NULL;
// 	this->physicinterface = NULL;
// 	this->renderinterface = NULL;
// }

// AssetImporter::AssetImporter(const AssetImporter& other){
// 	this->physicinterface = NULL;
// 	this->renderinterface = NULL;
// 	*this = other;
// }

// AssetImporter::AssetImporter(Scene* scene, RenderingInterface* renderinginerface, PhysicInterface* physicinterface){
// 	this->scene = scene;
// 	this->setPhysicInterface(physicinterface);
// 	this->setRenderInterface(renderinginerface);
// }

// AssetImporter::~AssetImporter(void){

// }

// void* AssetImporter::loadtexture(const char* cfilename, unsigned int* pwidth,
//         unsigned int* pheight, TextureDesc::Format* pformat,
//         TextureDesc::Format* pinternalformat, TextureDesc::Type* ptype) {

// 	FREE_IMAGE_FORMAT picformat;
// 	FREE_IMAGE_COLOR_TYPE colortype;
// 	FREE_IMAGE_TYPE imagetype;
// 	FIBITMAP* bitmap;
// 	unsigned int internalformat;
// 	void* pixeldata = NULL;
// 	unsigned int width;
// 	unsigned int height;
// 	unsigned int Bpp = 1;	/*	TODO fix for future */

// 	FreeImage_Initialise();

// 	/*	loading the file.	*/
// 	picformat = FreeImage_GetFileType(cfilename);
// 	if(picformat == FIF_UNKNOWN)
// 		throw std::invalid_argument(format("Non Supported Texture %s", cfilename));

// 	bitmap = FreeImage_Load(picformat, cfilename, 0);
// 	if(bitmap == NULL)
// 		throw std::runtime_error(format("Failed loading file %s", cfilename));

// 	/*	*/
// 	colortype = FreeImage_GetColorType(bitmap);
// 	imagetype = FreeImage_GetImageType(bitmap);

// 	/*	*/
// 	width = FreeImage_GetWidth(bitmap);
// 	height = FreeImage_GetHeight(bitmap);

// 	switch(colortype){
// 	case FIC_RGB:
// 		*pformat = TextureDesc::eBGR;
// 		*pinternalformat = TextureDesc::eRGB;
// 		Bpp = 3;
// 		break;
// 	case FIC_RGBALPHA:
// 		*pformat = TextureDesc::eBGRA;
// 		*pinternalformat = TextureDesc::eRGBA;
// 		Bpp = 4;
// 		break;
// 	case FIC_MINISWHITE:
// 	case FIC_MINISBLACK:
// 		*pformat = TextureDesc::eSingleColor;
// 		*pinternalformat = TextureDesc::eSingleColor;
// 		Bpp = 1;
// 		break;
// 	default:
// 		break;
// 	}

// 	*ptype = TextureDesc::eUnsignedByte;

// 	/*	Copy.	*/
// 	pixeldata = malloc(width * height * Bpp);
// 	memcpy(pixeldata, FreeImage_GetBits(bitmap), width * height * Bpp);
// 	FreeImage_Unload(bitmap);

// 	FreeImage_DeInitialise();

// 	/*	assigned */
// 	if(pwidth)
// 		*pwidth = width;
// 	if(pheight)
// 		*pheight = height;

// 	return pixeldata;
// }

// TextureObject* AssetImporter::loadTexture(const char* cfilename){

// 	TextureDesc desc = { 0 };
// 	TextureObject* tex = NULL;
// 	void* pixeldata = NULL;
// 	TextureDesc::Format format;
// 	TextureDesc::Format internalformat;
// 	unsigned int width;
// 	unsigned int height;
// 	TextureDesc::Type type;

// 	/*	*/
// 	if((pixeldata = loadtexture(cfilename, &width, &height, &format, &internalformat, &type))){

// 		desc.width = width;
// 		desc.height = height;
// 		desc.pixel = pixeldata;

// 		/**/
// 		desc.target = TextureDesc::eTexture2D;
// 		desc.format = format;
// 		desc.internalformat = internalformat;
// 		desc.type = type;
// 		desc.numlevel = 5;
// 		desc.usemipmaps = 1;
// 		tex = renderinterface->createTexture(&desc);

// 	}
// 	free(pixeldata);
// 	return tex;
// }

// TextureObject* AssetImporter::loadTextureArray(const char* texture,...){

// 	FREE_IMAGE_FORMAT picformat;
// 	FIBITMAP* bitmap;
// 	TextureDesc desc = {0};
// 	TextureObject* tex = NULL;

// 	return tex;
// }

// TextureObject* AssetImporter::loadCubeTexture(const char* right, const char* left, const char* top, const char* bottom, const char* far, const char* near){
// 	TextureDesc desc = {0};
// 	TextureObject* tex = NULL;
// 	TextureDesc::Format format;
// 	TextureDesc::Format internalformat;
// 	unsigned int width;
// 	unsigned int height;
// 	TextureDesc::Type type;

// 	desc.cubepixel[0] = loadtexture(right, &width, &height, &format, &internalformat, &type);
// 	desc.cubepixel[1] = loadtexture(left, &width, &height, &format, &internalformat, &type);
// 	desc.cubepixel[2] = loadtexture(top, &width, &height, &format, &internalformat, &type);
// 	desc.cubepixel[3] = loadtexture(bottom, &width, &height, &format, &internalformat, &type);
// 	desc.cubepixel[4] = loadtexture(far, &width, &height, &format, &internalformat, &type);
// 	desc.cubepixel[5] = loadtexture(near, &width, &height, &format, &internalformat, &type);
// 	desc.width = width;
// 	desc.height = height;

// 	/*	*/
// 	desc.target = TextureDesc::eCubeMap;
// 	desc.format = format;
// 	desc.internalformat = internalformat;
// 	desc.type = type;
// 	desc.numlevel = 5;
// 	desc.usemipmaps = 1;
// 	tex = renderinterface->createTexture(&desc);

// 	free(desc.cubepixel[0]);
// 	free(desc.cubepixel[1]);
// 	free(desc.cubepixel[2]);
// 	free(desc.cubepixel[3]);
// 	free(desc.cubepixel[4]);
// 	free(desc.cubepixel[5]);
// 	return tex;
// }

// TextureObject* AssetImporter::loadCubeTexture(const char* align){
// 	TextureDesc desc = {0};
// 	TextureObject* tex = NULL;
// 	TextureDesc::Format format;
// 	TextureDesc::Format internalformat;
// 	unsigned int width;
// 	unsigned int height;
// 	TextureDesc::Type type;
// 	void* pixel;

// 	/*	Load texture data.	*/
// 	pixel = loadtexture(align, &width, &height, &format, &internalformat, &type);
// 	if(pixel == NULL){
// 		return NULL;
// 	}

// 	/*	*/
// 	for(int i = 0; i < 6; i++)
// 		desc.cubepixel[i] = pixel;

// 	/*	Assign texture descriptor.	*/
// 	desc.width = width;
// 	desc.height = height;
// 	desc.target = TextureDesc::eCubeMap;
// 	desc.format = format;
// 	desc.internalformat = internalformat;
// 	desc.type = type;
// 	desc.numlevel = 5;
// 	desc.usemipmaps = 1;
// 	tex = renderinterface->createTexture(&desc);

// 	free(pixel);

// 	return tex;
// }

// ShaderObject* AssetImporter::loadShader(const char* vshader, const char* fshader,
// 		const char* gshader, const char* tcshader,
// 		const char* teshader, ZipFileSystem* zip){

// 	/*	*/
// 	typedef struct default_texture_location_t{
// 		const char* texname;
// 		int loc;
// 	}DefaultTextureLocation;

// 	/*	Texture location.   */
// 	static const DefaultTextureLocation texloc[] = {
// 			{"texture0", 0 },
// 			{"texture1", 1 },
// 			{"texture2", 2 },
// 			{"texture3", 3 },
// 			{"texture4", 4 },
// 			{"texture5", 5 },
// 			{"texture6", 6 },
// 			{"texture7", 7 },
// 			{"diffuse0", 0 },
// 			{"world0",   1 },
// 			{"normal0",  2 },
// 			{"depth0",   3 },
// 			{0, 0}
// 	};

// 	DefaultTextureLocation* uniloc;
// 	ShaderObject* shader = NULL;
// 	char* vsource = NULL;
// 	char* fsource = NULL;
// 	char* gsource = NULL;
// 	char* tcsource = NULL;
// 	char* tesource = NULL;

// 	/*	load source.	*/
// 	assert(vshader);
// 	assert(fshader);

// 	/*	Load from zipfile.	*/
// 	if(zip){
// 		zip->loadString(vshader, (void**)&vsource);
// 		zip->loadString(fshader, (void**)&fsource);
// 		zip->loadString(gshader, (void**)&gsource);
// 		zip->loadString(tcshader, (void**)&tcsource);
// 		zip->loadString(teshader, (void**)&tesource);
// 	}
// 	else{

// 		/*	*/
// 		zip = ZipFileSystem::createZipFileObject("/usr/share/pvengine/defaultshader.zip");	/*	TODO fix zip file path.	*/

// 		/*	*/
// 		if(vshader){
// 			if(strstr(vshader, ".gz")){
// 				AssetImporter::loadCompressedString(vshader, &vsource);
// 			}else{
// 				AssetImporter::loadString(vshader, &vsource);
// 			}
// 		}

// 		/*	*/
// 		if(fshader){
// 			if(strstr(fshader, ".gz")){
// 				AssetImporter::loadCompressedString(fshader, &fsource);
// 			}else{
// 				AssetImporter::loadString(fshader, &fsource);
// 			}
// 		}

// 		/*	*/
// 		if(gshader){
// 			if(strstr(gshader, ".gz")){
// 				AssetImporter::loadCompressedString(gshader, &gsource);
// 			}else{
// 				AssetImporter::loadString(gshader, &gsource);
// 			}
// 		}

// 		/*	*/
// 		if(tcshader){
// 			if(strstr(tcshader, ".gz")){
// 				AssetImporter::loadCompressedString(tcshader, &tcsource);
// 			}else{
// 				AssetImporter::loadString(tcshader, &tcsource);
// 			}
// 		}

// 		/*	*/
// 		if(teshader){
// 			if(strstr(teshader, ".gz")){
// 				AssetImporter::loadCompressedString(teshader, &tesource);
// 			}else{
// 				AssetImporter::loadString(teshader, &tesource);
// 			}
// 		}

// 		delete zip;
// 	}

// 	/*	*/
// 	shader = loadShaderBySource(vsource, fsource, gsource, tcsource, tesource, zip);

// 	/*	*/
// 	uniloc = texloc;
// 	while(uniloc->texname){
// 		if(shader->getLocation(uniloc->texname)  >= 0){
// 			shader->setInt(shader->getLocation(uniloc->texname), uniloc->loc);
// 		}
// 		uniloc++;
// 	}

// 	/*	Release source codes.	*/
// 	free(vsource);
// 	free(fsource);
// 	free(gsource);
// 	free(tcsource);
// 	free(tesource);

// 	return shader;
// }

// ShaderObject* AssetImporter::loadShaderBySource(const char* vsource, const char* fsource,
// 		const char* gsource, const char* tcsource,
// 		const char* tesource, ZipFileSystem* zip){

// 	ShaderObject* shader = NULL;
// 	ShaderDesc desc = {0};
// 	char* invshad = NULL;
// 	const int nsources = 4;
// 	char glver[128];
// 	const char* vsources[4] = {NULL};
// 	const char* fsources[4] = {NULL};
// 	const char* gsources[4] = {NULL};
// 	const char* tcsources[4] = {NULL};
// 	const char* tesources[4] = {NULL};

// 	/*	*/
// 	static const char* vconst = "#define PV_VERTEX\n";
// 	static const char* fconst = "#define PV_FRAGMENT\n";
// 	static const char* gconst = "#define PV_GEOMETRY\n";
// 	static const char* tcconst = "#define PV_TCTESSELLATION\n";
// 	static const char* teconst = "#define PV_TETESSELLATION\n";


// 	sprintf(glver, "#version %d\n", (int)(strtof(renderinterface->getShaderVersion(), NULL) * 100.0f));

// 	/*	Add internal shader.	*/
// 	if(zip->loadString("glsl/internal/internalV.glsl", (void**)&invshad) < 0){
// 		fprintf(stderr, "Failed to load internal shader.\n");
// 		return NULL;
// 	}

// 	if(vsource){
// 		vsources[0] = glver;
// 		vsources[1] = invshad;
// 		vsources[2] = vconst;
// 		vsources[3] = vsource;
// 		desc.vertexsource = vsources;
// 		desc.numvert = nsources;
// 	}
// 	if(fsource){
// 		fsources[0] = glver;
// 		fsources[1] = invshad;
// 		fsources[2] = fconst;
// 		fsources[3] = fsource;
// 		desc.fragmentsource = fsources;
// 		desc.numfrag = nsources;
// 	}
// 	if(gsource){
// 		gsources[0] = glver;
// 		gsources[1] = invshad;
// 		gsources[2] = gconst;
// 		gsources[3] = gsource;
// 		desc.geometrysource = gsources;
// 		desc.numgeo = nsources;
// 	}
// 	if(tcsource){
// 		tcsources[0] = glver;
// 		tcsources[1] = invshad;
// 		tcsources[2] = tcconst;
// 		tcsources[3] = tcsource;
// 		desc.tessellationco = tcsources;
// 		desc.numtesco = nsources;
// 	}
// 	if(tesource){
// 		tesources[0] = glver;
// 		tesources[1] = invshad;
// 		tesources[2] = teconst;
// 		tesources[3] = tesource;
// 		desc.tessellationev = tesources;
// 		desc.numtesco = nsources;
// 	}

// 	/*	Create shader.	*/
// 	shader = renderinterface->createShader(&desc);

// 	/*	*/
// 	free(invshad);
// 	return shader;
// }

// Node* AssetImporter::initNoodeRoot(const void* pScene, const void* ainodes, Node* parent,
// 		const std::vector<Geometry*>& geo,
// 		const std::vector<Material*>& mat) {

// 	/*  */
// 	const aiNode* nodes = (const aiNode*)ainodes;
// 	const aiScene* pscene = (const aiScene*)pScene;
// 	unsigned int gameObjectCount = 0;
// 	unsigned int meshCount = 0;
// 	unsigned int i;
// 	Node* pobject;
// 	Renderer* renderer;
// 	aiVector3D position, scale;
// 	aiQuaternion rotation;



// 	/*	Assign mesh.	*/
// 	if(nodes->mMeshes){

// 		/*	Create renderer object.	*/
// 		renderer = getScene()->getScenePool()->createRenderer();
// 		pobject = renderer;

// 		/*	Assign geometry object.	*/
// 		for(i = 0; i < nodes->mNumMeshes; i++){
// 			const unsigned int meshindex = nodes->mMeshes[i];
// 			const unsigned int materialindex = pscene->mMeshes[meshindex]->mMaterialIndex;

// 			/*	Assert the index never execedes.	*/
// 			assert(meshindex < geo.size());
// 			assert(materialindex < mat.size());

// 			/*	*/
// 			renderer->setGeometry(geo[meshindex], renderer->getNumGeometry());//renderer->getNumGeometry());

// 			renderer->setMaterial(mat[materialindex], renderer->getNumMaterial());// );


// 			/*  TODO bind rigidbody.    */
// 			RigidBodyDesc rigidBodyDesc = {};
// 			rigidBodyDesc.mass = 1.0f;
// 			rigidBodyDesc.node = NULL;
// 			rigidBodyDesc.isKinematic = true;
// 			rigidBodyDesc.collision = NULL;
// 			//RigidBody* body = physicinterface->createRigibody(&rigidBodyDesc);
// 			//physicinterface->addRigidBody(body);
// 		}
// 	}
// 	else{
// 		/*	*/
// 		pobject = getScene()->getScenePool()->createNode();
// 	}
// 	pobject->setName(nodes->mName.C_Str());


// 	/*	Extract position, rotation, position from transformation matrix.	*/
// 	nodes->mTransformation.Decompose(scale, rotation, position);
// 	if(parent){
// 		pobject->setParent( parent );
// 	}
// 	else
// 		pobject->setParent( NULL );

// 	/*	Set object transformation.	*/
// 	pobject->setPosition(PVVector3(position.x, position.y, position.z));
// 	pobject->setScale(PVVector3(scale.x, scale.y, scale.z));
// 	pobject->setRotation( PVQuaternion(rotation.w, rotation.x, rotation.y, rotation.z));

// 	/*	Iterate through all childrens.	*/
// 	for(unsigned int x = 0; x < nodes->mNumChildren; x++){
// 		pobject->addChild( initNoodeRoot(pScene, (void*)nodes->mChildren[x], pobject, geo, mat) );
// 	}

// 	return pobject;
// }

// Node* AssetImporter::loadSceneNode(const std::string& cfilename){

// 	Importer importer;
// 	Node* rootnode = NULL;
// 	std::vector<Geometry*> gobj;
// 	std::vector<Material*> mobj;
// 	std::vector<TextureObject*> tobj;
// 	std::map<int, Geometry*> sobj;
// 	unsigned int x, y, z;

// 	std::string directory;

// 	/*  TODO relocate to proper function for dealgin with it.   */
// 	const size_t last_slash_idx = cfilename.rfind('/');
// 	if (std::string::npos != last_slash_idx)
// 	{
// 		directory = cfilename.substr(0, last_slash_idx);
// 	}

// 	assert(this->scene);
// 	assert(this->renderinterface);

// 	const aiScene* pScene = importer.ReadFile(cfilename, aiProcessPreset_TargetRealtime_Quality | aiProcess_CalcTangentSpace);

// 	if(pScene == NULL){
// 		Debug::log("%s\n", importer.GetErrorString() );

// 	}else{

// 		/*	*/
// 		Debug::log("filename %s\n", cfilename.c_str());
// 		Debug::log("number of textures %d\n", pScene->mNumTextures);
// 		Debug::log("number of animation %d\n", pScene->mNumAnimations);
// 		Debug::log("number of meshes %d\n", pScene->mNumMeshes);
// 		Debug::log("number of materials. %d\n", pScene->mNumMaterials);
// 		Debug::log("number of lights. %d\n", pScene->mNumLights);

// 		/*	Textures.	*/
// 		const aiTexture* texture;
// 		for(x = 0; x < pScene->mNumTextures; x++){
// 			texture = pScene->mTextures[x];
// 			TextureDesc desc;
// 			TextureObject* texobj;

// 			/*	*/
// 			desc.width = texture->mWidth;
// 			desc.height = texture->mHeight;
// 			desc.target = TextureDesc::eTexture2D;
// 			desc.type = TextureDesc::eUnsignedByte;
// 			desc.internalformat = TextureDesc::eRGB;
// 			desc.format = TextureDesc::eRGB;
// 			desc.pixel = texture->pcData;

// 			texobj = renderinterface->createTexture(&desc);
// 			tobj.push_back(texobj);
// 		}

// 		/*	Iterate through mesh.	*/
// 		for(x = 0; x < pScene->mNumMeshes; x++){

// 			/*	*/
// 			Geometry* geobj;
// 			GeometryDesc desc = {0};
// 			unsigned int numVertices;
// 			unsigned int numIndices;
// 			aiMesh* mesh = pScene->mMeshes[x];
// 			float* vertices;
// 			unsigned int* indices;
// 			unsigned int stride = (3 + 2 + 3 + 3);	/*	vertex, uv, normal, tangent.	*/
// 			unsigned int nvertexsize = stride * sizeof(float);
// 			unsigned int indicesstride = sizeof(unsigned int);

// 			/*	*/
// 			numVertices = mesh->mNumVertices;
// 			numIndices = mesh->mNumFaces;
// 			vertices = (float*)malloc(mesh->mNumVertices * nvertexsize);
// 			indices = (unsigned int*)malloc(mesh->mNumFaces * 3 * indicesstride );

// 			/*	Iterate through each vertices.	*/
// 			for(y = 0; y < numVertices; y++){
// 				vertices[y * stride + 0] = mesh->mVertices[y].x;
// 				vertices[y * stride + 1] = mesh->mVertices[y].y;
// 				vertices[y * stride + 2] = mesh->mVertices[y].z;

// 				/*	*/
// 				if( mesh->mTextureCoords[0] != NULL ){
// 					vertices[y * stride + 3] = mesh->mTextureCoords[0][y].x;
// 					vertices[y * stride + 4] = mesh->mTextureCoords[0][y].y;
// 				}
// 				else{
// 					vertices[y * stride + 3] = 0.0f;
// 					vertices[y * stride + 4] = 0.0f;
// 				}

// 				/*	*/
// 				if(mesh->mNormals){
// 					vertices[y * stride + 5] = mesh->mNormals[y].x;
// 					vertices[y * stride + 6] = mesh->mNormals[y].y;
// 					vertices[y * stride + 7] = mesh->mNormals[y].z;
// 				}

// 				/*	*/
// 				if(mesh->mTangents){
// 					vertices[y * stride + 8] = mesh->mTangents[y].x;
// 					vertices[y * stride + 9] = mesh->mTangents[y].y;
// 					vertices[y * stride + 10] = mesh->mTangents[y].z;
// 				}

// 			}

// 			/*	*/
// 			for(y = 0; y < numIndices; y++){
// 				//assert(mesh->mFaces[y].mNumIndices == 3);
// 				indices[y * 3 + 0] = mesh->mFaces[y].mIndices[0];
// 				indices[y * 3 + 1] = mesh->mFaces[y].mIndices[1];
// 				indices[y * 3 + 2] = mesh->mFaces[y].mIndices[2];
// 			}

// 			/*  Compute AABB.   */
// 			//GeometryUtil::computeAABB(vertices, numVertices);


// 			/*	Geometry description.	*/
// 			desc.primitive = GeometryDesc::eTriangles;
// 			desc.numVerticecs = numVertices;
// 			desc.numIndices = numIndices * 3;
// 			desc.buffer = vertices;
// 			desc.indices = indices;
// 			desc.vertexStride = nvertexsize;
// 			desc.indicesStride = indicesstride;

// 			/*	Geometry description.	*/
// 			desc.numVertexAttributes = 4;
// 			desc.vertexattribute[0].index = 0;
// 			desc.vertexattribute[0].size = 3;
// 			desc.vertexattribute[0].datatype = GeometryDesc::eFloat;
// 			desc.vertexattribute[0].offset = 0;

// 			desc.vertexattribute[1].index = 1;
// 			desc.vertexattribute[1].size = 2;
// 			desc.vertexattribute[1].datatype = GeometryDesc::eFloat;
// 			desc.vertexattribute[1].offset = 12;

// 			desc.vertexattribute[2].index = 2;
// 			desc.vertexattribute[2].size = 3;
// 			desc.vertexattribute[2].datatype = GeometryDesc::eFloat;
// 			desc.vertexattribute[2].offset = 20;

// 			desc.vertexattribute[3].index = 3;
// 			desc.vertexattribute[3].size = 3;
// 			desc.vertexattribute[3].datatype = GeometryDesc::eFloat;
// 			desc.vertexattribute[3].offset = 32;

// 			/*	Create geometry.	*/
// 			geobj = renderinterface->createGeometry(&desc);
// 			gobj.push_back(geobj);
// 			sobj[mesh->mMaterialIndex] = geobj;

// 			/*  Compute bounding box.   */


// 			/*  Create collision object.    */
// 			CollisionDesc collisionDesc = {};
// 			collisionDesc.ePrimitive = CollisionDesc::eMesh;
// 			collisionDesc.meshshape.vertexcount = numVertices;
// 			collisionDesc.meshshape.indicescount = numIndices;
// 			collisionDesc.meshshape.indices = indices;
// 			collisionDesc.meshshape.vertices = vertices;
// 			collisionDesc.meshshape.indicesStrip = stride;
// 			//Collision* collision = physicinterface->createCollision(&collisionDesc);

// 			/*	*/
// 			free(vertices);
// 			free(indices);
// 		}

// 		/*	Iterate through all materials.	*/
// 		for(x = 0; x < pScene->mNumMaterials; x++){
// 			Material* mat;
// 			aiMaterial* assmat;
// 			aiString path;
// 			TextureObject* tex;
// 			aiTextureMapMode mapmode;

// 			/*	Create material object.	*/
// 			mat = getScene()->getScenePool()->createMaterial();
// 			mobj.push_back(mat);

// 			/*	*/
// 			assmat = pScene->mMaterials[x];
// 			assert(assmat);

// 			/*	load all texture assoicated with texture.	*/
// 			for (y = 0; y < aiTextureType_UNKNOWN; y++) {
// 				for (z = 0; z < assmat->GetTextureCount((aiTextureType)y); z++) {

// 					/*	extract texture information.	*/
// 					if (assmat->GetTexture((aiTextureType) y, z, &path, NULL,
// 							NULL, NULL, NULL, &mapmode)
// 							== aiReturn_SUCCESS) {
// 						if (path.C_Str()) {
// 							try {
// 								tex = AssetImporter::loadTexture(
// 										format("%s/%s", directory.c_str(), path.C_Str()).c_str());
// 								mat->setTexture(y - aiTextureType_DIFFUSE, tex);
// 							}
// 							catch (std::exception& error){
// 								Debug::error("%s\n", error.what());

// 								mat->setTexture(y - aiTextureType_DIFFUSE, NULL);

// 								//mat->setTextureScale(y - aiTextureType_DIFFUSE, assmat->Get())

// 							}
// 						}
// 					}

// 					tex = NULL;
// 				}/**/
// 			}/**/

// 		}

// 		/*	Iterate through all animations.	*/
// 		for(x = 0; x < pScene->mNumAnimations; x++){
// 			aiAnimation* anim = pScene->mAnimations[x];

// 			for(y = 0; y < anim->mNumChannels; y++){
// 				aiNodeAnim* ani = anim->mChannels[y];
// 			}
// 		}

// 		/*	Iterate through all nodes.	*/
// 		rootnode = getScene()->getScenePool()->createNode();
// 		for(x = 0; x < pScene->mRootNode->mNumChildren; x++){
// 			rootnode->addChild( initNoodeRoot(pScene, pScene->mRootNode->mChildren[x], rootnode, gobj, mobj) );
// 		}

// 		for(x = 0; x < pScene->mNumLights; x++){
// 			Light* light = this->scene->getScenePool()->createLight();
// 			//pScene->mLights[x]->
// 			rootnode->addChild((Node*)light);
// 		}

// 	}

// 	return rootnode;
// }

// long int AssetImporter::loadFile(const char* cfilename, char** data){
// 	FILE* f;
// 	long int nbytes;
// 	unsigned long flen;

// 	/*	Open file.	*/
// 	f = fopen(cfilename, "rb");
// 	if( f == NULL){
// 		fprintf(stderr, "Failed to open file %s, %s.\n", cfilename, strerror(errno));
// 		return -1;
// 	}

// 	/*	Get size of the file.	*/
// 	fseek(f, 0, SEEK_END);
// 	flen = ftell(f);
// 	fseek(f, 0, SEEK_SET);

// 	/*	Allocate buffer file will fit in.	*/
// 	*data = (char*)malloc(flen);
// 	assert(*data);

// 	/*	Read all data from file to buffer.	*/
// 	nbytes = fread(*data, 1, flen, f);
// 	fclose(f);

// 	return nbytes;
// }

// long int AssetImporter::loadString(const char* cfilename, char** data){
// 	long int nbytes = loadFile(cfilename, data);
// 	if(*data){
// 		*data = (char*)realloc(*data, nbytes + 1);
// 		(*data)[nbytes] = '\0';
// 	}
// 	return nbytes;
// }

// long int AssetImporter::loadCompressedFile(const char* cfilename, char** data){

// 	long int nbytes = 0;
// 	gzFile gz;
// 	char buf[1024];
// 	int status;
// 	const unsigned int buflen = sizeof(buf);

// 	/*	Open compress file.	*/
// 	gz = gzopen(cfilename, "rb");
// 	if( gz == NULL ){
// 		fprintf(stderr, "Failed to open compressed file %s, %s.\n", cfilename, gzerror(gz, NULL));
// 		return -1;
// 	}

// 	/*	Inflate compressed file one page at a time.	*/
// 	*data = NULL;
// 	while( ( status = gzread(gz, buf, buflen)) > 0){
// 		nbytes += status;
// 		*data = (char*)realloc(*data, nbytes);
// 		memcpy(*data + ( nbytes - status), buf, status);
// 	}

// 	gzclose(gz);

// 	return nbytes;
// }

// long int AssetImporter::loadCompressedString(const char* cfilename, char** data){
// 	long int nbytes = loadCompressedFile(cfilename, data);
// 	if(*data){
// 		*data = (char*)realloc(*data, nbytes + 1);
// 		(*data)[nbytes] = '\0';
// 	}
// 	return nbytes;
// }

