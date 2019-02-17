// stdafx.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets qui sont utilisés fréquemment,
// et sont rarement modifiés
//
#pragma once
//
#include <iostream>
#include <sstream>
#include <cassert>
#include <ctime>
#include <limits>
#include <cmath>

using namespace std;

// Génération de nombres fractionnaires aléatoire compris entre 0 et d
inline double dRand(double d)
{
    assert( d >= 0.0 );
    if( d == 0.0 )
        return 0.0;

    // On génére un doubel compris dans l'intervalle [0, 1[ , 1 exclus.
    // (attention aux erreurs de débordement arithmétique : RAND_MAX + 1 pourrait
    // devenir égal à INT_MIN dans certaines implémentation !
    double r01 = static_cast<double>(rand())/(static_cast<double>(RAND_MAX) + 1.0);
    double r = d*r01;
    assert( r < d ); // Le cas ne peut jamais se produire
    return r;
}

// Génération de nombres entiers aléatoires compris entre 0 et iMax-1 (inclus)
inline long iRand(long iMax)
{
    assert( iMax > 0 );
    long iR = static_cast<long>(dRand(iMax));
    assert(iR < iMax);
    return iR;
}

// Génération de nombres fractionnaires aléatoire compris entre min et max
inline double dRand(double min, double max)
{
    assert( min <= max );
    return min + dRand(max-min);
}

// Renvoie vrai/faux équiprobables
inline bool bRand(void)
{
    return dRand(1.0) < 0.5;
}

