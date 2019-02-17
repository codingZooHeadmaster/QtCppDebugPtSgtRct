#pragma once
#include "pt.h"

class sgt
{
// Data ________________________________________________________________________
	
	pt pt1, pt2;                        // Les deux points extrémités du segment
	                                            // Les extrémités sont ordonnées
public:
// Construction ________________________________________________________________

	sgt(void);      // Construction par défaut : les deux extrémités à l'origine
	sgt(pt pt1_, pt pt2_);                // Constuction à partir de deux points

// Accesseurs __________________________________________________________________

	const pt get_p1(void) const;   // Renvoie une copie du premier point du segt
	void set_p1(pt p);              // Donne une valeur au premier point du segt

	const pt get_p2(void) const;    // Renvoie une copie du second point du segt
	void set_p2(pt p);               // Donne une valeur au second point du segt

	// Ces fonctions retournent les limites des intervalles définis par les pro-
	// jections du segment sur les axes x et y : [x1,x2] et [y1,y2]  
	double x1(void) const;
	double x2(void) const;
	double y1(void) const;
	double y2(void) const;

// Opérations __________________________________________________________________

	// Renvoie "vrai" si ce segment-ci et l'argument sont égaux / non-égaux
	// (leurs premiers points extrémités sont égales et leurs seconds points 
	// extrémités sont égales).
	bool operator==(const sgt& s2) const;
 
	// Renvoie la distance euclidienne entre les deux extrémités du segment
	double length(void) const;

	// Renvoie la distance euclidienne du segment au point argument
	double euclide(pt ptRef) const;

	// Renvoie "vrai" si et seulement si le segment est ascendant: pt2 se trouve
	// au dessus et à droite de pt1
	bool Ascending(void) const;

	// Translate le segment de (xOff,yOff)
	void offset(double xOff, double yOff);        

	// Renvoie le point milieu du segment.
	pt centerPt(void) const;

	// Renvoie le point du segment qui est le plus proche du point argument
	pt closerTo(const pt& refPt) const;

	// Allonge le segment sans changer son point milieu, ni son orientation. Les
	// extrémités sont déplacées  de manière à ce que sa longueur soit augmentée 
	// de l'argument "d". Si "d" est négatif, une assertion est déclenchée.
	void inflate(double d);

	// Ecriture dans un flux au format : SGT((x,y), (x,y))
	void print(ostream& s) const;
};

 ostream& operator<<(ostream& f, const sgt& s);

//______________________________________________________________________________
// Construction par défaut
inline sgt::sgt(void) : pt1(), pt2() { }

// construction par les extremités
inline sgt::sgt(pt p1_, pt p2_) : pt1(p1_), pt2(p2_) { }

// Egalité de deux segments
inline bool sgt::operator==(const sgt& s2) const
{ return get_p1()==s2.get_p1() && get_p2()==s2.get_p2();  }

// Insertion dans un flux
inline ostream& operator<<(ostream& f, const sgt& s)
{ s.print(f); return f; }

inline void sgt::print(ostream& s) const
{ s << "SGT(" << get_p1() << ", " << get_p2() << ")"; }

// Renvoie une copie du premier point du segment
inline const pt sgt::get_p1(void) const
{ return pt1; }

// Donne une valeur au premier point du segment
inline void sgt::set_p1(pt p)
{ pt1 = p; }
         
// Renvoie une copie du second point du segment
inline const pt sgt::get_p2(void) const
{ return pt2; }
   
// Donne une valeur au second point du segment
inline void sgt::set_p2(pt p)
{ pt2 = p; }
         
// Ces fonctions renvoient les abscisses et ordonnées des projections du segment
// sur les axes x et y : [x1, x2] et [y1, y2] où x1 <= x2 et y1 <= y2.
inline double sgt::x1(void) const
{ return min(get_p1().getX(), get_p2().getX()); }

inline double sgt::x2(void) const
{ return max(get_p1().getX(), get_p2().getX()); }

inline double sgt::y1(void) const
{ return min(get_p1().getY(), get_p2().getY()); }

inline double sgt::y2(void) const
{ return max(get_p1().getY(), get_p2().getY()); }

// Renvoie la distance entre les deux extrémités 
inline double sgt::length(void) const
{ return get_p1().euclide(get_p2()); }

// Renvoie la distance euclidienne du segment au point argument
inline double sgt::euclide(pt ptRef) const
{ return ptRef.euclide(get_p1(), get_p2()); }

// Renvoie "vrai" si et seulemnt si le segment est ascendant : pt2 se trouve
// au dessus et à droite de pt1
inline bool sgt::Ascending(void) const
{
    return   get_p1().getX() <= get_p2().getX()
          && get_p1().getY() <= get_p2().getY();
}

// Renvoie le point milieu du segment
inline pt sgt::centerPt(void) const
{ return get_p1().centerPt(get_p2()); }

// Renvoie le point du segment qui est le plus proche du point argument
inline pt sgt::closerTo(const pt& RefPt) const
{ return RefPt.closerTo(get_p1(), get_p2()); }


