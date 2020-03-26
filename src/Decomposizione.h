/*
 * decomposizione.h
 *
 *  Created on: Mar 15, 2020
 *      Author: guido
 */

#ifndef DECOMPOSIZIONE_H_
#define DECOMPOSIZIONE_H_

namespace quadrati {

    class Decomposizione {
        private:
            long int  obiettivo;
            long int* addendi;
            long int  resto;
            int  livello;
            bool completa;
            long int  iterazione;

            void basicInit(long);

        public:
            Decomposizione();
            Decomposizione(long);
            virtual ~Decomposizione();

            long int getObiettivo();
            void setObiettivo(long);

            long* getAddendi();
            void setAddendi(long*);

            bool getCompleta();
            void setCompleta(bool);

            long int getResto();
            void setResto(long int);

            int getLivello();
            void setLivello(int);

            long int getIterazione();
            void setIterazione(long int);

    };

} /* namespace quadrati */

#endif /* DECOMPOSIZIONE_H_ */
