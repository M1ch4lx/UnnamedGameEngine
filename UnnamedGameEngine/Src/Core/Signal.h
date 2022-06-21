#pragma once

#include "Common.h"

namespace UEngine
{
	template<typename TSignal>
	using SignalCallback = std::function<void(TSignal&)>;

	class SignalListener;

	class Signal
	{
		friend class SignalListener;
	private:
		SignalListener* source;

	public:
		SignalListener* Source() const
		{
			return source;
		}
	};

	class SignalListener
	{
	protected:
		template<typename TSignal>
		void SetSignalCallback(const SignalCallback<TSignal>& callback)
		{
			*GetSignalCallback<TSignal>() = callback;
		}

		template<typename TSignal>
		SignalCallback<TSignal>* GetSignalCallback()
		{
			static_assert(std::is_base_of_v<Signal, TSignal>);
			static SignalCallback<TSignal> callback;
			return &callback;
		}

	public:
		template<typename TSignal>
		void ConnectSignal(const SignalCallback<TSignal>& callback)
		{
			this->SetSignalCallback<TSignal>(callback);
		}

		template<typename TSignal>
		void EmitSignal(TSignal& signal)
		{
			signal.source = this;
			auto& callback = *GetSignalCallback<TSignal>();
			if (callback)
			{
				callback(signal);
			}
		}
	};
}