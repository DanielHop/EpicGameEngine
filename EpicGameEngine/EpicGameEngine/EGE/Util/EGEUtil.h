#pragma once

namespace EGE { namespace Util{
	
	template<typename T>
	class Comptr
	{
	public:
		Comptr(T* instance)
		{
			this->instance = instance;
		}

		Comptr()
		{
			
		}

		~Comptr()
		{
			this->instance->Release();
		}

		T* GetInstance()
		{
			return instance;
		}

		T** GetPointerInstance()
		{
			return &instance;
		}
	private:
		T* instance;
	};
}}	