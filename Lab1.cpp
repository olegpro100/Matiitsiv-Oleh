#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Користувач
class User {
private:
    std::string name;

public:
    explicit User(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }
};

// Клас з Immutable
class Car {
private:
    const std::string model;
    const std::shared_ptr<User> currentUser;
    const std::vector<std::shared_ptr<User>> previousUsers;

public:
    Car(const std::string& model, const std::shared_ptr<User>& currentUser,
        const std::vector<std::shared_ptr<User>>& previousUsers)
        : model(model), currentUser(currentUser), previousUsers(previousUsers) {}

    // створення нового об'єкта з оновленим користувачем
    Car changeUser(const std::shared_ptr<User>& newUser) const {
        std::vector<std::shared_ptr<User>> updatedUsers = previousUsers;
        if (currentUser != nullptr) {
            updatedUsers.push_back(currentUser);
        }
        return Car(model, newUser, updatedUsers);
    }

    void printCarInfo() const {
        std::cout << "Модель автомобіля: " << model << std::endl;
        if (currentUser) {
            std::cout << "Поточний користувач: " << currentUser->getName() << std::endl;
        }
        else {
            std::cout << "Автомобіль наразі не використовується." << std::endl;
        }
        std::cout << "Історія користувачів автомобіля:" << std::endl;
        for (const auto& user : previousUsers) {
            std::cout << "- " << user->getName() << std::endl;
        }
    }
};

int main() {
    auto user1 = std::make_shared<User>("Іван Іваненко");
    auto user2 = std::make_shared<User>("Олена Петрівна");

    setlocale(LC_ALL, "Ukrainian");

    // почат. об'єкта автомобіля
    Car car("Toyota Corolla", nullptr, {});
    car.printCarInfo();

    // (створення нового об'єкта)
    auto updatedCar1 = car.changeUser(user1);
    updatedCar1.printCarInfo();

    // Ще одна зміна корист.
    auto updatedCar2 = updatedCar1.changeUser(user2);
    updatedCar2.printCarInfo();

    return 0;
}