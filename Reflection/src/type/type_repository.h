#pragma once

#include <unordered_map>

#include "type_info.h"
#include "type_id.h"

namespace rtti {

	class TypeRepository
	{
	public:
		TypeRepository(const TypeRepository&) = delete;
		TypeRepository(TypeRepository& other) = delete;
		~TypeRepository() = default;

		static TypeRepository* GetInstance() {
			static TypeRepository m_instance;

			return &m_instance;
		}

		template<typename T>
		static TypeId RegisterType() {
			TypeId id{ typeid(T) };
			m_register[id] = TypeInfo::Create<T>();

			return id;
		}

		static TypeInfo& GetTypeInfo(TypeId id) { return m_register[id]; }

		template <typename T>
		static TypeId GetTypeId() {
			TypeId id{ typeid(T) };
			return id;
		}
		static const std::unordered_map<uint64_t, TypeInfo>& GetRegister() { return m_register; }

	private:
		TypeRepository() = default;

	private:
		inline static std::unordered_map<uint64_t, TypeInfo> m_register{};
	};

} // rtti
