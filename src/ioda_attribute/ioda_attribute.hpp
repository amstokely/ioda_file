//
// Created by astokely on 5/13/25.
//

#ifndef IODA_VARIABLE_HPP
#define IODA_VARIABLE_HPP
#include <string>
#include <unordered_map>
#include <memory>
#include "ioda_obs_schema/ioda_obs_schema.h"

class IodaAttribute {
    std::string m_name;
    std::unique_ptr<IodaObsSchema> m_schema = std::make_unique<IodaObsSchema>(YAML::LoadFile(IODA_SCHEMA_YAML));
public:
    explicit IodaAttribute(const std::string &name) {
        m_name = m_schema->getAttribute(name)->getValidName();
    }

    [[nodiscard]] std::string getName() const {
        return m_name;
    }
};


#endif //IODA_VARIABLE_HPP
