/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:18:35 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 17:26:39 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* Make a TargetGenerator class, in canonical form, and as before,
non-copyable.

It will have the following functions:

* void learnTargetType(ATarget*), teaches a target to the generator

* void forgetTargetType(string const &), that makes the generator forget a
  target type if it's known

* ATarget* createTarget(string const &), that creates a target of the
  specified type */

#ifndef TARGETGENERATOR_HPP
# define TARGETGENERATOR_HPP

# include "ATarget.hpp"
# include <vector>

class TargetGenerator   {

public:
    TargetGenerator();
    void        learnTargetType(ATarget* tolearn);
    void        forgetTargetType(std::string const &toforget);
    ATarget*    createTarget(std::string const &tocreate);
    ~TargetGenerator();
private:
    std::vector<ATarget*>   database;
    TargetGenerator(const TargetGenerator& rhs);
    void    operator=(const TargetGenerator& rhs);
};

#endif
  