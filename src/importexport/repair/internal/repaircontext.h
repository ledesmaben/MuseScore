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
#ifndef MU_IMPORTEXPORT_REPAIR_INTERNAL_REPAIRCONTEXT_H
#define MU_IMPORTEXPORT_REPAIR_INTERNAL_REPAIRCONTEXT_H

#include "../irepaircontext.h"
#include "modularity/ioc.h"

// TODO: put these in a more sensical namespace.
namespace mu::notation {
class RepairContext : public IRepairContext, public muse::Injectable
{
public:

    RepairContext(const muse::modularity::ContextPtr& iocCtx);

    // set the current repair node.
    void setCurrentRepairNode(repairData::Ptr& r) override;
    repairData::Ptrc getCurrentRepairNode() const override;

    inline bool repairEnabled() override{
        return m_repairEnabled;
    }

    inline void startRepair() override{
        m_repairEnabled = true;
    }
    inline void endRepair() override{
        m_repairEnabled = false;
    }

private:

    // The current repair node
    repairData::Ptr m_currentRepairNode;
    // Indicator of whether repair is enabled.
    bool m_repairEnabled;
};

RepairContext::RepairContext(const muse::modularity::ContextPtr& iocCtx)
    : muse::Injectable(iocCtx),
    m_currentRepairNode(nullptr),
    m_repairEnabled(false){

}

void RepairContext::setCurrentRepairNode(repairData::Ptr& r){
    m_currentRepairNode = r;
}

repairData::Ptrc RepairContext::getCurrentRepairNode() const{
    return m_currentRepairNode;
}

}

#endif // MU_IMPORTEXPORT_REPAIR_INTERNAL_REPAIRCONTEXT_H
