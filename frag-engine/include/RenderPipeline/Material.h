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
#ifndef _MATERIAL_H_
#define _MATERIAL_H_ 1
#include "RenderQueue.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"

/**
 *	Responsible for associated textures and
 *	shader.
 */
class FVDECLSPEC Material {
   public:
    Material(void);

	// virtual void PushUniforms(UniformHandler &uniformObject, const Transform *) = 0;
	// virtual void PushDescriptors(DescriptorsHandler &descriptorSet) = 0;


    /**
     *
     * @param shader
     */
    void setShader(ShaderObject* shader);
    ShaderObject* getShader(void);

    /**
     *
     * @param index
     * @param tex
     */
    void setTexture(int index, TextureObject* tex);
    TextureObject* getTexture(int index);

    void setMainColor(const PVColor& color);
    PVColor getMainColor(void) const;

    /**
     *
     * @param index
     * @param offset
     */
    void setTextureOffset(int index, PVVector2 offset);

    /**
     *
     * @param index
     * @return
     */
    PVVector2 getTextureOffset(int index) const;

    /**
     *
     * @param index
     * @param scale
     */
    void setTextureScale(int index, PVVector2 scale);

    /**
     *
     * @param index
     * @return
     */
    PVVector2 getTextureScale(int index) const;

    /**
     *	Bind material to current material on
     *	the current thread.
     */
    void bind(void);

    /**
     *
     * @return
     */
    RenderQueue getRenderQueue(void) const;

   public: /*  Get and set methods.  */
    int getInt(const char* name);
    void setInt(const char* name, int value);

    void setIntArray(const char* name, int nrElements, int* elements);
    int* getIntArray(const char* name, int* nrElements);

    float getFloat(const char* name);
    void setFloat(const char* name, float value);

    void setFloatArray(const char* name, int nrElements, float* elements);
    float* getFloatArray(const char* name, int* nrElements);

    void setVectorArray(const char* name, int nrElements, PVVector4* elements);
    PVVector4* getVectorArray(const char* name, int* nrElements);

   private:                               /*	Attributes.	*/
    //std::vector<TextureObject*> textures; /*  */
    //ShaderObject* shader;                 /*	*/
};

#endif