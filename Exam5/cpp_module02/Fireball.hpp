/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fireball.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:15:06 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 16:18:17 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIREBALL_HPP
# define FIREBALL_HPP

# include "ASpell.hpp"

class   Fireball    :   public ASpell   {

public:
	Fireball();
	virtual ~Fireball();
    virtual ASpell* clone(void) const	;

};

#endif
