/*
 * PrmDblImplCfg.hpp
 *
 * Project override for the parameter database. Keep this sized to the
 * expected number of deployment parameters plus margin.
 */

#ifndef PRMDB_PRMDBLIMPLCFG_HPP_
#define PRMDB_PRMDBLIMPLCFG_HPP_

namespace {

enum {
    PRMDB_NUM_DB_ENTRIES = 10,    // !< Number of entries in the parameter database
    PRMDB_ENTRY_DELIMITER = 0xA5  // !< Byte value that should precede each parameter in file; sanity check against
                                  // file integrity. Should match ground system.
};

}

#endif /* PRMDB_PRMDBLIMPLCFG_HPP_ */
