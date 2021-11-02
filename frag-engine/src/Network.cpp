// #include "Debug.h"
// #include "network/Network.h"

// #include <netinet/in.h>
// #include <netdb.h>
// #include <sys/socket.h>
// #include <openssl/aes.h>
// #include <openssl/rsa.h>
// #include <openssl/sha.h>
// #include <openssl/bio.h>
// #include <openssl/tls1.h>
// #include <openssl/ssl.h>
// #include <openssl/x509.h>
// #include <openssl/pem.h>
// #include <openssl/rand.h>
// #include <openssl/blowfish.h>

// #include "PoolAllactor.h"
// #include "ProtocolHeaders.h"
// #include "physic/PhysicInterface.h"
// #include "UIDGenerator.h"


// Connection* NetWork::broadcast = NULL;						/*	*/
// std::map<unsigned int, Connection*> NetWork::connections;	/*	*/
// PoolAllactor<Connection> poolconnections(32);				/*	*/
// UIDGenerator NetWork::uidgenerator;							/*	*/

// /*	TODO add address family.	*/
// Connection* NetWork::bind(unsigned int port, TransportProtocol protocol, unsigned int listen){

// 	Config* config;

// 	Connection* connection = NULL;	/*	*/
// 	int sock = 0;					/*	*/
// 	unsigned int afinet = 0;		/*	*/
// 	unsigned int prot = 0;			/*	*/
// 	struct sockaddr_in addr4;		/*	*/
// 	struct sockaddr_in6 addr6;		/*	*/
// 	struct sockaddr* addr;			/*	*/
// 	socklen_t slen;					/*	*/
// 	struct hostent *host;			/*	*/

// 	/*	*/
// 	afinet = AF_INET;
// 	switch(protocol){
// 	case eTCP:
// 		sock = SOCK_STREAM;
// 		prot = IPPROTO_TCP;
// 		break;
// 	case eUDP:
// 		sock = SOCK_DGRAM;
// 		prot = IPPROTO_UDP;
// 		break;
// 	}

// 	/*	Create socket and bind it to process.	*/
// 	sock =  socket(afinet, sock, prot);
// 	if(sock < 0){
// 		return NULL;
// 	}

// 	/*	*/
// 	bzero((char*) &addr4, sizeof(addr4));
// 	addr4.sin_family = afinet;
// 	addr4.sin_addr.s_addr = INADDR_ANY;
// 	addr4.sin_port = htons(port);


// 	/*	*/
// 	if (::bind(sock, (struct sockaddr*) &addr4, sizeof(addr4)) < 0) {
// 		fprintf(stderr, strerror(errno));
// 		close(sock);
// 		return NULL;
// 	}

// 	/*	*/
// 	connection = allocateConnection();


// 	/*	*/
// 	switch(protocol){
// 	case eTCP:
// 		::listen(sock, listen);
// 		connection->setTCPSocket(sock);
// 		break;
// 	case eUDP:
// 		connection->setUDPSocket(sock);
// 		break;
// 	}


// 	return connection;
// }

// Connection* NetWork::accept(Connection* binded){

// 	struct sockaddr clientname;
// 	socklen_t clilen = sizeof (clientname);
// 	unsigned int socknew;
// 	Connection* con = NULL;

// 	/*	Accept TCP connection.	*/
// 	socknew = ::accept(binded->getTCPSocket(), (struct sockaddr *) &clientname, &clilen);
// 	if (socknew < 0){
// 		perror ("accept");
// 		return NULL;
// 	}

// 	/*	*/
// 	con = allocateConnection();
// 	if(con == NULL){
// 		return NULL;
// 	}

// 	/*	*/
// 	con->setTCPSocket(socknew);
// 	NetWork::addClient(con);



// 	/*	*/
// //	PacketConnectionReplay replay = {0};
// //	replay.uid = con->getUID();
// //	replay.compression = binded->getCompression();
// //	replay.encrypt = binded->getEncryption();

// 	/*	If using encryption. Create RSA key for establish a connection.	*/
// 	//if(con->getEncryption() != Connection::eNoneEncryption){
// 	//	RSA* pclientkey = NULL;
// 	//	PacketRequest req = { 0 };

// 		/*	Generate or fetch precompute asymmetric cipher.*/

// 		/*	Assigned it to serve replay packet.*/

// 	//}

// 	/*	*/
// 	Debug::log("Sending connection replay to %s.\n", con->getExternalIP());
// 	//con->sendPacket(PhysicInterface::eConnectionReplay, &replay, sizeof(replay));

// 	/*	Set connection.	*/
// 	//con->setCompression(binded->getCompression());
// 	/*con->setEncryption(bindconec->getEncryption(), prikey, 16);	*/



// 	return con;
// }

// Connection* NetWork::connect(const char* host, unsigned int port){

// 	Connection* con = NULL;			/*	*/
// 	int sock;						/*	*/
// 	struct sockaddr* addr;			/*	*/
// 	struct sockaddr_in addr4;		/*	*/
// 	struct sockaddr_in6 addr6;		/*	*/
// 	socklen_t lensoc;				/*	*/
// 	struct hostent *server;			/*	*/

// 	/*	*/
// 	sock = socket(AF_INET, SOCK_STREAM, 0);
// 	if(sock < 0){
// 		fprintf(stderr, "%s.\n", strerror(errno));
// 		return NULL;
// 	}

// 	/*	*/
// 	server = gethostbyname(host); /*get host information by ip name or ip explicitly*/
// 	if (!server) {
// 		close(sock);
// 		fprintf(stderr, "Failed to gethostbyname, %s.\n", strerror(errno));
// 		return NULL;
// 	}

