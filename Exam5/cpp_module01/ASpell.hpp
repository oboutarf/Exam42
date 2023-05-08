/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:02:34 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/07 21:26:22 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Create an abstract class called ASpell, in Coplien's form, that has the
following protected attributes:
* name (string)
* effects (string)
Both will have getters (getName and getEffects) that return strings.
Also add a clone pure method that returns a pointer to ASpell.
All these functions can be called on a constant object.
ASpell has a constructor that takes its name and its effects, in that order.
Finally, add to your ASpell class a launch function that takes a reference to
constant ATarget.
This one will simply call the getHitBySpell of the passed object, passing the
current instance as parameter.
*/

#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>
# include <string>
# include "ATarget.hpp"

class   ASpell  {

public:
    ASpell();
    ASpell(std::string name, std::string effects);
    ASpell(const ASpell& rhs);
    std::string         getName()                   const;
    std::string         getEffects()                const;
    void                launch(const ATarget& tgt)  const;
    virtual ASpell*     clone()                     const = 0;
    virtual ~ASpell();
    ASpell&             operator=(const ASpell& rhs);
protected:
    std::string name;
    std::string effects;

};

#endif
