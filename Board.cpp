#include "Board.h"
#include "Player.h"

void Board::free()
{
	for (int i = 0; i < fieldCount; i++) {
		delete fields[i];
		fields[i] = nullptr;
	}

	delete[] fields;
	fields = nullptr;
}

void Board::copyFrom(const Board& other)
{
	fieldCount = other.fieldCount;
	fields = new Field * [fieldCount] { nullptr };
	for (size_t i = 0; i < 40; i++)
	{
		fields[i] = other.fields[i]->clone();
	}
	for (size_t i = 0; i < other.allProperties.size(); i++)
	{
		int indxToCast = -1;
		Property* propRef = other.allProperties[i];
		for (size_t j = 0; j < 40; i++)
		{
			Property* asProp = dynamic_cast<Property*>(other.fields[j]);
			if (!asProp) continue;

			if (asProp->getName() == propRef->getName())
			{
				indxToCast = j;
				break;
			}
		}
		allProperties.push_back(dynamic_cast<Property*>(fields[i]));
	}
}

void Board::moveFrom(Board&& other)
{
	fieldCount = other.fieldCount;
	fields = other.fields;
	allProperties = other.allProperties;

	other.fields = nullptr;
	for (size_t i = 0; i < other.allProperties.size(); i++)
	{
		other.allProperties[i] = nullptr;
	}
}

Board::Board(int size) : fieldCount(size) {
	fields = new Field * [fieldCount] {};
}

Board::Board(const Board& other)
{
	copyFrom(other);
}

Board::Board(Board&& other) noexcept
{
	moveFrom(std::move(other));
}

Board& Board::operator=(const Board& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Board& Board::operator=(Board&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

Board::~Board() {
	free();
}

void Board::setField(int index, Field* field) {
	if (index >= 0 && index < fieldCount)
		fields[index] = field;

	if (field && field->isProperty()) {
		Property* p = field->asProperty();
		registerProperty(p);
	}
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

		std::cout << "You own all properties of color group. Build cottage for 25$? (y/n): ";
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

		int cottageCount = 0;
		for (int m = 0; m < selected->getMortgageCount(); ++m) {
			if (selected->getMortgageAt(m)->getType() == MortgageType::Cottage)
				cottageCount++;
		}

		if (cottageCount == 4) {
			std::cout << "This property has 4 cottages. Build a castle for 50$ instead? (y/n): ";
			char castleChoice;
			std::cin >> castleChoice;
			if (castleChoice == 'y' || castleChoice == 'Y') {
				if (player->getBalance() < 50) {
					std::cout << "Insufficient balance to buy castle!";
				}
				else {
					selected->buildCastle();
					player->pay(50);
					std::cout << "Castle built on " << selected->getName().c_str() << "!\n";
				}
			}
		}
		else {
			if (player->getBalance() < 50) {
				std::cout << "Insufficient balance to buy cottage!";
			}
			else {
				selected->buildCottage();
				player->pay(25);
				std::cout << "Cottage built on " << selected->getName().c_str() << "!\n";
			}
		}
	}
}

Property* Board::tryConvertToProperty(Field* field) {
	return field ? field->asProperty() : nullptr;
}

void Board::handleLanding(Player* player) {
	
	Field* current = getField(player->getPosition());
	if (!current) return;

	std::cout << player->getName() << " landed on field " << player->getPosition() << ".\n";

	current->onLand(*player);
}
