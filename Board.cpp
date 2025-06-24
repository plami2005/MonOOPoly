#include "Board.h"
#include "Player.h"

Board::Board(int size) : fieldCount(size) {
    fields = new Field * [fieldCount] {};
}

Board::~Board() {
    for (int i = 0; i < fieldCount; ++i)
        delete fields[i];
    delete[] fields;
}

void Board::setField(int index, Field* field) {
    if (index >= 0 && index < fieldCount)
        fields[index] = field;
}

Field* Board::getField(int index) const {
    if (index < 0 || index >= fieldCount)
        return nullptr;
    return fields[index];
}

int Board::getSize() const {
    return fieldCount;
}

void Board::registerProperty(Property* p) {
    allProperties.push_back(p);
}

const MyVector<Property*>& Board::getAllProperties() const {
    return allProperties;
}

void Board::offerBuildingOptions(Player* player) {
    for (int c = 0; c < getAllProperties().size(); ++c) {
        Color col = getAllProperties()[c]->getColor();
        if (!player->ownsAllOfColor(col, this))
            continue;

        std::cout << "You own all properties of color group. Build cottage? (y/n): ";
        char choice;
        std::cin >> choice;

        if (choice != 'y' && choice != 'Y')
            continue;

        std::cout << "Choose property to build cottage on:\n";
        const MyVector<Property*>& props = getAllProperties();
        for (size_t i = 0; i < props.size(); ++i) {
            if (props[i]->getColor() == col && props[i]->getOwner() == player) {
                std::cout << i << ": " << props[i]->getName().c_str() << "\n";
            }
        }

        int selectedIndex = -1;
        std::cin >> selectedIndex;
        if (selectedIndex < 0 || selectedIndex >= props.size())
            continue;

        Property* selected = props[selectedIndex];
        if (selected->getOwner() != player || selected->getColor() != col)
            continue;

        // Преброяваме къщите на имота
        int cottageCount = 0;
        for (int m = 0; m < selected->getMortgageCount(); ++m) {
            if (selected->getMortgageAt(m)->getType() == MortgageType::Cottage)
                cottageCount++;
        }

        if (cottageCount == 4) {
            std::cout << "This property has 4 cottages. Build a castle instead? (y/n): ";
            char castleChoice;
            std::cin >> castleChoice;
            if (castleChoice == 'y' || castleChoice == 'Y') {
                selected->buildCastle();
                std::cout << "Castle built on " << selected->getName().c_str() << "!\n";
            }
        }
        else {
            selected->buildCottage();
            std::cout << "Cottage built on " << selected->getName().c_str() << "!\n";
        }
    }
}

// Премести това в началото на Board.cpp, преди offerBuildingOptions
Property* Board::tryConvertToProperty(Field* field) {
    return field ? field->asProperty() : nullptr;
}


void Board::handleLanding(Player* player) {
    Field* current = getField(player->getPosition());
    if (!current) return;

    Property* property = tryConvertToProperty(current);
    if (!property)
        return;

    if (property->getOwner() == nullptr) {
        std::cout << player->getName() << " landed on " << property->getName().c_str() << ". Price: $" << property->getPrice() << ". Buy? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            if (player->getBalance() >= property->getPrice()) {
                player->pay(property->getPrice());
                property->setOwner(player);
                player->addOwnedProperty(property);
                std::cout << "You bought " << property->getName().c_str() << "!\n";
            }
            else {
                std::cout << "Not enough money.\n";
            }
        }
    }
    else if (property->getOwner() != player) {
        int rent = property->calculateRent();
        std::cout << player->getName() << " landed on " << property->getName().c_str()
            << " owned by " << property->getOwner()->getName() << ". Pays rent: $" << rent << "\n";
        if (!player->pay(rent)) {
            std::cout << player->getName().c_str() << " couldn't afford the rent and went bankrupt!\n";

            for (int i = 0; i < allProperties.size(); ++i) {
                if (allProperties[i]->getOwner() == player)
                    allProperties[i]->setOwner(nullptr);
            }

            player->bankrupt();
        }
        else {
            property->getOwner()->receive(rent);
        }

    }
}
