#include "stdafx.h"
#include "pt.h"
#include "sgt.h"

static void testPt(void);
static void testSgt(void);

void testPtSgt(void)
{
	testPt();
	testSgt();
}

void testPt(void) // Premiers test des points __________________________________
{
	// Construction par défaut et affichage, surcharge ==
	pt p0;
	cout << "p0 = " << p0 << endl;
	assert( p0 == p0 );

	// Construction par position
	double x = dRand(-1000, 2000);
	double y = dRand(-1000, 2000);
	pt p1(x,y);
	cout << "p1 = " << p1 << endl;
	assert( EPSEQUAL(p1.getX(), x) );
	assert( EPSEQUAL(p1.getY(), y) );

	// Distance entre points
	double d01 = p0.euclide(p1);
	assert( EPSEQUAL(d01*d01, x*x + y*y) );

	// Construction par copie implicite
	pt p2(p1);
	assert( p2 == p1 );

	// Affectation implicite
	pt p3(dRand(-1, 2), dRand(-3, 4));
	cout << "p3 = " << p3 << endl;
	p3 = p2;
	cout << "p3 = " << p3 << endl;
	assert( p3 == p2 );

	// Déplacement et distance
	// On construit un triangle rectangle aléatoire et on vérifie le théorème de
    // Pythagore
	pt pT1(dRand(-10, 20), dRand(-30, 40)); // sommet angle droit
	pt pT2(pT1);
	double dx12 = dRand(-50, 60);
    // à droite ou à gauche du sommet de l'angle droit, même ordonnée
    pT2.offset( dx12, 0 );
	pt pT3(pT1);
	double dy13 = dRand(-70, 80);
    // au dessous ou au dessus du sommet de l'angle droit, même abscisee
    pT3.offset( 0, dy13 );
	// Hypothenuse : pT2-pT3
	double d12 = pT1.euclide(pT2);
	double d13 = pT1.euclide(pT3);
	double d23 = pT2.euclide(pT3);
	assert( EPSEQUAL(d12*d12 + d13*d13,  d23*d23) );

	// Point milieu
	pt p6(dRand(-90,100), dRand(-110, 120));
	pt p7 = p3.centerPt(p6);
	assert( EPSEQUAL(p3.euclide(p7), p3.euclide(p6)/2.0) );
	assert( EPSEQUAL(p6.euclide(p7), p3.euclide(p6)/2.0) );
	assert( EPSEQUAL( p1.centerPt(p3).euclide(p1) + p1.centerPt(p3).euclide(p3),
                      p1.euclide(p3)) );

	// On vérifie closerTo en générant 3 points aléatoires pC1, pC2 et pC3. 
	// On calcule pClose le point du segment [pC1,pC2] le plus proche de pC3.
	// Puis on vérifie qu'une sélection d'autres points aléatoires du segment
	// [pC1,pC2] sont tous plus éloignés.

	pt pC1(dRand(-10, 20), dRand(-30, 40));
	pt pC2(dRand(-40, 50), dRand(-60, 70));
	pt pC3(dRand(-80, 90), dRand(-100, 110));
	pt ptCloser = pC3.closerTo(pC1, pC2);
	double dOpt = pC3.euclide(ptCloser);

	for(int i=0; i<100; ++i)
	{
		double d01 = dRand(0, 1);
		pt ptTest(pC1); // On déplace ptTest sur le segment [pC1,pC2]
		ptTest.offset( d01*(pC2.getX()-pC1.getX()), d01*(pC2.getY()-pC1.getY()));
		double dTest = ptTest.euclide(pC3);
		assert( dTest >= dOpt - EPSILON); // EPSILON nécessaire !
	}
}


void testSgt(void) // Les segments _____________________________________________
{
	pt p1(dRand(-10, 20), dRand(-30, 40));
	pt p2(dRand(-40, 50), dRand(-60, 70));
	pt p3(dRand(-80, 90), dRand(-100, 110));

	sgt s1(p3, p2);
	cout << "s1 =" << s1 << endl;

	// Egalite, longueur
	sgt s2(p3, p2);
	assert(s1 == s2);
	assert( EPSEQUAL(s1.length(), s2.length()) );

	// Copie
	sgt ss2(s2);
	assert(ss2==s2);

	// Affectation
	ss2 = s1;
	assert(ss2 == s1);

	// Déplacement
	double rdx = dRand(70); // >= 0
	double rdy = dRand(80); // >= 0

	sgt s3(s1);
	s3.offset(rdx, rdy);
	s3.offset(-rdx,-rdy);
	assert( s3 == s1 ); // idempotent

	pt p4(p3);
	p4.offset(rdx,rdy);
	sgt s4(p3, p4);
	assert( s4.Ascending() );

	rdx = dRand(-90, 100); // Signé
	rdy = dRand(-110, 120); 
	assert( EPSEQUAL(s4.length(), p3.euclide(p4)) );
	pt p5 =  s4.centerPt();
	s4.offset(rdx,rdy);
	p5.offset(rdx, rdy);
	assert( p5 == s4.centerPt() );
	assert( ! sgt(s4.get_p2(), s4.get_p1()).Ascending() );

	assert(s1==s2);
    for(int i=0; i<10; ++i)
        double d = dRand(-s2.length(), s2.length());
        s2.inflate(d);


	// CloserTo
	{
		for(int k=0; k<1000; ++k)
		{
			// Vérifie sgt::closerTo en générant 3 points aléatoires p1, p2, p3.
			// Calcule pClose le point du segment [p1,p2] le plus proche de p3.
			// Puis vérifie qu'une sélection d'autres points aléatoires du segment
			// [p1,p2] sont tous plus éloignés du segment que pClose.

			pt p1(dRand(-1000, 2000), dRand(-3000,4000));
			pt p2(dRand(-5000, 6000), dRand(-7000,8000));
			sgt s0(p1, p2);
			pt p3(dRand(-9000, 10000), dRand(-11000,12000));

			pt ptCloser = s0.closerTo(p3);
			double dOpt = p3.euclide(ptCloser);

			for(int i=0; i<100; ++i)
			{
				double d01 = dRand(0, 1);
				pt ptTest(p1); // On déplace ptTest sur le segment [p1,p2]
				ptTest.offset( d01*(p2.getX()-p1.getX()), d01*(p2.getY()-p1.getY()));
				double dTest = ptTest.euclide(p3);
				assert( dTest >= dOpt - EPSILON); // EPSILON nécessaire !
			}
		}
	}
}


