/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dummy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:20:36 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 13:13:13 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* In the same way, create a concrete ATarget called Dummy, the type of which
is "Target Practice Dummy". You must also implement its clone() method. */

#ifndef DUMMY_HPP
# define DUMMY_HPP

# include "ATarget.hpp"

class Dummy :   public ATarget  {

public:
    Dummy();
    virtual ~Dummy();
    virtual ATarget*    clone() const;
};

#endif