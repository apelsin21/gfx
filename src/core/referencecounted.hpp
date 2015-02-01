#ifndef REFERENCE_COUNTED_HPP
#define REFERENCE_COUNTED_HPP

namespace core {
    class ReferenceCounted {
        private:
            int referenceCount;
        public:
            ReferenceCounted();
            virtual ~ReferenceCounted();

            void Grab();
            // returns true if nothing is referencing it,
            // otheriwse returns false
            bool Drop();

            int GetReferenceCount();
    };
}

#endif //REFERENCE_COUNTED_HPP
