#pragma once

namespace EGE { namespace Content{
	class IContent
	{
	public:
		void Init();
		void Destroy();

	protected:
		~IContent();

		virtual void ICInit() {}
		virtual void ICDestroy() {}

		void MasterInit();
		void MasterDestroy();

	private:
		bool mIsDestroyed{ false };
	};
}}
