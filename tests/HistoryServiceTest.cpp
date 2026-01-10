#include "../include/domain/HistoryService.h"
#include "../include/domain/EnvironmentalMetric.h"
#include "mock/MockStorage.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <memory>

using ::testing::Assign;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SaveArg;
using ::testing::SetArgReferee;
using std::chrono::system_clock;


TEST(HistoryServiceTest, processMeasurementSucceeds) {
    const auto mockStorage = std::make_shared<MockStorage>();

    const Domain::HistoryService historyService{mockStorage};

    EXPECT_CALL(*mockStorage, addMeasurement(::testing::_));

    ASSERT_NO_THROW(
        historyService.processMeasurement(Domain::EnvironmentalMetric{std::chrono::system_clock::now(), 10, 20, 30}));
}

TEST(HistoryServiceTest, processMeasurementFailure) {
    const auto mockStorage = std::make_shared<MockStorage>();

    const Domain::HistoryService historyService{mockStorage};

    EXPECT_CALL(*mockStorage, addMeasurement).WillOnce(::testing::Throw(std::runtime_error{"TEST"}));

    ASSERT_THROW(
        historyService.processMeasurement(Domain::EnvironmentalMetric{std::chrono::system_clock::now(), 10, 20, 30}),
        std::runtime_error);
}
