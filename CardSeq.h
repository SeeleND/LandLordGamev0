#ifndef HAND_H
#define HAND_H

#include "Cards.h"
#include <QVector>

enum Type
{
    Unknown,			// 未知
    Pass,				// 过

    Single,			// 单
    Pair,				// 对

    Triple,			// 三个
    Triple_Single,		// 三带一
    Triple_Pair,		// 三带二

    Plane,				// 飞机
    Plane_Two_Single,	// 飞机带单
    Plane_Two_Pair,	// 飞机带双

    Seq_Pair,			// 连对
    Seq_Single,		// 顺子

    Bomb,				// 炸弹
    Bomb_Single,		// 炸弹带一个
    Bomb_Pair,			// 炸弹带一对
    Bomb_Two_Single,	// 炸弹带两单

    Bomb_Jokers,			// 王炸
    Bomb_Jokers_Single,	// 王炸带一个
    Bomb_Jokers_Pair,		// 王炸带一对
    Bomb_Jokers_Two_Single	// 王炸带两单

};
class CardSeq
{
public:
    CardSeq();
    CardSeq(Type type,CardPoint Base,int extra);
    CardSeq(const Cards& cards);

    bool operator ==(const CardSeq& hand);

    void FromCards(const Cards& cards);
    void JudgeHand();

    bool CanBeat(const CardSeq& other);
    Type GetType();
    CardPoint GetBasePoint();
    int GetExtra();

protected:
    Type  handType;
    CardPoint  basePoint;
    int  extra;

    QVector<CardPoint>  oneCard;
    QVector<CardPoint>  twoCards;
    QVector<CardPoint>  threeCards;
    QVector<CardPoint>  fourCards;
};

#endif // HAND_H
