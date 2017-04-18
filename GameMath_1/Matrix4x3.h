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
	//构造 析构 什么的
	/**
	@Params axis 
		1: x axis
		2: y axis
		3: z axis
	@Params Theta: the angle of rotate
	*/
	void SetRotate(int axis, float Theta);
	/**
	@param v: Vector3 用来作为缩放系数
	*/
	void SetupScale(const Vector3 &v);

	/**
	@param n: 用单位向量来确定任意轴向的投影平面
	*/
	void SetupProject(Vector3 &n);
	
	/**
	@axis ： 1 绕着y轴 2 绕着x轴 3 绕着z轴
	k: x=k y=k z=k 不再是绕着xyz轴 可以绕着任意轴
	*/
	void SetupReflect(int axis,float k);

	/**
	@Param v: 用单位Vector确定镜像的平面
	*/
	void SetupReflect(Vector3 &n);
	/**
	@param axis: 1 x轴无变化 yz轴切变 2 y轴无变化 xz切变 3 z轴无变化 xy切变
	@param s   : 切变系数
	@param t   : 切变系数
	*/
	void SetupShear(int axis, float s, float t);

	void zero_Translation();
	/**
	@param d: 通过向量赋值平移矩阵
	原来的线性变换矩阵不发生变化
	*/
	void SetTranslation(const Vector3 &d);
	/**
	@param d: 同理 但是线性矩阵变成单位矩阵
	*/
	void SetupTranslation(const Vector3 &d);


};
//矩阵 矩阵 相乘
Matrix4x3 &operator *(const Matrix4x3& a, const Matrix4x3& b);
//矩阵 向量 相乘
Vector3 operator *(const Vector3& _V, const Matrix4x3& m);

Matrix4x3 &operator *=( Matrix4x3& a, const Matrix4x3& b);

Vector3 operator *=( Vector3& _V, const Matrix4x3& m);
/**
@param m : 计算矩阵的行列式
*/
float determinant(const Matrix4x3 &m);
/**
@param m: 计算矩阵的逆
why
矩阵的逆非常有用 可以撤销3d线性变换中的操作
*/
Matrix4x3 inverse(const Matrix4x3 &m);
/**
@ m: 返回平移矩阵作为Vector3
*/
Vector3 getTranslation(const Matrix4x3 &m);

#endif // !__Matrix4x3_H
