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
#ifndef _NETWORK_H_
#define _NETWORK_H_ 1
#include "network/Connection.h"
#include "UIDGenerator.h"
#include <map>

namespace fragengine
{
	/**
	 *	Responsible for performing connection and
	*	binding for the network.
	*/
	class FVDECLSPEC NetWork{
	public:
		static const int defaultPort = 55555;		/*	Default port for server.	*/
		static const int broadcastport = 55554;		/*	Default broadcast port.	*/

		/**
		 *	Transfer protocol.
		*/
		enum TransportProtocol{
			TCP = 0x1,		/*	*/
			UDP = 0x2,		/*	*/
		};

		/**
		 *	Create binded socket connection.
		*
		*	\port the process will listen to.
		*
		*	\protocol the connection shall use.
		*
		*	\listen only important when using TCP.
		*
		*	@Return
		*/
		static Connection* bind(unsigned int port = defaultPort,
				TransportProtocol protocol = eTCP, unsigned int listen = 32);

		/**
		 *	Create connection to IP address.
		*	The transport protocol will be assigned by the connection.
		*
		*	@Return non null pointer if successfully.
		*/
		static Connection* connect(const char* host,
				unsigned int port = defaultPort);

		/**
		 *	Accept incoming connection.
		*/
		static Connection* accept(Connection* binded);

		/**
		 *	Create broadcast socket connection.
		*
		*	@Return non null pointer if successfully.
		*/
		static Connection* createBroadcastConnection(void);

		/**
		 *	Get connection from unique identifier.
		*
		*	@Return non null pointer if connection exists.
		*/
		static Connection* getClientConnectionByUID(unsigned int uid);

		/**
		 *	Add client connection to the network of the process.
		*/
		static void addClient(Connection* connection);

		/**
		 *	Remove connection from the network of the process.
		*/
		static void disconnect(Connection* connection);

		/**
		 *	Disconnect all connection.
		*/
		static void disconnectAll(void);

		/**
		 *	Get number of client connections.
		*	@Return number of client connections.
		*/
		static unsigned int getNumClientConnections(void);


		/**
		 *
		 *	@Return connection pointer.
		*/
		static Connection* allocateConnection(void);


	protected:	/*	Internal methods.	*/

		/**
		 *	Bind
		*/
		static int bind(int numip, const char** ips);

		/**
		 *
		 */
		static int internalconnect(const char* ip, unsigned int port);

	private:	/*	Attributes.	*/

		/*	TODO look at the design.	*/
		class NetworkInternal{
			static Connection* broadcast;
			static std::map<unsigned int, Connection*> connections;
			static UIDGenerator uidgenerator;	/*	*/
		};
		static Connection* broadcast;
		static std::map<unsigned int, Connection*> connections;
		static UIDGenerator uidgenerator;	/*	*/

		//static NetworkInternal* internal;
	};

} // namespace fragengine

#endif
