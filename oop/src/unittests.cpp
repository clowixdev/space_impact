#include <iostream>
#include <gtest/gtest.h>

#include "./classes/entity.h"
#include "./classes/player.h"
#include "./classes/boss.h"
#include "./classes/bullet.h"
#include "./classes/heart.h"
#include "./classes/asteroid.h"
#include "constants.h"

TEST(SpaceImpactTests, EntityTest) {
    EntityClass *testEntity = new EntityClass();

    testEntity->setSize(50);
    testEntity->setPosX(1000);
    testEntity->setPosY(300);

    EXPECT_EQ(testEntity->getSize(), 50);
    EXPECT_EQ(testEntity->getPosX(), 1000);
    EXPECT_EQ(testEntity->getPosY(), 300);

    testEntity->changePosX(100);
    testEntity->changePosY(-100);

    EXPECT_EQ(testEntity->getPosX(), 1000 + 100);
    EXPECT_EQ(testEntity->getPosY(), 300 - 100);

    delete testEntity;
}  

TEST(SpaceImpactTests, PlayerTest) {
    PlayerClass *testPlayer = new PlayerClass();
    testPlayer->init();

    testPlayer->changePosX(100);
    testPlayer->changePosY(-100);

    EXPECT_EQ(testPlayer->getPosX(), testPlayer->getSize() + 100);
    EXPECT_EQ(testPlayer->getPosY(), WINDOW_HEIGHT / 2 - 100);

    testPlayer->setLevel(2);
    testPlayer->changeScore(5);
    testPlayer->changeLives(-2);
    testPlayer->setSize(100);

    EXPECT_EQ(testPlayer->getLevel(), 2);
    EXPECT_EQ(testPlayer->getSize(), 100);
    EXPECT_EQ(testPlayer->getScore(), 0 + 5);
    EXPECT_EQ(testPlayer->getLives(), 3 - 2);

    delete testPlayer;
}

TEST(SpaceImpactTests, BossTest) {
    BossClass *testBoss = new BossClass();
    testBoss->init();

    testBoss->changePosX(100);
    testBoss->changePosY(-100);

    EXPECT_EQ(testBoss->getPosX(), WINDOW_WIDTH - testBoss->getSize() * 2 + 100);
    EXPECT_EQ(testBoss->getPosY(), WINDOW_HEIGHT / 2 - 100);

    testBoss->changeLives(-2);
    testBoss->setReachedBot(true);
    testBoss->setReachedTop(false);

    EXPECT_EQ(testBoss->getLives(), 10 - 2);
    EXPECT_EQ(testBoss->hasReachedBot(), true);
    EXPECT_EQ(testBoss->hasReachedTop(), false);

    delete testBoss;
}

TEST(SpaceImpactTests, HeartTest) {
    HeartClass *testHeart = new HeartClass();
    testHeart->init();

    testHeart->changePosX(100);
    testHeart->changePosY(-100);

    EXPECT_EQ(testHeart->getPosX(), WINDOW_WIDTH - testHeart->getSize() + 100);
    EXPECT_EQ(testHeart->getPosY(), -testHeart->getSize() - 100);

    testHeart->setSpawning(false);
    testHeart->setSpeed(25);

    EXPECT_EQ(testHeart->isSpawning(), false);
    EXPECT_EQ(testHeart->getSpeed(), 25);
    
    delete testHeart;
}

TEST(SpaceImpactTests, BulletTest) {
    BulletClass *testBullet = new BulletClass();
    testBullet->init();

    testBullet->changePosX(100);
    testBullet->changePosY(-100);

    EXPECT_EQ(testBullet->getPosX(), -testBullet->getSize() + 100);
    EXPECT_EQ(testBullet->getPosY(), -testBullet->getSize() - 100);

    testBullet->setSize(25);
    testBullet->setSpeed(25);

    EXPECT_EQ(testBullet->getSize(), 25);
    EXPECT_EQ(testBullet->getSpeed(), 25);

    delete testBullet;
}

TEST(SpaceImpactTests, AsteroidTest) {
    AsteroidClass *testSmallAsteroid = new AsteroidClass();
    testSmallAsteroid->init(SA_SIZE, SA_SPEED);

    testSmallAsteroid->changePosX(100);
    testSmallAsteroid->changePosY(-100);

    EXPECT_EQ(testSmallAsteroid->getPosX(), WINDOW_WIDTH - testSmallAsteroid->getSize() + 100);
    EXPECT_EQ(testSmallAsteroid->getPosY(), -testSmallAsteroid->getSize() - 100);

    testSmallAsteroid->setSize(25);
    testSmallAsteroid->setSpeed(25);

    EXPECT_EQ(testSmallAsteroid->getSize(), 25);
    EXPECT_EQ(testSmallAsteroid->getSpeed(), 25);

    delete testSmallAsteroid;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}