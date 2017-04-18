#ifndef __Matrix4x3_H
#define __Matrix4x3_H

class Vector3;
class Matrix4x3
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	float tx, ty, tz;
	//���� ���� ʲô��
	/**
	@Params axis 
		1: x axis
		2: y axis
		3: z axis
	@Params Theta: the angle of rotate
	*/
	void SetRotate(int axis, float Theta);
	/**
	@param v: Vector3 ������Ϊ����ϵ��
	*/
	void SetupScale(const Vector3 &v);

	/**
	@param n: �õ�λ������ȷ�����������ͶӰƽ��
	*/
	void SetupProject(Vector3 &n);
	
	/**
	@axis �� 1 ����y�� 2 ����x�� 3 ����z��
	k: x=k y=k z=k ����������xyz�� ��������������
	*/
	void SetupReflect(int axis,float k);

	/**
	@Param v: �õ�λVectorȷ�������ƽ��
	*/
	void SetupReflect(Vector3 &n);
	/**
	@param axis: 1 x���ޱ仯 yz���б� 2 y���ޱ仯 xz�б� 3 z���ޱ仯 xy�б�
	@param s   : �б�ϵ��
	@param t   : �б�ϵ��
	*/
	void SetupShear(int axis, float s, float t);

	void zero_Translation();
	/**
	@param d: ͨ��������ֵƽ�ƾ���
	ԭ�������Ա任���󲻷����仯
	*/
	void SetTranslation(const Vector3 &d);
	/**
	@param d: ͬ�� �������Ծ����ɵ�λ����
	*/
	void SetupTranslation(const Vector3 &d);


};
//���� ���� ���
Matrix4x3 &operator *(const Matrix4x3& a, const Matrix4x3& b);
//���� ���� ���
Vector3 operator *(const Vector3& _V, const Matrix4x3& m);

Matrix4x3 &operator *=( Matrix4x3& a, const Matrix4x3& b);

Vector3 operator *=( Vector3& _V, const Matrix4x3& m);
/**
@param m : ������������ʽ
*/
float determinant(const Matrix4x3 &m);
/**
@param m: ����������
why
�������ǳ����� ���Գ���3d���Ա任�еĲ���
*/
Matrix4x3 inverse(const Matrix4x3 &m);
/**
@ m: ����ƽ�ƾ�����ΪVector3
*/
Vector3 getTranslation(const Matrix4x3 &m);

#endif // !__Matrix4x3_H
