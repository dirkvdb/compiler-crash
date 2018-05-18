#pragma once

#include <mutex>
#include <optional>
#include <sqlpp11/sqlite3/sqlite3.h>
#include <string>

namespace pt {

// Database that contains precomputed risks for all the discharge points coordinates
class GeoDatabase
{
public:
    enum class AccessMode
    {
        ReadOnly,
        Create
    };

    GeoDatabase();
    ~GeoDatabase();

private:
    void prepareStatements();
    sqlpp::sqlite3::connection _db;
    struct PreparedStatements;
    std::unique_ptr<PreparedStatements> _statements;
};
}
