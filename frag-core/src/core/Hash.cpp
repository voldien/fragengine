#include"Core/Hash.h"
#include"Utils/StringUtil.h"
#include<openssl/md5.h>
#include <Exception/InvalidArgumentException.h>
#include <Exception/NotSupportedException.h>

using namespace fragcore;

Hash::Hash(Hash::ALGORITHM algorithm) {
	switch(algorithm) {
		case MD5:
			this->context = malloc(sizeof(MD5_CTX));
			MD5_Init ((MD5_CTX*)this->context);
			break;
		case SHA128:
		case SHA256:
		case SHA512:
			throw NotSupportedException();
		default:
			throw InvalidArgumentException(fvformatf("Invalid hash enumerator - %d", algorithm));
	}

	/*      */
	this->algorithm = algorithm;
}

Hash::~Hash(void) {
	free(this->context);
}

void Hash::update(const void *pdata, size_t nbytes) {
	switch(this->algorithm){
		case MD5:
			MD5_Update ((MD5_CTX*)this->context, pdata, nbytes);
			break;
		case SHA128:
		case SHA256:
		case SHA512:
		default:
			throw NotSupportedException("Not supported");
	}
}

void Hash::update(const Ref<IO> &io){
	char buffer[4096];
	long int prev_pos = io->getPos();
	long int len;

	while((len = io->read(sizeof(buffer),buffer)) >= 0){
		this->update(buffer, len);
	}

	io->seek(prev_pos, IO::Seek::SET);
}

void Hash::final(std::vector<unsigned char> &hash) {
	switch(this->algorithm){
		case MD5:
			hash.resize(MD5_DIGEST_LENGTH);
			MD5_Final (hash.data(),(MD5_CTX*)this->context);
			break;
		case SHA128:
		case SHA256:
		case SHA512:
		default:
			throw NotSupportedException("Not supported");
	}
}


Hash::ALGORITHM Hash::getAlgorithm(void) const {
	return this->algorithm;
}

Hash::Hash(const Hash &other) {

}

Hash::Hash(void) {

}

void Hash::computeMD5(const void *pdata, size_t nbytes, unsigned char md5[16]) {

	std::vector<unsigned char> h;
	Hash hash(MD5);
	hash.update(pdata, nbytes);
	hash.final(h);
	memcpy(md5, h.data(), sizeof(md5));
}
