#include "RotationMatrix.h"
#include "Vector3.h"	
#include "EulerAngles.h"
#include "MathUtility.h"
#include "Quaternion.h"
void RotationMatrix::identity()
{
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

Vector3 RotationMatrix::inertialToObject(Vector3 & v) const
{
	return Vector3(v.x*m11 + v.y*m21 + v.z*m31,
		          v.x*m12 + v.y*m22 + v.z*m32,
	              v.x*m13+v.y*m23+v.z*m33);
}

//�������  ��������������������� ��������ֱ��ת��
Vector3 RotationMatrix::objectToInertial(Vector3 & v) const
{
	return Vector3(v.x*m11+v.y*m12+v.z*m13,
			      v.x*m21+v.y*m22+v.z*m23,
				  v.x*m31+v.y*m32+v.z*m33);
}

void RotationMatrix::Setup(EulerAngles & orentation)
{
	//��������ϵת������������ϵ
	float sh, ch, sp, cp, sb, cb;
	sinCos(&sh, &ch, orentation.heading);
	sinCos(&sp, &cp, orentation.pitch);
	sinCos(&sb, &cb, orentation.bank);
	m11 = ch*cb + sh*sp*sb; m12 = -ch*sb + sh*sp*cb; m13 = sh*cp;
	m21 = sb*cp; m22 = cb*cp; m23 = -sp;
	m31 = -sh*cb + ch*sp*sb; m32 = sb*sh + ch*sp*cb; m33 = ch*cp;

}

void RotationMatrix::frominertialToObject(const Quaternion & q)
{
	//��������ϵ����������ϵ
	m11 = 1.0f - 2.0f*(q.y*q.y + q.z*q.z);
	m12 = 2.0f*(q.x*q.y + q.w*q.z);
	m13 = 2.0f*(q.x*q.z - q.w*q.y);

	m21 = 2.0f*(q.x*q.y - q.w*q.z);
	m22 = 1.0f - 2.0f*(q.x*q.x + q.z*q.z);
	m23 = 2.0f*(q.y*q.z + q.w*q.x);

	m31 = 2.0f*(q.x*q.z + q.w*q.y);
	m32 = 2.0f*(q.y*q.z - q.w*q.x);
	m33 = 1.0f - 2.0f*(q.x*q.x + q.y*q.y);

}

void RotationMatrix::fromobjectToInertial(const Quaternion & q)
{
	//��������ϵ �� ��������ϵ 
	//��Ϊ������������ ���Ծ������ ���Ǿ����ת�� ����ֱ��copy
	m11 = 1.0f - 2.0f*(q.y*q.y + q.z*q.z);
	m12 = 2.0f*(q.x*q.y - q.w*q.z);
	m13 = 2.0f*(q.x*q.z + q.w*q.y);

	m21 = 2.0f*(q.x*q.y + q.w*q.z);
	m22 = 1.0f - 2.0f*(q.x*q.x + q.z*q.z);
	m23 = 2.0f*(q.y*q.z - q.w*q.x);

	m31 = 2.0f*(q.x*q.z - q.w*q.y);
	m32 = 2.0f*(q.y*q.z + q.w*q.x);
	m33 = 1.0f - 2.0f*(q.x*q.x + q.y*q.y);
}
