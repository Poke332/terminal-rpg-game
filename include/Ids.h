#pragma once

namespace Ids {

    namespace Stat {
        constexpr const char* hp = "hp";
        constexpr const char* max_hp = "max_hp";
        constexpr const char* attack = "attack";
        constexpr const char* armor = "armor";
        constexpr const char* crit_chance = "crit_chance";
        constexpr const char* crit_damage = "crit_damage";
        constexpr const char* damage_bonus = "damage_bonus";
        constexpr const char* damage_reduction = "damage_reduction";
        constexpr const char* block_chance = "block_chance";
        constexpr const char* healing_bonus_pct = "healing_bonus_percentage";
        constexpr const char* healing_bonus_base = "healing_bonus_base";
    }

    namespace SkillType {
        constexpr const char* single_cast_enemy = "single_cast_enemy";
        constexpr const char* single_cast_ally = "single_cast_ally";
        constexpr const char* self_cast = "self_cast";
        constexpr const char* aoe_enemy = "aoe_enemy";
        constexpr const char* aoe_adjacent_enemy = "aoe_adjacent_enemy";
        constexpr const char* aoe_ally = "aoe_ally";
        constexpr const char* aoe_adjacent_ally = "aoe_adjacent_ally";
    }

    namespace Resource {
        constexpr const char* rage = "Rage";
        constexpr const char* focus = "Focus";
        constexpr const char* meditation = "Meditation";
    }

    namespace ItemName {
        constexpr const char* health_potion = "Health Potion";
        constexpr const char* attack_scroll = "Attack Scroll";
    }

    namespace EffectName {
        constexpr const char* burning = "Burning";
        constexpr const char* hellfire = "Hellfire";
        constexpr const char* spore_rot = "Spore Rot";
    }

} // namespace Ids
