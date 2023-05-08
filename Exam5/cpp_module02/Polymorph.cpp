/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:21:38 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 16:24:24 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Polymorph.hpp"

Polymorph::Polymorph()  :   ASpell("Polymorph", "turned into a critter")    {}

Polymorph::~Polymorph() {}

ASpell* Polymorph::clone(void)  const   {
    return new Polymorph(*this);
} 