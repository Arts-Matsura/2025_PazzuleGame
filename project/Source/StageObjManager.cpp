#include "StageObjManager.h"
#include "StageObj.h"

StageObjManager::StageObjManager()
{
}

StageObjManager::~StageObjManager()
{
}

bool StageObjManager::CollCheckCapsule(VECTOR p1, VECTOR p2, float r, VECTOR* push)
{
    bool hitFlag = false;
    VECTOR pushVec = VGet(0,0,0);

    std::list<StageObj*> objs = FindGameObjects<StageObj>();
    for (StageObj* obj : objs) {
        MV1SetupCollInfo(obj->HitModel(), -1, 8, 8, 8);
        // 当たり判定をして、pushVecを作る
        MV1_COLL_RESULT_POLY_DIM dim = 
            MV1CollCheck_Capsule(obj->HitModel(), -1, p1, p2, r);
        for (int i = 0; i < dim.HitNum; i++) {
            hitFlag = true;
            //dim.Dim[i]の情報を見て、pushVecを作る
            // ポリゴンと線分の距離を求める
            float len = Segment_Triangle_MinLength(
                p1, p2, dim.Dim[i].Position[0], dim.Dim[i].Position[1],
                dim.Dim[i].Position[2]);
            if (len > r)
                continue;
            // 押し返す量は、(r-len)になる
            VECTOR newPush = dim.Dim[i].Normal * (r - len);
            newPush.y = 0;
            pushVec += newPush;
            VECTOR pushVecNorm = VNorm(pushVec);
            float pushIn = VDot(pushVecNorm, newPush);
            // これが新しく押す量
            if (pushIn < VSize(pushVec)) {
                VECTOR v = pushVecNorm * pushIn;
                pushVec += newPush - v;
            }
            else {
                pushVec = newPush;
            }
        }
        MV1CollResultPolyDimTerminate(dim);
    }
    if (push != nullptr) {
        *push = pushVec;
    }
    return hitFlag;
}

bool StageObjManager::CollCheckLine(VECTOR pos, VECTOR look, VECTOR* hitPos)
{
    float minDist = VSquareSize(pos-look); //最小の距離を取っておく変数
    VECTOR hitPosRet = pos;
    bool out = false;
    std::list<StageObj*> objs = FindGameObjects<StageObj>();
    for (auto obj : objs) {
        obj->SetOpacity(1.0f);
        MV1SetupCollInfo(obj->HitModel(), -1, 8, 8, 8);
        MV1_COLL_RESULT_POLY ret =
            MV1CollCheck_Line(obj->HitModel(), -1, look, pos);
        if (ret.HitFlag) {
            if (obj->IsTag("Stage_Obj001")) {
                obj->SetOpacity(0.7f);
            } else {
                float dist= VSquareSize(ret.HitPosition - look); // この当たった距離
                if (dist < minDist) {
                    minDist = dist;
                    hitPosRet = ret.HitPosition;
                    out = true;
                }
            }
        }
    }
    if (out) {
        // 一番近いHitPositionを*hitPosに入れる
        *hitPos = hitPosRet;
    }
    return out;
}
