#include "CardSeq.h"
#include <QMap>

CardSeq::CardSeq()
{}

CardSeq::CardSeq(Type type, CardPoint base, int extra)
{
    this->handType = type;
    this->basePoint = base;
    this->extra = extra;
}

CardSeq::CardSeq(const Cards& cards)
{
    FromCards(cards);
    JudgeHand();
}

void CardSeq::FromCards(const Cards& cards)//
{
    CardList cardList = cards.ToCardList();

    int* cardRecord = new int[Card_End];
    memset(cardRecord, 0, sizeof(int) * Card_End);

    CardList::const_iterator it = cardList.constBegin();
    for (; it != cardList.constEnd(); it++)
    {
        cardRecord[(int)it->point]++;
    }

     oneCard.clear();
     twoCards.clear();
     threeCards.clear();
     fourCards.clear();

    for (int i = 0; i < Card_End; i++)
    {
        if (cardRecord[i] == 1)
        {
             oneCard.push_back((CardPoint)i);
        }
        else if (cardRecord[i] == 2)
        {
             twoCards.push_back((CardPoint)i);
        }
        else if (cardRecord[i] == 3)
        {
             threeCards.push_back((CardPoint)i);
        }
        else if (cardRecord[i] == 4)
        {
             fourCards.push_back((CardPoint)i);
        }
    }

    delete[] cardRecord;
}

