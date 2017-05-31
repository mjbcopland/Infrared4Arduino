#ifndef IRSIGNAL_H
#define	IRSIGNAL_H

#include "InfraredTypes.h"
#include "IrSequence.h"
#include "IrUtility.h"

/**
 * This class models an IR signal with intro-, repeat-, and ending sequences.
 * This class is immutable.
 */
class IrSignal {
public:
    static const frequency_t defaultFrequency = 38000U;
    static const frequency_t invalidFrequency = (frequency_t) -1;

    inline IrSignal(const IrSignal& orig)
    : frequency(orig.frequency), intro(orig.intro), repeat(orig.repeat), ending(orig.ending) {
    }

    inline IrSignal(IrSignal&& orig)
    : frequency(orig.frequency), intro(ir::move(orig.intro)), repeat(ir::move(orig.repeat)), ending(ir::move(orig.ending)) {
    }

    template<typename T, typename U, typename V>
    inline IrSignal(T&& intro, U&& repeat, V&& ending, frequency_t frequency)
    : frequency(frequency), intro(ir::forward<T>(intro)), repeat(ir::forward<U>(repeat)), ending(ir::forward<V>(ending)) {
    }

    template<typename T, typename U, typename V>
    inline IrSignal(T&& intro, size_t introLength, U&& repeat, size_t repeatLength, V&& ending, size_t endingLength, frequency_t frequency)
    : frequency(frequency), intro(std::forward<T>(intro), introLength), repeat(ir::forward<U>(repeat), repeatLength), ending(ir::forward<V>(ending), endingLength) {
    }

private:
    const frequency_t frequency;
    const IrSequence intro;
    const IrSequence repeat;
    const IrSequence ending;

public:

    /**
     * Creates a (deep) copy of the current object.
     * The user must delete it manually.
     * @return Pointer to the cloned object.
     */
    IrSignal *clone() const;

    frequency_t getFrequency() const {
        return frequency;
    }

    const IrSequence& getEnding() const {
        return ending;
    }

    const IrSequence& getRepeat() const {
        return repeat;
    }

    const IrSequence& getIntro() const {
        return intro;
    }

    /**
     * Print a human readable representation of the IrSignal on the Stream supplied.
     * @param stream Stream onto the output is printed.
     * @param usingSigns is true, prepend marks with '+' and gaps with '-'.
     */
    void dump(Stream& stream, boolean usingSigns = false) const;

    /**
     * Print a human readable representation of the IrSignal on the Stream supplied, using signs.
     * @param stream Stream onto the output is printed.
     */
    void dumpWithSigns(Stream& stream) const {
        dump(stream, true);
    };

    /**
     * If the frequency is sensible, print it to the stream and return true.
     * Otherwise do nothing and return false.
     * No extra spaces or line feeds are generated.
     */
    boolean dumpFrequency(Stream& stream) const {
        return dumpFrequency(stream, frequency);
    };

    /**
     * Static version of dumpFrequency.
     * @param stream Stream onto the output is printed.
     * @param frequency modulation frequency
     */
    static boolean dumpFrequency(Stream& stream, frequency_t frequency);

    /**
     * Implementation of the count semantics, i.e.,
     * how many repetitions should be sent if the signal is sent noSend times.
     * @param noSends number of times to "send signal".
     */
    unsigned int noRepetitions(unsigned int noSends) const {
        return noSends == 0 ? 0
                : getIntro().isEmpty() ? noSends : noSends - 1;
    }


};

#endif	/* IRSIGNAL_H */
