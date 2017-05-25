#include <catch.hpp>

#include "../../../Engine/Math/Vector.h"

TEST_CASE("Generic vector functionality", "[vector]")
{
	using namespace etm;

	int32 input1 = 1;
	int32 input2 = 2;
	int32 input3 = 3;
	int32 input4 = 4;
	int32 input5 = 5;

	SECTION("default constructor")
	{
		vector<5, int32> vec = vector<5, int32>();
		REQUIRE(vec[0] == 0);
		REQUIRE(vec[1] == 0);
		REQUIRE(vec[2] == 0);
		REQUIRE(vec[3] == 0);
		REQUIRE(vec[4] == 0);
	}
	SECTION("single input constructor")
	{
		vector<5, int32> vec = vector<5, int32>(input1);
		REQUIRE(vec[0] == input1);
		REQUIRE(vec[1] == input1);
		REQUIRE(vec[2] == input1);
		REQUIRE(vec[3] == input1);
		REQUIRE(vec[4] == input1);
	}
	SECTION("initializer list constructor")
	{
		vector<5, int32> vec = { input1, input2, input3, input4, input5 };

		SECTION("verify initializer list")
		{
			REQUIRE(vec[0] == input1);
			REQUIRE(vec[1] == input2);
			REQUIRE(vec[2] == input3);
			REQUIRE(vec[3] == input4);
			REQUIRE(vec[4] == input5);
		}
		SECTION("copy constructor")
		{
			vector<5, int32> vec2 = vector<5, int32>(vec);
			REQUIRE(vec2[0] == input1);
			REQUIRE(vec2[1] == input2);
			REQUIRE(vec2[2] == input3);
			REQUIRE(vec2[3] == input4);
			REQUIRE(vec2[4] == input5);
		}
		SECTION("negate operator")
		{
			vector<5, int32> vec2 = -vec;

			//original unharmed
			REQUIRE(vec[0] == input1);
			REQUIRE(vec[1] == input2);
			REQUIRE(vec[2] == input3);
			REQUIRE(vec[3] == input4);
			REQUIRE(vec[4] == input5);
			//new vector inverted
			REQUIRE(vec2[0] == -input1);
			REQUIRE(vec2[1] == -input2);
			REQUIRE(vec2[2] == -input3);
			REQUIRE(vec2[3] == -input4);
			REQUIRE(vec2[4] == -input5);
		}
	}
}

