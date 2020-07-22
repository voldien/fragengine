#ifndef _FV_IOUTIL_H_
#define _FV_IOUTIL_H_ 1
#include"IO.h"
#include"../Ref.h"

namespace fragview{

	class FVDECLSPEC IOUtil {
		public:
			static long int loadFileMem(Ref<IO> &io, char **data);
			static long int loadFile(Ref<IO> &in, Ref<IO> &out);

			static long int loadStringMem(Ref<IO> &io, char **data);
			static long int loadString(Ref<IO> &in, Ref<IO> &out);
	};
}

#endif