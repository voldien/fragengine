#ifndef _FRAG_CORE_IOUTIL_H_
#define _FRAG_CORE_IOUTIL_H_ 1
#include"IO.h"
#include"../Ref.h"

namespace fragcore {

	/**
	 * 
	 */
	class FVDECLSPEC IOUtil {
		public:

			/*	*/
			static long int loadFileMem(const Ref<IO> &io, char **data);
			static long int loadFile(const Ref<IO> &in, Ref<IO> &out);

			/*	*/
			static long int loadStringMem(const Ref<IO> &io, char **data);
			static long int loadString(const Ref<IO> &in, Ref<IO> &out);
	};
}

#endif