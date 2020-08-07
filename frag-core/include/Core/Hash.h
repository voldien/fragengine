#ifndef _FRAG_CORE_HASH_H_
#define _FRAG_CORE_HASH_H_ 1
#include"../Def.h"
#include"IO/IO.h"
#include"Ref.h"
#include"Object.h"
#include <vector>

namespace fragview {

	/**
	 *
	 */
	class FVDECLSPEC Hash : public Object {
	public:
		enum ALGORITHM {
			MD5,        /*  */
			SHA128,     /*  */
			SHA256,     /*  */
			SHA512,     /*  */
		};
		Hash(ALGORITHM algorithm);

		~Hash(void);

		/*  Add additional data to be used for computing.   .*/
		void update(const void* pdata, size_t nbytes);
		void update(const Ref<IO> &io);
		/*  Get the final hash value.   */
		void final(std::vector<unsigned char>& hash);

		ALGORITHM getAlgorithm(void) const;
	private:
		void* context;
		ALGORITHM algorithm;    /**/

		Hash(const Hash& other);
		Hash(void);
	public:
		//TODO static of non static hash object.
		static void computeMD5(const void* pdata, size_t nbytes, unsigned char md5[16]);
		//void computeMD5(IO* io, unsigned char md5[16]);

	};

}

#endif