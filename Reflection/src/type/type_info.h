#pragma once

#include <iostream>

#include <type_traits>
#include <bitset>

#include "type_name.h"

namespace rtti {

	enum TypeFlags {
		TypeFlags_IsFundamental,
		TypeFlags_IsIntegral,
		TypeFlags_IsFloatingPoint,
		TypeFlags_IsTriviallyCopyable,

		TypeFlags_Size
	};

	class TypeInfo {
	public:
		TypeInfo() = default;
		~TypeInfo() = default;

		std::bitset<TypeFlags_Size> const GetFlags() const { return m_flags; }
		std::string_view GetName() const { return m_type_name; }
		size_t GetSize() const { return m_size; }
		size_t GetAlignment() const { return m_alignment; }

		template <typename T>
		static TypeInfo Create() {
			TypeInfo ti{};

			ti.m_type_name = TypeName<T>();
			ti.m_size = sizeof(T);
			ti.m_alignment = alignof(T);

			ti.m_flags[TypeFlags_Size - 1 - TypeFlags_IsFundamental]		= std::is_fundamental_v<T>;
			ti.m_flags[TypeFlags_Size - 1 - TypeFlags_IsIntegral]			= std::is_integral_v<T>;
			ti.m_flags[TypeFlags_Size - 1 - TypeFlags_IsFloatingPoint]		= std::is_floating_point_v<T>;
			ti.m_flags[TypeFlags_Size - 1 - TypeFlags_IsTriviallyCopyable]	= std::is_trivially_copyable_v<T>;

			return ti;
		}

	private:
		std::string_view m_type_name = "None";
		size_t m_size = 0;
		size_t m_alignment = 0;

		std::bitset<TypeFlags_Size> m_flags {};

	private:
		friend std::ostream& operator<<(std::ostream& os, const TypeInfo& typeinfo) {
			os <<	"Type Name: "	<< typeinfo.m_type_name		<< std::endl <<
					"Size: "		<< typeinfo.m_size			<< std::endl <<
					"Alignment: "	<< typeinfo.m_alignment		<< std::endl <<
					"Flags:"		<< typeinfo.m_flags;

			return os;
		}
	};
	
} // rtti
