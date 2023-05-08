/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:02:36 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/07 21:26:43 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

ASpell::ASpell(void)    {}

ASpell::ASpell(std::string name, std::string effects)   {
    this->name = name;       
    this->effects = effects;       
}

ASpell::ASpell(const ASpell& rhs)   {
    this->name = rhs.name;
    this->effects = rhs.effects;
}

std::string ASpell::getName(void)                       const    {
    return this->name;
}

std::string ASpell::getEffects(void)                    const    {
    return this->effects;
}

void                ASpell::launch(const ATarget& tgt)  const   {
    tgt.getHitBySpell(*this);
}

ASpell::~ASpell()   {}

ASpell&     ASpell::operator=(const ASpell& rhs)    {
    this->name = rhs.name;
    this->effects = rhs.effects;
    return *this;
}