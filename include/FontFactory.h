#ifndef _FV_FONTFACTORY_H_
#define _FV_FONTFACTORY_H_ 1
#include"Core/IO/IO.h"
#include"Def.h"
#include"Prerequisites.h"
#include"Font.h"

namespace fragview {
	/**
	 *
	 */
	class FVDECLSPEC FontFactory {
	public:

		enum Encoding {
			ASCII,
			UTF8,
			UTF16,
		};

		static Font *createFont(IRenderer *renderer, IO *io, float size, Encoding encoding = ASCII);
		static Font *createFont(Image *image, Ref<IO> &io, float size, Encoding encoding = UTF8);
		//static Font* createFont(IRenderer* renderer, void* pdata, unsigned long nBytes, float size, Encoding encoding = ASCII);

	private:    /*	Prevent one from creating an instance of this class.	*/

		FontFactory(void) = default;
		FontFactory(const FontFactory &other) = default;
	};
}

#endif