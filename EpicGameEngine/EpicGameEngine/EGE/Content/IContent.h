#pragma once

namespace EGE { namespace Content{
	class IContent
	{
	public:
		void Init();
		void Destroy();

	protected:
		~IContent();

		virtual void IInit() {}
		virtual void IDestroy() {}

		void MasterInit();
		void MasterDestroy();

	private:
		bool mIsDestroyed{ false };
	};
}}
