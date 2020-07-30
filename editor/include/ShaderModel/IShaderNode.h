//
// Created by voldie on 01/03/19.
//

#ifndef FRAGVIEW_ISHADERNODE_H
#define FRAGVIEW_ISHADERNODE_H
#include"Def.h"
#include "ShaderEdge.h"
#include<vector>

class IShaderNode {
public:

	std::vector<ShaderEdge*> getEdges(void);

	int getNrChildren(void) const;
	IShaderNode* getChild(int index);

	void addChild(IShaderNode *pNode) {
		ShaderEdge edge;
		edge.start = this;
		edge.end = pNode;
		this->edges.push_back(edge);
	}

private:
	std::vector<ShaderEdge> edges;
	
};

#endif