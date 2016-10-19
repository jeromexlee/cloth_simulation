#ifndef PARAMS_H
#define PARAMS_H

#define DAMPING 0.01
#define TIMESTEP_SIZE 0.5*0.5
#define SPRING_ITERATIONS 15 
#define N_CLIP 1.0
#define F_CLIP 1000.0
#define FOV 80
#define MOVE_STEP 0.3

#define PI 3.1415926535898
#define Cos(th) cos(PI/180*(th))
#define Sin(th) sin(PI/180*(th))
#define Length(x) (sizeof (x) / sizeof *(x))
#define DEF_WINDOW_HEIGHT 600
#define DEF_WINDOW_WIDTH 700
#define DEF_WINDOW_POS_H 150
#define DEF_WINDOW_POS_W 150
#define DEF_ASP 1
#define DEF_DIM 25
#define DEF_TH 340
#define DEF_PH 30
#define DEF_FOV 25
#define DEF_ECX 0
#define DEF_ECY 0
#define DEF_ECZ 0
#define DEF_AXES 1
#define DEF_PARAMS 1
#define DEF_OVERLAY 0
#define SKY_FRONT 0
#define SKY_RIGHT 1
#define SKY_LEFT 2
#define SKY_BACK 3
#define SKY_UP 4
#define SKY_DOWN 5


#endif
