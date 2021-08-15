/*
 * decomposizione.h
 *
 *  Created on: Mar 15, 2020
 *      Author: Guido
 */
#include <iostream>
#include <cmath>
#include <cassert>

#include "spdlog/spdlog.h"

#ifndef DECOMPOSIZIONE_H_
#define DECOMPOSIZIONE_H_

using namespace std;

namespace quadrati {

    class Decomposizione {
        private:
            long obiettivo;
            long* addendi;
            long* limiti;
            long resto;
            int  livello;
            bool completa;
            long iterazione;

            void basicInit(long);

        public:
            Decomposizione();
            Decomposizione(long);
            virtual ~Decomposizione();

            long getObiettivo();
            void setObiettivo(long);

            long* getAddendi();
            void  setAddendo(int, long);
            void  setAllAddendi(long*);

            long* getLimiti();
            void  setLimite(int, long);

            bool getCompleta();
            void setCompleta(bool);

            int getLivello();
            void setLivello(int);

            long getIterazione();
            void setIterazione(long);

            long getResto();
            long sommaQuadratiAddendi();

            void outputCurrentStatus();

            bool controllaInvarianti();
    };

} /* namespace quadrati */

#endif /* DECOMPOSIZIONE_H_ */
