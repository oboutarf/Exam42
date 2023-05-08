/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oscobou <oscobou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:18:32 by oscobou           #+#    #+#             */
/*   Updated: 2023/05/08 17:33:07 by oscobou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()  {}

void        TargetGenerator::learnTargetType(ATarget* tolearn)  {
    for (std::vector<ATarget*>::iterator it = database.begin(); it != database.end(); it++)  {
        if ((*it)->getType() == tolearn->getType())
            return;
    }
    database.push_back(tolearn->clone());
}

void        TargetGenerator::forgetTargetType(std::string const &toforget)  {
    for (std::vector<ATarget*>::iterator it = database.begin(); it != database.end(); it++)  {
        if ((*it)->getType() == toforget)    {
            delete *it;
            database.erase(it);
            return ;
        }
    }
}

ATarget*    TargetGenerator::createTarget(std::string const &tocreate)  {
	for (std::vector<ATarget*>::iterator it = database.begin(); it != database.end(); ++it)
		if ((*it)->getType() == tocreate)
			return *it;
	return NULL;
}

TargetGenerator::~TargetGenerator() {}
