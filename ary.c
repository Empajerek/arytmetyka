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

/*

                   .     _,
                   |`\__/ /
                   \  . .(
                    | __T|
                   /   |
      _.---======='    |
     //               {}
    `|      ,   ,     {}
     \      /___;    ,'s
      ) ,-;`    `\  //
     | / (        ;||
     ||`\\        |||
     ||  \\       |||
jgs  )\   )\      )||
     `"   `"      `""

*/

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

  w.min = (ISZERO(a.min) || ISZERO(b.min)) ? 0 : 
    MIN(MIN(a.min*b.min, a.min*b.max), MIN(a.max*b.min, a.min*b.max));

  w.max = (ISZERO(a.max) || ISZERO(b.max)) ? 0 : 
    MAX(MAX(a.min*b.min, a.min*b.max), MAX(a.max*b.min, a.min*b.max));

  return w;
};

/*

   \\
   (o>
\\_//)
 \_/_)
  _|_

*/

wartosc podzielic(wartosc a, wartosc b){
    wartosc w;

    if(in_wartosc(b,0)){
      if(ISZERO(b.min)){

        w.min = (a.min > 0) ? a.min / b.max : -HUGE_VAL;
        w.max = (a.max < 0) ? a.max / b.max : HUGE_VAL;

      } else if(ISZERO(b.max)){

        w.min = (a.max < 0) ? a.max / b.min : -HUGE_VAL;
        w.max = (a.min > 0) ? a.min / b.min : HUGE_VAL;

      } else {
        w.min = -HUGE_VAL;
        w.max = HUGE_VAL;
      }
    } else {
      w.min = MIN(MIN(a.min/b.min, a.min/b.max), MIN(a.max/b.min, a.min/b.max));
      w.max = MAX(MAX(a.min/b.min, a.min/b.max), MAX(a.max/b.min, a.min/b.max));
    }
    return w;
};