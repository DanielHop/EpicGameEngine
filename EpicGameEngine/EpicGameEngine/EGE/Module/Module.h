#pragma once

#include <iostream>

using ModuleID = size_t;

namespace EGE{ namespace Module{

	class Module
	{
	public:
		void Init();
		void Destroy();

		void SetID(ModuleID id) { if (id == 0) this->id = id; }

	protected:
		~Module() {}

		virtual void LocalInit() {}
		virtual void LocalDestroy() {}
	private:
		void MasterInit();
		void MasterDestroy();

	private:
		ModuleID id;
	};
}}