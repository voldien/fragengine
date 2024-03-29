#include"Graphic/SpriteBatch.h"
// /**
//  *	Sprite attributes.
//  *
//  */
// typedef struct sb_sprite_t
// {
// 	float pos[3];	/*	World position.	*/
// 	float angle;	/*	Angle in radian.	*/
// 	float rect[4];	/*	View rectangle. */
// 	int texture;	/*	Texture index.*/
// 	float scale;	/*	Uniform aligned scale.	*/
// 	float color[4]; /*	Diffuse Color.	*/
// } SBSprite;

// /**
//  *	Uniform location cache.
//  */
// typedef struct sb_sprite_uniform_index_t
// {
// 	int locationViewMatrix; /*	*/
// 	int locationScale;		/*	*/
// 	int locationTexture;	/*	*/
// } SBSpriteUniformIndex;

// /**
//  *	Sprite batch.
//  */
// typedef struct sb_sprite_batch_t
// {

// 	/*  Number of sprite allocated.   */
// 	unsigned int num;		   /*	Number of allocated sprites.    */
// 	unsigned int numDraw;	   /*	Number of sprite in batch.  */
// 	unsigned int numlabelDraw; /*	Number of label sprite in batch.    */
// 	unsigned int vao;		   /*	Vertex geometry object uid. */

// 	/*  Round buffer for sprites.   */
// 	int nbuffers;			 /*  Number of buffers.  */
// 	int nthBuffer;			 /*  Current bound buffer.   */
// 	unsigned int buffers[3]; /*  Buffer array ID.    */
// 	SBSprite *cspritemap;	 /*  */
// 	SBSprite *clabelmap;	 /*  */

// 	/*	*/
// 	SBShader spriteShader; /*	Sprite shader.  */
// 	SBShader fontShader;   /*  Font shader.    */

// 	/*	*/
// 	int numTexture;		/*	Number of associated textures.	*/
// 	int numMaxTextures; /*	Max number of texture units.	*/

// 	/*	*/
// 	unsigned int *textures; /*  Texture index table.    */
// 	SBSprite *sprite;		/*  Sprite buffer.  */
// 	SBSprite *label;		/*  Label buffer.  */

// 	/*  View space. */
// 	float scale;		/*  Global aligned world scale. */
// 	float scaleY;		/*  */
// 	float cameraPos[2]; /*  Camera position in world space. */
// 	float rotation;		/*  Global rotation.    */

// 	/*	view matrix.	*/
// 	float viewmatrix[3][3];	   /*  Cached view matrix for sprite transformations.   */
// 	float projectMatrix[3][3]; /*  */

// 	/*	Screen space.   */
// 	unsigned int width;	 /*  Viewport width from sbBeginSpriteBatch. */
// 	unsigned int height; /*  Viewport height from sbBeginSpriteBatch. */

// 	/*	cached uniform locations.	*/
// 	SBSpriteUniformIndex uniform; /*  Shader uniform location.    */

// } SBSpriteBatch;

// SBSpriteBatch *sbCreateSpriteBatch(SBSpriteBatch *spritebatch)
// {
// 	int x;
// 	int texture[512];
// 	const int numSprites = 4096;
// 	GLfloat mpointsize;
// 	const size_t nrTextures = 16;

// 	/*	Constants.	*/
// 	const uint32_t vertex_offset = 0;
// 	const uint32_t angle_offset = 12;
// 	const uint32_t rect_offset = 12 + 4;
// 	const uint32_t tex_offset = 12 + 20;
// 	const uint32_t scale_offset = 12 + 24;
// 	const uint32_t color_offset = 12 + 28;

// 	/*	Load OpenGL functions.	*/
// 	if (!sb_internal_load_gl_func())
// 		return NULL;

// 	/*	Get	max combined texture units.	*/
// 	sbGetNumTextureUnits(&spritebatch->numMaxTextures);

// 	/*  Allocate textures.  */
// 	spritebatch->textures = (unsigned int *)malloc(sizeof(unsigned int) * spritebatch->numMaxTextures);
// 	memset(spritebatch->textures, 0, sizeof(unsigned int) * spritebatch->numMaxTextures);
// 	spritebatch->numTexture = 0;
// 	assert(spritebatch->textures);

