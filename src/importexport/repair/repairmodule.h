/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-Studio-CLA-applies
 *
 * MuseScore Studio
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore Limited
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef MU_IMPORTEXPORT_REPAIRMODULE_H
#define MU_IMPORTEXPORT_REPAIRMODULE_H

#include <memory>

#include "modularity/imodulesetup.h"
#include "internal/repaircontext.h"


namespace mu::iex::repair {
class RepairModule : public muse::modularity::IModuleSetup
{
public:

    std::string moduleName() const override;
    void registerExports() override;

private:
    std::shared_ptr<mu::notation::RepairContext> m_repairContext;
};
}


void mu::iex::repair::RepairModule::registerExports()
{
    m_repairContext = std::make_shared<mu::notation::RepairContext>(iocContext());
    ioc()->registerExport<mu::notation::IRepairContext>(moduleName(), m_repairContext);
}

std::string mu::iex::repair::RepairModule::moduleName() const
{
    return "iex_repair";
}

#endif // MU_IMPORTEXPORT_REPAIRMODULE_H
