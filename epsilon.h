#ifndef EPSILON_H
#define EPSILON_H
#include <cmath>

// Comparaison des nombres fractionnaires (égalité à EPSILON près)
const double EPSILON = 1.0e-5;
inline bool EPSEQUAL(double a, double b) { return fabs(a-b) < EPSILON; }

#endif // EPSILON_H
