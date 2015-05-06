
#include <gtest/gtest.h>
#include <leveldb/db.h>

class LevelDBTest : public ::testing::Test {
protected:
    LevelDBTest(){};
    virtual ~LevelDBTest(){};

    virtual void SetUp();
    virtual void TearDown();
    leveldb::DB* db;
};

void LevelDBTest::SetUp() {
    db = NULL;
}

void LevelDBTest::TearDown() {
    if( db != NULL ){
        delete db;
        db = NULL;
    }
}

leveldb::Status openTempDB( leveldb::DB** pDB ) {
    long int tmp = static_cast<long int>( time(NULL) );
    std::stringstream ss;
    ss << "/tmp/tempdb-" << tmp;
    leveldb::Options options;
    options.create_if_missing = true;
    return leveldb::DB::Open( options, ss.str(), pDB );
}

TEST_F( LevelDBTest, testOpenDB ){
    leveldb::Status st = openTempDB( &db );
    EXPECT_TRUE( st.ok() );
    EXPECT_TRUE( db != NULL );
}

TEST_F( LevelDBTest, testPutGetValue ){
    leveldb::Status st = openTempDB( &db );
    EXPECT_TRUE( st.ok() );
    EXPECT_TRUE( db != NULL );

    std::string key = "key";
    std::string value;
    st = db->Get( leveldb::ReadOptions(), key, &value );
    EXPECT_FALSE( st.ok() );

    st = db->Put( leveldb::WriteOptions(), key, "value" );
    EXPECT_TRUE( st.ok() );

    st = db->Get( leveldb::ReadOptions(), key, &value );
    EXPECT_TRUE( st.ok() );
    EXPECT_EQ( std::string( "value" ), value );
}

TEST_F( LevelDBTest, testDeleteValue ){
    leveldb::Status st = openTempDB( &db );
    EXPECT_TRUE( st.ok() );
    EXPECT_TRUE( db != NULL );

    std::string key = "key1";
    std::string value;
    st = db->Get( leveldb::ReadOptions(), key, &value );
    EXPECT_FALSE( st.ok() );

    st = db->Delete( leveldb::WriteOptions(), key );
    EXPECT_TRUE( st.ok() );

    st = db->Put( leveldb::WriteOptions(), key, "value" );
    EXPECT_TRUE( st.ok() );

    st = db->Delete( leveldb::WriteOptions(), key );
    EXPECT_TRUE( st.ok() );

    st = db->Get( leveldb::ReadOptions(), key, &value );
    EXPECT_FALSE( st.ok() );
}