// 	/*  Buffer allocation.  */
// 	spritebatch->nthBuffer = 0;
// 	spritebatch->nbuffers = sizeof(spritebatch->buffers) / sizeof(spritebatch->buffers[0]);
// 	memset(spritebatch->buffers, 0, spritebatch->nbuffers * sizeof(spritebatch->buffers[0]));

// 	/*	Sprites.    */
// 	spritebatch->scale = 1.0f;
// 	spritebatch->sprite = NULL;
// 	sbSpriteBatchAllocateSprite(spritebatch, numSprites);

// 	/*	Create vertex buffer.   */
// 	sbGenVertexArrays(1, &spritebatch->vao);
// 	spbGLBindVertexArray(spritebatch->vao);

// 	/*	TODO resolve.   */
// 	spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->buffers[0]);
// 	spbGLEnableVertexAttribArrayARB(0);
// 	spbGLEnableVertexAttribArrayARB(1);
// 	spbGLEnableVertexAttribArrayARB(2);
// 	spbGLEnableVertexAttribArrayARB(3);
// 	spbGLEnableVertexAttribArrayARB(4);
// 	spbGLEnableVertexAttribArrayARB(5);
// 	spbGLVertexAttribPointerARB(0, 3, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 								(const void *)vertex_offset);
// 	spbGLVertexAttribPointerARB(1, 1, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 								(const void *)angle_offset);
// 	spbGLVertexAttribPointerARB(2, 4, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 								(const void *)rect_offset);
// 	spbGLVertexAttribPointerARB(3, 1, GL_INT, GL_FALSE, sizeof(SBSprite),
// 								(const void *)tex_offset);
// 	spbGLVertexAttribPointerARB(4, 1, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 								(const void *)scale_offset);
// 	spbGLVertexAttribPointerARB(5, 4, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 								(const void *)color_offset);

// 	spbGLBindVertexArray(0);

// 	if (!sbEnableRotation(spritebatch, 0))
// 	{
// 		sbReleaseSpriteBatch(spritebatch);
// 		return NULL;
// 	}

// 	/*	Cache sprite uniform location.	*/
// 	spritebatch->uniform.locationViewMatrix = sbGetShaderLocation(
// 		&spritebatch->spriteShader, "gmat");
// 	spritebatch->uniform.locationScale = sbGetShaderLocation(
// 		&spritebatch->spriteShader, "gscale");
// 	spritebatch->uniform.locationTexture = sbGetShaderLocation(
// 		&spritebatch->spriteShader, "textures");

// 	/*	Validate cache uniform locations.   */
// 	if (spritebatch->uniform.locationScale == -1 ||
// 		spritebatch->uniform.locationTexture == -1 ||
// 		spritebatch->uniform.locationViewMatrix == -1)
// 	{
// 		return NULL;
// 	}

// 	/*	Init shader.    */
// 	setShaderUniform1fv(&spritebatch->spriteShader, spritebatch->uniform.locationScale, 1, &spritebatch->scale);

// 	/*	Set texture index mapping.	*/
// 	for (x = 0; x < spritebatch->numMaxTextures; x++)
// 		texture[x] = x;

// 	/*  TODO fix constant size. */
// 	setShaderUniform1iv(&spritebatch->spriteShader, spritebatch->uniform.locationTexture, nrTextures,
// 						(const GLint *)&texture[0]);

// 	sbBindShader(NULL);

// 	/*	Enable hardware sprite feature. */
// #if !defined(GL_ES_VERSION_2_0)
// 	/*	TODO resolve.   */
// 	glEnable(GL_POINT_SPRITE_ARB);
// 	glEnable(GL_PROGRAM_POINT_SIZE_ARB);
// 	spbGLPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
// 	spbGLPointParameterf(GL_POINT_SIZE_MIN, 1.0f);
// 	glGetFloatv(GL_POINT_SIZE_MAX, &mpointsize);
// 	spbGLPointParameterf(GL_POINT_SIZE_MAX, mpointsize);
// 	spbGLPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
// 	//GL_POINT_DISTANCE_ATTENUATION_ARB
// #endif

