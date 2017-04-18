#ifndef __AABB3_Include_H__
#define __AABB3_Include_H__
#include "Vector3.h"
#include "Matrix4x3.h"
class AABB3
{
public:
	 Vector3 min;
	 Vector3 max;

public:
	//AABB的大小
	Vector3 Size()  { return max - min; }
	
	//AABB－ｘ
	float XSize() { return max.x - min.x; }

	//AABB -y
	float YSize() { return max.y - min.x; }

	//AABB -z
	float ZSize() { return max.z - min.z;}

	//AABB -center
	Vector3 Center() { return (min + max)* 0.5f; }

public:
	Vector3 Corner(int i); //根据索引得到AABB的8个顶点
	void Empty();//清空那个AABB边界框
	bool isEmpty() const; //AABB是不是空的，还是用到上面函数
	void Add(const Vector3 &p);//增加点
	void Add(const AABB3 &box);//扩张AABB
	bool Contain(Vector3 &p); //检测一个点是否在AABB内部
	void SetToTransformedBox(const AABB3 &box, const Matrix4x3 &m); //当物体线性变换的时候 外围的AABB也跟着线性变换
	Vector3 ClosestPointTo(const Vector3 &p);
};
#endif