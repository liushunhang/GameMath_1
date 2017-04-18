#ifndef Quaternion_H
#define Quaternion_H
//��Ԫ����
class EulerAngles;
class Vector3;
class RotationMatrix;
class Quaternion
{
public:
	float w, x, y, z;
	void identity() { w = 1.0f; x = y = z = 0.0f; }

	//���� x y z ����ת
	void SetToRotateAboutX(float theta);
	void SetToRotateAboutY(float theta);
	void SetToRotateAboutZ(float theta);

	//������������ת
	void SetToRotateAboutAxis(const Vector3 &axis, float theta);

	//��ȡ��ת��
	float getRotationAngle() const;
	// ��ȡ��ת��
	Vector3 getRotationAxis() const;

	//��Ԫ��������
	Quaternion operator *(const Quaternion &a) const;
	Quaternion operator *=(const Quaternion &a);

	//��Ԫ���淶�� ����float������˵ ���д�������֮�� ���ݴ������
	void normalize();

	//����ת����ת��Ϊ��Ԫ��
	void fromRotationMatrix(const RotationMatrix &m);

	//ŷ����ת������Ԫ��  ��������ϵ ת���� ��������ϵ
	void SetToRotateObjectToinertial(const EulerAngles &orentation);
	//ŷ����ת������Ԫ�� ��������ϵת������������ϵ
	void SetToRotateInertialToObject(const EulerAngles &orentation);
};
//ȫ�ֵ�λ��Ԫ������
//extern const Quaternion kQuaternionIdentity = {1.0f,0.0f,0.0f,0.0f};
//��Ԫ�����
extern float dotProduct(const Quaternion &a, const Quaternion &b);

//��Ԫ���Ĺ���
extern Quaternion conjugate(const Quaternion &q);

//������Ԫ������
extern Quaternion pow(const Quaternion &q, float exponent);
//��Ԫ����ֵ����
extern Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);
#endif // !Quaternion_H
