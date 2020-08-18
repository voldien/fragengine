

#if defined(FRAG_VERTEX_SHADER)
uniform mat4 MVP;
uniform mat4 PVM;

#endif

out gl_PerVertex{
    vec4 gl_Position;
    float gl_PointSize;
    float gl_ClipDistance[];
};
