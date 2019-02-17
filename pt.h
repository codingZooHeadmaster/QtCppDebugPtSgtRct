#pragma once
#include <iostream>
#include <cassert>
#include <climits>
#include <cmath>
using namespace std;

#include "epsilon.h"


class sgt;     // Pré-déclaration, en attendant l'inclusion de sgt.h dans pt.cpp

class pt
{
private:
// Data
    double x, y;                                         // Coordonnées du point

public:
// Constructeurs _______________________________________________________________

    pt(void);                                        // Point initialisé à (0,0)
    pt(double x_, double y_);      // Point initialisé aux coordonnées arguments

// Accesseurs __________________________________________________________________

    double getX(void) const;                  // Renvoie la valeur de labscisse
    double getY(void) const;                  // Renvoie la valeur de lordonnée

    void setX(double x_);          // Donne la valeur de l'argument à l'abscisse
    void setY(double y_);           // Donne la valeur de l'argument à lordonnée

// Opérations __________________________________________________________________

    // Translate (déplacement relatif) le point de (xOff,yOff)
    void offset(double xOff, double yOff);

    // Renvoie "vrai" si et seulement si le point est égal au point argument
    bool operator==(const pt& p2) const;

    // Calcule la distance euclidienne entre le point et le point argument
    double euclide(const pt& p2) const;

    // Calcule le milieu du segment allant du point au point argument
    pt centerPt(const pt& p2) const;

    // Renvoie la distance du point au segment de droite [p1,p2]. Au retour, si
    // le pointeur "closerPt" est non nul, alors *closerPt sera le point du sgt
    // [p1, p2] qui se trouve le plus proche du point sur lequel est appelée la
    // fonction.
    double euclide(const pt& p1, const pt& p2, pt* closerPt=0) const;

    // Renvoie le point du segment [p1, p2] qui est le plus proche du point sur
    // lequel est appelé la fonction
    pt closerTo(const pt& p1, const pt& p2) const;

    // Renvoie un segment dont les extrémités vont du point au point argument
    sgt toSgt(const pt& p2) const;

// E/S ________________________________________________________________________

    // Ecrit le point dans un flux sous la forme « PT(x, y) »
    void print(ostream& s) const;
};

//  Insertion dans un flux
ostream& operator<<(ostream& s, const pt& p);



// DEFINITION DES FONCTIONS INLINE
//______________________________________________________________________________

inline double pt::getX(void) const
{ return this->x ; };

inline double pt::getY(void) const
{ return this->y ; };

inline void pt::setX(double x_)
{ this->x = x_ ; };

inline void pt::setY(double y_)
{ this->y = y_ ; };

inline pt::pt(void) // Construction par défaut
    : x(0)
    , y(0)
{ }

inline pt::pt(double x_, double y_) // Créé à partir des coordonnées
    : x(x_)
    , y(y_)
{ }


inline double pt::euclide(const pt& p2) const
{ return sqrt(double((this->x - p2.x)*(this->x - p2.x) + (this->y - p2.y)*(this->y - p2.y))); }

// Translate le point de (xOff,yOff)
inline void pt::offset(double xOff, double yOff)
{ this->x += xOff; this->y += yOff; }

// Calcule le point milieu du segment aboutissant au point argument.
inline pt pt::centerPt(const pt& p2) const
{
    return pt( (this->x+p2.x)/2.0, double(this->y+p2.y)/2.0 );
}

// Ecrit ce point-ci dans un flux sous la forme « PT(x, y) »
inline void pt::print(ostream& s) const
{ s << "PT( " << this->x << ", " << this->y << " )"; }



