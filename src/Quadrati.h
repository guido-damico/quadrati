/*
 * Quadrati.h
 *
 *  Created on: Mar 6, 2020
 *      Author: Guido
 */

#ifndef QUADRATI_H_
#define QUADRATI_H_

#include <stdio.h>
#include <iostream>

#include "Decomposizione.h"

using namespace std;

namespace quadrati {

    class Quadrati {
        private:
            int trovaLivelloDisponibile(Decomposizione);
            int sommaQuadratiAddendi(Decomposizione);
            void outputDebug(Decomposizione, int, int);
            void azzeraAddendiDalLivello(Decomposizione&, int);

        public:
            Quadrati();
            virtual ~Quadrati();

            void updateProgress(long int, long int);
            Decomposizione addendi(Decomposizione&);
    };

} /* namespace quadrati */

#endif /* QUADRATI_H_ */
