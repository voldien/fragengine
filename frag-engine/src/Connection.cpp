#include"network/Connection.h"
#include<netdb.h>
#include<arpa/inet.h>
#include<lz4.h>
#include<zlib.h>
#include<openssl/aes.h>
/*	*/

Connection::Connection(void){
	this->compression = eNoneCompression;
	this->encryption = eNoneEncryption;
	this->externalport = 0;
	this->port = 0;
	this->tcpsocket = 0;
	this->udpsocket = 0;
	this->their_addr = NULL;
	this->uid = 0;

	this->inet = 0;

	this->symetricdeckey = NULL;
	this->symetricenckey = NULL;
	this->asymetrickey = NULL;

	this->encryptiontmpbuffer = NULL;
	this->compresiontmpbuffer = NULL;
	this->combufsize = 0;
	this->encbufsize = 0;

	memset(this->IP, 0, sizeof(this->IP));
	memset(this->externIP, 0, sizeof(this->externIP));

}
Connection::Connection(const Connection& other){
	*this = other;
}
Connection::~Connection(void){
	free(this->encryptiontmpbuffer);
	free(this->compresiontmpbuffer);

	free( this->symetricdeckey );
	free( this->symetricenckey );
}

const char* Connection::getIP(void)const{
	return this->IP;
}
const char* Connection::getExternalIP(void)const{
	return this->externIP;
}

unsigned int Connection::getPort(void)const{
	return this->port;
}
unsigned int Connection::getExternalPort(void)const{
	return this->externalport;
}





unsigned int Connection::getUID(void)const{
	return this->uid;
}

void Connection::setCompression(Compression compression){

	this->compression = compression;

	if(compression != eNoneCompression){
		this->combufsize = sizeof(unsigned int) * 1024;
		this->compresiontmpbuffer = realloc(this->compresiontmpbuffer, this->combufsize);
		switch(compression){
		case eLz4:
			LZ4_compressBound(this->combufsize);
			break;
		case eGzip:
			compressBound(this->combufsize);
			break;
		default:
			break;
		}
	}
}
Connection::Compression Connection::getCompression(void)const{
	return this->compression;
}

void Connection::setEncryption(Encryption encryption, const void* pkey, unsigned int plength){
	this->encryption = encryption;

	/*	*/
	if(encryption != eNoneEncryption){

		this->encbufsize = sizeof(unsigned int) * 1024;
		this->encryptiontmpbuffer = realloc(this->encryptiontmpbuffer, this->encbufsize);
		memset(this->encryptiontmpbuffer, 0, this->encbufsize);

		switch(encryption){
		case eAES128:
		case eAES192:
		case eAES256:
			this->symetricdeckey = malloc(sizeof(AES_KEY));
			this->symetricdeckey = malloc(sizeof(AES_KEY));

			AES_set_decrypt_key((const unsigned char*)pkey, plength * 8, (AES_KEY*)this->symetricdeckey);
			AES_set_encrypt_key((const unsigned char*)pkey, plength * 8, (AES_KEY*)this->symetricenckey);
			break;
		default:
			break;
		}
	}
}
Connection::Encryption Connection::getEncryption(void)const{
	return this->encryption;
}


int Connection::getTCPSocket(void)const{
	return this->tcpsocket;
}
void Connection::setTCPSocket(int socket){
	this->tcpsocket = socket;

	/*	Get ip and port used on the local machine.	*/
	struct sockaddr_in addr;
	socklen_t len;
	getsockname(socket, (struct sockaddr *)&addr, &len);
	memcpy(this->IP, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	this->port = ntohs(addr.sin_port);

	/*	Get external connection IP and port.	*/
	getpeername(socket, (struct sockaddr *)&addr, &len);
	memcpy(this->externIP, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
	this->externalport = ntohs(addr.sin_port);
}

int Connection::getUDPSocket(void)const{
	return this->udpsocket;
}
void Connection::setUDPSocket(int socket, const char* addrr, unsigned int port){

	struct sockaddr_in addr;			/*	*/
	socklen_t len;						/*	*/
	struct sockaddr_in* their = NULL;	/*	*/
	struct hostent *he = NULL;			/*	*/

	this->udpsocket = socket;

	/**/
	he = gethostbyname(addrr);

	/*	*/
	their_addr = realloc(their_addr, sizeof(struct sockaddr_in));
	their = (struct sockaddr_in*)their_addr;

	/*	*/
	bzero(their_addr, sizeof(struct sockaddr_in));
	their->sin_family = AF_INET;		/* host byte order	*/
	their->sin_port = htons(port);		/* short, network byte order	*/
	their->sin_addr.s_addr = inet_addr(addrr);

	this->port = port;
	getsockname(socket, (struct sockaddr *)&addr, &len);
	memcpy(this->IP, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)) + 1);
}



