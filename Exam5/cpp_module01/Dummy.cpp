/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:20:33 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 13:11:04 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dummy.hpp"

Dummy::Dummy()  : ATarget("Target Practice Dummy")  {}

ATarget*    Dummy::clone(void)  const   {
    return new Dummy(*this);
}

Dummy::~Dummy()    {}