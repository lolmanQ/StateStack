#pragma once
#include "Vector4.h"

namespace Tga
{
	class Color
	{
	public:

		Color()
			:myR(0.0f)
			, myG(0.0f)
			, myB(0.0f)
			, myA(0.0f)
		{}

		Color(const float& aR, const float& aG, const float& aB)
		{
			myR = aR;
			myG = aG;
			myB = aB;
			myA = 1.0;
		}

		Color(const float& aR, const float& aG, const float& aB, const float& aA)
		{
			myR = aR;
			myG = aG;
			myB = aB;
			myA = aA;
		}

		Color(const std::initializer_list<float>& aList)
		{
			assert(aList.size() == 3 || aList.size() == 4 && "Color initializer list must have 3 or 4 elements");

			myR = aList.begin()[0];
			myG = aList.begin()[1];
			myB = aList.begin()[2];
			if (aList.size() == 4)
				myA = aList.begin()[3];
			else
				myA = 1.0f;
		}

		static Color Red() { return Color(1.0f, 0.0f, 0.0f); }
		static Color Green() { return Color(0.0f, 1.0f, 0.0f); }
		static Color Blue() { return Color(0.0f, 0.0f, 1.0f); }
		static Color White() { return Color(1.0f, 1.0f, 1.0f); }
		static Color Black() { return Color(0.0f, 0.0f, 0.0f); }

		void Set(const float& aR, const float& aG, const float& aB, const float& aA)
		{
			myR = aR;
			myG = aG;
			myB = aB;
			myA = aA;
		}

		Vector4f AsVec4() const
		{
			return Vector4f(myR, myG, myB, myA);
		}

		static float InverseEOTF(float x)
		{
			if (x >= 0.04045f)
				return powf((x + 0.055f) / (1.0f + 0.055f), 2.4f);
			else
				return x / 12.92f;
		}

		Vector4f AsLinearVec4() const
		{
			return Vector4f(InverseEOTF(myR), InverseEOTF(myG), InverseEOTF(myB), myA);
		}

		unsigned int AsHex() const
		{
			unsigned char r = static_cast<unsigned char>(myR * 255.0f);
			unsigned char g = static_cast<unsigned char>(myG * 255.0f);
			unsigned char b = static_cast<unsigned char>(myB * 255.0f);
			unsigned char a = static_cast<unsigned char>(myA * 255.0f);

			unsigned int final = 0;
			final |= (a << 24);
			final |= (r << 16);
			final |= (g << 8);
			final |= (b);
			return final;
		}

		float myR;
		float myG;
		float myB;
		float myA;
	};
}