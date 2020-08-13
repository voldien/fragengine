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
#ifndef _FRAG_ENGINE_NODE_H_
#define _FRAG_ENGINE_NODE_H_ 1
#include "Transform.h"
#include "GlobalState/GlobalState.h"
#include<Core/dataStructure/ITree.h>
#include <list>


namespace fragcore {

	class FVDECLSPEC Node : public Object, public ITree<Node> {
	public:
		Node(void);

		~Node(void);

		Node *root(void) const override;

		Node *getParent(void) const override;

		void setParent(Node *parent) override;

		unsigned int getNumChildren(void) const override;

		void addChild(Node *pchild) override;

		void removeChild(int index) override;

		Node *getChild(int index) const override;

		int getNodeChildIndex(Node *node) override;

	public:
		GlobalState *getGlobalState(int state);

		const GlobalState *getGlobalState(int state) const;

	protected:
		Transform local;
	private:
		std::list<GlobalState *> globalList;
	};
}

#endif
