#include "Matrix4x3.h"
#include "Vector3.h"
#include "MathUtility.h"
#include "RotationMatrix.h"
#include "EulerAngles.h"
#include<iostream>
using namespace std;
/**
@param n: if n < 0.00001 return 0 or return n
*/
float to_zero(float n)
{
	return ((abs(n) < 0.00001) ? 0 : n); 
}
void Print_m(const Matrix4x3& m)
{
	cout << to_zero(m.m11) << "\t" << to_zero(m.m12) << "\t" << to_zero(m.m13) << endl;
	cout << to_zero(m.m21) << "\t" << to_zero(m.m22) << "\t" << to_zero(m.m23) << endl;
	cout << to_zero(m.m31) << "\t" << to_zero(m.m32) << "\t" << to_zero(m.m33) << endl;

}
void Print_V(const Vector3& v)
{
	cout << "[" << to_zero(v.x) << "," << to_zero(v.y) << "," << to_zero(v.z) << "]" << endl;
}
/**
@param v ƽ���ϵĵ�
@param n ƽ���ϵ�ĸ���
*/
Vector3 ComputeBestFitNormal(const Vector3 v[], int n)
{
	Vector3 result=KZeroVector;
	//�����һ���㿪ʼ
	const Vector3 *p = &v[n - 1];
	for (int i = 0; i < n; ++i)
	{
		const Vector3 *c = &v[i];
		result.x += (p->z + c->z)*(p->y - c->y);
		result.y += (p->x + c->x)*(p->z - c->z);
		result.z += (p->y + c->y)*(p->x - c->x);
		p = c;
	}
	result.normalize();//�淶��
	return result;
}
int main()
{
	//Matrix4x3 a, b ,c;
	//a.m11 = 1; a.m12 = -5; a.m13 = 3;
	//a.m21 = 0; a.m22 = -2; a.m23 = 6;
	//a.m31 = 7; a.m32 = 2; a.m33 = -4;

	//b.m11 = -8; b.m12 = 6; b.m13 = 1;
	//b.m21 = 7; b.m22 = 0; b.m23 = -3;
	//b.m31 = 2; b.m32 = 4; b.m33 = 5;
	//c = a*b;

	//Matrix4x3 m;
	//m.m11 = -2; m.m12 = 0; m.m13 = 3;
	//m.m21 = 5; m.m22 = 7; m.m23 = -6;
	//m.m31 = 1; m.m32 = -4; m.m33 = 2;

	//Vector3 v(3, -1, 4);
	//v *= m; //�� r=v*mһ���Ľ��

	//Vector3 v2(10, 0, 0),r;
	//Print_V(v2);
	//Matrix4x3 M;
	//M.SetRotate(3, kPiOver2); //��z����ת90 ���Ӧ���� 0 10 0 ���ȷʵ��0 10 0
	//cout << endl;
	//Print_m(M);
	//cout << endl;
	//r = v2*M;

	//Print_V(r);

	//cout << "��������" << endl;
	//Vector3 V3(10, 20, 30),V4;
	//Vector3 S(1, 2, 3);
	//Matrix4x3 Ms;
	//Ms.SetupScale(S);

	//V4 = V3* Ms;
	//Print_V(V4);

	////���Ա任 ����ͶӰ
	//Vector3 n(0, 0, 1),R; //�� x y ƽ��ͶӰ
	//
	//Matrix4x3 Mp;
	//Mp.SetupProject(n);
	//R = V3 * Mp;
	//cout << "���� ͶӰ xyƽ��" << endl;
	//Print_V(R);
	////Print_m(c);
	//cout << "���Ա任 ����" << endl;
	//Vector3 n(0, 0, 1), b; //xy��Ϊ���� z�ᷢ���仯�� ��λ����
	//Vector3 v(10, 20, 30);
	//Print_V(v);
	//Matrix4x3 m;
	//m.SetupReflect(n);
	//b = v * m;
	//Print_V(b);
	//cout << "���Ա任 �б�" << endl;
	//m.SetupShear(1, 1, 2);
	//b = v*m;
	//Print_V(b);
	/*cout << "���������ʽ" << endl;
	Matrix4x3 m;
	m.m11 = 1; m.m12 = 6; m.m13 = 2;
	m.m21 = 3; m.m22 = 8; m.m23 = 9;
	m.m31 = 4; m.m32 = 5; m.m33 = 7;
	float Mdeter = determinant(m);
	cout << Mdeter << endl;*/

	//cout << "�������" << endl;
	//Matrix4x3 m;
	//m.m11 = -4; m.m12 = -3; m.m13 = 3;
	//m.m21 = 0; m.m22 = 2; m.m23 = -2;
	//m.m31 = 1; m.m32 = 4; m.m33 = -1;
	//Matrix4x3 r=inverse(m); //m�������
	//Print_m(r);

	//Matrix4x3 a = m*r;//��λ����

	//Print_m(a);
	
	Vector3 v(10, 20, 30);
	RotationMatrix m; //����y����ת30 ��������ϵ ת������������ϵ
	/*m.m11 = 0.866f; m.m12 = 0.0f; m.m13 = -0.5f;
	m.m21 = 0.0f; m.m22 = 1.0f; m.m23 = 0.0f;
	m.m31 = 0.5f; m.m32 = 0.0f; m.m33 = 0.866f;*/
	m.Setup(EulerAngles(30 * kPi / 180, 0, 0)); //ŷ����ת��������
	Vector3 v2 = m.inertialToObject(v);
	Print_V(v2);

	 v2 = m.objectToInertial(v);

	Print_V(v2);


	getchar();
	return 0;
}