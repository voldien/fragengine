/**
	Simple physic simulation with a server-client model support.
	Copyright (C) 2016  Valdemar Lindberg

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
#ifndef _FRAG_ENGINE_CONNECTION_H_
#define _FRAG_ENGINE_CONNECTION_H_ 1
#include <FragCore.h>

namespace fragengine {
	/**
	 * @brief
	 *	Responsible for transfer low level data and
	 *	associated data with the connection.
	 */
	class FVDECLSPEC Connection : public fragcore::UIDObject {
		friend class NetWork;

	  public:
		enum Compression {
			NoneCompression = 0x0, /*	No compression.	*/
			Gzip,				   /*	Slower but higher compression ratio.	*/
			Lz4,				   /*	Faster but with lower compression ratio.	*/
		};

		enum Encryption {
			NoneEncryption = 0x0, /*	No encryption.	*/
			AES128 = 0x1,		  /*	AES 128 bit encryption.	*/
			AES192 = 0x2,		  /*	AES 192 bit encryption.	*/
			AES256 = 0x4,		  /*	AES 256 bit encryption.	*/
			DES3 = 0x8,			  /*	DES3.	*/
			BlowFish = 0x10,	  /*	BlowFish.	*/
		};

	  public:
		Connection();
		Connection(const Connection &other);
		~Connection();

		/**
		 *	Get IP address of the connection.
		 *
		 *	@Return none null terminate string.
		 */
		const char *getIP() const;

		const char *getExternalIP() const;

		/**
		 *	Get port.
		 *
		 *	@Return
		 */
		unsigned int getPort() const;

		unsigned int getExternalPort() const;

		/**
		 *	Set compression used for this connection.
		 */
		void setCompression(Compression compression);
		Compression getCompression() const;

		/**
		 *	Set encryption used for the connection.
		 */
		void setEncryption(Encryption encryption, const void *pkey, unsigned int plength);
		Encryption getEncryption() const;

		/**
		 *	Get/Set TCP socket used with this connection.
		 *
		 */
		int getTCPSocket() const;
		void setTCPSocket(int socket);

		/**
		 *	UDP socket.
		 *
		 *	@Return
		 */
		int getUDPSocket() const;
		void setUDPSocket(int socket, const char *addr = "127.0.0.1", unsigned int port = 0);

		/**
		 *	Send packet with a packet header prior.
		 *
		 *	@Return
		 */
		int sendPacket(unsigned int sType, const void *data, unsigned int len);

		/**
		 *	Send a sequence if bytes.
		 *
		 *	@Return number of bytes sent.
		 */
		int send(const void *data, unsigned int len);

		/**
		 *	Recv packet.
		 *
		 *	@Return
		 */
		// long int recvPeekHeader(PacketHeader* header);
		// long int recvPacketHeader(PacketHeader* header);
		// long int recvPacket(PacketHeader* header, void* buf, unsigned int* size);
		// long int recv(void* buf, unsigned int size);

		/**
		 *	UDP
		 *
		 *	@Return	number of bytes.
		 */
		int sendTo(const void *data, unsigned int size);
		// int sendToPacket(unsigned int sType, const void* data, unsigned int size);
		int recvFrom(void *data, unsigned int size);

	  protected: /*	Internal methods. */
		void *intcompress();
		void *intencrypt();
		void *intuncompress();
		void *intdecrypt();

	  protected:				   /*	Attributes.	*/
		unsigned int uid;		   /*	unique connection identifier.	*/
		unsigned int port;		   /*	port.	*/
		unsigned int externalport; /*	external port.	*/
		char IP[32];			   /*	IP address.*/
		char externIP[32];		   /*	external IP address.	*/
		Compression compression;   /*	compression.	*/
		Encryption encryption;	   /*	encryption.	*/
		int tcpsocket;			   /*	socket.	*/
		int udpsocket;			   /*	socket.	*/
		void *their_addr;		   /*	UDP connection.	*/
		unsigned int inet;		   /*	type of socket, local or none local socket.	*/

		void *compresiontmpbuffer; /*	Compression	buffer.	*/
		void *encryptiontmpbuffer; /*	Encryption buffer.	*/
		unsigned int combufsize;   /*	Compression buffer size.	*/
		unsigned int encbufsize;   /*	Encryption buffer size.	*/

		void *symetricenckey;			  /*	symmetric cipher encryption key.	*/
		void *symetricdeckey;			  /*	symmetric cipher decryption key.	*/
		unsigned int numsymmetrickeybits; /*	Number of bit is used for the symmetric chiper key.	*/

		void *asymetrickey;				   /**/
		unsigned int numbitsforasymmetric; /**/

		void *sslcontext; /**/
	};
} // namespace fragengine

#endif
