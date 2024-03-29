/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:31:01 by oboutarf          #+#    #+#             */
/*   Updated: 2023/05/08 14:40:25 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock(std::string const& name, std::string const& title)   {
    this->name = name;
    this->title = title;
    std::cout << this->getName() << ": This looks like another boring day." << std::endl;
}

std::string const& Warlock::getName(void)       const    {
    return this->name;
}

std::string const& Warlock::getTitle(void)      const    {
    return this->title;
}

void    Warlock::setTitle(std::string const& title)    {
    this->title = title;
}

void    Warlock::learnSpell(ASpell* spell)  {
    if (spell)  {
        std::vector<ASpell*>::iterator   it = kSpell.begin();
        for (; it != kSpell.end(); it++)  {
            if ((*it)->getName() == spell->getName())
                return ;
        }
        this->kSpell.push_back(spell->clone());
    }
}

void    Warlock::forgetSpell(std::string nSpell)    {
    std::vector<ASpell*>::iterator  it = kSpell.begin();
    for (; it != kSpell.end(); it++) {
        if ((*it)->getName() == nSpell)    {
            delete *it;
            this->kSpell.erase(it);
            return ;
        }
    }
}
void    Warlock::launchSpell(std::string nSpell, ATarget const & tgt)  {
    std::vector<ASpell*>::iterator  it = kSpell.begin();
    for (; it != kSpell.end(); it++)   {
        if ((*it)->getName() == nSpell)    {
            (*it)->launch(tgt);
            return;
        }
    }
}

void        Warlock::introduce()                const    {
    std::cout << this->getName() << ": I am " << this->getName() << ", " << this->getTitle() << "!" << std::endl;
}

Warlock::~Warlock() {
    std::cout << this->getName() << ": My job here is done!" << std::endl;

}


/* --------------------------------------------------------------------------------

In the Warlock class, the switch statement is FORBIDDEN and its use would
result in a -42.

Below is a possible test main and its expected output:

~$ ./a.out | cat -e
Richard: This looks like another boring day.$
Richard: I am Richard, the Titled!$
Target Practice Dummy has been fwooshed!$
Richard: My job here is done!$ */