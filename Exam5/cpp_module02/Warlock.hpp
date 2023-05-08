/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:31:05 by oboutarf          #+#    #+#             */
/*   Updated: 2023/05/08 16:51:19 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

/* Add to the Warlock the following member functions:

* learnSpell, takes a pointer to ASpell, that makes the Warlock learn a spell
* forgetSpell, takes a string corresponding a to a spell's name, and makes the
	Warlock forget it. If it's not a known spell, does nothing.
* launchSpell, takes a string (a spell name) and a reference to ATarget, that
	launches the spell on the selected target. If it's not a known spell, does
	nothing.
You will need a new attribute to store the spells your Warlock knows. Several
types fit the bill, it's up to you to choose the best one. */

# include <iostream>  
# include <string>
# include "SpellBook.hpp"

class   Warlock {

public:
		Warlock(std::string const& name, std::string const& title);
		
		void                introduce()             const;
		std::string const&  getName(void)           const;
		std::string const&  getTitle(void)          const;
		void								learnSpell(ASpell* spell);
		void								forgetSpell(std::string nSpell);
		void								launchSpell(std::string nSpell, ATarget const& tgt);
		void                setTitle(std::string const& title);
		~Warlock();
private:
		std::string								name;
		std::string               				title;
		SpellBook								book;
		Warlock();
		Warlock(const Warlock& rhs);
		void    						operator=(const Warlock& rhs);

};

#endif