void CardSeq::JudgeHand()
{
     handType = Unknown;
     basePoint = Card_Begin;
     extra = 0;

    if ( oneCard.isEmpty() &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
         handType = Pass;
    }
    else if ( oneCard.size() == 1 &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())		// 单牌
    {
         handType = Single;
         basePoint =  oneCard[0];
    }
    else if ( oneCard.isEmpty() &&
         twoCards.size() == 1 &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())		// 对
    {
         handType = Pair;
         basePoint =  twoCards[0];
    }
    else if ( oneCard.isEmpty() &&
         twoCards.isEmpty() &&
         threeCards.size() == 1 &&
         fourCards.isEmpty())		// 三个
    {
         handType = Triple;
         basePoint =  threeCards[0];
    }
    else if ( oneCard.size() == 1 &&
         twoCards.isEmpty() &&
         threeCards.size() == 1 &&
         fourCards.isEmpty())		// 三带一
    {
         handType = Triple_Single;
         basePoint =  threeCards[0];
    }
    else if ( oneCard.isEmpty() &&
         twoCards.size() == 1 &&
         threeCards.size() == 1 &&
         fourCards.isEmpty())		// 三带二
    {
         handType = Triple_Pair;
         basePoint =  threeCards[0];
    }
    else if ( oneCard.isEmpty() &&
         twoCards.isEmpty() &&
         threeCards.size() == 2 &&
         fourCards.isEmpty())
    {
        qSort( threeCards.begin(),  threeCards.end());
        if ( threeCards[1] -  threeCards[0] == 1 &&
             threeCards[1] < Card_2)		// 飞机
        {
             handType = Plane;
             basePoint =  threeCards[0];
        }
    }
    else if ( oneCard.size() == 2 &&
         twoCards.isEmpty() &&
         threeCards.size() == 2 &&
         fourCards.isEmpty())
    {
        qSort( threeCards.begin(),  threeCards.end());
        qSort( oneCard.begin(),  oneCard.end());

        if ( threeCards[1] -  threeCards[0] == 1 &&
             oneCard[0] != Card_SJ &&
             oneCard[1] != Card_BJ &&
             threeCards[1] < Card_2)		// 飞机带两单，注意两单不是双王
        {
             handType = Plane_Two_Single;
             basePoint =  threeCards[0];
        }
    }
    else if ( oneCard.isEmpty() &&
         twoCards.size() == 2 &&
         threeCards.size() == 2 &&
         fourCards.isEmpty())
    {
        qSort( threeCards.begin(),  threeCards.end());
        if ( threeCards[1] -  threeCards[0] == 1 &&
             threeCards[1] < Card_2)		// 飞机带两对
        {
             handType = Plane_Two_Pair;
             basePoint =  threeCards[0];
        }
    }
    else if ( oneCard.isEmpty() &&
         twoCards.size() >= 3 &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
        qSort( twoCards.begin(),  twoCards.end());
        if ( twoCards.first() >= Card_3 &&
             twoCards.last() < Card_2 &&
             twoCards.last() -  twoCards.first() == ( twoCards.size() - 1))	// 连对
        {
             handType = Seq_Pair;
             basePoint =  twoCards[0];
             extra =  twoCards.size();
        }
    }
    else if ( oneCard.size() >= 5 &
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
        qSort( oneCard.begin(),  oneCard.end());
        if ( oneCard.first() >= Card_3 &&
             oneCard.last() < Card_2 &&
             oneCard.last() -  oneCard.first() == ( oneCard.size() - 1))		// 顺子
        {
             handType = Seq_Single;
             basePoint =  oneCard[0];
             extra =  oneCard.size();
        }
    }
    else if ( oneCard.isEmpty() &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.size() == 1)		// 炸弹
    {
         handType = Bomb;
         basePoint =  fourCards[0];
    }
    else if ( oneCard.size() == 1 &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.size() == 1)		// 炸弹带一个
    {
         handType = Bomb_Single;
         basePoint =  fourCards[0];
    }
    else if ( oneCard.isEmpty() &&
         twoCards.size() == 1 &&
         threeCards.isEmpty() &&
         fourCards.size() == 1)		// 炸弹带一对
    {
         handType = Bomb_Pair;
         basePoint =  fourCards[0];
    }
    else if ( oneCard.size() == 2 &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.size() == 1)
    {
        qSort( oneCard.begin(),  oneCard.end());

        if ( oneCard[0] != Card_SJ &&
             oneCard[1] != Card_BJ)		//  炸弹带两单，两单不是双王
        {
             handType = Bomb_Two_Single;
             basePoint =  fourCards[0];
        }
    }
    else if ( oneCard.size() == 2 &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
        qSort( oneCard.begin(),  oneCard.end());
        if ( oneCard[0] == Card_SJ &&  oneCard[1] == Card_BJ)		// 王炸
        {
             handType = Bomb_Jokers;
        }
    }
    else if ( oneCard.size() == 3 &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
        qSort( oneCard.begin(),  oneCard.end());
        if ( oneCard[1] == Card_SJ &&  oneCard[2] == Card_BJ)		// 王炸带一个
        {
             handType = Bomb_Jokers_Single;
        }
    }
    else if ( oneCard.size() == 2 &&
         twoCards.size() == 1 &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
        qSort( oneCard.begin(),  oneCard.end());
        if ( oneCard[0] == Card_SJ &&  oneCard[1] == Card_BJ)		// 王炸带一对
        {
             handType = Bomb_Jokers_Single;
        }
    }
    else if ( oneCard.size() == 4 &&
         twoCards.isEmpty() &&
         threeCards.isEmpty() &&
         fourCards.isEmpty())
    {
        qSort( oneCard.begin(),  oneCard.end());
        if ( oneCard[2] == Card_SJ &&  oneCard[3] == Card_BJ)		// 王炸带两个
        {
             handType = Bomb_Jokers_Two_Single;
        }
    }

}

bool CardSeq::operator ==(const CardSeq& hand)
{
    return ( handType == hand. handType &&
         basePoint == hand. basePoint &&
         extra == hand. extra);
}

Type CardSeq::GetType()
{
    return  handType;
}

CardPoint CardSeq::GetBasePoint()
{
    return  basePoint;
}

int CardSeq::GetExtra()
{
    return  extra;
}

bool CardSeq::CanBeat(const CardSeq& other)
{
    if ( handType == Unknown) return false;

    // 王炸无敌
    if ( handType == Bomb_Jokers) return true;

    if (other. handType == Pass) return true;

    // 炸弹可炸普通牌
    if (other. handType >= Single &&
        other. handType <= Seq_Single &&
         handType == Bomb)
    {
        return true;
    }
    //普通比较
    if ( handType == other. handType)
    {
        if ( handType == Seq_Pair ||  handType == Seq_Single)
        {
            return ( basePoint > other. basePoint &&  extra == other. extra);
        }
        else
        {
            return ( basePoint > other. basePoint);
        }
    }

    return false;
}
