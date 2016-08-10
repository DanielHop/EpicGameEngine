#include "IContent.h"

namespace EGE { namespace Content{
	IContent::~IContent()
	{
		Destroy();
	}

	void IContent::Init()
	{
		MasterInit();
		IInit();
	}

	void IContent::Destroy()
	{
		if (!mIsDestroyed)
		{
			MasterDestroy();
			IDestroy();
		}
	}

	void IContent::MasterInit()
	{
		//DO INIT STUFF
	}

	void IContent::MasterDestroy()
	{
		mIsDestroyed = true;
		//DO MASTER DESTROY STUFF
	}
}}