#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "app/ConsoleApp.h"
#include "fakes/FakeInputReader.h"
#include "inspection/ServiceCenter.h"
#include "park/Park.h"
#include "park/ParkReport.h"
#include "park/ParkService.h"
#include "support/CoutCapture.h"
#include "support/TestAssets.h"

// Сценарии консоли: ввод подменяется FakeInputReader, вывод перехватывается.
// Пункты меню: 1 - принять транспорт, 2 - принять вещь, 3 - удалить,
// 8 - демонстрация, 0 - выход.
class ConsoleAppTest : public ::testing::Test {
protected:
    Park park;
    ServiceCenter center;
    ParkService service{park, center};
    ParkReport report{park};
    TransportFactory transports;
    ItemFactory items;

    void SetUp() override {
        transports.registerType("scooter", [](InputReader& input) {
            const std::string number = input.readString("");
            const int simplicity = input.readInt("");

            return std::make_unique<Scooter>(
                number, "Scooter", "Model", EquipmentCondition::GOOD,
                simplicity);
        });

        // Этот шлем всегда сломан: техосмотр должен его отклонить.
        items.registerType("broken helmet", [](InputReader& input) {
            const std::string number = input.readString("");

            return std::make_unique<Helmet>(
                number, "Helmet", EquipmentCondition::BROKEN, "M");
        });
    }

    std::string run(std::vector<std::string> answers) {
        FakeInputReader input(std::move(answers));
        ConsoleApp app(service, report, transports, items, input);
        CoutCapture capture;

        app.run();

        return capture.str();
    }
};

TEST_F(ConsoleAppTest, ExitsOnZero) {
    EXPECT_NO_THROW(run({"0"}));
    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, ExitsQuietlyWhenInputEnds) {
    EXPECT_NO_THROW(run({}));
}

TEST_F(ConsoleAppTest, ExitsQuietlyWhenInputEndsInsideScenario) {
    EXPECT_NO_THROW(run({"1", "1", "SC-1"}));
    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, UnknownMenuItemChangesNothing) {
    EXPECT_NO_THROW(run({"99", "0"}));
    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, AcceptsTransportThatPassesInspection) {
    run({"1", "1", "SC-1", "8", "0"});

    EXPECT_EQ(park.count(), 1U);
    EXPECT_TRUE(park.findByInventoryNumber("SC-1") != nullptr);
}

TEST_F(ConsoleAppTest, InventoryItemIsInspectedAndRejectedWhenBroken) {
    run({"2", "1", "HM-1", "0"});

    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, InvalidDataDoesNotCrashAndAddsNothing) {
    EXPECT_NO_THROW(run({"1", "1", "SC-1", "11", "0"}));
    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, DuplicateInventoryNumberIsRefused) {
    run({"1", "1", "SC-1", "8", "1", "1", "SC-1", "8", "0"});

    EXPECT_EQ(park.count(), 1U);
}

TEST_F(ConsoleAppTest, OutOfRangeTypeChoiceChangesNothing) {
    EXPECT_NO_THROW(run({"1", "7", "0"}));
    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, BackFromTypeListChangesNothing) {
    EXPECT_NO_THROW(run({"1", "0", "0"}));
    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, RemovesItemByInventoryNumber) {
    run({"1", "1", "SC-1", "8", "3", "SC-1", "0"});

    EXPECT_EQ(park.count(), 0U);
}

TEST_F(ConsoleAppTest, RemovingMissingItemIsHarmless) {
    run({"1", "1", "SC-1", "8", "3", "NOPE", "0"});

    EXPECT_EQ(park.count(), 1U);
}

TEST_F(ConsoleAppTest, ReportsDoNotChangeThePark) {
    run({"1", "1", "SC-1", "8", "4", "5", "6", "7", "0"});

    EXPECT_EQ(park.count(), 1U);
}

TEST_F(ConsoleAppTest, BeginnerListShowsSuitableTransport) {
    const std::string output = run({"1", "1", "SC-1", "8", "6", "0"});

    EXPECT_TRUE(output.find("SC-1") != std::string::npos);
}

TEST_F(ConsoleAppTest, InventoryListShowsNumbers) {
    const std::string output = run({"1", "1", "SC-1", "3", "7", "0"});

    EXPECT_TRUE(output.find("SC-1") != std::string::npos);
}

TEST_F(ConsoleAppTest, DemoAcceptsOnlyItemsThatPassInspection) {
    run({"8", "0"});

    EXPECT_EQ(park.count(), 7U);
    EXPECT_TRUE(park.findByInventoryNumber("EB-002") == nullptr);
    EXPECT_TRUE(park.findByInventoryNumber("HM-002") == nullptr);
}

TEST_F(ConsoleAppTest, DemoShowsEnergyAndNumbers) {
    const std::string output = run({"8", "0"});

    EXPECT_TRUE(output.find("5.30") != std::string::npos);
    EXPECT_TRUE(output.find("SC-001") != std::string::npos);
    EXPECT_TRUE(output.find("CS-001") != std::string::npos);
}

TEST_F(ConsoleAppTest, DemoPicksTwoTransportsForBeginners) {
    run({"8", "0"});

    EXPECT_EQ(report.beginnerFriendly().size(), 2U);
}

TEST_F(ConsoleAppTest, DemoCanBeRunTwiceWithoutDuplicates) {
    EXPECT_NO_THROW(run({"8", "8", "0"}));
    EXPECT_EQ(park.count(), 7U);
}
