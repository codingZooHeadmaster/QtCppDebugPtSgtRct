#include "stdafx.h"
void testPtSgt(void);
void testPtSgtRct(void);

/*
 Version Initiale boguée.
 Partagez-vous le travail : corriger ce qui concerne  la classe sgt, corriger la classe rct.
 Travaillez chacun dans une branche séparée, par exemple debugSgt et debugRct.
 */

int main(void)
{
    // Initialisation du générateur aléatoire
    srand((unsigned int)time(0));

    // Test des composants de base
    testPtSgt();
    testPtSgtRct();
    return 0;
}
