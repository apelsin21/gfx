#include "core/referencecounted.hpp"

core::ReferenceCounted::ReferenceCounted()
    : referenceCount(1) {
    
}

core::ReferenceCounted::~ReferenceCounted() {
}

void core::ReferenceCounted::Grab() {
    this->referenceCount++;
}

bool core::ReferenceCounted::Drop() {
    this->referenceCount--;

    if(!this->referenceCount) {
        delete this;
        return true;
    }

    return false;
}

int core::ReferenceCounted::GetReferenceCount() {
    return this->referenceCount;
}
