#include "stdafx.h"
#include "pt.h"
#include "sgt.h"

// Renvoie un segment dont les extremités vont de ce point-ci au point argt
sgt pt::toSgt(const pt& p2) const
{ 
	return sgt(*this, p2);
}

ostream& operator<<(ostream& s, const pt& p)
{
    p.print(s);
    return s;
}

// Renvoie la distance de ce point au segment de droite [p1, p2]. Au retour,
// si le pointeur closerPt est non nul, alors *closerPt sera égal au point du
// segment [p1, p2] le plus proche.
double pt::euclide(const pt& p1, const pt& p2, pt* closerPt) const
{ 
    // On passe en représentation paramétrique de la droite passant par les 
	// deux points p1 et p2 : p(t) = p1 + t*(p2-p1)
	double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
	pt ptOpt;

    if ( p1.euclide(p2) < EPSILON ) // Le segment [p1, p2] est dégénéré
    {
		ptOpt = p1;
    }
	else
	{
		// On calcule la valeur de "t" qui minimise la distance.
		double t = ((x - p1.x) * dx + (y - p1.y) * dy) / (dx*dx + dy*dy);

		// Si 0<= t <= 1; P(t) se trouve sur le segment [p1, p2].
		// Si t < 0, p1 est le plus proche de ce point-ci.
		// Si t > 1, p2 est le plus proche de ce point-ci

		if (t < 0) // Le point le plus proche est p1
			ptOpt = p1;

		else if (t > 1) // Le point le plus proche est p2
			ptOpt = p2;

		else // Le point le plus proche se trouve sur le segment (p1,p2)
			ptOpt = pt(p1.x + t*dx, p1.y + t*dy);
	}
	// On affecte le point argument s'il y a lieu
	if(closerPt)
		*closerPt = ptOpt;

	// On retourne la distance de ce point-ci au point le plus proche
	return this->euclide(ptOpt);
}

// Renvoie le point du segment [p1,p2] qui est le plus proche de ce point-ci
pt pt::closerTo(const pt& p1, const pt& p2) const
{
	pt pClose;
	euclide(p1, p2, &pClose);
	return pClose;
}




