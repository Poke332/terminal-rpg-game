#include "Item.h"

class AttackScroll : public Item {
public:
    AttackScroll(int count);
    void useItem(Character& target) override;
};