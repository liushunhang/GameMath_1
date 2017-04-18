#include "EulerAngles.h"
#include "MathUtility.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"
#include "Quaternion.h"
void EulerAngles::fromObjectToWorldMatrix(const Matrix4x3 &m)
{
	float sp = -m.m32; //sin pitch
	//����������
	if (fabs(sp > 0.99999f))
	{
		pitch = kPiOver2*sp;
		bank = 0.0f;
		heading = atan2(m.m23, m.m11);
	}
	//������������
	else
	{
		heading = atan2(m.m31, m.m33);
		pitch = asin(sp);
		bank = atan2(m.m12, m.m22);
	}

}

void EulerAngles::fromWorldToObjectMatrix(const Matrix4x3 & m)
{
	//����� ��Ϊ����������������� ����ֱ�Ӽ���ת�þ��������
	float sp = -m.m23;
	//����
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
	//����
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

	//����������
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
	//������Ԫ��ת����ŷ���ǵĹ�ʽ 
	float sp = -2.0f*(q.y*q.z - q.w*q.x);
	//���������� cosp=0
	if (fabs(sp) > 0.99999f)
	{
		pitch = kPiOver2*sp;//����
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
	//������Ԫ��ת����ŷ���ǵĹ�ʽ 
	float sp = -2.0f*(q.y*q.z + q.w*q.x);
	//���������� cosp=0
	if (fabs(sp) > 0.99999f)
	{
		pitch = kPiOver2*sp;//����
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
