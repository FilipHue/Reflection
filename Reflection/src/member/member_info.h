#pragma once

#include <set>

#include "../variable/variable.h"

namespace rtti {

	class MemberInfo
	{
	public:
		MemberInfo(TypeId class_id, const std::string& name, Variable member_id, uint32_t offset, uint32_t size, uint32_t alignment)
			: m_class_id(class_id), m_name(name), m_member_id(member_id), m_offset(offset), m_size(size), m_alignment(alignment) {}

		void const SetClassId(TypeId class_id) { m_class_id = class_id; }
		void const SetName(const std::string& name) { m_name = name; }
		void const SetMemberId(Variable member_id) { m_member_id = member_id; }
		void const SetOffset(uint32_t offset) { m_offset = offset; }
		void const SetSize(uint32_t size) { m_size = size; }
		void const SetAlignment(uint32_t alignment) { m_alignment = alignment; }

		TypeId GetClassId() const { return m_class_id; }
		const std::string& GetName() const { return m_name; }
		Variable GetMemberId() const { return m_member_id; }
		uint32_t GetOffset() const { return m_offset; }
		uint32_t GetSize() const { return m_size; }
		uint32_t GetAlignment() const { return m_alignment; }

		friend bool operator<(const MemberInfo& lhs, const MemberInfo& rhs) {
			return lhs.m_offset < rhs.m_offset;
		}

	private:
		friend std::ostream& operator<<(std::ostream& os, const MemberInfo& member_info) {
			os << 
				"Class Id: "				<< member_info.m_class_id						<< std::endl <<
				"Name: "					<< member_info.m_name							<< std::endl <<
				"Member Info: "				<< std::endl									<<
					"\tName: "				<< member_info.m_member_id.GetName()			<< std::endl <<
					"\tIsConst: "			<< member_info.m_member_id.IsConst()			<< std::endl <<
					"\tIs volatile: "		<< member_info.m_member_id.IsVolatile()			<< std::endl <<
					"\tIs reference: "		<< member_info.m_member_id.IsReference()		<< std::endl <<
					"\tIs RValue: "			<< member_info.m_member_id.IsRValueReference()	<< std::endl <<
					"\tArray size: "		<< member_info.m_member_id.GetArraySize()		<< std::endl <<
					"\tPointer count: "		<< member_info.m_member_id.GetPointerCount()	<< std::endl <<
				"Offset: "					<< member_info.m_offset							<< std::endl <<
				"Size: "					<< member_info.m_size							<< std::endl <<
				"Alignment: "				<< member_info.m_alignment						<< std::endl;

			return os;
		}

	private:
		TypeId m_class_id;
		std::string m_name;
		Variable m_member_id;
		uint32_t m_offset;
		uint32_t m_size;
		uint32_t m_alignment;
	};
} // rtti