#ifndef PHYSIC_AUDIOFACTORY_H
#define PHYSIC_AUDIOFACTORY_H
#include"AudioInterface.h"

namespace fragview {
	class FVDECLSPEC AudioFactory {
	public:
		enum AudioAPI { /*  Official audio api.  */
			OpenAL,        /*	*/
			FMOD,          /*  */
		};

		/**
		 * Create audio interface
		 * @param audioapi
		 * @param resources
		 * @param config
		 * @return none NULL if successful.
		 */
		static AudioInterface *createAudioInterface(AudioAPI audioapi, IConfig *config);

		/**
		 * Create rendering interface
		 * @param cpathlib
		 * @param resources
		 * @param config
		 * @return none NULL if successful.
		 */
		static AudioInterface *createAudioInterface(const char *cpathlib, IConfig *config);

		/**
		 * Get rendering interface library file path.
		 * @param api valid api.
		 * @return non-null terminated string.
		 */
		static const char *getInterfaceLibraryPath(AudioAPI api);

	private:    /*	Prevent one from creating an instance of this class.	*/

		AudioFactory(void);

		AudioFactory(const AudioFactory &other);
	};
}

#endif