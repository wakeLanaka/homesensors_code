#include "../include/app/AirQualityController.h"
#include "mock/MockSensor.h"
#include "mock/MockService.h"
#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <memory>


using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

struct AirQualityTest : testing::Test {
    std::shared_ptr<Drivers::MockSensor> mockSensor;
    std::shared_ptr<Domain::MockService> mockService;

    void SetUp() override {
        mockSensor = std::make_shared<Drivers::MockSensor>();
        mockService = std::make_shared<Domain::MockService>();
    }
};

TEST_F(AirQualityTest, WarningWhenCo2IsBetween1000ppmAnd2000ppm) {
    App::AirQualityController controller{mockSensor, mockService};

    const Domain::EnvironmentalMetric metric{std::chrono::system_clock::now(), 1500.0f, 0, 0};

    EXPECT_CALL(*(mockSensor), readData)
            .WillOnce(Return(metric));
    EXPECT_CALL(*(mockService), processMeasurement(metric));
    EXPECT_CALL(*(mockService), getMetricsForLastHours(24));

    controller.update();
}

TEST_F(AirQualityTest, OkWhenCo2IsBelow1000ppm) {
    App::AirQualityController controller{mockSensor, mockService};

    SensorData goodCo2 = {999.0f};
    EXPECT_CALL(*mockSensor, readData(testing::_))
            .WillOnce(DoAll(SetArgReferee<0>(goodCo2), Return(true)));

    ASSERT_TRUE(controller.update());
    ASSERT_EQ(controller.getStatus(), Status::GOOD);
}

//
// TEST_F(AirQualityTest, UnacceptableWhenCo2IsMoreThan2000ppm) {
//     App::AirQualityController controller{mockSensor, mockService};
//
//     SensorData unacceptableCo2 = {2000.0f};
//     EXPECT_CALL(*mockSensor, readData(_))
//             .WillOnce(DoAll(SetArgReferee<0>(unacceptableCo2), Return(true)));
//
//     ASSERT_TRUE(controller.update());
//     ASSERT_EQ(controller.getStatus(), Status::UNACCEPTABLE);
// }
//
// TEST_F(AirQualityTest, ErrorWhenReadDataDoesNotReturnTrue) {
//     App::AirQualityController controller{mockSensor, mockService};
//
//     SensorData unacceptableCo2 = {0.0f};
//     EXPECT_CALL(*mockSensor, readData(_))
//             .WillOnce(DoAll(SetArgReferee<0>(unacceptableCo2), Return(false)));
//
//     ASSERT_FALSE(controller.update());
//     ASSERT_EQ(controller.getStatus(), Status::ERROR);
// }
//
// TEST_F(AirQualityTest, HandlesSensorErrorGracefully) {
//     App::AirQualityController controller{mockSensor, mockService};
//
//     EXPECT_CALL(*mockSensor, readData(_))
//             .WillOnce(testing::Throw(std::runtime_error("Sensor nicht gefunden")));
//
//     // EXPECT_CALL(*display, showStatus(testing::hasSubstr("Fehler")));
//     // EXPECT_CALL(*display, refresh());
//
//     controller.update();
// }
