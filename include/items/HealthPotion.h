#include "Item.h"

class HealthPotion : public Item {
public:
    HealthPotion(int count);
    void useItem(Character& target) override;
};