/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:30:15 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 17:14:59 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPELLBOOK_HPP
# define SPELLBOOK_HPP

#include "ASpell.hpp"
# include <vector>

class SpellBook {

public:
    SpellBook();
    void    learnSpell(ASpell* lSpell);
    void    forgetSpell(std::string const& fSpell);
    ASpell  *createSpell(std::string const& cSpell);
    ~SpellBook();
private:
    std::vector<ASpell*>      spells;
    SpellBook(const SpellBook& rhs);
    void    operator=(const SpellBook& rhs);
};

#endif
