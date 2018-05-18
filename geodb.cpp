#include "geodb.h"
#include "geoscheme.h"

#include <cassert>
#include <sqlpp11/sqlpp11.h>

namespace pt {

//#define DEBUG_QUERIES

namespace sql = sqlpp::sqlite3;

static db::Drinkwaterbeschermingsgebieden drinkingwaterProtection;

static sql::connection_config createConfig(const std::string& filename, GeoDatabase::AccessMode access)
{
    sql::connection_config config;
    config.path_to_database = filename;

    if (access == GeoDatabase::AccessMode::ReadOnly) {
        config.flags = SQLITE_OPEN_READONLY;
    } else if (access == GeoDatabase::AccessMode::Create) {
        config.flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
    }

#ifdef DEBUG_QUERIES
    config.debug = true;
#endif

    return config;
}

template <typename SelectType>
using PreparedStatement = decltype(((sql::connection*)nullptr)->prepare(*(SelectType*)nullptr));

auto getDrinkWaterProtectionRiskQuery = []() {
    return select(drinkingwaterProtection.value)
        .from(drinkingwaterProtection)
        .where(drinkingwaterProtection.xcoord == parameter(drinkingwaterProtection.xcoord) &&
               drinkingwaterProtection.ycoord == parameter(drinkingwaterProtection.ycoord));
};

struct GeoDatabase::PreparedStatements
{
    using GetDrinkingWaterProtectionRiskQuery = decltype(getDrinkWaterProtectionRiskQuery());
    PreparedStatement<GetDrinkingWaterProtectionRiskQuery> getGetDrinkingWaterProtectionRisk;
};

GeoDatabase::GeoDatabase()
: _db(createConfig("db.sqlite", AccessMode::ReadOnly))
, _statements(std::make_unique<PreparedStatements>())
{
    prepareStatements();
}

GeoDatabase::~GeoDatabase() = default;

void GeoDatabase::prepareStatements()
{
    _statements->getGetDrinkingWaterProtectionRisk = _db.prepare(getDrinkWaterProtectionRiskQuery());
}

}
