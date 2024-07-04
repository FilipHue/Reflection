#pragma once

#include "type_repository.h"

namespace rtti {

	template <typename T>
	class RegisterType
	{
	private:
		class RegisterTypeInternal
		{
		public:
			RegisterTypeInternal() {
				TypeRepository::GetInstance()->RegisterType<T>();
			}
		};

	private:
		inline static RegisterTypeInternal m_registerer{};
	};

#define _REGISTER_TYPE_INTERNAL(TYPE, ID)	static rtti::RegisterType<TYPE> _CONCAT(RegistererType_, ID) {}
#define REGISTER_TYPE(TYPE)	_REGISTER_TYPE_INTERNAL(TYPE, __COUNTER__)
} // rtti
