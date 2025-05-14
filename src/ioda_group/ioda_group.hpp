#ifndef IODA_GROUP_HPP
#define IODA_GROUP_HPP

#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>

#include "ioda_obs_schema/ioda_obs_schema.h"
#include "ioda_variable/ioda_variable.hpp"
#include "FilePathConfig.h"

class IodaGroup {
    std::string m_name;
    std::unordered_map<std::string, std::shared_ptr<IodaGroup> >
    m_groups;
    std::unordered_map<std::string, std::shared_ptr<IodaVariable> >
    m_variables;
    std::unique_ptr<IodaObsSchema> m_schema;

public:
    explicit IodaGroup(const std::string &name) {
        try {
            m_schema = std::make_unique<IodaObsSchema>(
                YAML::LoadFile(IODA_SCHEMA_YAML)
            );
            m_name = m_schema->getGroup(name)->getValidName();
        } catch (const std::exception &e) {
            throw std::runtime_error(
                "Failed to construct IodaGroup: " + std::string(
                    e.what()
                )
            );
        }
    }

    void addGroup(const std::string &name) {
        try {
            auto group = std::make_shared<IodaGroup>(name);
            m_groups[group->getName()] = group;
        } catch (const std::exception &e) {
            throw std::runtime_error(
                "Failed to add group '" + name + "': " + std::string(
                    e.what()
                )
            );
        }
    }

    void addVariable(const std::string &name) {
        try {
            auto pos = name.find('@');
            if (pos != std::string::npos) {
                const std::string varName = name.substr(0, pos);
                const std::string groupName = name.substr(pos + 1);
                addGroup(groupName);
                m_groups.at(groupName)->addVariable(varName);
            } else {
                auto variable = std::make_shared<IodaVariable>(name);
                m_variables[variable->getName()] = variable;
            }
        } catch (const std::exception &e) {
            throw std::runtime_error(
                "Failed to add variable '" + name + "': " + std::string(
                    e.what()
                )
            );
        }
    }

    std::shared_ptr<IodaVariable> getVariable(
        const std::string &name
    ) const {
        try {
            const auto [canonicalVar, canonicalGrp] =
                    parseVariableAndGroup(name);

            if (canonicalGrp == m_name) {
                auto it = m_variables.find(canonicalVar);
                if (it != m_variables.end()) return it->second;
                throw std::runtime_error(
                    "Variable not found in current group '" + m_name +
                    "': " + canonicalVar
                );
            }

            auto groupIt = m_groups.find(canonicalGrp);
            if (groupIt != m_groups.end()) {
                return groupIt->second->getVariable(canonicalVar);
            }

            throw std::runtime_error(
                "Group not found: " + canonicalGrp
            );
        } catch (const std::exception &e) {
            throw std::runtime_error(
                "Failed to get variable '" + name + "': " + std::string(
                    e.what()
                )
            );
        }
    }

    bool hasVariable(const std::string &name) const {
        try {
            const auto [canonicalVariableName, canonicalGroupName] =
                    parseVariableAndGroup(name);

            if (canonicalGroupName == m_name) {
                return m_variables.find(canonicalVariableName) != m_variables.
                       end();
            }

            auto groupIt = m_groups.find(canonicalGroupName);
            return groupIt != m_groups.end() && groupIt->second->
                   hasVariable(canonicalVariableName);
        } catch (const std::exception &e) {
            throw std::runtime_error(
                "Failed to check variable existence for '" + name +
                "': " + std::string(e.what())
            );
        }
    }

    [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<
        IodaGroup> > &getGroups() const {
        return m_groups;
    }

    [[nodiscard]] const std::unordered_map<std::string, std::shared_ptr<
        IodaVariable> > &getVariables() const {
        return m_variables;
    }

    [[nodiscard]] std::string getName() const {
        return m_name;
    }

private:
    // Shared logic to canonicalize variable and group names
    std::pair<std::string, std::string> parseVariableAndGroup(
        const std::string &name
    ) const {
        auto pos = name.find('@');
        if (pos != std::string::npos) {
            const std::string varPart = name.substr(0, pos);
            const std::string grpPart = name.substr(pos + 1);
            return {
                m_schema->getVariable(varPart)->getValidName(),
                m_schema->getGroup(grpPart)->getValidName()
            };
        }
        return {
            m_schema->getVariable(name)->getValidName(), m_name
        };
    }
};

#endif // IODA_GROUP_HPP