TEST_CASE("specific vec2 functionality", "[vector]")
{
	using namespace etm;

	float input1 = 3.22345f;
	float input2 = 3.345f;

	SECTION("default constructor")
	{
		etm::vec2 vec = etm::vec2();
		REQUIRE(vec.x == 0);
		REQUIRE(vec.y == 0);
	}
	SECTION("single input constructor")
	{
		etm::vec2 vec = etm::vec2(input1);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input1);
	}
	SECTION("argument list constructor")
	{
		etm::vec2 vec = { input1, input2};
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
	}
	SECTION("float arguments constructor")
	{
		etm::vec2 vec = etm::vec2(input1, input2);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
	}
	SECTION("copy constructor")
	{
		etm::vec2 vecOriginal = etm::vec2(input1, input2);
		SECTION("copy constructor")
		{
			etm::vec2 vec = etm::vec2(vecOriginal);
			REQUIRE(vec.x == input1);
			REQUIRE(vec.y == input2);
		}
		SECTION("[] operator")
		{
			etm::vec2 vec = etm::vec2(vecOriginal);
			REQUIRE(vec[0] == input1);
			REQUIRE(vec[1] == input2);
		}
		SECTION("- operator")
		{
			etm::vec2 vec = etm::vec2(-vecOriginal);
			REQUIRE(vecOriginal.x == input1);
			REQUIRE(vecOriginal.y == input2);
			REQUIRE(vec.x == -input1);
			REQUIRE(vec.y == -input2);
		}
	}
	SECTION("perpendicular operation")
	{
		etm::vec2 vec;
		SECTION("with 0")
		{
			vec = etm::vec2(0);
			REQUIRE(nearEqualsV(perpendicular(vec), etm::vec2(0)) == true);
		}
		SECTION("with pos pos")
		{
			vec = etm::vec2(1, 2);
			REQUIRE(nearEqualsV(perpendicular(vec), etm::vec2(-2, 1)) == true );
		}
		SECTION("with pos neg")
		{
			vec = etm::vec2(1, -2);
			REQUIRE(nearEqualsV(perpendicular(vec), etm::vec2(2, 1)) == true );
		}
		SECTION("with neg pos")
		{
			vec = etm::vec2(-1, 2);
			REQUIRE(nearEqualsV(perpendicular(vec), etm::vec2(-2, -1)) == true );
		}
		SECTION("with neg neg")
		{
			vec = etm::vec2(-1, -2);
			REQUIRE(nearEqualsV(perpendicular(vec), etm::vec2(2, -1)) == true );
		}
		REQUIRE(dot(vec, perpendicular(vec)) == 0);
	}
	SECTION("signed angle")
	{
		etm::vec2 a = etm::vec2(3, -1);
		etm::vec2 aNorm = normalize(a);
		SECTION("with 0")
		{
			//expected problem because zero vectors don't have deterministic results
			a = etm::vec2(0);
			aNorm = normalize(a);
			REQUIRE(nearEquals(angleSafeSigned(a, a), 0.f) == false);
			REQUIRE(nearEquals(angleFastSigned(aNorm, aNorm), 0.f) == false);
		}
		SECTION("with same")
		{
			REQUIRE(nearEquals(angleSafeSigned(a, a), 0.f) == true);
			REQUIRE(nearEquals(angleFastSigned(aNorm, aNorm), 0.f) == true);
		}
		SECTION("with perpendicular")
		{
			etm::vec2 b = perpendicular(a);
			etm::vec2 bNorm = normalize(b);
			REQUIRE(nearEquals(angleSafeSigned(a, b), etm::PI_DIV2) == true);
			REQUIRE(nearEquals(angleFastSigned(aNorm, bNorm), etm::PI_DIV2) == true);
		}
		SECTION("with negative sign")
		{
			etm::vec2 b = -perpendicular(a);
			etm::vec2 bNorm = normalize(b);
			REQUIRE(nearEquals(angleSafeSigned(a, b), -etm::PI_DIV2) == true);
			REQUIRE(nearEquals(angleFastSigned(aNorm, bNorm), -etm::PI_DIV2) == true);
		}
		SECTION("with opposite")
		{
			etm::vec2 b = -a;
			etm::vec2 bNorm = normalize(b);
			REQUIRE(nearEquals(angleSafeSigned(a, b), etm::PI) == true);
			REQUIRE(nearEquals(angleFastSigned(aNorm, bNorm), etm::PI) == true);
		}
		SECTION("45 degrees")
		{
			etm::vec2 b = etm::vec2(1, 1);
			etm::vec2 bNorm = normalize(b);
			REQUIRE(nearEquals(angleSafeSigned(a, b), etm::PI*0.25f) == true);
			REQUIRE(nearEquals(angleFastSigned(aNorm, bNorm), etm::PI*0.25f) == true);
			//fast angle can fail with unnormalized values
			REQUIRE(nearEquals(angleFastSigned(a, b), etm::PI*0.25f) == false);
		}
	}
}

TEST_CASE("specific vec3 functionality", "[vector]") 
{
	using namespace etm;

	float input1 = 3.22345f;
	float input2 = 3.345f;
	float input3 = 4.f;

	SECTION("default constructor")
	{
		vec3 vec = vec3();
		REQUIRE(vec.x == 0);
		REQUIRE(vec.y == 0);
		REQUIRE(vec.z == 0);
	}
	SECTION("single input constructor")
	{
		vec3 vec = vec3(input1);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input1);
		REQUIRE(vec.z == input1);
	}
	SECTION("argument list constructor")
	{
		vec3 vec = { input1, input2, input3 };
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
	}
	SECTION("float arguments constructor")
	{
		vec3 vec = vec3(input1, input2, input3);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
	}
	SECTION("vec2 - float arguments constructor")
	{
		vec3 vec = vec3(vec2(input1, input2), input3);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
	}
	SECTION("float - vec2 arguments constructor")
	{
		vec3 vec = vec3(input1, vec2(input2, input3));
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
	}
	SECTION("copy constructor")
	{
		vec3 vecOriginal = vec3(input1, input2, input3);
		SECTION("copy constructor")
		{
			vec3 vec = vec3(vecOriginal);
			REQUIRE(vec.x == input1);
			REQUIRE(vec.y == input2);
			REQUIRE(vec.z == input3);
		}
		SECTION("[] operator")
		{
			vec3 vec = vec3(vecOriginal);
			REQUIRE(vec[0] == input1);
			REQUIRE(vec[1] == input2);
			REQUIRE(vec[2] == input3);
		}
		SECTION("- operator")
		{
			vec3 vec = vec3(-vecOriginal);
			REQUIRE(vecOriginal.x == input1);
			REQUIRE(vecOriginal.y == input2);
			REQUIRE(vecOriginal.z == input3);
			REQUIRE(vec.x == -input1);
			REQUIRE(vec.y == -input2);
			REQUIRE(vec.z == -input3);
		}
	}
	SECTION("vec2 swizzle")
	{
		vec3 vec = vec3(input1, input2, input3);
		vec2 xy = vec.xy;
		REQUIRE(xy.x == vec.x);
		REQUIRE(xy.y == vec.y);
		vec2 yz = vec.yz;
		REQUIRE(yz.x == vec.y);
		REQUIRE(yz.y == vec.z);
	}
}