int Connection::sendPacket(unsigned int sType, const void* data, unsigned int len){

	PacketHeader* header = (PacketHeader*)data;
	const int packetsize = sizeof(PacketHeader);

	/*	Packet header description.	*/
	header->sType = sType;
	header->len = len;
	header->uid = this->getUID();	/*	from connection.	*/
	header->offset = packetsize;
	header->version = 1;
	::send(this->getTCPSocket(), &header, sizeof(header), MSG_MORE);

	return this->send(data, len);
}
int Connection::send(const void* data, unsigned int len){

	uLongf colen;
	const int buflen = 4096;

	while(0){

	}

	/*	TODO fix for when packet is data is greater then the buffers. So to add a while loop.*/
	switch(getCompression()){
	case eLz4:
		len = LZ4_compress((const char*)data, (char*)compresiontmpbuffer, len);
		data = (const char*)compresiontmpbuffer;
		break;
	case eGzip:
		compress((Bytef*)compresiontmpbuffer, &colen, (const Bytef *)data, len);
		data = compresiontmpbuffer;
		len = colen;
		break;
	case eNoneCompression:
	default:
		break;
	}


	switch(getEncryption()){
	default:
	case eNoneEncryption:
		break;
	case eAES128:
	case eAES192:
	case eAES256:
		AES_encrypt((const unsigned char*)data,
				(unsigned char*)this->encryptiontmpbuffer,
				(const AES_KEY*)this->symetricenckey);
		len = len + (len % 16);
		data = (const char*)encryptiontmpbuffer;
		break;
	}

	return ::send(this->tcpsocket, data, len, 0);
}


long int Connection::recvPeekHeader(PacketHeader* header){
	long int len;	/**/

	len = ::recv(this->getTCPSocket(), header, sizeof(PacketHeader), MSG_PEEK);

	return len;
}

long int Connection::recvPacket(PacketHeader* header, void* buf, unsigned int* size){

	long int len;	/**/

	len = ::recv(this->getTCPSocket(), header, sizeof(PacketHeader), 0);
	len += this->recv(buf, header->len - header->offset);

	return len;
}
long int Connection::recv(void* buf, unsigned int size){

	int len;
	long int clen;

	/*	*/
	len = ::recv(this->tcpsocket, buf, size, 0);

	/*	Decrypt the data.	*/
	switch(encryption){
	default:
	case eNoneEncryption:
		break;
	case eAES128:
	case eAES192:
	case eAES256:

		break;
	}

	/*	UnCompresss data.	*/
	switch(compression){
	case eGzip:
		uncompress((Bytef*)this->compresiontmpbuffer, (uLongf*)&clen, (const Bytef*)buf, len);
		len = clen;
		break;
	case eLz4:
		len = LZ4_decompress_safe((const char*)buf,
				(char*)this->compresiontmpbuffer,
				len,
				this->combufsize);
		memcpy(buf, this->encryptiontmpbuffer, len);
		break;
	case eNoneCompression:
	default:
		break;
	}

	return len;
}

int Connection::sendTo(const void* data, unsigned int size){

	struct sockaddr_in broadcastAddr; /* Broadcast address */

	memset(&broadcastAddr, 0, sizeof(broadcastAddr));	/* Zero out structure */
	broadcastAddr.sin_family = AF_INET;					/* Internet address family */
	broadcastAddr.sin_addr.s_addr = inet_addr(IP);		/* Broadcast IP address */
	broadcastAddr.sin_port = htons(getPort());      	/* Broadcast port */

	return ::sendto(this->udpsocket, data, size, 0, (struct sockaddr*)&broadcastAddr, sizeof(struct sockaddr));
}
int Connection::recvFrom(void* data, unsigned int size){
	return ::recvfrom(this->udpsocket, data, size, 0, NULL, NULL);
}

