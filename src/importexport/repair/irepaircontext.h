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
#ifndef MU_IMPORTEXPORT_REPAIR_IREPAIRCONTEXT_H
#define MU_IMPORTEXPORT_REPAIR_IREPAIRCONTEXT_H

#include "modularity/imoduleinterface.h"
#include "../engraving/internal/repairdata.h"

namespace mu::notation {
using mu::engraving::repairData;

class IRepairContext : MODULE_EXPORT_INTERFACE
{
    INTERFACE_ID(IRepairContext)

public:
    virtual ~IRepairContext() = default;

    // set the current repair node.
    virtual void setCurrentRepairNode(repairData::Ptr& r) = 0;
    virtual repairData::Ptrc getCurrentRepairNode() const = 0;
    virtual inline bool repairEnabled() = 0;
    virtual inline void startRepair() = 0;
    virtual inline void endRepair() = 0;

};
}

#endif // MU_IMPORTEXPORT_REPAIR_IREPAIRCONTEXT_H
