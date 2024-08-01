#include <iostream>
#include <optional>
#include <string>

// 模拟从数据库查询用户信息的结构体
struct User {
    int id;
    std::string firstName;
    std::optional<std::string> middleName;
    std::string lastName;
};

// 模拟从数据库查询用户信息的函数
std::optional<User> queryUserFromDatabase(int userId) {
    // 模拟数据库查询逻辑
    if (userId == 1) {
        return User{1, "John", "Paul", "Doe"};
    } else if (userId == 2) {
        return User{2, "Jane", std::nullopt, "Smith"};
    } else {
        return std::nullopt; // 用户不存在
    }
}

void printUserInfo(const User& user) {
    std::cout << "User ID: " << user.id << std::endl;
    std::cout << "First Name: " << user.firstName << std::endl;
    if (user.middleName) {
        std::cout << "Middle Name: " << *user.middleName << std::endl;
    } else {
        std::cout << "Middle Name: Not provided" << std::endl;
    }
    std::cout << "Last Name: " << user.lastName << std::endl;
}

int main() {
    int userId = 1;
    auto user = queryUserFromDatabase(userId);

    if (user) {
        printUserInfo(*user);
    } else {
        std::cout << "User with ID " << userId << " not found." << std::endl;
    }

    userId = 2;
    user = queryUserFromDatabase(userId);

    if (user) {
        printUserInfo(*user);
    } else {
        std::cout << "User with ID " << userId << " not found." << std::endl;
    }

    userId = 3;
    user = queryUserFromDatabase(userId);

    if (user) {
        printUserInfo(*user);
    } else {
        std::cout << "User with ID " << userId << " not found." << std::endl;
    }

    return 0;
}