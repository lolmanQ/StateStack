#pragma once
#include "Vector4.hpp"

namespace CU
{
	template<class T>
	class Matrix4x4
	{
	public:
		// Creates the identity matrix.
		Matrix4x4<T>();
		
		// Copy Constructor.
		Matrix4x4<T>(const Matrix4x4<T>& aMatrix);
		
		// Initializer list constructor (for teachers: used to just make rotation around axis creation easier)
		Matrix4x4<T>(std::initializer_list<T> aList);

		// () operator for accessing element (row, column) for read/write or read, respectively.
		T& operator()(const int aRow, const int aColumn);
		const T& operator()(const int aRow, const int aColumn) const;

		// boolean operators
		bool operator==(const Matrix4x4<T>& aMatrix) const;
		bool operator!=(const Matrix4x4<T>& aMatrix) const;

		// Math operators
		Matrix4x4<T> operator+(const Matrix4x4<T>& aMatrix) const;
		Matrix4x4<T> operator-(const Matrix4x4<T>& aMatrix) const;
		Matrix4x4<T> operator*(const Matrix4x4<T>& aMatrix) const;
		Matrix4x4<T> operator*(const T& aScalar) const;
		Vector4<T> operator*(const Vector4<T>& aVector) const;
		Matrix4x4<T>& operator+=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>& operator-=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>& operator*=(const Matrix4x4<T>& aMatrix);
		Matrix4x4<T>& operator*=(const T& aScalar);

		// get/set for rows and columns for ease of use
		Vector4<T> GetRow(const int& aRowIndex) const;
		Vector4<T> GetColumn(const int& aColumnIndex) const;

		void SetRow(const int& aRowIndex, const Vector4<T>& aVector);
		void SetColumn(const int& aColumnIndex, const Vector4<T>& aVector);

		std::string ToString() const;

		// Static functions for creating rotation matrices.
		static Matrix4x4<T> CreateRotationAroundX(const T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundY(const T aAngleInRadians);
		static Matrix4x4<T> CreateRotationAroundZ(const T aAngleInRadians);

		// Static function for creating a transpose of a matrix.
		static Matrix4x4<T> Transpose(const Matrix4x4<T>& aMatrixToTranspose);
		static Matrix4x4<T> GetFastInverse(const Matrix4x4<T>& aTransform);

	private:
		static const size_t myMatrixSize = 4;
		static const size_t myLength = myMatrixSize * myMatrixSize;
		T myData[myLength]; // Stores values of the matrix. (For teachers: I decided to go with c style array for more power to use stuff like memcopy)
	};

	using Matrix4x4f = Matrix4x4<float>;

#pragma region Constructors

	template<class T>
	inline Matrix4x4<T>::Matrix4x4()
	{
		std::memset(myData, 0, myLength * sizeof(T)); // Sets all array values to 0
		myData[0] = 1;
		myData[5] = 1;
		myData[10] = 1;
		myData[15] = 1;
	}
	
	template <typename T>
	Matrix4x4<T>::Matrix4x4(const Matrix4x4<T>& aMatrix)
	{
		std::memcpy(myData, aMatrix.myData, myLength * sizeof(T));
	}

	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(std::initializer_list<T> aList)
	{
		assert(aList.size() <= myLength && "Initializer list is to long.");
		std::memset(myData, 0, myLength * sizeof(T)); // starts matrix at 0 so if init list is not long enough then rest is 0
		std::memcpy(myData, aList.begin(), aList.size() * sizeof(T));
	}
	
#pragma endregion Constructors

#pragma region Operators

	template<typename T>
	inline T& Matrix4x4<T>::operator()(const int aRow, const int aColumn)
	{
		assert(aRow > 0 && aRow <= myMatrixSize && aColumn > 0 && aColumn <= myMatrixSize && "Indexes out of bounds");
		return myData[(aRow - 1) * 4 + (aColumn - 1)];
	}

	template<typename T>
	inline const T& Matrix4x4<T>::operator()(const int aRow, const int aColumn) const
	{
		assert(aRow > 0 && aRow <= myMatrixSize && aColumn > 0 && aColumn <= myMatrixSize && "Indexes out of bounds");
		return myData[(aRow - 1) * 4 + (aColumn - 1)];
	}

	template<typename T>
	inline bool Matrix4x4<T>::operator==(const Matrix4x4<T>& aMatrix) const
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
	inline bool Matrix4x4<T>::operator!=(const Matrix4x4<T>& aMatrix) const
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
	inline Matrix4x4<T> Matrix4x4<T>::operator+(const Matrix4x4<T>& aMatrix) const
	{
		// using += allows for reuse of code
		Matrix4x4<T> result(*this);
		return result += aMatrix;
	}

	template<typename T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator+=(const Matrix4x4<T>& aMatrix)
	{
		for (size_t i = 0; i < myLength; i++)
		{
			myData[i] += aMatrix.myData[i];
		}
		return *this;
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator-(const Matrix4x4<T>& aMatrix) const
	{
		// using -= allows for reuse of code
		Matrix4x4<T> result(*this);
		return result -= aMatrix;
	}

	template<typename T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator-=(const Matrix4x4<T>& aMatrix)
	{
		for (size_t i = 0; i < myLength; i++)
		{
			myData[i] -= aMatrix.myData[i];
		}
		return *this;
	}
	
	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const Matrix4x4<T>& aMatrix) const
	{
		// using -= allows for reuse of code
		Matrix4x4<T> result(*this);
		return result *= aMatrix;
	}

