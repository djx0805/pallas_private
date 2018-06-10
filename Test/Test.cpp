// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "..\PallasCore\Camera.h"
#include "..\PallasCore\Scene.h"
#include "..\PallasCore\Group.h"

#include "..\PallasMath\Vec2.h"
#include "..\PallasMath\Mat4.h"
#include "..\PallasMath\Quat.h"


#include "UpdateCallBackTest.h"

int main()
{

    pallas::Vec2<float> a(0.2, 0.3);
    pallas::Vec2<double> b(a);
    pallas::Vec2<short> c(127, 127);
    int length2 = c.length2<int>();
    int ll = c*c;
    double d = double(1 / 2);

    pallas::Mat4<float> ma;
    pallas::Mat4<double> mb;
    pallas::Mat4<double> mc(ma);
    bool isidentity = mc.isIdentity();
    //ll = mc[0][0];
	Test* ptest = new UpdateCallBackTest();
	ptest->run();


    return 0;
}

