/*
 * ViewArea.h
 *
 *  Created on: 2015-01-13
 *      Author: ovsoil
 */
#ifndef ViewArea_H
#define ViewArea_H

#include "rdscore_global.h"
#include "singleton.h"

#include <QtCore/QObject>
#include <QtGui/QPainter>

class ViewPainter;
class TargetPainter;

struct Point
{
    Point(int vx, int vy) : x(vx), y(vy) {}
    int x;
    int y;
}

/*!
 * \brief : The ViewArea class ��ͼ������
 * TODO: Ϊ�����ṩ���¹��ܣ����������Ϊ���࣬Ŀǰ��δ�Ͳ�ͬ�Ĵ���ϵͳ����ͨ�õ���ͼ�࣡
 *
 * ������ͼ��Ӧ����Ļ���괰����������ֱ���������򡢼���������
 * ���ṩ��Ļ���굽ֱ�����ꡢ��������໥����ת���Ľӿڡ�
 * ������Ļ���꣬�����Ͻ�Ϊ(0,0)��x������Ϊ����y������Ϊ��
 * \author : ovsoil
 * \date : 2014-01-15
 */

class ViewArea
{
public:
    explicit ViewArea(){};
    virtual ~ViewArea(){};

public:
    

protected:
    int left, top, right, bottom;
};
#endif // ViewArea_H