// 	/*	Initialize the batch	*/
// 	sbBeginSpriteBatch(spritebatch, NULL, 1.0f, 0.0f);
// 	sbEndSpriteBatch(spritebatch);

// 	return spritebatch;
// }

// static void enablePointSprite()
// {
// 	GLfloat mpointsize;
// 	glEnable(GL_POINT_SPRITE_ARB);
// 	glEnable(GL_PROGRAM_POINT_SIZE_ARB);
// 	spbGLPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
// 	spbGLPointParameterf(GL_POINT_SIZE_MIN, 1.0f);
// 	glGetFloatv(GL_POINT_SIZE_MAX, &mpointsize);
// 	spbGLPointParameterf(GL_POINT_SIZE_MAX, mpointsize);
// 	spbGLPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
// 	//GL_POINT_DISTANCE_ATTENUATION_ARB
// }

// int sbReleaseSpriteBatch(SBSpriteBatch *spritebatch)
// {
// 	int status;

// 	/*  Delete buffers. */
// 	//	if (spbGLIsBufferARB(spritebatch->vbo) == GL_TRUE)
// 	//		sbDestroyBuffer(spritebatch->vbo);
// 	if (spGLIsVertexArray(spritebatch->vao) == GL_TRUE)
// 		spGLDeleteVertexArrays(1, &spritebatch->vao);

// 	/*	Delete shaders. */
// 	if (sbIsShader(&spritebatch->spriteShader))
// 		sbDeleteShaderProgram(&spritebatch->spriteShader);
// 	if (sbIsShader(&spritebatch->fontShader))
// 		sbDeleteShaderProgram(&spritebatch->fontShader);

// 	/*	Release sprite buffer.	*/
// 	//free(spritebatch->sprite);
// 	spritebatch->sprite = NULL;

// 	/*  Release texture mapper. */
// 	free(spritebatch->textures);
// 	spritebatch->textures = NULL;

// 	/*	Clear memory.	*/
// 	//	status = !spbGLIsBufferARB(spritebatch->vbo);
// 	memset(spritebatch, 0, sizeof(*spritebatch));
// 	return status;
// }

// void sbSpriteBatchAllocateSprite(SBSpriteBatch *spritebatch, unsigned int num)
// {

// 	/*	Check for error.	*/
// 	if (spritebatch == NULL || num <= 0)
// 		return;

// 	/*	Flush current buffer if exists and is not in the middle of drawing.	*/ /*    TODO add better logic */
// 	if (spbGLIsBufferARB(spritebatch->buffers[spritebatch->nthBuffer]) && spritebatch->sprite && spritebatch->numDraw)
// 		sbFlushSpriteBatch(spritebatch);

// 	/*	Allocate local sprite buffer.	*/
// 	//spritebatch->sprite = realloc(spritebatch->sprite, num * sizeof(SBSprite));
// 	spritebatch->num = num;
// 	/*  Allocate sprite buffer on the graphic device.   */
// 	for (int i = 0; i < spritebatch->nbuffers; i++)
// 	{
// 		/*	Check if buffer has been created.	*/
// 		if (spbGLIsBufferARB(spritebatch->buffers[i]) == 0)
// 		{
// 			/*  Create vertex buffer.   */
// 			sbGenBuffers(1, &spritebatch->buffers[i]);
// 		}

// 		spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->buffers[i]);
// 		sbSetBufferSize(GL_ARRAY_BUFFER_ARB, spritebatch->buffers[i],
// 						spritebatch->num * sizeof(SBSprite), GL_DYNAMIC_DRAW);
// 		spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
// 	}

// 	spritebatch->nthBuffer = 0;

