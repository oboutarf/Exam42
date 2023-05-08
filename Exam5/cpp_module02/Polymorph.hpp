/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Polymorph.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:21:40 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 16:22:25 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYMORPH_HPP
# define POLYMORPH_HPP

# include "ASpell.hpp"

class   Polymorph    :   public ASpell   {

public:
	Polymorph();
	virtual ~Polymorph();
    virtual ASpell* clone(void) const	;

};

#endif
