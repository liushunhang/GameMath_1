#ifndef ROTATION_MATRIX_H
#define ROTATION_MATRIX_H
class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

public:
	void identity(); //��λ����
	Vector3 inertialToObject(Vector3 &v) const;
	Vector3 objectToInertial(Vector3 &v) const;

	//ŷ���� ת��������  
	void Setup(EulerAngles &orentation);

	//��Ԫ��ת�������� ��������ϵ �� ��������ϵ��ת��
	void frominertialToObject(const Quaternion &q);
	void fromobjectToInertial(const Quaternion &q);

};
#endif // !ROTATION_MATRIX_H

