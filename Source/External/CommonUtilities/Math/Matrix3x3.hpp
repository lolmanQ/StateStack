#pragma once
#include "Matrix4x4.hpp"
#include "Vector3.hpp"

namespace CU
{
	template<class T>
	class Matrix3x3
	{
	public:
		// Creates the identity matrix.
		Matrix3x3<T>();

		// Copy Constructor.
		Matrix3x3<T>(const Matrix3x3<T>& aMatrix);
		
		// Copies the top left 3x3 part of the Matrix4x4.
		Matrix3x3<T>(const Matrix4x4<T>& aMatrix);

		// Initializer list constructor (for teachers: used to just make rotation around axis creation easier)
		Matrix3x3<T>(std::initializer_list<T> aList);
		
		~Matrix3x3() = default;
		
		// () operator for accessing element (row, column) for read/write or read,respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;

		// boolean operators
		bool operator==(const Matrix3x3<T>& aMatrix) const;
		bool operator!=(const Matrix3x3<T>& aMatrix) const;

		// Math operators
		Matrix3x3<T> operator+(const Matrix3x3<T>& aMatrix) const;
		Matrix3x3<T> operator-(const Matrix3x3<T>& aMatrix) const;
		Matrix3x3<T> operator*(const Matrix3x3<T>& aMatrix) const;
		Matrix3x3<T> operator*(const T& aScalar) const;
		Vector3<T> operator*(const Vector3<T>& aVector) const;
		Matrix3x3<T>& operator+=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator-=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator*=(const Matrix3x3<T>& aMatrix);
		Matrix3x3<T>& operator*=(const T& aScalar);

		std::string ToString() const;

		// Static functions for creating rotation matrices.
		static Matrix3x3<T> CreateRotationAroundX(const T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundY(const T aAngleInRadians);
		static Matrix3x3<T> CreateRotationAroundZ(const T aAngleInRadians);

		// Static function for creating a transpose of a matrix.
		static Matrix3x3<T> Transpose(const Matrix3x3<T>& aMatrixToTranspose);

	private:
		static const size_t myMatrixSize = 3;
		static const size_t myLength = myMatrixSize * myMatrixSize;
		T myData[myLength]; // Stores values of the matrix. (For teachers: I decided to go with c style array for more power to use stuff like memcopy)
	};

	using Matrix3x3f = Matrix3x3<float>;

#pragma region Constructors
	
	template<class T>
	inline Matrix3x3<T>::Matrix3x3()
	{
		std::memset(myData, 0, myLength * sizeof(T)); // Sets all array values to 0
		myData[0] = 1;
		myData[4] = 1;
		myData[8] = 1;
	}

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3<T>& aMatrix)
	{
		std::memcpy(myData, aMatrix.myData, myLength * sizeof(T));
	}

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix4x4<T>& aMatrix)
	{
		const size_t rowMemorySize = myMatrixSize * sizeof(T);
		std::memcpy(myData, &aMatrix(1, 1), rowMemorySize);
		std::memcpy(myData + myMatrixSize, &aMatrix(2, 1), rowMemorySize);
		std::memcpy(myData + myMatrixSize * 2, &aMatrix(3, 1), rowMemorySize);
	}

	template<typename T>
	inline Matrix3x3<T>::Matrix3x3(std::initializer_list<T> aList)
	{
		assert(aList.size() <= myLength && "Initializer list is to long.");
		std::memset(myData, 0, myLength * sizeof(T)); // starts matrix at 0 so if init list is not long enough then rest is 0
		std::memcpy(myData, aList.begin(), aList.size() * sizeof(T));
	}
	
#pragma endregion Constructors

