#ifndef FRAGVIEW_SHADEREDGE_H
#define FRAGVIEW_SHADEREDGE_H

class IShaderNode;
class ShaderEdge {

public:
	IShaderNode* start;
	IShaderNode* end;
};

#endif