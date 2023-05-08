/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brickwall.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:25:38 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 17:37:17 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BrickWall.hpp"

BrickWall::BrickWall()  :   ATarget("Inconspicuous Red-brick Wall") {}


ATarget*    BrickWall::clone() const    {
    return new BrickWall(*this);
}

BrickWall::~BrickWall() {}