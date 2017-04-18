#ifndef Vector3_H
#define Vector3_H
#include <cmath>

class Vector3
{
public:
	float x, y, z;
public:
	//copy
	Vector3(const Vector3& v) :x(v.x), y(v.y), z(v.z) {	}
	//default
	Vector3() {	}
	//normal
	/**
	@Params
	nx , ny ,nz
	set the default values
	*/
	Vector3(float nx, float ny, float nz) :x(nx), y(ny), z(nz) {	}

public:
	//set the vector3 to zero vector

	void Zero()
	{
		x = y = z = 0.0f;
	}

	//set the object of the vector3 to the nagative vector
	Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	//�����ı����˳���
	//������������� ���� 
	Vector3 operator *(float a) const
	{
		return Vector3(x*a, y*a, z*a);
	}
	//��д
	Vector3 operator *=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}
	Vector3 operator /(float a) const
	{
		//�������������Ƚ���
		float OneOverA = 1.0f / a;
		return Vector3(x*OneOverA, y*OneOverA, z*OneOverA);
	}
	Vector3 operator /=(float a)
	{
		float OneOverA = 1.0f / a;
		x *= OneOverA;
		y *= OneOverA;
		z *= OneOverA;
		return *this;
	}
	//�����ļӼ�
	Vector3 operator +(const Vector3& _V)
	{
		return Vector3(x + _V.x, y + _V.y, z + _V.z);
	}
	Vector3 operator -(const Vector3& _V)
	{
		return Vector3(x - _V.x, y - _V.y, z - _V.z);
	}
	Vector3 operator +=(const Vector3& _V)
	{
		x += _V.x;
		y += _V.y;
		z += _V.z;
		return *this;
	}
	Vector3 operator -=(const Vector3& _V)
	{
		x -= _V.x;
		y -= _V.y;
		z -= _V.z;
		return *this;
	}
	//��׼������
	void normalize()
	{
		float magSq = x*x + y*y + z*z;
		if (magSq > 0.0f)
		{
			float OneOverMag = 1.0f / sqrt(magSq);
			x *= OneOverMag;
			y *= OneOverMag;
			z *= OneOverMag;
		}
	}
	//������������ �õ����Ǳ��� ������*��
	float operator *(const Vector3& _V)
	{
		return x*_V.x + y*_V.y + z*_V.z;
	}

	

};

//get the length of vector3
inline float VectorMag(const Vector3& _Vector)
{
	return sqrt(_Vector.x * _Vector.x + _Vector.y * _Vector.y + _Vector.z * _Vector.z);
}
//������x������ʱ�� ���������������
inline Vector3 operator *(float a, const Vector3& _V)
{
	return Vector3(a*_V.x, a*_V.y, a*_V.z);
}

inline float Distance(Vector3& _V1, const Vector3& _V2)
{
	/*float dx = _V1.x - _V2.x;
	float dy = _V1.y - _V2.y;
	float dz = _V1.z - _V2.z;
	return sqrt(dx*dx + dy*dy + dz*dz);*/
	return VectorMag(_V1 - _V2);
}
//������x�� �õ�������ԭ�����������໥��ֱ������
//��������x�˹�ʽ
inline Vector3 CrossProduct(const Vector3& _V1, const Vector3& _V2)
{
	return Vector3(

		_V1.y*_V2.z - _V1.z*_V2.y,
		_V1.x*_V2.z - _V1.z*_V2.x,
		_V1.x*_V2.y - _V1.y*_V2.x
	);
}

extern const Vector3 KZeroVector;

#endif
