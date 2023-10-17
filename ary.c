#include <stdbool.h>
#include <math.h>
#include "ary.h"

typedef struct wartosc {
  double min;
  double max;
  } wartosc;

#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ISZERO(x) ( fabs(x) < (2e-10) ? (true) : (false))

wartosc wartosc_dokladnosc(double x, double p){
  wartosc w = {x - p, x + p};
  return w;
}
wartosc wartosc_od_do(double x, double y){
  wartosc w = {x, y};
  return w;
};

wartosc wartosc_dokladna(double x){
  wartosc w = {x, x};
  return w;
};

bool in_wartosc(wartosc w, double x){
  if(w.min <= x && x <= w.max)
      return true;
  return false;
};

double min_wartosc(wartosc w){
  return w.min;
};

double max_wartosc(wartosc w){
  return w.max;
};

double sr_wartosc(wartosc w){
  return (w.min + w.max)/2;
};

wartosc plus(wartosc a, wartosc b){
  wartosc w = {a.min + b.min, a.max + b.max};
  return w;
};

wartosc minus(wartosc a, wartosc b){
  wartosc w = {a.min - b.max, a.max - b.min};
  return w;
};


wartosc razy(wartosc a, wartosc b){
  wartosc w;
  w.min = MIN(MIN(a.min*b.min, a.min*b.max), MIN(a.max*b.min, a.min*b.max));
  w.max = MAX(MAX(a.min*b.min, a.min*b.max), MAX(a.max*b.min, a.min*b.max));
  return w;
};

wartosc podzielic(wartosc a, wartosc b){
    wartosc w;
git
    w.min = MIN(MIN(a.min/b.min, a.min/b.max), MIN(a.max/b.min, a.min/b.max));
    w.max = MAX(MAX(a.min/b.min, a.min/b.max), MAX(a.max/b.min, a.min/b.max));

    if(in_wartosc(b, 0)){
        if(a.max > 0)
            w.max = HUGE_VAL;
        if(a.min < 0)
            w.min = -HUGE_VAL;
    }

    return w;
};