#ifndef DRIVER_HPP
#define DRIVER_HPP

#include "core/referencecounted.hpp"

namespace gfx {
    class Driver : public core::ReferenceCounted {
        protected:
        public:
            Driver();
            virtual ~Driver();
    };
}

#endif //DRIVER_HPP
