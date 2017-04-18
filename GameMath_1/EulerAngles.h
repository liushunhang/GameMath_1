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

	//矩阵转换为欧拉角
	//物体坐标系->惯性坐标系
	void fromObjectToWorldMatrix(const Matrix4x3 &m);
	//惯性坐标系->物体坐标系
	void fromWorldToObjectMatrix(const Matrix4x3 &m);
	//惯性坐标系->物体坐标系 参数是旋转矩阵
	void fromRotationMatrix(const RotationMatrix &m);
	//限制角范围
	void canonize();

	//将四元数转换成欧拉角 物体坐标系 -》 惯性坐标系
	void fromObjectToInertialQuaternion(const Quaternion &q);

	//惯性坐标系 转换到 物体坐标系 因为这是相反的操作 四元数相反的操作就是共轭
	void fromInertialToObjectQuaternion(const Quaternion &q);
};
#endif // !EulerAngles_H
