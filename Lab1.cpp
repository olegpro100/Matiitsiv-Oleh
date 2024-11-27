#include <iostream>
#include <vector>
#include <string>
#include <memory>

// ����������
class User {
private:
    std::string name;

public:
    explicit User(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }
};

// ���� � Immutable
class Car {
private:
    const std::string model;
    const std::shared_ptr<User> currentUser;
    const std::vector<std::shared_ptr<User>> previousUsers;

public:
    Car(const std::string& model, const std::shared_ptr<User>& currentUser,
        const std::vector<std::shared_ptr<User>>& previousUsers)
        : model(model), currentUser(currentUser), previousUsers(previousUsers) {}

    // ��������� ������ ��'���� � ��������� ������������
    Car changeUser(const std::shared_ptr<User>& newUser) const {
        std::vector<std::shared_ptr<User>> updatedUsers = previousUsers;
        if (currentUser != nullptr) {
            updatedUsers.push_back(currentUser);
        }
        return Car(model, newUser, updatedUsers);
    }

    void printCarInfo() const {
        std::cout << "������ ���������: " << model << std::endl;
        if (currentUser) {
            std::cout << "�������� ����������: " << currentUser->getName() << std::endl;
        }
        else {
            std::cout << "��������� ����� �� ���������������." << std::endl;
        }
        std::cout << "������ ������������ ���������:" << std::endl;
        for (const auto& user : previousUsers) {
            std::cout << "- " << user->getName() << std::endl;
        }
    }
};

int main() {
    auto user1 = std::make_shared<User>("���� ��������");
    auto user2 = std::make_shared<User>("����� �������");

    setlocale(LC_ALL, "Ukrainian");

    // �����. ��'���� ���������
    Car car("Toyota Corolla", nullptr, {});
    car.printCarInfo();

    // (��������� ������ ��'����)
    auto updatedCar1 = car.changeUser(user1);
    updatedCar1.printCarInfo();

    // �� ���� ���� ������.
    auto updatedCar2 = updatedCar1.changeUser(user2);
    updatedCar2.printCarInfo();

    return 0;
}