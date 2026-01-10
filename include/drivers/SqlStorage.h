#ifndef AIRLOG_SQL_STORAGE_H_
#define AIRLOG_SQL_STORAGE_H_

#include "IHistoryStorage.h"
#include <sqlite3.h>
#include <string>

namespace Drivers {
    struct SqlStorage : IHistoryStorage {
        explicit SqlStorage(const std::string &);

        ~SqlStorage() override;

        void addMeasurement(Domain::EnvironmentalMetric) const override;

        std::vector<Domain::EnvironmentalMetric> getMetricsForLastHours(int) const override;

        sqlite3 *getDB() const;

    private:
        void createSchema() const;

        sqlite3 *m_db{};
        sqlite3_stmt *m_insertEnvironmentalMetricsStmt{};
        sqlite3_stmt *m_selectEnvironmentalMetricsStmt{};
        sqlite3_stmt *m_createTableEnvironmentalMetricsStmt{};
    };
}
#endif
