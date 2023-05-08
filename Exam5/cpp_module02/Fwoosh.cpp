/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:10:39 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 16:17:17 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fwoosh.hpp"

Fwoosh::Fwoosh(void)    :   ASpell("Fwoosh", "fwooshed")    {}

ASpell* Fwoosh::clone(void) const   {
    return new Fwoosh(*this);
}

Fwoosh::~Fwoosh(void)   {}
