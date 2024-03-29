/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:51:28 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 15:59:57 by oboutarf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

ATarget::ATarget(void)  {}

ATarget::ATarget(std::string type)  {
    this->type = type;
}

ATarget::ATarget(const ATarget& rhs)   {
    this->type = rhs.type;
}

void    ATarget::getHitBySpell(const ASpell& shot)          const   {
    std::cout << this->getType() << " has been " << shot.getEffects() << "!" << std::endl;
}

std::string const&  ATarget::getType(void)                  const  {
    return this->type;
}

ATarget::~ATarget() {}

ATarget&    ATarget::operator=(const ATarget& rhs)   {
    this->type = rhs.type;
    return *this;
}
