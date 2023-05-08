/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fwoosh.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:10:42 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/07 21:17:58 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FWOOSH_HPP
# define FWOOSH_HPP

# include "ASpell.hpp"

/* When all this is done, create an implementation of ASpell called Fwoosh. Its
default constructor will set the name to "Fwoosh" and the effects to
"fwooshed". You will, of course, implement the clone() method. In the case of
Fwoosh, it will return a pointer to a new Fwoosh object. */


class Fwoosh    :   public ASpell   {

public:
    Fwoosh();
    virtual ~Fwoosh();
    virtual ASpell* clone(void) const   ;

};

#endif
