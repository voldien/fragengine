/*
    Copyright (C) 2015  Valdemar Lindberg

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
#ifndef _FRAG_CORE_TREE_H_
#define _FRAG_CORE_TREE_H_ 1
#include"../../Exception/InvalidArgumentException.h"
#include"../../Def.h"
#include"Iterator.h"

namespace fragview {

	/**
	 * 
	 */
	template<class T>
	class ITree {
	public:
		ITree(void) {
			this->sibling = NULL;
			this->numChildren = 0;
			this->child = NULL;
			this->parent = NULL;
		}

		virtual T *root(void) const {
			if (this->getParent())
				return this;
			else
				return this->getParent()->root();
		}

		virtual bool isEmpty(void) const {
			return this->getNumChildren() == 0;
		}

		virtual T *getParent(void) const {
			return this->parent;
		}

		virtual void setParent(T *parent) {
			this->parent = parent;
		}

		virtual unsigned int getNumChildren(void) const {
			this->numChildren;
		}

		virtual void addChild(T *pchild) {
			T *find;
			assert(pchild);

			this->numChildren++;
			if (!this->child) {
				this->setChild(pchild);
				child->setParent(this);
			} else {

				find = this->child;
				while (find) {
					if (find->sibling)
						find = find->sibling;
					else break;
				}
				find->sibling = pchild;
				find->sibling->setParent(this);
			}
		}

		virtual void removeChild(int index) {
			ITree *sn = getChild(index - 1);
			ITree *n = sn->sibling;
			sn->setSibling(n->sibling);
			n->parent = NULL;
		}

		virtual T *getChild(int index) const {
			if(index < 0 || index >= this->getNumChildren())
				throw InvalidArgumentException("");
			T *chi = this->child;
			for (int x = 0; x <= index; x++) {
				chi = chi->sibling;
			}
			return chi;
		}

		virtual int getNodeChildIndex(T *node) {
			T *n = this->child;
			int i = 0;
			while (n) {
				if (n == node) {
					return i;
				}
				i++;
				n = n->child;
			}
			return -1;
		}

		class TIterator : public Iterator<T>{
		public:
/*			TIterator &operator++(void) override {
				return Iterator::operator++();
			}

			TIterator &operator++(int i) override {
				return Iterator::operator++(i);
			}

			TIterator &operator--(void) override {
				return Iterator::operator--();
			}

			TIterator &operator+=(int n) override {
				return Iterator::operator+=(n);
			}

			TIterator &operator-=(int n) override {
				return Iterator::operator-=(n);
			}

			TIterator &operator+(int n) override {
				return Iterator::operator+(n);
			}

			TIterator &operator-(int n) override {
				return Iterator::operator-(n);
			}

			TIterator &operator[](int index) const override {
				return Iterator::operator[](index);
			}

			T &operator->(void) const override {
				return Iterator::operator->();
			}

			T &operator*(void) const override {
				return Iterator::operator*();
			}

			T &operator*(void) override {
				return Iterator::operator*();
			}

			bool operator==(const TIterator &iterator) override {
				return Iterator::operator==(iterator);
			}

			bool operator!=(const TIterator &iterator) override {
				return Iterator::operator!=(iterator);
			}

			Iterator<T> &operator=(const TIterator &iterator) override {
				return Iterator::operator=(iterator);
			}*/
		};

		/*  TODO determine if iterator can be added.    */
//		virtual TIterator begin(void);
//		virtual TIterator end(void);

	protected:  /*  */
		void setSibling(T *sibling) {
			this->sibling = sibling;
		}

		void setChild(T *child) {
			this->child = child;
		}

	private:    /*  */
		T *parent;                  /*	parent node.	*/
		T *sibling;                 /*	sibling node.	*/
		T *child;                   /*	child node.	*/
		unsigned int numChildren;   /*	number of children node attached.	*/
	};
}
#endif