// 	//	const uint32_t vertex_offset = 0;
// 	//	const uint32_t angle_offset = 12;
// 	//	const uint32_t rect_offset = 12 + 4;
// 	//	const uint32_t tex_offset = 12 + 20;
// 	//	const uint32_t scale_offset = 12 + 24;
// 	//	const uint32_t color_offset = 12 + 28;
// 	//
// 	//	/*  */
// 	//	spritebatch->nbuffers = 2;
// 	//	spritebatch->nthBuffer = 0;
// 	//	spritebatch->buffers = realloc(spritebatch->buffers, sizeof(*spritebatch->buffers) * spritebatch->nthBuffer);
// 	//	spritebatch->vaos = realloc(spritebatch->vaos, sizeof(*spritebatch->vaos) * spritebatch->nthBuffer);
// 	//	for(int i = 0; i < spritebatch->nbuffers; i++){
// 	//		sbGenVertexArrays(1, &spritebatch->vaos[i]);
// 	//		sbGenBuffers(1, &spritebatch->buffers[i]);
// 	//		sbSetBufferSize(GL_ARRAY_BUFFER_ARB, spritebatch->vbo,
// 	//		                spritebatch->num * sizeof(SBSprite), GL_DYNAMIC_DRAW);
// 	//		spbGLBindVertexArray(spritebatch->vao);
// 	//
// 	//		/*	TODO resolve.   */
// 	//		spbGLBindBufferARB(GL_ARRAY_BUFFER_ARB, spritebatch->vbo);
// 	//		spbGLEnableVertexAttribArrayARB(0);
// 	//		spbGLEnableVertexAttribArrayARB(1);
// 	//		spbGLEnableVertexAttribArrayARB(2);
// 	//		spbGLEnableVertexAttribArrayARB(3);
// 	//		spbGLEnableVertexAttribArrayARB(4);
// 	//		spbGLEnableVertexAttribArrayARB(5);
// 	//		spbGLVertexAttribPointerARB(0, 3, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 	//		                            (const void *) vertex_offset);
// 	//		spbGLVertexAttribPointerARB(1, 1, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 	//		                            (const void *) angle_offset);
// 	//		spbGLVertexAttribPointerARB(2, 4, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 	//		                            (const void *) rect_offset);
// 	//		spbGLVertexAttribPointerARB(3, 1, GL_INT, GL_FALSE, sizeof(SBSprite),
// 	//		                            (const void *) tex_offset);
// 	//		spbGLVertexAttribPointerARB(4, 1, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 	//		                            (const void *) scale_offset);
// 	//		spbGLVertexAttribPointerARB(5, 4, GL_FLOAT, GL_FALSE, sizeof(SBSprite),
// 	//		                            (const void *) color_offset);
// 	//
// 	//		spbGLBindVertexArray(0);
// 	//	}

// 	spbGLBindVertexArray(0);
// }

// int sbEnableRotation(SBSpriteBatch *spritebatch, int rotation)
// {
// 	if (!rotation)
// 	{
// 		/*	Load sprite shader.	*/
// 		if (!sbCreateShaderv(&spritebatch->spriteShader, gc_shader_spriteV,
// 							 gc_shader_spriteF, NULL))
// 		{
// 			/*	failure	*/
// 			return 0;
// 		}
// 		/*  Load sprite label shader.   */
// 		if (!sbCreateShaderv(&spritebatch->fontShader, gc_shader_labelV,
// 							 gc_shader_labelF, NULL))
// 		{
// 			/*	failure	*/
// 			return 0;
// 		}
// 	}
// 	else
// 	{
// 		/*	Load sprite shader.	*/
// 		if (!sbCreateShaderv(&spritebatch->spriteShader, gc_shader_spriteV,
// 							 gc_shader_spriteF, gc_shader_spriteG))
// 		{
// 			/*	failure	*/
// 			return 0;
// 		}
// 		/*  Load sprite label shader.   */
// 		if (!sbCreateShaderv(&spritebatch->fontShader, gc_shader_labelV,
// 							 gc_shader_labelF, gc_shader_labelG))
// 		{
// 			/*	failure	*/
// 			return 0;
// 		}
// 	}
// 	return 1;
// }

// void sbBeginSpriteBatch(SBSpriteBatch *SB_RESTRICT spriteBatch,
// 						const float *SB_RESTRICT camerapos, float scale, float rotation)
// {
// 	int rect[4];

// 	/*  Reset sprite and texture counter.   */
// 	spriteBatch->numDraw = 0;
// 	spriteBatch->numlabelDraw = 0;

