#ifndef DATA_H
#define DATA_H

#include <cstdlib>
#include <vector>
#include <string>

#include <math3d.h>
#include "Singleton.h"


using std::vector;
using std::string;

enum SYMBOL_TYPE
{
    SYMBOL_TYPE_POINT = 0,           // 小圆点
    SYMBOL_TYPE_CIRCLE,		   	 // 圆圈
    SYMBOL_TYPE_TRIANGLE_UP,     // 正三角形
    SYMBOL_TYPE_TRIANGLE_DOWN,   // 倒三角形
    SYMBOL_TYPE_DIAMOND,         // 菱形
    SYMBOL_TYPE_CROSS,           // 十字
    SYMBOL_TYPE_EMPTYCROSS,      // 中空十字
    SYMBOL_TYPE_SQUARE,          // 正方形
    SYMBOL_TYPE_SQUARE_CROSS,    // 正方形+十字
    SYMBOL_TYPE_DIAG_CROSS,      // X形
    SYMBOL_TYPE_BIAS,            // 斜线
    SYMBOL_TYPE_ASTERISK,        // 星号
    SYMBOL_TYPE_ARROW,           //箭头
    SYMBOL_TYPE_COUNT
};

enum SYMBOL_COLOR
{
    SYMBOL_COLOR_RED = 0,       //红
    SYMBOL_COLOR_GREEN,     //绿
    SYMBOL_COLOR_BLUE,      //蓝
    SYMBOL_COLOR_COUNT
};

const M3DVector3f Colors[SYMBOL_COLOR_COUNT] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255}
};

const int SymbolSize = 32;

struct PointTrace
{
    M3DVector2f pos;
    SYMBOL_TYPE type;
    SYMBOL_COLOR color;
    int size;
    double range;
    string comment;
};

class PointTraceContainer : public ISingleton<PointTraceContainer>
{
public:
    void init();
    void update(int n);
public:
    vector<PointTrace> elems;
    bool isupdateall;
    int index_last;
    int index_crt;

private:
    PointTraceContainer();
    ~PointTraceContainer(){}

    friend class ISingleton<PointTraceContainer>;
    friend class auto_ptr<PointTraceContainer>;

    PointTraceContainer(const PointTraceContainer&);
    PointTraceContainer& operator =(const PointTraceContainer&);

public:
    const static int NUM_POINTTRACE = 100;
};

#endif // DATA_H
