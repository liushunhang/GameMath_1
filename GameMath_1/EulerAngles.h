#ifndef EulerAngles_H
#define EulerAngles_H
#include "Matrix4x3.h"
#include "RotationMatrix.h"
class Quaternion;
class EulerAngles
{
public:
	float heading;
	float pitch;
	float bank;
public:
	EulerAngles(){}
	EulerAngles(float hd,float pt,float bk):heading(hd),pitch(pt),bank(bk){}

	//����ת��Ϊŷ����
	//��������ϵ->��������ϵ
	void fromObjectToWorldMatrix(const Matrix4x3 &m);
	//��������ϵ->��������ϵ
	void fromWorldToObjectMatrix(const Matrix4x3 &m);
	//��������ϵ->��������ϵ ��������ת����
	void fromRotationMatrix(const RotationMatrix &m);
	//���ƽǷ�Χ
	void canonize();

	//����Ԫ��ת����ŷ���� ��������ϵ -�� ��������ϵ
	void fromObjectToInertialQuaternion(const Quaternion &q);

	//��������ϵ ת���� ��������ϵ ��Ϊ�����෴�Ĳ��� ��Ԫ���෴�Ĳ������ǹ���
	void fromInertialToObjectQuaternion(const Quaternion &q);
};
#endif // !EulerAngles_H
