/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:30:13 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 17:14:50 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "SpellBook.hpp"

SpellBook::SpellBook()  {}

void    SpellBook::learnSpell(ASpell* lSpell)   {
    if (lSpell)  {
        std::vector<ASpell*>::iterator   it = spells.begin();
        for (; it != spells.end(); it++)  {
            if ((*it)->getName() == lSpell->getName())
                return ;
        }
        spells.push_back(lSpell->clone());
    }
}

void    SpellBook::forgetSpell(std::string const& fSpell)   {
    std::vector<ASpell*>::iterator  it = spells.begin();
    for (; it != spells.end(); it++) {
        if ((*it)->getName() == fSpell)    {
            delete *it;
            spells.erase(it);
            return ;
        }
    }
}

ASpell  *SpellBook::createSpell(std::string const& gSpell)  {
    std::vector<ASpell*>::iterator  it = spells.begin();
    for (; it != spells.end(); it++)
        if ((*it)->getName() == gSpell)
            return *it;
    return NULL;
}

SpellBook::~SpellBook() {}