// 	/*	Get current size of the viewport.	*/
// 	/*	TODO resolve.   */
// 	glGetIntegerv(GL_VIEWPORT, rect);
// 	spriteBatch->width = (unsigned int)(rect[2] - rect[0]);
// 	spriteBatch->height = (unsigned int)(rect[3] - rect[1]);
// 	spriteBatch->scale = scale;
// 	spriteBatch->rotation = rotation;

// 	/*	Camera view position.	*/
// 	if (camerapos)
// 	{
// 		spriteBatch->cameraPos[0] = -camerapos[0];
// 		spriteBatch->cameraPos[1] = camerapos[1];
// 	}
// 	else
// 	{
// 		spriteBatch->cameraPos[0] = 0;
// 		spriteBatch->cameraPos[1] = 0;
// 	}

// 	/*	Clean texture map buffer.	*/
// 	const size_t size = sizeof(unsigned int) * spriteBatch->numTexture;
// 	memset(spriteBatch->textures, 0, size);
// 	spriteBatch->numTexture = 0;

// 	/*  Update round robin buffer index.    */
// 	assert(spriteBatch->nbuffers > 0);
// 	spriteBatch->nthBuffer++;
// 	spriteBatch->nthBuffer %= spriteBatch->nbuffers;

// 	/*  Fetch buffer.   */
// 	assert(spriteBatch->nthBuffer >= 0 && spriteBatch->nthBuffer < spriteBatch->nbuffers);
// 	spriteBatch->sprite = (SBSprite *)sbMapBufferWOnly(GL_ARRAY_BUFFER_ARB, spriteBatch->buffers[spriteBatch->nthBuffer]);
// 	spbGLBindVertexArray(spriteBatch->vao);
// 	spGLBindVertexBuffer(0, spriteBatch->buffers[spriteBatch->nthBuffer], 0, sizeof(SBSprite));
// }

// void sbEndSpriteBatch(SBSpriteBatch *spriteBatch)
// {

// 	/*  Flush sprite buffers to GPU Memory. */
// 	sbFlushSpriteBatch(spriteBatch);

// 	/*	Draw sprites.	*/
// 	sbDisplaySprite(spriteBatch);
// }

// static int updateTextureTable(SBSpriteBatch *SB_RESTRICT spriteBatch, const SBTexture *SB_RESTRICT texture)
// {
// 	int i;

// 	/*  Update texture index table. */
// 	for (i = 0; i < spriteBatch->numMaxTextures; i++)
// 	{
// 		if (spriteBatch->textures[i] == texture->texture)
// 			return i;
// 		else
// 		{
// 			if (spriteBatch->textures[i] == NULL)
// 			{
// 				spriteBatch->textures[i] = texture->texture;
// 				spriteBatch->numTexture++;
// 				return i + 1;
// 			}
// 		}
// 	}
// 	return 0;
// }

// void sbDrawSprite(SBSpriteBatch *spriteBatch, SBTexture *texture,
// 				  const float *position, const float *rect, const float *color,
// 				  float scale, float angle, float depth)
// {

// 	sbAddSprite(spriteBatch, texture, position, rect, color, scale, angle, depth);

// 	if (spriteBatch->numDraw >= spriteBatch->num || spriteBatch->numTexture >= spriteBatch->numMaxTextures)
// 	{

// 		/*  Flush if buffer is full.    */
// 		sbEndSpriteBatch(spriteBatch);

// 		/*  */
// 		const float cameraPos[2] = {-spriteBatch->cameraPos[0], spriteBatch->cameraPos[1]};
// 		sbBeginSpriteBatch(spriteBatch, cameraPos, spriteBatch->scale, spriteBatch->rotation);
// 	}
// }

// void sbDrawSpriteNormalize(SBSpriteBatch *spritebatch, SBTexture *texture, const float *position,
// 						   const float *rect, const float *color, float scale, float angle, float depth)
// {

// 	sbAddSpriteNormalized(spritebatch, texture, position, rect, color, scale, angle, depth);

// 	if (spritebatch->numDraw >= spritebatch->num || spritebatch->numTexture >= spritebatch->numMaxTextures)
// 	{
// 		/*  Flush if buffer is full.    */
// 		sbEndSpriteBatch(spritebatch);