	template<typename T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator*=(const Matrix4x4<T>& aMatrix)
	{
		Matrix4x4<T> result;
		for (int i = 1; i <= 4; i++)
		{
			for (int j = 1; j <= 4; j++)
			{
				T product(0);
				for (int k = 1; k <= 4; k++)
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
	inline Matrix4x4<T> Matrix4x4<T>::operator*(const T& aScalar) const
	{
		// using *= allows for reuse of code
		Matrix4x4<T> result(*this);
		return result *= aScalar;
	}
	
	template<typename T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator*=(const T& aScalar)
	{
		for (int i = 0; i < myLength; i++)
		{
			myData[i] *= aScalar;
		}
		return *this;
	}

	template<typename T>
	inline Vector4<T> Matrix4x4<T>::operator*(const Vector4<T>& aVector) const
	{
		Vector4<T> result;
		result.x = (myData[0] * aVector.x) + (myData[4] * aVector.y) + (myData[8] * aVector.z) + (myData[12] * aVector.w);
		result.y = (myData[1] * aVector.x) + (myData[5] * aVector.y) + (myData[9] * aVector.z) + (myData[13] * aVector.w);
		result.z = (myData[2] * aVector.x) + (myData[6] * aVector.y) + (myData[10] * aVector.z) + (myData[14] * aVector.w);
		result.w = (myData[3] * aVector.x) + (myData[7] * aVector.y) + (myData[11] * aVector.z) + (myData[15] * aVector.w);
		return result;
	}
	
	//Returns the vector aVector multiplied by the scalar aScalar
	template <typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix4x4<T>& aMatrix)
	{
		return aMatrix * aVector;
	}
	
#pragma endregion Operators
	
#pragma region Member functions

	template<class T>
	inline Vector4<T> Matrix4x4<T>::GetRow(const int& aRowIndex) const
	{
		assert(aRowIndex > 0 && aRowIndex <= myMatrixSize && "Index out of bounds");
		return Vector4<T>(myData[(aRowIndex - 1) * 4 + 0], myData[(aRowIndex - 1) * 4 + 1], myData[(aRowIndex - 1) * 4 + 2], myData[(aRowIndex - 1) * 4 + 3]);
	}

	template<class T>
	inline Vector4<T> Matrix4x4<T>::GetColumn(const int& aColumnIndex) const
	{
		assert(aColumnIndex > 0 && aColumnIndex <= myMatrixSize && "Index out of bounds");
		int index = aColumnIndex - 1;
		return Vector4<T>(myData[index], myData[4 + index], myData[8 + index], myData[12 + index]);
	}

	template<class T>
	inline void Matrix4x4<T>::SetRow(const int& aRowIndex, const Vector4<T>& aVector)
	{
		assert(aRowIndex > 0 && aRowIndex <= myMatrixSize && "Index out of bounds");
		myData[(aRowIndex - 1) * 4 + 0] = aVector.x;
		myData[(aRowIndex - 1) * 4 + 1] = aVector.y;
		myData[(aRowIndex - 1) * 4 + 2] = aVector.z;
		myData[(aRowIndex - 1) * 4 + 3] = aVector.w;
	}

	template<class T>
	inline void Matrix4x4<T>::SetColumn(const int& aColumnIndex, const Vector4<T>& aVector)
	{
		assert(aColumnIndex > 0 && aColumnIndex <= myMatrixSize && "Index out of bounds");
		int index = aColumnIndex - 1;
		myData[index] = aVector.x;
		myData[4 + index] = aVector.y;
		myData[8 + index] = aVector.z;
		myData[12 + index] = aVector.w;
	}

	template<class T>
	inline std::string Matrix4x4<T>::ToString() const
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
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundX(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			T(1), 0,  0,  0,
			0,  cos, sin, 0,
			0, -sin, cos, 0,
			0,  0,  0,  T(1)
		};
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundY(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			cos, 0, -sin, 0,
			0, T(1), 0,   0,
			sin, 0,  cos, 0,
			0,   0,  0, T(1)
		};
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::CreateRotationAroundZ(const T aAngleInRadians)
	{
		const T cos = std::cos(aAngleInRadians);
		const T sin = std::sin(aAngleInRadians);
		return
		{
			cos,  sin, 0, 0,
			-sin, cos, 0, 0,
			0,    0, T(1),0,
			0,    0, 0, T(1)
		};
	}

	template<typename T>
	inline Matrix4x4<T> Matrix4x4<T>::Transpose(const Matrix4x4<T>& aMatrixToTranspose)
	{
		Matrix4x4<T> result;
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

	template<class T>
	inline Matrix4x4<T> Matrix4x4<T>::GetFastInverse(const Matrix4x4<T>& aTransform)
	{
		Matrix4x4<T> result = Matrix4x4<T>::Transpose(aTransform);
		result.SetColumn(4, { T(0), T(0), T(0), T(1) });
		
		Vector4<T> translation = -aTransform.GetRow(4);
		translation.w = T(1);
		
		translation = translation * result;
		result.SetRow(4, translation);

		return result;
	}

#pragma endregion Static functions
}

namespace CommonUtilities = CU;