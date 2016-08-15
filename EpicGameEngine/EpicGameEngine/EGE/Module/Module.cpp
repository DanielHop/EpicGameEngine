#include "Module.h"

namespace EGE{ namespace Module{
	void Module::Init()
	{
		MasterInit();
		LocalInit();
	}

	void Module::Destroy()
	{
		MasterDestroy();
		LocalDestroy();
	}

	void Module::MasterInit()
	{
		
	}

	void Module::MasterDestroy()
	{

	}
}}