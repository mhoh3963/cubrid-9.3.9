/*
 * Copyright (C) 2008 Search Solution Corporation. All rights reserved by Search Solution.
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include "dbgw3/Common.h"
#include "dbgw3/Exception.h"
#include "dbgw3/Logger.h"
#include "dbgw3/Value.h"
#include "dbgw3/SynchronizedResource.h"
#include "dbgw3/system/Mutex.h"
#include "dbgw3/sql/DatabaseInterface.h"
#include "dbgw3/sql/Statement.h"
#include "dbgw3/sql/ResultSet.h"

namespace dbgw
{

  namespace sql
  {

    ResultSet::ResultSet(trait<Statement>::sp pStatement) :
      m_bClosed(false), m_pStatement(pStatement)
    {
    }

    void ResultSet::close()
    {
      system::_MutexAutoLock lock(&m_mutex);

      if (m_bClosed)
        {
          return;
        }

      m_bClosed = true;

      lock.unlock();

      doClose();

      closeResource();
    }

    trait<Statement>::sp ResultSet::getStatement() const
    {
      return m_pStatement;
    }

    void ResultSet::doUnlinkResource()
    {
      close();
    }

  }

}
