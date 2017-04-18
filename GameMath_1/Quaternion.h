#ifndef Quaternion_H
#define Quaternion_H
//四元数类
class EulerAngles;
class Vector3;
class RotationMatrix;
class Quaternion
{
public:
	float w, x, y, z;
	void identity() { w = 1.0f; x = y = z = 0.0f; }

	//绕着 x y z 轴旋转
	void SetToRotateAboutX(float theta);
	void SetToRotateAboutY(float theta);
	void SetToRotateAboutZ(float theta);

	//绕着任意轴旋转
	void SetToRotateAboutAxis(const Vector3 &axis, float theta);

	//获取旋转角
	float getRotationAngle() const;
	// 获取旋转轴
	Vector3 getRotationAxis() const;

	//四元数运算编程
	Quaternion operator *(const Quaternion &a) const;
	Quaternion operator *=(const Quaternion &a);

	//四元数规范化 对于float数据来说 进行大量计算之后 数据存在误差
	void normalize();

	//将旋转矩阵转化为四元数
	void fromRotationMatrix(const RotationMatrix &m);

	//欧拉角转换成四元数  物体坐标系 转换到 惯性坐标系
	void SetToRotateObjectToinertial(const EulerAngles &orentation);
	//欧拉角转换成四元数 惯性坐标系转换到物体坐标系
	void SetToRotateInertialToObject(const EulerAngles &orentation);
};
//全局单位四元数常量
//extern const Quaternion kQuaternionIdentity = {1.0f,0.0f,0.0f,0.0f};
//四元数点乘
extern float dotProduct(const Quaternion &a, const Quaternion &b);

//四元数的共轭
extern Quaternion conjugate(const Quaternion &q);

//计算四元数的幂
extern Quaternion pow(const Quaternion &q, float exponent);
//四元数插值计算
extern Quaternion slerp(const Quaternion &q0, const Quaternion &q1, float t);
#endif // !Quaternion_H
