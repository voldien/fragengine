#ifndef _FRAG_CORE_SINGLETON_H_
#define _FRAG_CORE_SINGLETON_H_ 1
#include"../Def.h"
#include"SmartReference.h"

namespace fragcore {
	template <class T>
	class FVDECLSPEC Singleton : SmartReference
	{
	public:
		static T* _instance;
		static Ref<T> &getInstance(void)
		{
			if (_instance == NULL)
			{
				T *instance = new T();
				Ref<T> ref = Ref<T>(instance);
				instance->onCreation(ref);
			}
			return Ref<T>(_instance);
		}

		virtual void onCreation(Ref<T> &instance);
	};
}
#endif