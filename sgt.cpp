#include "stdafx.h"
#include "sgt.h"

// Translation de (xOff,yOff)
const void sgt::offset(double xOff, double yOff)
{ 
	pt1.offset(xOff, yOff); 
	pt2.offset(xOff, yOff); 
}


// Allonge le segment sans changer son point milieu, ni son orientation. 
// Les extrémités sont déplacées de manière à ce que sa longueur soit augmentée
// de la valeur de l'argument "d". Si "d < 0", une assertion est déclenchée.
void sgt::inflate(double d)
{
	double L = length();
	assert( d >= -L/2 );
#ifdef _DEBUG
	const sgt ss(*this); // Copie pour test de validation
#endif
	
	// Un vecteur directeur unitaire correspondant au vecteur pt1->pt2
	double dx = (get_p2().getX()-get_p1().getX())/L;
	double dy = (get_p2().getY()-get_p1().getY())/L;
	assert( EPSEQUAL( pt(0,0).euclide(pt(dx,dy)), 1.0) );

	// Un déplacement des extémités conservant centre et orientation
	dx *= (d/2.0);
	dy *= (d/2.0);
	pt1.offset(-dx, -dy);
	pt2.offset(dx, dy);

	// On contrôle le changement de longueur
	assert( EPSEQUAL(length(), L+d) );

	// On contrôle l'invariance du centre
	assert( ss.centerPt() == centerPt() );

	// On contrôle l'invariance de la pente
	assert(
           EPSEQUAL(get_p1().getX(), get_p2().getX())
		|| EPSEQUAL( dy/dx, (ss.get_p2().getY() - ss.get_p1().getY())
                          / (ss.get_p2().getX() - ss.get_p1().getX()) )
           );
}