// 		/*  */
// 		const float cameraPos[2] = {-spritebatch->cameraPos[0], spritebatch->cameraPos[1]};
// 		sbBeginSpriteBatch(spritebatch, cameraPos, spritebatch->scale, spritebatch->rotation);
// 	}
// }

// int sbDrawSpriteLabel(SBSpriteBatch *spritebatch, const char *label, SBFont *font, float *position, float *rect,
// 					  float *color, float scale,
// 					  float angle, float depth)
// {
// 	int i;
// 	const size_t len = strlen(label);
// 	float xOffset = 0;
// 	float yOffset = 0;

// 	/*  Iterate through each character. */
// 	for (i = 0; i < len; i++)
// 	{
// 		const int charIndex = label[i];
// 		const float fontRect[4] = {font->tex_x1[charIndex], font->tex_x1[charIndex], font->tex_y1[charIndex],
// 								   font->tex_y2[charIndex]};
// 		const float charPos[] = {position[0] + xOffset, position[1] + yOffset};

// 		/*  Draw.   */
// 		sbDrawSprite(spritebatch, &font->texture, charPos, fontRect, color, scale, angle, depth);

// 		/*  Update offset.  */
// 		xOffset += font->width[charIndex] + font->offset_x[charIndex];
// 		yOffset += font->height[charIndex] + font->offset_x[charIndex];
// 	}

// 	return 0;
// }

// int sbDrawSpriteLabelNormalized(SBSpriteBatch *spritebatch, const char *label,
// 								SBFont *font, float *position, float *rect, float *color, float scale,
// 								float angle, float depth)
// {
// 	int i;
// 	const size_t len = strlen(label);
// 	/*  Iterate through each character. */
// 	for (i = 0; i < len; i++)
// 	{
// 		const float x = position[0] * (float)spritebatch->width;
// 		const float y = position[1] * (float)spritebatch->height;

// 		const float normalizePos[2] = {x, y};
// 		sbDrawSpriteLabel(spritebatch, label, font, normalizePos, rect, color, scale, angle, depth);
// 	}
// 	return 1;
// }

// int sbAddSpriteNormalized(SBSpriteBatch *spritebatch, SBTexture *texture,
// 						  const float *position, const float *rect, const float *color,
// 						  float scale, float angle, float depth)
// {

// 	int texIndex;
// 	const unsigned int numDraw = spritebatch->numDraw;
// 	SBSprite *SB_RESTRICT sprite = &spritebatch->sprite[numDraw];

// 	if (spritebatch->numDraw == spritebatch->num)
// 		return 0;

// 	/*	Screen coordinate. [0,0] - [w,h], top left -> bottom right. to  normalized coordinate system.   */
// 	sprite->pos[0] = 2.0f * position[0] - 1.0f + (((float)texture->width) / ((float)spritebatch->width));
// 	sprite->pos[1] = 2.0f * position[1] - 1.0f - (((float)texture->height) / ((float)spritebatch->height));
// 	sprite->pos[2] = depth;

// 	/*  Compute view rectangle. */
// 	if (rect)
// 	{
// 		sprite->rect[0] = rect[0];
// 		sprite->rect[1] = rect[1];
// 		sprite->rect[2] = rect[2];
// 		sprite->rect[3] = rect[3];
// 	}
// 	else
// 	{
// 		sprite->rect[0] = 0.0f;
// 		sprite->rect[1] = 0.0f;
// 		sprite->rect[2] = 1.0f;
// 		sprite->rect[3] = 1.0f;
// 	}
// 	/*  Compute diffuse color.  */
// 	if (color)
// 	{
// 		sprite->color[0] = color[0];
// 		sprite->color[1] = color[1];
// 		sprite->color[2] = color[2];
// 		sprite->color[3] = color[3];
// 	}
// 	else
// 	{
// 		sprite->color[0] = 1.0f;
// 		sprite->color[1] = 1.0f;
// 		sprite->color[2] = 1.0f;
// 		sprite->color[3] = 1.0f;
// 	}
// 	/*  Assign angle and scale. */
// 	sprite->angle = angle;
// 	sprite->scale = scale;

// 	/*  Update texture index table. */
// 	texIndex = updateTextureTable(spritebatch, texture);

