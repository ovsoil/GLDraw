#include "Data.h"

PointTraceContainer::PointTraceContainer()
    :isupdateall(false)
    ,index_last(0)
    ,index_crt(0)
{
    srand((int)time(0));
    init();
}

void PointTraceContainer::init()
{
    for(int i = 0; i < NUM_POINTTRACE; ++i)
    {
        PointTrace pt;
        pt.pos[0] = -1.0 + (2.0 * rand() / RAND_MAX);
        pt.pos[1] = -1.0 + (2.0 * rand() / RAND_MAX);
        pt.type = (SYMBOL_TYPE)((double)SYMBOL_TYPE_COUNT * rand() / RAND_MAX);
        pt.color = (SYMBOL_COLOR)((double)SYMBOL_COLOR_COUNT * rand() / RAND_MAX);

        pt.range = 0.2 * rand() / RAND_MAX;
        pt.size = 10;
        pt.comment = "Hello";
        elems.push_back(pt);
    }
}

void PointTraceContainer::update(int n)
{
    for(int i = 0; i< n; ++i)
    {
        PointTrace pt;
        pt.pos[0] = -1.0 + (2.0 * rand() / RAND_MAX);
        pt.pos[1] = -1.0 + (2.0 * rand() / RAND_MAX);
        pt.type = (SYMBOL_TYPE)(SYMBOL_TYPE_COUNT * rand() / RAND_MAX);
        pt.color = (SYMBOL_COLOR)(SYMBOL_COLOR_COUNT * rand() / RAND_MAX);

        pt.range = 0.2 * rand() / RAND_MAX;
        pt.size = 10;
        pt.comment = "Hello";

        elems[index_crt++] = pt;
        if(index_crt == NUM_POINTTRACE)
            index_crt = 0;
        if(index_crt == index_last)
            isupdateall = true;
    }

}
