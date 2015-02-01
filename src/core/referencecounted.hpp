#ifndef REFERENCE_COUNTED_HPP
#define REFERENCE_COUNTED_HPP

namespace core {
    class ReferenceCounted {
        private:
            int _referenceCount;
        public:
            ReferenceCounted();
            virtual ~ReferenceCounted();

            void grab();
            // returns true if nothing is referencing it,
            // otheriwse returns false
            bool drop();

            int getReferenceCount();
    };
}

#endif //REFERENCE_COUNTED_HPP
