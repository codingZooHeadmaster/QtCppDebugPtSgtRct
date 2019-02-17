#include "stdafx.h"
#include "./pt.h"
#include "./sgt.h"
#include "./rct.h"


void testPtSgtRct(void)// Test des rectangles
{
	rct rLimit(-10000, 10000, -10000, 10000);
	pt p10 = rLimit.randPt();
	pt p11 = rLimit.randPt();

	rct r1(p10, p11);
	cout << "r1 = " << r1 << endl;
	cout << "bottomLeft = " << r1.bottomLeft() << endl;
	cout << "topRight = " << r1.topRight() << endl;

	rct rUp(r1.bottomLeft(), r1.topRight());
	assert( rUp == r1 );

	rct r2(r1);
	assert( r1 == r2 );

	rct r3;
	r3 = r1;
	assert( r3 == r2 );

	double rdx = dRand(10000);
    double rdy = dRand(20000);
	r2.inflate(rdx, rdy);
	cout << "r2 = " << r1 << endl;
	assert( EPSEQUAL(r1.width()+rdx, r2.width()) );
	assert( EPSEQUAL( r1.height()+rdy, r2.height()) );
	assert( EPSEQUAL(r2.area(), r1.area() + rdx*rdy+ rdy*r1.width() + rdx*r1.height()) );

	assert( r2.centerPt() == r1.centerPt() );

    rdx = dRand(10000);
    rdy = dRand(10000);
	rct r4(r1);
	r4.offset(rdx,rdy);
	cout << "r3 = " << r4 << endl;
	assert( EPSEQUAL(r4.get_x1(), r1.get_x1() + rdx) );

	pt ptCr1 = r1.centerPt();
	ptCr1.offset(rdx,rdy);
	r1.offset(rdx,rdy);
	assert( r1.centerPt() == ptCr1 );

	rct r5(r1);
	rct URct = rct(-1000, -1000, 1000, 1000).randRct();
	r5.unionRct( URct );

	assert( r5.contains(r1) );
	assert( r5.contains(URct) );

	// Test euclide : si le point est, resp. à gauche, à doite, au dessous ou au
    // dessus d'un rectangle, sa distance au rectange esr égale à sa distance au
    // côté en vis à vis.
	for(int i=0; i<1000; ++i)
	{
		rct r6 = rct(-10000, -10000, 10000, 10000).randRct();
		rct r8 = r6.randRct();
		pt ptRef = r6.randPt();
		double dRef = r8.euclide(ptRef);
		if( r8.contains(ptRef) )
			assert( EPSEQUAL(dRef , 0) );
		else if( ptRef.getX() < r8.get_x1() )
			assert( EPSEQUAL(dRef, ptRef.euclide(r8.bottomLeft(), pt(r8.get_x1(), r8.get_y2()))) );
		else if( ptRef.getX() > r8.get_x2() )
			assert( EPSEQUAL(dRef, ptRef.euclide(pt(r8.get_x2(), r8.get_y1()), pt(r8.get_x2(), r8.get_y2()))) );
		else if( ptRef.getX() < r8.get_y1() )
			assert( EPSEQUAL(dRef, ptRef.euclide(pt(r8.get_x1(), r8.get_y1()), pt(r8.get_x2(), r8.get_y1()))) );
		else if( ptRef.getX() < r8.get_y2() )
			assert( EPSEQUAL(dRef, ptRef.euclide(pt(r8.get_x1(), r8.get_y2()), pt(r8.get_x2(), r8.get_y2()))) );
		else assert(0);
	}
	cout << "Test rct::euclide(pt) OK" << endl;
}


