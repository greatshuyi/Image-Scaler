#ifndef __YUV_H__
#define __YUV_H__

#include<vector>
#include<cstdlib>
#include<cstdio>

#include "systemc.h"

#include "def.h"


using namespace std;

struct yuv {


    int height;
    int width;
    int format;

    int size;

    vector<sc_uint<Y_WIDTH> > y;
    vector<sc_uint<Y_WIDTH> > u;
    vector<sc_uint<Y_WIDTH> > v;

    // used in output to

    
    yuv(int h, int w, int f)
    {
        this->h = h;
        this->w = w;
        this->f = f;
        this.size = h*w;
        y();
        u();
        v();

    }

    ~yuv() {
        y.clear();
        u.clear();
        v.clear();
    }

    inline const int height() const
    {
        return height;
    }

    inline const int width() const
    {
        return width;
    }

    /*
    inline const int size() const
    {
        return height * width
    }
    */

    inline const int groups() const
    {

        if (format == YUV444)
            return y.size();
        else if(foramt == YUV422)
            return y.size()/2;
        else
            return y.size()/2 + u.size();
    }

    YUV_T& get(int id);

    void to_plannar(int *y, int *u, int *v);
};




#endif
