/* By Kenzie Wright - SPDX-License-Identifier: Apache-2.0 */

#include "engine/tests/UnitTester.h"
#include "engine/utilities/Common.h"

void ctUnitTestMath3D() {
    ctVec3 v = ctVec3Zero();
    float f;

    /* Add */
    ctVec3Add(&v, ctVec3Make(1.0f, 0.5f, 1.0f));
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(1.0f, 0.5f, 1.0f)));

    /* Sub */
    ctVec3Sub(&v, ctVec3Make(1.0f, 0.5f, 1.0f));
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(0.0f, 0.0f, 0.0f)));

    /* Asignment */
    v = ctVec3Make(3.5f, 2.5f, 1.5f);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(3.5f, 2.5f, 1.5f)));

    /* Negate */
    ctVec3Negate(&v);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(-3.5f, -2.5f, -1.5f)));

    /* Multiply */
    ctVec3Mult(&v, ctVec3Make(1.0f, 4.0f, 2.0f));
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(-3.5f, -10.0f, -3.0f)));

    /* Scale */
    ctVec3Scale(&v, -1.0f);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(3.5f, 10.0f, 3.0f)));

    /* Divide */
    v = CT_VEC3_UP;
    ctVec3DivideFloat(&v, 2.0f);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(0.0f, 0.5f, 0.0f)));

    /* Array Population */
    float arr[] = {0.1f, 3.0f, 4.0f, 5.0f};
    v = ctVec3FromFloat3(arr);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(0.1f, 3.0f, 4.0f)));

    /* Divide Vector */
    ctVec3Divide(&v, ctVec3Make(0.1f, 3.0f, 4.0f));
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(1.0f, 1.0f, 1.0f)));

    /* Dot Product */
    f = ctVec3Dot(CT_VEC3_UP, CT_VEC3_FORWARD);
    ctUnitTestAssert(ctFloatApproxEqual(f, 0.0f));
    f = ctVec3Dot(CT_VEC3_UP, CT_VEC3_RIGHT);
    ctUnitTestAssert(ctFloatApproxEqual(f, 0.0f));
    f = ctVec3Dot(CT_VEC3_UP, CT_VEC3_UP);
    ctUnitTestAssert(ctFloatApproxEqual(f, 1.0f));
    f = ctVec3Dot(CT_VEC3_UP, CT_VEC3_DOWN);
    ctUnitTestAssert(ctFloatApproxEqual(f, -1.0f));

    /* Distance */
    f = ctVec3Distance(ctVec3Make(-1.0f, -1.0f, -1.0f), ctVec3Make(1.0f, 1.0f, 1.0f));
    ctUnitTestAssert(ctFloatApproxEqual(f, 3.464102f));

    /* Length */
    f = ctVec3Length(ctVec3Make(1.0f, 1.0f, 1.0f));
    ctUnitTestAssert(ctFloatApproxEqual(f, 1.732051f));

    /* Normalize */
    v = ctVec3Make(1.0f, 1.0f, 1.0f);
    ctVec3Normalize(&v);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3FromFloat(0.57735020504592532206f)));

    /* Abs */
    v = ctVec3Make(-1.0f, -1.0f, -1.0f);
    ctVec3Abs(&v);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(1.0f, 1.0f, 1.0f)));

    /* Saturate */
    v = ctVec3Make(-1.0f, 0.5f, 2.0f);
    ctVec3Saturate(&v);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(0.0f, 0.5f, 1.0f)));

    /* Cross */
    ctVec3Cross(&v, CT_VEC3_UP, CT_VEC3_FORWARD);
    ctUnitTestAssert(ctVec3ApproxEqual(v, CT_VEC3_LEFT));

    /* Lerp */
    ctVec3Lerp(&v, ctVec3FromFloat(0.0f), ctVec3FromFloat(1.0f), 0.5f);
    ctUnitTestAssert(ctVec3ApproxEqual(v, ctVec3Make(0.5f, 0.5f, 0.5f)));

    /* Quaternion Axis Angle */
    //ctQuat q = ctQuatFromAxisAngle(CT_VEC3_UP, ctDeg2Radf(90.0f));
    //ctUnitTestAssert()
    //ctAssert(0);
}