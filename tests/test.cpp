#include <Transaction.h>
#include <Account.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using::testing::Return;
using::testing::AtLeast;
using::testing::NiceMock;

class MockAccount: public Account{
public:
MockAccount(int id, int balance):Account(id, balance){}
MOCK_METHOD(int, GetBalance, (), (const, override));
MOCK_METHOD(void, ChangeBalance, (int diff), (override));
MOCK_METHOD(void, Lock, (), (override));
MOCK_METHOD(void, Unlock, (), (override));
};

class MockTransaction: public Transaction{
public:
MOCK_METHOD(void, SaveToDataBase, (Account& from, Account& to, int sum), (override));
};

TEST(Account, GetBalance){
NiceMock<MockAccount> acc(1,100);
EXPECT_EQ(acc.Account::GetBalance(), 100);
}

TEST(Account, ChangeBalance){
NiceMock<MockAccount> acc(0, 100);
EXPECT_THROW(acc.Account::ChangeBalance(50), std::runtime_error);
acc.Account::Lock();
acc.Account::ChangeBalance(50);
EXPECT_EQ(acc.Account::GetBalance(), 150);
}


