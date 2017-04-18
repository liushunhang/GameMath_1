#include "Quaternion.h"
#include "MathUtility.h"
#include "Vector3.h"
#include "RotationMatrix.h"
#include "EulerAngles.h"
#include <assert.h>
//根据四元数公式 求旋转
class RotationMatrix;
void Quaternion::SetToRotateAboutX(float theta)
{
	float thetaOver2 = theta*0.5f;
	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::SetToRotateAboutY(float theta)
{
	float thetaOver2 = theta*0.5f;
	w = cos(thetaOver2);
	y = sin(thetaOver2);
	x = 0.0f;
	z = 0.0f;
}

void Quaternion::SetToRotateAboutZ(float theta)
{
	float thetaOver2 = theta*0.5f;
	w = cos(thetaOver2);
	z = sin(thetaOver2);
	x = 0.0f;
	y = 0.0f;
}

void Quaternion::SetToRotateAboutAxis(const Vector3 & axis, float theta)
{
	float thetaOver2 = theta * 0.5f;
	//一定要是单位向量
	assert(fabs(VectorMag(axis)) < 0.01f);
	float sinThetaOver2 = sin(thetaOver2);
	x = sinThetaOver2*axis.x;
	y = sinThetaOver2*axis.y;
	z = sinThetaOver2*axis.z;
}

float Quaternion::getRotationAngle() const
{
	//根据四元数公式 得到theta
	float thetaOver2 = SafeAcos(w);
	return thetaOver2 * 2.0f;
}

Vector3 Quaternion::getRotationAxis() const
{
	//根据四元数公式得到 xyz轴 nx=x/sintheta/2 ...

	//根据三角函数 得到theta
	float sinThetaOver2Sq = 1.0f - w*w;
	float OneOversinThetaOver2Sq = 1 / sqrt(sinThetaOver2Sq);

	return Vector3(x*OneOversinThetaOver2Sq, y*OneOversinThetaOver2Sq, z*OneOversinThetaOver2Sq);
}

Quaternion Quaternion::operator*(const Quaternion & a) const
{
	//根据四元数叉乘法则计算 利用的是转化的 就是从左至右  标准的是从右到左 不方便
	Quaternion result;
	result.w = w*a.w - x*a.x - y*a.y - z*a.z;
	result.x = w*a.x + x*a.w + z*a.y - y*a.z;
	result.y = w*a.y + y*a.w + x*a.z - z*a.x;
	result.z = w*a.z + z*a.w + y*a.x - x*a.y;
	return result;
}

Quaternion Quaternion::operator*=(const Quaternion & a)
{
	*this = *this* a;
	return *this;
}

void Quaternion::normalize()
{
	//计算当前的四元数的mo
	float mag = (float)sqrt(w*w + x*x + y*y + z*z);
	if (mag > 0.0f)  //模正常
	{
		//规范化
		float oneOverMag = 1.0f / mag;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else //模不正常
	{
		assert(false);
		identity(); //设为单位四元数
	}
}

void Quaternion::fromRotationMatrix(const RotationMatrix &m)
{
	//根据前面的四元数转为为矩阵 可以得出一个 矩阵
	//根据这个矩阵 可得
	//根据这个公式计算
	//4w*w -1=m11+m22+m33-> x y z
	//4x*x -1=m11-m22-m33-> w y z
	//4y*y -1=m22-m11-m33-> w x z
	//4z*z -1=m33-m11-m22-> x y w
	float m11 = m.m11;
	float m12 = m.m12;
	float m13 = m.m13;

	float m21 = m.m21;
	float m22 = m.m22;
	float m23 = m.m23;
	
	float m31 = m.m31;
	float m32 = m.m32;
	float m33 = m.m33;
	//4w*w-1
	float fourWSquaredMinus1 = m11 + m22 + m33;
	//4x*x-1
	float fourXSquaredMinus1 = m11 - m22 - m33;
	//4y*y-1
	float fourYSquaredMinus1 = m22 - m11 - m33;
	//4z*z-1
	float fourZSquaredMinus1 = m33 - m11 - m22;

	//假设W最大  即 4w*w-1 最大
	int biggestIndex = 0;
	float fourBiggestSquaredMinus1 = fourWSquaredMinus1; 
	if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		//x最大
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		//y最大
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		//z最大
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}
	//最大值 根据4x*x-1
	float biggestValue = sqrt(fourBiggestSquaredMinus1 + 1.0f)*0.5f;
	float mult = 0.25 / biggestValue;
	switch (biggestIndex)
	{
	case 0:   //w 根据先前得到的矩阵计算 xyz   这里的算法是图形图像编程精粹中 一个专家的经验算法 
		w = biggestValue;
		x = (m23 - m32)*mult;
		y = (m31 - m13)*mult;
		z = (m12 - m21)*mult;
		break;
	case 2:   //x
		x = biggestValue;
		w = (m23 - m32)*mult;
		y = (m12 + m21)*mult;
		z = (m31 + m13)*mult;
		break;
	case 3:   //y
		y = biggestValue;
		w = (m31 - m13)*mult;
		x = (m12 + m21)*mult;
		z = (m23 + m32)*mult;
		break;
	case 4:	  //z
		z = biggestValue;
		w = (m12 - m21)*mult;
		x = (m31 + m13)*mult;
		y = (m23 + m32)*mult;
		break;
	default:
		break;
	}
}

void Quaternion::SetToRotateObjectToinertial(const EulerAngles & orentation)
{
	float oneOver2H = orentation.heading*0.5;
	float oneOver2B = orentation.bank*0.5;
	float oneOver2P = orentation.pitch*0.5;

	float sb, cb, sp, cp, sh, ch;
	sinCos(&sb, &cb, oneOver2B);
	sinCos(&sp, &cp, oneOver2P);
	sinCos(&sh, &ch, oneOver2H);

	w = ch*cp*cb + sh*sp*sb;
	x = ch*sp*cb + sh*cp*sb;
	y = sh*cp*cb - ch*sp*sb;
	z = ch*cp*sb - sh*sp*cb;
}

void Quaternion::SetToRotateInertialToObject(const EulerAngles & orentation)
{
	float oneOver2H = orentation.heading*0.5;
	float oneOver2B = orentation.bank*0.5;
	float oneOver2P = orentation.pitch*0.5;

	float sb, cb, sp, cp, sh, ch;
	sinCos(&sb, &cb, oneOver2B);
	sinCos(&sp, &cp, oneOver2P);
	sinCos(&sh, &ch, oneOver2H);

	w = -ch*cp*cb - sh*sp*sb;
	x = ch*sp*cb - sh*cp*sb;
	y = ch*sp*sb - sh*cp*cb;
	z = sh*sp*cb - ch*cp*sb;
}

float dotProduct(const Quaternion &a, const Quaternion &b)
{
	return a.w*b.w + a.x*b.x + a.y*b.y + a.z*b.z;
}

Quaternion conjugate(const Quaternion & q)
{
	//根据四元数共轭法则 虚部变为负数
	Quaternion result;
	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	return result;
}

Quaternion pow(const Quaternion & q, float exponent)
{
	//根据四元数 幂运算法则
	//w <=1 否则 sin theta  cos theta =0
	if (fabs(q.w) > 0.9999f)
	{
		return q;
	}
	float alpha = acos(q.w); // alphe=theta/2
	//新的alpha
	float newAlpha = exponent * alpha;
	Quaternion result;
	result.w = cos(newAlpha);
	float mult = sin(newAlpha) / sin(alpha);
	result.x = q.x* mult;
	result.y = q.y* mult;
	result.z = q.z* mult;
	return result;
}

Quaternion slerp(const Quaternion & q0, const Quaternion & q1, float t)
{
	//计算四元数的点乘
	float CosOmega = dotProduct(q0, q1);
	//四元数相同方位存在两个四元数 判断是否合法
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;
	if (CosOmega < 0.0f)
	{
		q1w = -q1.w;
		q1x = -q1.x;
		q1y = -q1.y;
		q1z = -q1.z;
		CosOmega = -CosOmega;

	}
	float k0, k1;
	if (CosOmega > 0.99999f)
	{
		k0 = 1.0f - t;
		k1 = t;
	}
	else
	{
		float sinOmega = sqrt(1.0f - CosOmega*CosOmega);
		float Omega = atan2(sinOmega, CosOmega);
		float OneOversinOmega = 1.0f / sinOmega;
		k0 = sin((1.0 - t)*Omega)*OneOversinOmega;
		k1 = sin(t*Omega)*OneOversinOmega;
		Quaternion result;
		result.x = k0*q0.x + k1*q1x;
		result.y = k0*q0.y + k1*q1y;
		result.z = k0*q0.z + k1*q1z;
		result.w = k0*q0.w + k1*q1w;
		return result;
	}
}
