/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:37:37 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 13:54:48 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATARGET_HPP
# define ATARGET_HPP

/* Now you will create an ATarget abstract class, in Coplien's form. It has a type
attribute, which is a string, and its associated getter, getType, that return a
reference to constant string.
In much the same way as ASpell, it has a clone() pure method.
All these functions can be called on a constant object.
It has a constructor that takes its type.

Now, add to your ATarget a getHitBySpell function that takes a reference to
constant ASpell.
It will display :
<TYPE> has been <EFFECTS>!
<TYPE> is the ATarget's type, and <EFFECTS> is the return of the ASpell's
getEffects function. */

# include <iostream>
# include <string>

class       ASpell;
# include "ASpell.hpp"

class ATarget   {

public:
    ATarget();
    ATarget(std::string type);
    ATarget(const ATarget& rhs);
    void                    getHitBySpell(const ASpell& shot)   const;
    std::string const&      getType()                           const;
    ATarget&                operator=(const ATarget& rhs);
    virtual ATarget*        clone()                             const = 0;
    virtual ~ATarget();
protected:
    std::string type;

};

#endif