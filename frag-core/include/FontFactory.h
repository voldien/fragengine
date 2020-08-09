

#ifndef _FRAG_CORE_FONTFACTORY_H_
#define _FRAG_CORE_FONTFACTORY_H_ 1
#include"Core/IO/IO.h"
#include"Def.h"
#include"Prerequisites.h"
#include"Core/Ref.h"
#include"Font.h"


namespace fragcore {
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

		static Font *createFont(Ref<IRenderer> &renderer, Ref<IO> &io, float size, Encoding encoding = ASCII);
		static Font *createSDFFont(Ref<IRenderer> &renderer, Ref<IO> &io, float size, Encoding encoding = ASCII);
		//static Font *createFont(Image *image, Ref<IO> &io, float size, Encoding encoding = UTF8);
		//static void CreateSDF(void);
	private:    /*	Prevent one from creating an instance of this class.	*/

		FontFactory(void) = default;
		FontFactory(const FontFactory &other) = default;
	};
}

#endif