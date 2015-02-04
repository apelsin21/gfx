#ifndef REFERENCE_COUNTED_HPP
#define REFERENCE_COUNTED_HPP

#include <iostream>

namespace core {
    class ReferenceCounted {
        private:
            int _nReferences;
        public:
            ReferenceCounted();
            virtual ~ReferenceCounted();

            void grab();
            //returns true if nothing is referencing it,
            //otheriwse returns false
            bool drop();

            int getReferenceCount();
    };
}

#endif //REFERENCE_COUNTED_HPP
