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
	void identity(); //单位矩阵
	Vector3 inertialToObject(Vector3 &v) const;
	Vector3 objectToInertial(Vector3 &v) const;

	//欧拉角 转换到矩阵  
	void Setup(EulerAngles &orentation);

	//四元数转化到矩阵 惯性坐标系 到 物体坐标系的转化
	void frominertialToObject(const Quaternion &q);
	void fromobjectToInertial(const Quaternion &q);

};
#endif // !ROTATION_MATRIX_H