// 	/*	*/
// 	switch(server->h_addrtype){
// 	case AF_INET:
// 		/*	*/
// 		bzero((void*) &addr4, sizeof(addr4));
// 		addr4.sin_family = server->h_addrtype; /*AF_INET;*/
// 		/*	copy server addr data.	*/
// 		bcopy((char*) server->h_addr,
// 		(char*)&addr4.sin_addr.s_addr,
// 		server->h_length);
// 		addr4.sin_port = htons(port);
// 		addr = (struct sockaddr*)&addr4;
// 		lensoc = sizeof(addr4);
// 		break;
// 	case AF_INET6:
// 		lensoc = sizeof(addr6);
// 		break;
// 	default:
// 		fprintf(stderr, "Invalid address family type, %d.\n", server->h_addrtype);
// 		close(sock);
// 		return NULL;
// 	}

// 	/*	*/
// 	if (::connect(sock, addr, lensoc) < 0) {
// 		close(sock);
// 		fprintf(stderr, "%s\n", strerror(errno));
// 		return NULL;
// 	}


// 	con = allocateConnection();

// 	/*	*/
// 	con->setTCPSocket(sock);

// 	PacketInitInfo init = { 0 };

// 	con->recv(&init.header, sizeof(init.header));

// 	PacketClientOption replay = { 0 };

// 	con->send(&replay, sizeof(replay));
// 	/*	Get replay from the server, before continue in order to initialize the connection properly.	*/

// 	con->recv(&replay, sizeof(replay));
// 	if(replay.comp){
// 		con->setCompression((Connection::Compression)replay.comp);
// 	}


// 	/*	Send public key if using encryption.	*/
// 	//if(replay.encrypt != Connection::eNoneEncryption){

// 	//	RSA* publickey = NULL;
// 	//RSA* privatekey = NULL;
// 	//	unsigned int keysize;
// 	//unsigned char* pkey;

// 		//con->recv()

// 	//	con->setEncryption((Connection::Encryption)replay.encrypt, replay.key, replay.key[0]);

// 	//	RSA_free(publickey);
// 	//}



// 	/*	bind broadcast port */
// 	broadcast = NetWork::bind(broadcastport, eUDP);
// 	if(broadcast == NULL){

// 	}


// 	/*	create UDP connection*/
// 	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
// 	/*	TODO resolve.
// 	ExConnectSocket(sock, ip, port);
// 	if(sock > 0){
// 		con->setUDPSocket( sock );
// 	}
// 	/*

// 	return con;

// 	poolconnections.Return(con);	/*	TODO improve.	*/
// 	return NULL;
// }


// Connection* NetWork::createBroadcastConnection(){

// 	Connection* connection = NULL;
// 	int bcast_sock;
// 	int broadcastEnable = 1;
// 	int ret;
// 	int af = AF_INET;

// 	/*	Create UDP socket.	*/
// 	bcast_sock = socket(af, SOCK_DGRAM, IPPROTO_UDP);
// 	if(bcast_sock < 0 ){
// 		fprintf(stderr, "Failed to create socket %s.\n", strerror(errno));
// 		return NULL;
// 	}

// 	/*	Set socket option.	*/
// 	ret = setsockopt(bcast_sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
// 	if( ret < 0 ){
// 		fprintf(stderr, "Failed to set socket option, %s.\n", strerror(errno));
// 		return NULL;
// 	}

// 	/*	Allocate connection.	*/
// 	connection = allocateConnection();
// 	connection->setUDPSocket(bcast_sock, "255.255.255.255", broadcastport);

// 	return connection;
// }

// Connection* NetWork::getClientConnectionByUID(unsigned int uid){
// 	return NetWork::connections[uid];
// }

// void NetWork::addClient(Connection* connection){

// 	/*	Add unique identifier for the connection.	*/
// 	connection->uid = uidgenerator.getNextUID();

// 	/*	Add connection to the network connection mappper.	*/
// 	connections[connection->getUID()] = connection;

// 	/**/
// 	Debug::log("Added connection from %s:%d.\n", connection->getExternalIP(),
// 			connection->getExternalPort());
// }
// void NetWork::disconnect(Connection* connection){


// 	/*	Close socket.	*/
// 	if(connection->getTCPSocket() > 0){
// 		close(connection->getTCPSocket());
// 	}
// 	if(connection->getUDPSocket() > 0){
// 		close(connection->getUDPSocket());
// 	}

// 	/*	Remove from network mapper.	*/
// 	std::map<unsigned int, Connection*>::iterator it = connections.find(connection->getUID());
// 	connections.erase(it);

// 	Debug::log("Disconnected connection %s:%d.\n", connection->getExternalIP(),
// 			connection->getExternalPort());
// }


// void NetWork::disconnectAll(){

// 	std::map<unsigned int, Connection*>::iterator it;

// 	/*	*/
// 	for( it = connections.begin(); it != connections.end(); it++){
// 		Connection* con = (*it).second;
// 		NetWork::disconnect(con);
// 	}

// }



// unsigned int NetWork::getNumClientConnections(){
// 	return connections.size();
// }

// Connection* NetWork::allocateConnection(){
// 	Connection* con = poolconnections.obtain();
// 	if(con == NULL){
// 		poolconnections.resize(2 * poolconnections.reserved());
// 		con = poolconnections.obtain();
// 		assert(con);
// 	}
// 	return con;
// }




// int NetWork::bind(int numip, const char** ips){

// }
// int NetWork::internalconnect(const char* ip, unsigned int port){

// }

