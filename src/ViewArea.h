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
 * \brief : The ViewArea class 视图区域类
 * TODO: 为该类提供以下功能，并可以设计为虚类，目前尚未就不同的窗口系统建立通用的视图类！
 *
 * 管理视图对应的屏幕坐标窗口区域、中心直角坐标区域、极坐标区域，
 * 并提供屏幕坐标到直角坐标、极坐标的相互坐标转换的接口。
 * 窗口屏幕坐标，以左上角为(0,0)，x轴向右为正，y轴向下为正
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