TEST_CASE("specific vec4 functionality", "[vector]")
{
	using namespace etm;

	float input1 = 3.22345f;
	float input2 = 3.345f;
	float input3 = 4.f;
	float input4 = 2.f;

	SECTION("default constructor")
	{
		vec4 vec = vec4();
		REQUIRE(vec.x == 0);
		REQUIRE(vec.y == 0);
		REQUIRE(vec.z == 0);
		REQUIRE(vec.w == 0);
	}
	SECTION("single input constructor")
	{
		vec4 vec = vec4(input1);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input1);
		REQUIRE(vec.z == input1);
		REQUIRE(vec.w == input1);
	}
	SECTION("argument list constructor")
	{
		vec4 vec = { input1, input2, input3, input4 };
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);

		REQUIRE(vec.r == input1);
		REQUIRE(vec.g == input2);
		REQUIRE(vec.b == input3);
		REQUIRE(vec.a == input4);

		REQUIRE(vec[0] == input1);
		REQUIRE(vec[1] == input2);
		REQUIRE(vec[2] == input3);
		REQUIRE(vec[3] == input4);
	}
	SECTION("float arguments constructor")
	{
		vec4 vec = vec4(input1, input2, input3, input4);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("vec2 - vec2 arguments constructor")
	{
		vec4 vec = vec4(vec2(input1, input2), vec2(input3, input4));
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("vec2 - float - float arguments constructor")
	{
		vec4 vec = vec4(vec2(input1, input2), input3, input4);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("float - float - vec2 arguments constructor")
	{
		vec4 vec = vec4(input1, input2, vec2(input3, input4));
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("float - vec2 - float arguments constructor")
	{
		vec4 vec = vec4(input1, vec2(input2, input3), input4);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("float - vec3 arguments constructor")
	{
		vec4 vec = vec4(input1, vec3(input2, input3, input4));
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("vec3 - float arguments constructor")
	{
		vec4 vec = vec4(vec3(input1, input2, input3), input4);
		REQUIRE(vec.x == input1);
		REQUIRE(vec.y == input2);
		REQUIRE(vec.z == input3);
		REQUIRE(vec.w == input4);
	}
	SECTION("copy constructor")
	{
		vec4 vecOriginal = vec4(input1, input2, input3, input4);
		SECTION("copy constructor")
		{
			vec4 vec = vec4(vecOriginal);
			REQUIRE(vec.x == input1);
			REQUIRE(vec.y == input2);
			REQUIRE(vec.z == input3);
			REQUIRE(vec.w == input4);
		}
		SECTION("- operator")
		{
			vec4 vec = vec4(-vecOriginal);
			REQUIRE(vecOriginal.x == input1);
			REQUIRE(vecOriginal.y == input2);
			REQUIRE(vecOriginal.z == input3);
			REQUIRE(vecOriginal.w == input4);
			REQUIRE(vec.x == -input1);
			REQUIRE(vec.y == -input2);
			REQUIRE(vec.z == -input3);
			REQUIRE(vec.w == -input4);
		}
	}
	SECTION("vec2 swizzle")
	{
		vec4 vec = vec4(input1, input2, input3, input4);
		vec2 xy = vec.xy;
		REQUIRE(xy.x == vec.x);
		REQUIRE(xy.y == vec.y);
		vec2 yz = vec.yz;
		REQUIRE(yz.x == vec.y);
		REQUIRE(yz.y == vec.z);
		vec2 zw = vec.zw;
		REQUIRE(zw.x == vec.z);
		REQUIRE(zw.y == vec.w);
	}
	SECTION("vec3 swizzle")
	{
		vec4 vec = vec4(input1, input2, input3, input4);
		vec3 xyz = vec.xyz;
		REQUIRE(xyz.x == vec.x);
		REQUIRE(xyz.y == vec.y);
		REQUIRE(xyz.z == vec.z);
		vec3 rgb = vec.rgb;
		REQUIRE(rgb.x == vec.x);
		REQUIRE(rgb.y == vec.y);
		REQUIRE(rgb.z == vec.z);
		REQUIRE(rgb.x == vec.r);
		REQUIRE(rgb.y == vec.g);
		REQUIRE(rgb.z == vec.b);
	}
}