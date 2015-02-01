#include "core/referencecounted.hpp"

core::ReferenceCounted::ReferenceCounted()
    : _referenceCount(1) {
    
}

core::ReferenceCounted::~ReferenceCounted() {
}

void core::ReferenceCounted::grab() {
    this->_referenceCount++;
}

bool core::ReferenceCounted::drop() {
    this->_referenceCount--;

    if(!this->_referenceCount) {
        delete this;
        return true;
    }

    return false;
}

int core::ReferenceCounted::getReferenceCount() {
    return this->_referenceCount;
}
