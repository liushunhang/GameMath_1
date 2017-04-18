#include "AABB3.h"

Vector3 AABB3::Corner(int i)
{
	       //6 7
	      //4 5
	// 2 3
	// 0 1
	//根据8个点的索引返回Vector3
	//普通的做法是写8个if
	//if (i == 0) return Vector3(min.x, min.y, min.z);
	//我们用点数学技巧 一行代码搞定
	return Vector3((i & 1) ? max.x : min.x, (i & 2) ? max.y : min.y, (i & 4) ? max.z : min.z);
}

void AABB3::Empty()
{
	//如何判定AABB边界框是空的呢 我们让min 很大 让 max很小
	const float kBigNumber = 1e37;
	min.x = min.y = min.z=kBigNumber;
	max.x = max.y = max.z = -kBigNumber;
}

bool AABB3::isEmpty() const
{
	//根据上面的函数 我们知道 如果AABB是空的可做以下判定
	return (min.x > max.x) || (min.y > max.y) || (min.z > max.z);
}

void AABB3::Add(const Vector3 & p)
{
	//如果增加的点在AABB的外部 就扩张 x<min.x  x>max.x
	if (p.x < min.x) min.x = p.x;
	if (p.x > max.x) max.x = p.x;

	if (p.y < min.y) min.y = p.y;
	if (p.y > max.y) max.x = p.y;

	if (p.z < min.z) min.z = p.z;
	if (p.z > max.z) max.z = p.z;
}

void AABB3::Add(const AABB3 & box)
{
	//同理 增加的Box的点扩张 box.min.x <min.x  box.max.x>max.x
	if (box.min.x < min.x) min.x = box.min.x;
	if (box.max.x > max.x) max.x = box.max.x;

	if (box.min.y < min.y) min.y = box.min.y;
	if (box.max.y > max.y) max.y = box.max.y;

	if (box.min.z < min.z) min.z = box.min.z;
	if (box.max.z > max.z) max.z = box.max.z;
}

bool AABB3::Contain(Vector3 &p)
{
	//如果物体在AABB中 那么它满足 p.x>=min.x && p.x<=max.x
	return (p.x >= min.x && p.x <= max.x) && (p.y >= min.y && p.y <= max.y) && (p.z >= min.z && p.z <= max.z);
}

void AABB3::SetToTransformedBox(const AABB3 & box, const Matrix4x3 & m)
{
	//一般来做的话是 box.min.x *m.xx 做9次线性变换 这里我们用点数学技巧的话 可以不用做9次
	//box 不能为空
	if (box.isEmpty())
	{
		Empty();
		return;
	}
	//平移
	min = max = getTranslation(m);

	//我们要得到最新的 AABB 也就是要得到 min max  min最小  max 最大
	//m11<0  min我们取x的最大 max取x最小  
	//m11>0 min我们取x的最小 max取x最大
	if (m.m11 > 0.0f)
	{
		min.x += m.m11*box.min.x;
		max.x += m.m11*box.max.x;
	}
	else
	{
		min.x += m.m11*box.max.x;
		max.x += m.m11*box.min.x;
	}
	if (m.m12 > 0.0f)
	{
		min.y += m.m12*box.min.x;
		max.y += m.m12*box.max.x;
	}
	else
	{
		min.y += m.m12*box.max.x;
		max.y += m.m12*box.min.x;
	}
	if (m.m13 > 0.0f)
	{
		min.z += m.m13*box.min.x;
		max.z += m.m13*box.max.x;
	}
	else
	{
		min.z += m.m13*box.max.x;
		max.z += m.m13*box.min.x;
	}
	if (m.m21 > 0.0f)
	{
		min.x += m.m21*box.min.y;
		max.x += m.m21*box.max.y;
	}
	else
	{
		min.x += m.m21*box.max.y;
		max.x += m.m21*box.min.y;
	}
	if (m.m22 > 0.0f)
	{
		min.y += m.m22*box.min.y;
		max.y += m.m22*box.max.y;
	}
	else
	{
		min.y += m.m22*box.max.y;
		max.y += m.m22*box.min.y;
	}
	if (m.m23 > 0.0f)
	{
		min.z += m.m23*box.min.y;
		max.z += m.m23*box.max.y;
	}
	else
	{
		min.z += m.m23*box.max.y;
		max.z += m.m23*box.min.y;
	}
	if (m.m31 > 0.0f)
	{
		min.x += m.m31*box.min.z;
		max.x += m.m31*box.max.z;
	}
	else
	{
		min.z += m.m31*box.max.z;
		max.z += m.m31*box.min.z;
	}
	if (m.m32 > 0.0f)
	{
		min.y += m.m32*box.min.z;
		max.y += m.m32*box.max.z;
	}
	else
	{
		min.y += m.m31*box.max.z;
		max.y += m.m31*box.min.z;
	}
	if (m.m33 > 0.0f)
	{
		min.z += m.m33*box.min.z;
		max.z += m.m33*box.max.z;
	}
	else
	{
		min.z += m.m33*box.max.z;
		max.z += m.m33*box.min.z;
	}
}

Vector3 AABB3::ClosestPointTo(const Vector3 & p)
{
	Vector3 r;
	//如果r.x<min.x那么最近的点就是Min.x
	if (p.x < min.x)
	{
		r.x = min.x;
	}
	else if (p.x > max.x)
	{
		r.x = max.x;
	}
	else
	{
		r.x = p.x;
	}

	if (p.y < min.y)
	{
		r.y = min.y;
	}
	else if (p.y > max.y)
	{
		r.y = max.y;
	}
	else
	{
		r.y = p.y;
	}

	if (p.z < min.z)
	{
		r.z = min.z;
	}
	else if (p.z > max.z)
	{
		r.z = max.z;
	}
	else
	{
		r.z = p.z;
	}

	return r;
}
