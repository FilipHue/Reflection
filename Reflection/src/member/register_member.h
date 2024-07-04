#pragma once

#include "member_repository.h"

namespace rtti {

	struct RegisterMember
	{
		RegisterMember(TypeId class_id, const std::string& name, Variable member_id, uint32_t offset, uint32_t size, uint32_t alignment) {
			MemberRepository::RegisterMember(class_id, name, member_id, offset, size, alignment);
		}
	};

#define REGISTER_MEMBER(TYPE, MEMBER) static RegisterMember TYPE##MEMBER{TypeRepository::RegisterType<TYPE>(), #MEMBER, Variable::Create<decltype(TYPE::MEMBER)>(), offsetof(TYPE, MEMBER), sizeof(decltype(TYPE::MEMBER)), alignof(decltype(TYPE::MEMBER))};
} // rtti