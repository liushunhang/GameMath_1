#include "Vector3.h"
#include <iostream>
using namespace std;
void Print_v(const Vector3& v)
{
	cout << "[" << v.x << "," << v.y << "," << v.z << "]" << endl;
}
//int  main1()
//{
//	//零向量 向量长度  负向量
//	Vector3 v1(2, 5, 6);
//	float v1Mag = VectorMag(v1);
//	cout << v1Mag << endl;
//	Print_v(v1);
//	Vector3 v2 = -v1;
//	Print_v(v2);
//	v2.Zero();
//	Print_v(v2);
//
//	Vector3 v3(4, 5, 6);
//	Vector3 v4 = v3 * 2;//operator*
//	Vector3 v5 = 2 * v3;//operator(float a,const Vector3& _V)
//	Vector3 v6 = v3 / 2;
//	Print_v(v6);
//	v3.normalize();
//	Print_v(v3);
//
//	Print_v(v4);
//	Print_v(v5);
//
//	//向量的加法
//	Vector3 v7(5, 6, 7);
//	Vector3 v8(7, 8, 9);
//	Vector3 v9 = v7 + v8;
//	Print_v(v9);
//
//	//通过向量计算两个点之间的距离 但是向量应该从原点出发
//	float dis=Distance(v7, v8);
//	cout << dis << endl;
//
//	Vector3 v10(3,-2,7);
//	Vector3 v11(0, 4, -1);
//
//
//	float dp = v10*v11;
//	double db = acos(dp /( VectorMag(v10) *VectorMag(v11))) * 180/3.1415;
//	cout << "this angle of v10 and v11 is:" << db << endl;
//
//	Vector3 v12(1, 3, 4);
//	Vector3 v13(2, -5, 8);
//	//叉乘 得到了与原来两个向量都垂直的新向量
//	Vector3 v14=CrossProduct(v12, v13);
//	Print_v(v14);
//
//	getchar();
//	return 0;
//}