#pragma once

#include <set>

#include "member_info.h"
#include "../variable/variable.h"

namespace rtti {

	class MemberRepository
	{
	public:
		MemberRepository(const MemberRepository&) = delete;
		MemberRepository& operator=(const MemberRepository&) = delete;
		~MemberRepository() = default;

		static MemberRepository& GetInstance() {
			static MemberRepository s_instance;
			return s_instance;
		}

		static void RegisterMember(TypeId class_id, const std::string& name, Variable member_id, uint32_t offset, uint32_t size, uint32_t alignment) {
			MemberInfo member{ class_id, name, member_id, offset, size, alignment };

			s_member_register[class_id].insert(member);
		}

		static const std::set<MemberInfo>& GetMembers(TypeId class_id) {
			return s_member_register[class_id];
		}

		static const std::unordered_map<uint64_t, std::set<MemberInfo>>& GetRegister() {
			return s_member_register;
		}

	private:
		MemberRepository() = default;

	private:
		inline static std::unordered_map<uint64_t, std::set<MemberInfo>> s_member_register;
	};
} // rtti
