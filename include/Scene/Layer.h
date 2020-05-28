
#ifndef _FV_LAYER_H_
#define _FV_LAYER_H_ 1
#include"../Def.h"
#include"../Core/Object.h"
#include<string>

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC Layer : public Object {
	public:
		Layer(void) {
			this->index = 0;
		}

		Layer(const Layer &layer) {
			this->index = layer.index;
		}

		Layer(unsigned int index) {
			this->index = index;
		}

		unsigned int getIndex(void) const {
			return this->index;
		}

		void setIndex(unsigned int index) {
			this->index = index;
		}

		void setName(const std::string &name) override {
			Object::setName(name);
		}

		std::string getName(void) override {
			return Object::getName();
		}

		std::string &getName(void) const override {
			//return getIndexByName(this->index);
		}

	private:    /*  */

		unsigned int index;
	public:
		/*  */
		static void setIndextName(unsigned int index, const char *cname);

		static const std::string &getIndexName(unsigned int index);

		static Layer getIndexByName(const char *cname);

	private:
		static std::string name[32];    /*  32 layers.  */
	};
}
#endif
