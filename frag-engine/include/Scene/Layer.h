
#ifndef _FRAG_ENGINE_LAYER_H_
#define _FRAG_ENGINE_LAYER_H_ 1
#include<Core/Object.h>
#include<string>

namespace fragengine {
	using namespace fragcore;
	/**
	 *
	 */
	class FVDECLSPEC Layer : public Object {
	public:
		Layer() {
			this->index = 0;
		}

		Layer(const Layer &layer) {
			this->index = layer.index;
		}

		Layer(unsigned int index) {
			this->index = index;
		}

		unsigned int getIndex() const {
			return this->index;
		}

		void setIndex(unsigned int index) {
			this->index = index;
		}

		void setName(const std::string &name) noexcept override { Object::setName(name); }

		std::string getName() noexcept override { return Object::getName(); }

		std::string &getName() const noexcept override {
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
