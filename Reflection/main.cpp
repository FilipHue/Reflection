#include "src/type/register_type.h"
#include "src/variable/variable.h"
#include "src/member/register_member.h"

#include <tuple>

#define TEST_TYPE 0
#define TEST_VAR 0
#define TEST_MEMBER 1

using namespace rtti;

struct TestTransform {
	float x;
	float y;
	float z;
};

struct TestQuaternion {
	float x;
	float y;
	float z;
	float w;
};

struct TestScale {
	float x;
	float y;
	float z;

};

struct GameComponent {
	TestTransform transform;
	TestQuaternion rotation;
	TestScale scale;

	std::unordered_map<int, int> data;
};

int main() {
#if TEST_TYPE
	REGISTER_TYPE(char);
	REGISTER_TYPE(short);
	REGISTER_TYPE(int);
	REGISTER_TYPE(unsigned int);
	REGISTER_TYPE(long);
	REGISTER_TYPE(unsigned long);
	REGISTER_TYPE(long long);
	REGISTER_TYPE(unsigned long long);
	REGISTER_TYPE(float);
	REGISTER_TYPE(double);

	TypeRepository* rep = TypeRepository::GetInstance();

	auto& reg = rep->GetRegister();
	for (auto& pair : reg) {
		std::cout << pair.first << " with:\n" << pair.second << std::endl << std::endl;
	}
#endif

#if TEST_VAR
	std::cout << Variable::Create<int>() << std::endl;
	std::cout << Variable::Create<int&>() << std::endl;
	std::cout << Variable::Create<int&&>() << std::endl;
	std::cout << Variable::Create<int*>() << std::endl;
	std::cout << Variable::Create<int**>() << std::endl;
	std::cout << Variable::Create<int[8]>() << std::endl;

	std::cout << Variable::Create<const int>() << std::endl;
	std::cout << Variable::Create<const int&>() << std::endl;
	std::cout << Variable::Create<const int&&>() << std::endl;
	std::cout << Variable::Create<const int*>() << std::endl;
	std::cout << Variable::Create<const int**>() << std::endl;
	std::cout << Variable::Create<const int[8]>() << std::endl;

	std::cout << Variable::Create<const volatile int>() << std::endl;
	std::cout << Variable::Create<const volatile int&>() << std::endl;
	std::cout << Variable::Create<const volatile int&&>() << std::endl;
	std::cout << Variable::Create<const volatile int*>() << std::endl;
	std::cout << Variable::Create<const volatile int**>() << std::endl;
	std::cout << Variable::Create<const volatile int[8]>() << std::endl;

	std::cout << Variable::Create<const volatile int[8][10]>() << std::endl;
	std::cout << Variable::Create<const volatile int***[8][10]>() << std::endl;
	std::cout << Variable::Create<const volatile int***&>() << std::endl;
	std::cout << Variable::Create<int***&>() << std::endl;
#endif

#if TEST_MEMBER
	REGISTER_MEMBER(TestTransform, x);
	REGISTER_MEMBER(TestTransform, y);
	REGISTER_MEMBER(TestTransform, z);

	REGISTER_MEMBER(TestQuaternion, x);
	REGISTER_MEMBER(TestQuaternion, y);
	REGISTER_MEMBER(TestQuaternion, z);
	REGISTER_MEMBER(TestQuaternion, w);

	REGISTER_MEMBER(TestScale, x);
	REGISTER_MEMBER(TestScale, y);
	REGISTER_MEMBER(TestScale, z);

	REGISTER_MEMBER(GameComponent, transform);
	REGISTER_MEMBER(GameComponent, rotation);
	REGISTER_MEMBER(GameComponent, scale);

	REGISTER_MEMBER(GameComponent, data);

	MemberRepository* rep = &MemberRepository::GetInstance();

	auto& reg = rep->GetRegister();
	for (auto& pair : reg) {
		std::cout << pair.first << " with:\n";
		for (auto& member : pair.second) {
			std::cout << member << std::endl;
		}
		std::cout << std::endl;
	}
#endif

	return 0;
}
