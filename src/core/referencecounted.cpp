#include "core/referencecounted.hpp"

core::ReferenceCounted::ReferenceCounted()
    : _nReferences(1) {
    
}

core::ReferenceCounted::~ReferenceCounted() {
}

void core::ReferenceCounted::grab() {
    this->_nReferences++;
}

bool core::ReferenceCounted::drop() {
    this->_nReferences--;

    if(!this->_nReferences) {
        delete this;
        return true;
    }

    return false;
}

int core::ReferenceCounted::getReferenceCount() {
    return this->_nReferences;
}
