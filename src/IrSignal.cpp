#include "IrSignal.h"
#include "IrSender.h"

IrSignal *IrSignal::clone() const {
    return new IrSignal(*this);
}

void IrSignal::dump(Stream& stream, boolean usingSigns) const {
    boolean printedSomething = dumpFrequency(stream);
    if (printedSomething)
        stream.println();
    intro.dump(stream, usingSigns);
    repeat.dump(stream, usingSigns);
    ending.dump(stream, usingSigns);
}

boolean IrSignal::dumpFrequency(Stream& stream, frequency_t frequency) {
    if (frequency > 0 && frequency != invalidFrequency) {
        stream.print(F("f="));
        stream.print(frequency);
        return true;
    }
    return false;
}
