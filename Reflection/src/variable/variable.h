#pragma once

#include <string>
#include "../type/register_type.h"

namespace rtti {
	static uint32_t VariableFlags_Const				= 1 << 0;
	static uint32_t VariableFlags_Volatile			= 1 << 1;
	static uint32_t VariableFlags_Reference			= 1 << 2;
	static uint32_t VariableFlags_RValueReference	= 1 << 3;

	class Variable
	{
	public:
		Variable(TypeId id) : m_type_id(id) {}
		Variable() = default;
		
		// https://stackoverflow.com/questions/9851594/standard-c11-way-to-remove-all-pointers-of-a-type
		
		template <typename T> struct remove_all_pointers
		{
			using Type = T;
		};

		template <typename T> struct remove_all_pointers<T*>
		{
			using Type = remove_all_pointers<T>::Type;
		};

		template <typename T>
		using remove_all_pointers_t = remove_all_pointers<T>::Type;

		template <typename T>
		static Variable Create() {
			using RemoveExtents		= std::remove_all_extents_t<T>;
			using RemoveReferences	= std::remove_reference_t<RemoveExtents>;
			using RemovePointers	= remove_all_pointers_t<RemoveReferences>;
			using BaseType			= std::remove_cvref_t<RemovePointers>;

			RegisterType<BaseType> type{};

			auto variable = Variable(TypeRepository::GetTypeId<BaseType>());

			bool is_reference			= std::is_reference_v<T>;
			bool is_rvaluereference		= std::is_rvalue_reference_v<T>;
			bool is_const				= std::is_const_v<RemovePointers>;
			bool is_volatile			= std::is_volatile_v<RemovePointers>;

			uint8_t pointer_count = CountPointers<RemoveReferences>();
			uint64_t array_size = sizeof(T) / sizeof(RemoveExtents);

			if (is_const)				variable.SetConstFlag();
			if (is_volatile)			variable.SetVolatileFlag();
			if (is_reference)			variable.SetReferenceFlag();
			if (is_rvaluereference)		variable.SetRValueReferenceFlag();

			variable.SetPointerCount(pointer_count);
			variable.SetArraySize(array_size);

			return variable;
		}

		std::string GetName() const {
			std::string name = std::string{ TypeRepository::GetTypeInfo(m_type_id).GetName() };

			if (IsVolatile())				name = "volatile " + name;
			if (IsConst())					name = "const " + name;

			for (auto i = 0; i < m_pointer_count; i++) {
				name += "*";
			}

			if (m_array_size > 1) {
				name += "[";
				name += std::to_string(m_array_size);
				name += "]";
			}

			if (IsRValueReference())	name += "&&";
			else if (IsReference())		name += "&";

			return name;
		}

		void SetConstFlag()				{ m_flags |= VariableFlags_Const; }
		void SetVolatileFlag()			{ m_flags |= VariableFlags_Volatile; }
		void SetReferenceFlag()			{ m_flags |= VariableFlags_Reference; }
		void SetRValueReferenceFlag()	{ m_flags |= VariableFlags_RValueReference; }

		bool IsConst() const			{ return m_flags & VariableFlags_Const; }
		bool IsVolatile() const			{ return m_flags & VariableFlags_Volatile; }
		bool IsReference() const		{ return m_flags & VariableFlags_Reference; }
		bool IsRValueReference() const	{ return m_flags & VariableFlags_RValueReference; }

		void SetArraySize(uint64_t size)	{ m_array_size = size; }
		void SetPointerCount(uint8_t count) { m_pointer_count = count; }

		uint64_t GetArraySize() const		{ return m_array_size; }
		uint64_t GetPointerCount() const	{ return m_pointer_count; }

		size_t GetSize()		{ return TypeRepository::GetTypeInfo(m_type_id).GetSize(); }
		size_t GetAlignment()	{ return TypeRepository::GetTypeInfo(m_type_id).GetAlignment(); }
		uint64_t GetHash()		{ return m_type_id.GetId() * 
										 m_array_size * 
										 (static_cast<uint64_t>(m_pointer_count) << 32) ^
										 static_cast<uint64_t>(m_flags) << 48;
		}

	private:
		template <typename T>
		static uint8_t CountPointers(uint8_t count = 0) {
			if (std::is_pointer_v<T>) {
				return CountPointers<std::remove_pointer_t<T>>(++count);
			}

			return count;
		}

		friend bool operator==(const Variable& lhs, const Variable& rhs) {
			return lhs.m_type_id == rhs.m_type_id &&
				lhs.m_array_size == rhs.m_array_size &&
				lhs.m_pointer_count == rhs.m_pointer_count &&
				lhs.m_flags == rhs.m_flags;
		}

		friend std::ostream& operator<<(std::ostream& os, const Variable& variable) {
			os << 
				"Name: "				<< variable.GetName()			<< std::endl <<
				"Is const: "			<< variable.IsConst()			<< std::endl <<
				"Is volatile: "			<< variable.IsVolatile()		<< std::endl <<
				"Is reference: "		<< variable.IsReference()		<< std::endl <<
				"Is rvalue reference: " << variable.IsRValueReference() << std::endl <<
				"Array size:"			<< variable.GetArraySize()		<< std::endl <<
				"Pointer count: "		<< variable.GetPointerCount()	<< std::endl;

			return os;
		}

	private:
		TypeId m_type_id;
		uint64_t m_array_size = 0;
		uint8_t m_pointer_count = 0;
		uint8_t m_flags = 0;
	};
} // rtti
