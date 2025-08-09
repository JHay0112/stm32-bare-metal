/**
 * Control of flash metadata region. Loaded at compile time.
 * Used for storage of "special" constants (e.g. a version number) that may be
 * used in debugging a device.
 *
 * Author: J. L. Hay
 */

#ifndef SYS_METADATA_H
#define SYS_METADATA_H


#define SYS_METADATA_SET_STR(name, len, val) \
    __attribute__((used, section (".metadata"))) \
    static const char name[len] = val


#endif