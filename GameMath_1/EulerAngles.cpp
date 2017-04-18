#include "EulerAngles.h"
#include "MathUtility.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"
#include "Quaternion.h"
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
	float sp = -m.m32; //sin pitch
	//处理万向锁
	if (fabs(sp > 0.99999f))
	{
		pitch = kPiOver2*sp;
		bank = 0.0f;
		heading = atan2(m.m23, m.m11);
	}
	//不存在万向锁
	else
	{
		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}

}

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 & m)
{
	//逆矩阵 因为这个矩阵是正交矩阵 所以直接计算转置矩阵就行了
	float sp = -m.m23;
	//处理
	if (fabs(sp) > 0.99999f)
	{
		pitch = kPiOver2*sp;
		bank = 0.0f;
		heading = atan2(m.m31, m.m11);
	}
	else
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

void EulerAngles::fromRotationMatrix(const RotationMatrix & m)
{
	float sp = -m.m23;
	//处理
	if (fabs(sp) > 0.99999f)
	{
		pitch = kPiOver2*sp;
		bank = 0.0f;
		heading = atan2(m.m31, m.m11);
	}
	else
	{
		heading = atan2(m.m13, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m21, m.m22);
	}
}

void EulerAngles::canonize()
{
	pitch = wrapPi(pitch);
	if (pitch < -kPiOver2)
	{
		pitch = -kPi - pitch;
		heading += kPi;
		bank += kPi;
	}
	else if (pitch > kPiOver2)
	{
		pitch = kPi - pitch;
		heading += kPi;
		bank += kPi;
	}

	//处理万向锁
	if (fabs(pitch) > kPiOver2 - 1e-4)
	{
		heading += bank;
		bank = 0.0f;
	}
	else
	{
		bank = wrapPi(bank);

	}
	heading = wrapPi(heading);
}

void EulerAngles::fromObjectToInertialQuaternion(const Quaternion & q)
{
	//根据四元数转换乘欧拉角的公式 
	float sp = -2.0f*(q.y*q.z - q.w*q.x);
	//处理万向锁 cosp=0
	if (fabs(sp) > 0.99999f)
	{
		pitch = kPiOver2*sp;//正负
		heading = atan2(-q.x*q.z + q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sp);
		heading = atan2(q.x*q.z + q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y + q.w*q.z, 0.5 - q.x*q.x - q.z*q.z);
	}
}

void EulerAngles::fromInertialToObjectQuaternion(const Quaternion & q)
{
	//根据四元数转换乘欧拉角的公式 
	float sp = -2.0f*(q.y*q.z + q.w*q.x);
	//处理万向锁 cosp=0
	if (fabs(sp) > 0.99999f)
	{
		pitch = kPiOver2*sp;//正负
		heading = atan2(-q.x*q.z - q.w*q.y, 0.5f - q.y*q.y - q.z*q.z);
		bank = 0.0f;
	}
	else
	{
		pitch = asin(sp);
		heading = atan2(q.x*q.z - q.w*q.y, 0.5f - q.x*q.x - q.y*q.y);
		bank = atan2(q.x*q.y - q.w*q.z, 0.5 - q.x*q.x - q.z*q.z);
	}
}
