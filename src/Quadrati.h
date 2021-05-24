/*
 * Quadrati.h
 *
 *  Created on: Mar 6, 2020
 *      Author: Guido
 */

#ifndef QUADRATI_H_
#define QUADRATI_H_

#include <iostream>

#include "spdlog/spdlog.h"
#include "Decomposizione.h"

using namespace std;

namespace quadrati {

    class Quadrati {
        private:
            int trovaLivelloDisponibile(Decomposizione);
            void azzeraAddendiDalLivello(Decomposizione&, int);
            long stimaNuovoAddendo(Decomposizione&);

        public:
            Quadrati();
            virtual ~Quadrati();

            Decomposizione addendi(Decomposizione&);
    };

} /* namespace quadrati */

#endif /* QUADRATI_H_ */
