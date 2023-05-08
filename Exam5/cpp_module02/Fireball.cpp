/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:15:04 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 16:20:46 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Fireball.hpp"

Fireball::Fireball()    :   ASpell("Fireball", "burnt to a crisp")    {}

ASpell* Fireball::clone() const   {
    return new Fireball(*this);
}

Fireball::~Fireball()   {}
