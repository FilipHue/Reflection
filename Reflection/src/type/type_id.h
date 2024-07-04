#pragma once

#include <cstdint>
#include <typeindex>

namespace rtti {

	class TypeId
	{
	public:
		TypeId(std::type_index typeindex) {
			m_id = HashId(typeindex);
		}
		TypeId(uint64_t id) : m_id(id) {}
		~TypeId() = default;

		const uint64_t GetId() const { return m_id; }

		operator uint64_t() const {
			return m_id;
		}

		friend bool operator==(const TypeId& lhs, const TypeId& rhs) {
			return lhs.m_id == rhs.m_id;
		}

	private:
		static uint64_t HashId(std::type_index& typeindex) {
			std::uint64_t hash_value = 0xcbf29ce484222325ULL;
			constexpr std::uint64_t prime = 0x108080001b3ULL;

			for (char c : std::string_view(typeindex.name())) {
				hash_value ^= static_cast<std::uint64_t>(c);
				hash_value *= prime;
			}

			return hash_value;
		}

	private:
		uint64_t m_id;
	};

} //rtti
