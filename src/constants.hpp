#pragma once

#include <set>

#define STEP 0.01

/*diode*/
#define V_T_DIODE 0.026
#define I_SAT_DIODE (10*pow(10, -12))

/*BJT*/
#define ALPHA_R 0.02
#define ALPHA_F 0.99
#define I_SAT_EMITTER (2*pow(10, -14))
#define I_SAT_COLLECTOR (99*pow(10, -14))
#define V_T_COLLECTOR 0.026
#define V_T_EMITTER 0.026

/*MOSFET*/
#define V_t_MOSFET 0.6
#define LAMBDA 0.01
#define BETA 0.0005

#define TAU_RELATIVE 0.001
#define TAU_ABSOLUTE 0.001

extern std::set<char> INDEPENDENT_SOURCES ;
extern std::set<char> LINEAR_ELEMENTS ;
extern std::set<char> NONLINEAR_ELEMENTS ;
extern std::set<char> DYNAMIC_ELEMENTS ;

