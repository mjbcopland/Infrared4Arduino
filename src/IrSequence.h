#ifndef IRSEQUENCE_H
#define	IRSEQUENCE_H

#include "InfraredTypes.h"

/**
 * This class consists of a vector of durations. The even entries denotes spaces,
 * while the odd entries denotes gaps. The length should always be even, i.e.,
 * the sequences starts with a space, and ends with a gap.
 * This class is immutable.
 */
class IrSequence {
private:
    const microseconds_t *durations;
    size_t length;

public:
    /** Create an empty sequence. */
    IrSequence();

    /**
     * Creates an IrSequence. Copies the durations array.
     * @param durations const array of microseconds durations
     * @param length length of durations. Should be even (not checked).
     */
    IrSequence(microseconds_t const* const& durations, size_t length);

    /**
     * Creates an IrSequence. Takes ownership of the durations array.
     * @param durations const array of microseconds durations
     * @param length length of durations. Should be even (not checked).
     */
    IrSequence(microseconds_t const*&& durations, size_t length);

    virtual ~IrSequence();

    /**
     * Creates an IrSequence. Copies the original data.
     * @param orig original IrSequence to be cloned
     */
    IrSequence(const IrSequence& orig);

    /**
     * Creates an IrSequence. Takes ownership of the original data.
     * @param orig original IrSequence to be cloned
     */
    IrSequence(IrSequence&& orig);

    /**
     * Returns the length of the data.
     * @return length
     */
    size_t getLength() const {
        return length;
    }

    boolean isEmpty() const {
        return length == 0;
    }

    const microseconds_t *getDurations() const {
        return durations;
    }

    /**
     * Creates a (deep) clone of the current object.
     * The used must delete it manually.
     * @return pointer to the cloned object
     */
    IrSequence *clone() const;

    /**
     * Prints the IrSequence on the stream provided.
     * @param stream Stream onto the output is printed.
     * @param usingSigns If true,  Gaps are written with a leading '+', spaces with a leading '-'.
     */
    void dump(Stream& stream, boolean usingSigns = false) const;

    /**
     * Prints the IrSequence on the stream provided. Gaps are written with a
     * leading '+', spaces with a leading '-'.
     * @param stream Stream onto the output is printed.
     */
    void dumpWithSigns(Stream& stream) const {
        dump(stream, true);
    };
};

#endif	/* IRSEQUENCE_H */

