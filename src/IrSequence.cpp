#include "IrSequence.h"
#include "IrUtility.h"
#include <string.h>

IrSequence::IrSequence() : durations(nullptr), length(0) {
};

IrSequence::IrSequence(microseconds_t const* const& durations, size_t length)
: durations(new microseconds_t[length]), length(length) {
    memcpy(this->durations, durations, length * sizeof(microseconds_t));
}

IrSequence::IrSequence(microseconds_t const*&& durations, size_t length)
: durations(durations), length(length) {
    durations = nullptr;
}

IrSequence::IrSequence(IrSequence const& orig)
: IrSequence(orig.durations, orig.length) {
}

IrSequence::IrSequence(IrSequence&& orig)
: IrSequence(ir::move(orig.durations), orig.length) {
}

IrSequence::~IrSequence() {
    delete[] durations;
}

IrSequence *IrSequence::clone() const {
    return new IrSequence(*this);
}

void IrSequence::dump(Stream& stream, boolean usingSigns) const {
    for (unsigned int i = 0U; i < length; i++) {
        if (i > 0U)
            stream.print(' ');
        if (usingSigns)
            stream.print((i & 1) ? '-' : '+');
        stream.print(durations[i], DEC);
    }
    stream.println();
}
