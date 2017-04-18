#include "Matrix4x3.h"
#include "Vector3.h"
#include <assert.h>
#include "MathUtility.h"
Matrix4x3 & operator*(const Matrix4x3 & a, const Matrix4x3 & b)
{
	Matrix4x3 r;
	r.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31;
	r.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32;
	r.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33;

	r.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31;
	r.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32;
	r.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33;

	r.m31 = a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31;
	r.m32 = a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32;
	r.m33 = a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33;
	//平移部分
	r.tx = a.tx*b.m11 + a.ty*b.m21 + a.tz*b.m31 + b.tx;
	r.ty = a.tx*b.m12 + a.ty*b.m22 + a.tz*b.m32 + b.ty;
	r.tz = a.tx*b.m13 + a.ty*b.m32 + a.tz*b.m33 + b.tz;
	return r;

}

Vector3 operator*(const Vector3 & _V, const Matrix4x3 & m)
{
	return Vector3(_V.x*m.m11 + _V.y*m.m21 + _V.z*m.m31,

		_V.x*m.m12 + _V.y*m.m22 + _V.z*m.m32,

		_V.x*m.m13 + _V.y*m.m23 + _V.z*m.m33);
	//无需涉及平移部分
}

Matrix4x3 & operator*=( Matrix4x3 & a, const Matrix4x3 & b)
{
	return a = a*b;
}

Vector3 operator*=( Vector3 & _V, const Matrix4x3 & m)
{
	return _V = _V*m;
}

float determinant(const Matrix4x3 & m)
{
	return m.m11*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m31 - m.m21*m.m33) + m.m13*(m.m21*m.m32 - m.m22*m.m31);
}

Matrix4x3 inverse(const Matrix4x3 & m)
{
	Matrix4x3 r;
	float det = determinant(m);
	assert(fabs(det) > 0.00001f); //只有非奇异矩阵才有逆
	float OneOverDet = 1 / det;
	r.m11 = (m.m22*m.m33 - m.m23*m.m32)*OneOverDet;
	r.m12 = (m.m13*m.m32 - m.m12*m.m33)*OneOverDet;
	r.m13 = (m.m12*m.m23 - m.m13*m.m22)*OneOverDet;

	r.m21 = (m.m23*m.m31 - m.m21*m.m33)*OneOverDet;
	r.m22 = (m.m11*m.m33 - m.m13*m.m31)*OneOverDet;
	r.m23 = (m.m13*m.m21 - m.m11*m.m23)*OneOverDet;

	r.m31 = (m.m21*m.m32 - m.m22*m.m31)*OneOverDet;
	r.m32 = (m.m12*m.m31 - m.m11*m.m32)*OneOverDet;
	r.m33 = (m.m11*m.m22 - m.m12*m.m21)*OneOverDet;
	return r;
}

Vector3 getTranslation(const Matrix4x3 & m)
{
	return Vector3(m.tx,m.ty,m.tz);
}

void Matrix4x3::SetRotate(int axis, float Theta)
{
	float s, c;
	sinCos(&s, &c, Theta);
	switch (axis)
	{
	case 1:  //x轴旋转矩阵
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;   //1.0  0.0  0.0
		m21 = 0.0f; m22 = c; m23 = s;		   // 0.0 cos  sin
		m31 = 0.0f; m32 = -s; m23 = c;	   // 0.0 -sin cos
		break;
	case 2:  //y轴旋转矩阵
		m11 = c; m12 = 0.0f; m13 = -s;	   // cos 0.0 -sin
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;  // 0.0 1.0 0.0
		m31 = s; m32 = 0.0f; m33 = c;		   // sin 0.0 cos
		break;
	case 3:  //z轴旋转矩阵
		m11 = c; m12 = s; m13 = 0.0f;		   // cos sin 0.0
		m21 = -s; m22 = c; m23 = 0.0f;	   // -sin cos 0.0
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;  // 0.0 0.0 1.0
		break;
	default:
		assert(false);
		break;
	}
	tx = ty = tz = 0.0f;
}

void Matrix4x3::SetupScale(const Vector3 & v)
{
	m11 = v.x; m12 = 0.0f; m13 = 0.0f;  //缩放矩阵
	m21 = 0.0f; m22 = v.y; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = v.z;
}

void Matrix4x3::SetupProject(Vector3 &n)
{
	assert(fabs(n*n - 1.0f) < 0.00001); //n是否是单位向量
	m11 = 1 - n.x*n.x;				//正交投影矩阵 任意空间平面
	m22 = 1 - n.y*n.y;
	m33 = 1 - n.z*n.z;

	m12 = m21 = -n.x*n.y;
	m13 = m31 = -n.x*n.z;
	m23 = m32 = -n.z*n.y;
}

void Matrix4x3::SetupReflect(int axis,float k)
{
	switch (axis)
	{
	case 1:
		m11 = -1.0f; m12 = 0.0f; m13 = 0.0f;  //绕着y轴的镜像矩阵
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		tx = 2.0f*k;
		ty = 0.0f;
		tz = 0.0f;
		break;
	case 2:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;  //绕着x轴的镜像矩阵
		m21 = 0.0f; m22 = -1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		tx = 0.0f;
		ty = 2.0f*k;
		tz = 0.0f;
		break;
	case 3:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f; //绕着z轴的镜像矩阵
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = -1.0f;
		tx = 0.0f;
		ty = 0.0f;
		tz = 2.0f*k;
		break;
	default:
		assert(false);
	}
}

void Matrix4x3::SetupReflect(Vector3 & n)
{
	assert((fabs(n*n - 1.0f) < 0.00001f)); //n是否为单位向量
	float ax = -2.0f*n.x;
	float ay = -2.0f*n.y;
	float az = -2.0f*n.z;

	m11 = 1.0f + ax*n.x;
	m22 = 1.0f + ay*n.y;
	m33 = 1.0f + az*n.z;

	m12 = m21 = ax*n.y;
	m13 = m31 = ax*n.z;
	m23 = m32 = ay*n.z;

	tx = ty = tz = 0.0f;
}

void Matrix4x3::SetupShear(int axis, float s, float t)
{
	switch (axis)
	{
	case 1:
		m11 = 1.0f; m12 = s; m13 = t;       //yz切变
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 2:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;       //xz切变
		m21 = s;    m22 = 1.0f; m23 = t;
		m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
		break;
	case 3:
		m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;       //xy切变
		m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
		m31 = s;   m32 = t; m33 = 1.0f;
		break;
	default:
		assert(false);
	}
	tx = ty = tz = 0.0f;
}

void Matrix4x3::zero_Translation()
{
	tx = ty = tz = 0.0f;
}

void Matrix4x3::SetTranslation(const Vector3 & d)
{
	tx = d.x;
	ty = d.y;
	tz = d.z;
}

void Matrix4x3::SetupTranslation(const Vector3 & d)
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
	tx = d.x; ty = d.y; tz = d.z;
}