// 	/*	sprite texture index.	*/
// 	sprite->texture = (GLint)texIndex;

// 	/*	Update sprite count.    */
// 	spritebatch->numDraw++;

// 	return 1;
// }

// int sbAddSprite(SBSpriteBatch *spriteBatch, SBTexture *texture, const float *position,
// 				const float *rect, const float *color, float scale, float angle,
// 				float depth)
// {

// 	/*  Normalize coordinate.    */
// 	const float x = position[0] / (float)spriteBatch->width;
// 	const float y = position[1] / (float)spriteBatch->height;

// 	/*  */
// 	const float normalizePos[2] = {x, y};
// 	sbAddSpriteNormalized(spriteBatch, texture, (const float *)normalizePos, rect, color, scale, angle, depth);

// 	return 1;
// }

// void sbRemoveSprite(SBSpriteBatch *spritebatch, int index)
// {

// 	/*  Check if index is valid.    */
// 	if (index < spritebatch->numDraw)
// 	{

// 		/*	Set last element in the index that going to be removed.*/
// 		memcpy(&spritebatch->sprite[index],
// 			   &spritebatch->sprite[spritebatch->numDraw - 1],
// 			   sizeof(SBSprite));
// 		spritebatch->numDraw--;
// 	}
// }

// int sbFlushSpriteBatch(SBSpriteBatch *spritebatch)
// {

// 	/*  */
// 	if (spritebatch->numDraw > 0)
// 	{
// 		/*	DMA/Transfer sprite buffer to Graphic Memory.  */

// 		//void *pbuf = sbMapBufferWOnly(GL_ARRAY_BUFFER_ARB, spritebatch->vbo);
// 		//memcpy(pbuf, (const void *) spritebatch->sprite, spritebatch->numDraw * sizeof(SBSprite));
// 		return sbUnmapBuffer(GL_ARRAY_BUFFER_ARB);
// 	}
// 	sbUnmapBuffer(GL_ARRAY_BUFFER_ARB);
// 	return 1;
// }

// /*	TODO resolve.   */
// static sbEnablePointSprite(int enable)
// {
// 	if (enable)
// 		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
// 	else
// 		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
// }

// void sbDisplaySprite(SBSpriteBatch *spriteBatch)
// {

// 	float matscale[3][3];
// 	float rotmat[3][3];
// 	float tranmat[3][3];
// 	float TR[3][3];

// 	sbEnablePointSprite(1);

// 	/*  Only continue if elements needs to be drawn.    */
// 	if (spriteBatch->numDraw <= 0 && spriteBatch->numlabelDraw <= 0)
// 		return;

// 	/*	Bind textures.  */
// 	sbBindTextures(spriteBatch->textures, 0, spriteBatch->numTexture);

// 	/*	Load shader.    */
// 	sbBindShader(&spriteBatch->spriteShader);

// 	/*	Update view matrix and global scale*/
// 	sbMatrix3x3Translation(tranmat, spriteBatch->cameraPos);
// 	sbMatrix3x3Scale(matscale, spriteBatch->scale);
// 	sbMatrix3x3Rotation(rotmat, spriteBatch->rotation);
// 	sbMatrix3x3MultiMatrix3x3(tranmat, rotmat, TR);
// 	sbMatrix3x3MultiMatrix3x3(matscale, TR, spriteBatch->viewmatrix);

// 	/*	Update uniform variables.   */
// 	setShaderUniform1fv(&spriteBatch->spriteShader, spriteBatch->uniform.locationScale, 1, &spriteBatch->scale);
// 	setShaderUniformMatrix3x3fv(&spriteBatch->spriteShader, spriteBatch->uniform.locationViewMatrix, 1,
// 								&spriteBatch->viewmatrix[0][0]);

// 	/*	Draw sprites.	*/
// 	sbDrawArray(spriteBatch->vao, 0, spriteBatch->numDraw);
// 	/*	labels.	*/
// 	//sbBindShader(&spriteBatch->fontShader);
// 	//sbDrawArray(spriteBatch->vao, (spriteBatch->num -spriteBatch->numlabelDraw) , spriteBatch->numlabelDraw);

// 	sbEnablePointSprite(0);
// }