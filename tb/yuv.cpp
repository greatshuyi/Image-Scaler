#include "yuv.h"

void initialize(int w=16, int h=16, int f = YUV422)
{
    int w_tmp, h_tmp, f_tmp, b_tmp;
    if (f != YUV422 && f != YUV420 && f != YUV444)
        f_tmp = YUV420;
    else
        f_tmp = f;
        
    w_tmp = (w < 0 || w > 256) ? 16 : (w % 2 == 0) ? w : w + 1;
    h_tmp = (h < 0 || h > 256) ? 16 : (h % 2 == 0) ? h : h + 1; 

    this->w = w_tmp;
    this->h = h_tmp;
    this->size = w_tmp * h_tmp;
    this->format = f_tmp;

    // Y
    y.clear();
    for (int i = 0; i < w_tmp * h_tmp; i++) {
        sc_uint<Y_WIDTH> y_tmp = rand() % (1 << Y_WIDTH);
        y[i] = y_tmp;
    }

    // U
    u.clear();
    int s;
    s = f_tmp == YUV444 ? w_tmp * h_tmp :
        f_tmp == YUV422 ? (int)(w_tmp * h_tmp / 2) :
        f_tmp == YUV420 ? (int)(w_tmp * h_tmp / 4);
    for (int i = 0; i < s; i++) {
        sc_uint<U_WIDTH> u_tmp = rand() % (1 << U_WIDTH);
        u[i] = u_tmp;
    }

    // V
    v.clear();
    s = f_tmp == YUV444 ? w_tmp * h_tmp :
        f_tmp == YUV422 ? (int)(w_tmp * h_tmp / 2) :
        f_tmp == YUV420 ? (int)(w_tmp * h_tmp / 4);
    for (int i = 0; i < s; i++) {
        sc_uint<V_WIDTH> v_tmp = rand() % (1 << V_WIDTH);
        v[i] = v_tmp;
    }
}


YUV_T& yuv::get(int id)
{

    YUV_T tmp;

    int id_tmp;

    if (id < 0) {
        id_tmp = 0;
        cout << "Source: fetch pixel @" << id;
        cout <<" below 0, defauts to 0" << endl;
    } else {
        id_tmp = id;
    }


    int yid, uid, vid;
    
    // TODO: continue this
    
    if (format == YUV422) {

        if (2*id_tmp > size-1) {
            id_tmp = size/2 - 1;
            cout << "Source: fetch pixel goup @" << id;
            cout <<" beyond " << size/2-1 << ", defaults to " << size/2-1 << endl;
        }

        yid = 2*id_tmp;
        tmp.yl = y[yid];
        tmp.yh = y[yid+1];
        tmp.u = u[id_tmp];
        tmp.v = v[id_tmp];

    } else if (format=YUV420) {

        if (2*id_tmp > size - 1) {
            
            tmp.yh = tmp.yl = 0;

            if (id_tmp > 3 * size / 4 - 1) {
                cout << " Source: fetch pixel group @" << id_tmp;
                cout << " beyond " 3*size/4-1;
                cout << "defaults to last one" << endl;
                uid = 3*size/4-1;
                vid = uid;
            } else {
                uid = id_tmp - size / 2;
                vid = uid;
            }
                
            tmp.u = u[uid];
            tmp.v = v[vid];
        } else {

            tmp.u = tmp.v = 0;
            tmp.yl = y[2*id_tmp];
            tmp.yh = y[2*id_tmp+1];
        }
    } else {

        if (id_tmp > size-1) {
            id_tmp = size-1;
            cout << "Source: fetch pixel @" << id;
            cout <<" beyond " << size << ", defaults to " << size << endl;
        }
            
        tmp.yl = y[id_tmp];
        tmp.yh = 0;
        tmp.u = u[id_tmp];
        tmp.v = v[id_tmp];
    }

    return tmp;
}


void to_planar(int* y, int *u, int *v)
{
    return;
}