#pragma region Operators
	
	template<typename T>
	inline T& Matrix3x3<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow > 0 && aRow <= myMatrixSize && aColumn > 0 && aColumn <= myMatrixSize && "Indexes out of bounds");
		return myData[(aRow - 1) * 3 + (aColumn - 1)];
	}

	template<typename T>
	inline const T& Matrix3x3<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow > 0 && aRow <= myMatrixSize && aColumn > 0 && aColumn <= myMatrixSize && "Indexes out of bounds");
		return myData[(aRow - 1) * 3 + (aColumn - 1)];
	}

	template<typename T>
	inline bool Matrix3x3<T>::operator==(const Matrix3x3<T>& aMatrix) const
	{
		for (size_t i = 0; i < myLength; i++)
		{
			if (myData[i] != aMatrix.myData[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	inline bool Matrix3x3<T>::operator!=(const Matrix3x3<T>& aMatrix) const
	{
		for (size_t i = 0; i < myLength; i++)
		{
			if (myData[i] != aMatrix.myData[i])
			{
				return true;
			}
		}
		return false;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator+(const Matrix3x3<T>& aMatrix) const
	{
		// using += allows for reuse of code
		Matrix3x3<T> result(*this);
		return result += aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator+=(const Matrix3x3<T>& aMatrix)
	{
		for (size_t i = 0; i < myLength; i++)
		{
			myData[i] += aMatrix.myData[i];
		}
		return *this;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator-(const Matrix3x3<T>& aMatrix) const
	{
		// using -= allows for reuse of code
		Matrix3x3<T> result(*this);
		return result -= aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator-=(const Matrix3x3<T>& aMatrix)
	{
		for (size_t i = 0; i < myLength; i++)
		{
			myData[i] -= aMatrix.myData[i];
		}
		return *this;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const Matrix3x3<T>& aMatrix) const
	{
		// using *= allows for reuse of code
		Matrix3x3<T> result(*this);
		return result *= aMatrix;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const Matrix3x3<T>& aMatrix)
	{
		Matrix3x3<T> result;
		for (int i = 1; i <= myMatrixSize; i++)
		{
			for (int j = 1; j <= myMatrixSize; j++)
			{
				T product{ 0 };
				for (int k = 1; k <= myMatrixSize; k++)
				{
					product += this->operator()(i, k) * aMatrix(k, j);
				}
				result(i, j) = product;
			}
		}
		std::memcpy(myData, result.myData, sizeof(T) * myLength);
		return *this;
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::operator*(const T& aScalar) const
	{
		// using *= allows for reuse of code
		Matrix3x3<T> result(*this);
		return result *= aScalar;
	}

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator*=(const T& aScalar)
	{
		for (int i = 0; i < myLength; i++)
		{
			myData[i] *= aScalar;
		}
		return *this;
	}
	
	template<typename T>
	inline Vector3<T> Matrix3x3<T>::operator*(const Vector3<T>& aVector) const
	{
		Vector3<T> result;
		result.x = (myData[0] * aVector.x) + (myData[3] * aVector.y) + (myData[6] * aVector.z);
		result.y = (myData[1] * aVector.x) + (myData[4] * aVector.y) + (myData[7] * aVector.z);
		result.z = (myData[2] * aVector.x) + (myData[5] * aVector.y) + (myData[8] * aVector.z);
		return result;
	}
	
	//Returns the vector aVector multiplied by the scalar aScalar
	template <typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix3x3<T>& aMatrix)
	{
		return aMatrix * aVector;
	}
	
#pragma endregion Operators

#pragma region Member functions
	
	template<class T>
	inline std::string Matrix3x3<T>::ToString() const
	{
		std::string result;
		for (size_t y = 0; y < myMatrixSize; y++)
		{
			for (size_t x = 0; x < myMatrixSize; x++)
			{
				result += std::to_string(this->operator()(y, x)) + " ";
			}
			result += "\n";
		}
		return result;
	}
	
#pragma endregion Member functions
	
#pragma region Static functions
	
	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundX(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			T(1), 0, 0,
			0, cos, sin,
			0, -sin, cos
		};
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundY(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			cos, 0, -sin,
			0, T(1), 0,
			sin, 0, cos
		};
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::CreateRotationAroundZ(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			cos,  sin, 0,
			-sin, cos, 0,
			0,    0, T(1)
		};
	}

	template<typename T>
	inline Matrix3x3<T> Matrix3x3<T>::Transpose(const Matrix3x3<T>& aMatrixToTranspose)
	{
		Matrix3x3<T> result;
		// Flip row and column to get flipped along diagonal
		for (size_t row = 1; row <= myMatrixSize; row++)
		{
			for (size_t column = 1; column <= myMatrixSize; column++)
			{
				result(static_cast<int>(row), static_cast<int>(column)) = aMatrixToTranspose(static_cast<int>(column), static_cast<int>(row));
			}
		}
		return result;
	}

#pragma endregion Static functions
}

namespace CommonUtilities = CU;