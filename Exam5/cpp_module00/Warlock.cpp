/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oboutarf <oboutarf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:31:01 by oboutarf          #+#    #+#             */
/*   Updated: 2023/05/08 15:48:41 by oboutarf         ###   ########.fr       */
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