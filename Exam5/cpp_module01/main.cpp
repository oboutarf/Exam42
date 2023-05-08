/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:07:15 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 13:08:46 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Dummy.hpp"
# include "Fwoosh.hpp"
# include "Warlock.hpp"

int main()
{
  Warlock richard("Richard", "the Titled");

  Fwoosh*   fwoosh = new Fwoosh();
  Dummy     bob;

  richard.learnSpell(fwoosh);

  richard.introduce();
  richard.launchSpell("Fwoosh", bob);

  richard.forgetSpell("Fwoosh");
  richard.launchSpell("Fwoosh", bob);
}