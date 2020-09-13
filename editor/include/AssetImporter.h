/**
    Simple physic simulation with a server-client model support.
    Copyright (C) 2016  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _FRAG_EDITOR_ASSET_IMPORTER_H_
#define _FRAG_EDITOR_ASSET_IMPORTER_H_ 1
#include"System.h"
#include"ZipFile.h"
#include"RenderingInterface.h"

namespace frageditor{
	/**
	 *	Responsible for importing assets
	*	into application and convert into
	*	usable asset.
	*/
	class FVDECLSPEC AssetImporter{
	public:
		AssetImporter(Scene* scene,
				RenderingInterface* renderinginerface,
				PhysicInterface* physicinterface);
		AssetImporter(const AssetImporter& other);
		~AssetImporter(void);

		/**
		 *	Load texture from storage.
		*
		*	\cfilename:
		*
		*	@Return none null texture if successfully.
		*/
		void* loadtexture(const char* cfilename, unsigned int* pwidth,
					unsigned int* pheight, TextureDesc::Format* pformat,
					TextureDesc::Format* pinternalformat, TextureDesc::Type* ptype);
		TextureObject* loadTexture(const char* cfilename);
		TextureObject* loadTextureArray(const char* cfilename,...);
		TextureObject* loadCubeTexture(const char* right, const char* left,
				const char* top, const char* bottom,
				const char* far, const char* near);
		TextureObject* loadCubeTexture(const char* align);

		/**
		 * Loader shader from storage.
		 * @param vshader
		 * @param fshader
		 * @param gshader
		 * @param tcshader
		 * @param teshader
		 * @param zip
		 * @return none null texture if successfully.
		 */
		ShaderObject* loadShader(const char* vshader, const char* fshader,
				const char* gshader = NULL, const char* tcshader = NULL,
				const char* teshader = NULL, ZipFileSystem* zip = NULL);
		ShaderObject* loadShaderBySource(const char* vshader, const char* fshader,
				const char* gshader = NULL, const char* tcshader = NULL,
				const char* teshader = NULL, ZipFileSystem* zip = NULL);

		/**
		 *	Loader geometry.
		*
		*	@Return non-null pointer if successfully.
		*/
		Node* loadSceneNode(const std::string& cfilename);
		Node* initNoodeRoot(const void* PV_RESTRICT pScene,
				const void* PV_RESTRICT ianodes, Node* PV_RESTRICT parent,
				const std::vector<Geometry*>& PV_RESTRICT geo,
				const std::vector<Material*>& PV_RESTRICT mat);


	private:	/*	Private methods.	*/

		/**
		 *	Set rendering interface.
		*/
		void setRenderInterface(RenderingInterface* interface){
			this->renderinterface = interface;
		}

		/**
		 *	Set physic interface.
		*/
		void setPhysicInterface(PhysicInterface* interface){
			this->physicinterface = interface;
		}

		inline Scene* getScene(void){
			return this->scene;
		}

	private:	/*	Attributes.	*/

		RenderingInterface* renderinterface;	/*	*/
		PhysicInterface* physicinterface;		/*	*/
		Scene* scene;						/*	*/

	private:	/*	Prevent one from creating an instance of this class.	*/

		AssetImporter(void);

	public:	/*	Static methods.	*/

		/**
		 *	Load file.
		*
		*	@Return number of bytes loaded.
		*/
		static long int loadFile(const char* PV_RESTRICT cfilename,
				char** PV_RESTRICT data);
		static long int loadString(const char* PV_RESTRICT cfilename,
				char** PV_RESTRICT data);

		/**
		 *	Load compressed file.
		*
		*	@Return number of bytes loaded.
		*/
		static long int loadCompressedFile(const char* PV_RESTRICT cfilename,
				char** PV_RESTRICT data);
		static long int loadCompressedString(const char* PV_RESTRICT cfilename,
				char** PV_RESTRICT data);

	};

}

#endif
