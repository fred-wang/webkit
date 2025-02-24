/*
 * Copyright (C) 2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "IDBRequestData.h"

#include "IDBConnectionToServer.h"
#include "IDBDatabase.h"
#include "IDBOpenDBRequest.h"

namespace WebCore {

IDBRequestData::IDBRequestData(IDBClient::TransactionOperation& operation)
    : m_serverConnectionIdentifier(operation.transaction().database().connectionProxy().serverConnectionIdentifier())
    , m_requestIdentifier(operation.identifier())
    , m_transactionIdentifier(operation.transactionIdentifier())
    , m_objectStoreIdentifier(operation.objectStoreIdentifier())
    , m_indexIdentifier(operation.indexIdentifier())
{
    if (m_indexIdentifier)
        m_indexRecordType = operation.indexRecordType();

    if (operation.cursorIdentifier())
        m_cursorIdentifier = *operation.cursorIdentifier();
}

IDBRequestData::IDBRequestData(IDBConnectionIdentifier serverConnectionIdentifier, IDBResourceIdentifier requestIdentifier, IDBResourceIdentifier transactionIdentifier, std::optional<IDBResourceIdentifier>&& cursorIdentifier, std::optional<IDBObjectStoreIdentifier> objectStoreIdentifier, std::optional<IDBIndexIdentifier> indexIdentifier, IndexedDB::IndexRecordType indexRecordType, uint64_t requestedVersion, IndexedDB::RequestType requestType)
    : m_serverConnectionIdentifier(serverConnectionIdentifier)
    , m_requestIdentifier(requestIdentifier)
    , m_transactionIdentifier(transactionIdentifier)
    , m_cursorIdentifier(WTFMove(cursorIdentifier))
    , m_objectStoreIdentifier(objectStoreIdentifier)
    , m_indexIdentifier(indexIdentifier)
    , m_indexRecordType(WTFMove(indexRecordType))
    , m_requestedVersion(requestedVersion)
    , m_requestType(requestType)
{
}

IDBRequestData::IDBRequestData(const IDBRequestData& other)
    : m_serverConnectionIdentifier(other.m_serverConnectionIdentifier)
    , m_requestIdentifier(other.m_requestIdentifier)
    , m_transactionIdentifier(other.m_transactionIdentifier)
    , m_cursorIdentifier(other.m_cursorIdentifier)
    , m_objectStoreIdentifier(other.m_objectStoreIdentifier)
    , m_indexIdentifier(other.m_indexIdentifier)
    , m_indexRecordType(other.m_indexRecordType)
    , m_requestedVersion(other.m_requestedVersion)
    , m_requestType(other.m_requestType)
{
}

IDBRequestData::IDBRequestData(const IDBRequestData& that, IsolatedCopyTag)
    : m_serverConnectionIdentifier(that.m_serverConnectionIdentifier)
{
    isolatedCopy(that, *this);
}


IDBRequestData IDBRequestData::isolatedCopy() const
{
    return { *this, IsolatedCopy };
}

void IDBRequestData::isolatedCopy(const IDBRequestData& source, IDBRequestData& destination)
{
    destination.m_serverConnectionIdentifier = source.m_serverConnectionIdentifier;
    destination.m_requestIdentifier = source.m_requestIdentifier;
    destination.m_transactionIdentifier = source.m_transactionIdentifier;
    destination.m_cursorIdentifier = source.m_cursorIdentifier;
    destination.m_objectStoreIdentifier = source.m_objectStoreIdentifier;
    destination.m_indexIdentifier = source.m_indexIdentifier;
    destination.m_indexRecordType = source.m_indexRecordType;
    destination.m_requestedVersion = source.m_requestedVersion;
    destination.m_requestType = source.m_requestType;
}

IDBConnectionIdentifier IDBRequestData::serverConnectionIdentifier() const
{
    return m_serverConnectionIdentifier;
}

IDBResourceIdentifier IDBRequestData::requestIdentifier() const
{
    return m_requestIdentifier;
}

IDBResourceIdentifier IDBRequestData::transactionIdentifier() const
{
    return m_transactionIdentifier;
}

IDBResourceIdentifier IDBRequestData::cursorIdentifier() const
{
    ASSERT(m_cursorIdentifier);
    return *m_cursorIdentifier;
}

IDBObjectStoreIdentifier IDBRequestData::objectStoreIdentifier() const
{
    ASSERT(m_objectStoreIdentifier);
    return *m_objectStoreIdentifier;
}

std::optional<IDBIndexIdentifier> IDBRequestData::indexIdentifier() const
{
    ASSERT(m_objectStoreIdentifier || m_indexIdentifier);
    return m_indexIdentifier;
}

IndexedDB::IndexRecordType IDBRequestData::indexRecordType() const
{
    ASSERT(m_indexIdentifier);
    return m_indexRecordType;
}

uint64_t IDBRequestData::requestedVersion() const
{
    return m_requestedVersion;
}

} // namespace WebCore
