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
	//AABB�Ĵ�С
	Vector3 Size()  { return max - min; }
	
	//AABB����
	float XSize() { return max.x - min.x; }

	//AABB -y
	float YSize() { return max.y - min.x; }

	//AABB -z
	float ZSize() { return max.z - min.z;}

	//AABB -center
	Vector3 Center() { return (min + max)* 0.5f; }

public:
	Vector3 Corner(int i); //���������õ�AABB��8������
	void Empty();//����Ǹ�AABB�߽��
	bool isEmpty() const; //AABB�ǲ��ǿյģ������õ����溯��
	void Add(const Vector3 &p);//���ӵ�
	void Add(const AABB3 &box);//����AABB
	bool Contain(Vector3 &p); //���һ�����Ƿ���AABB�ڲ�
	void SetToTransformedBox(const AABB3 &box, const Matrix4x3 &m); //���������Ա任��ʱ�� ��Χ��AABBҲ�������Ա任
	Vector3 ClosestPointTo(const Vector3 &p);
};
#endif