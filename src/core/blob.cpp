//
// Copyright (C) 2004-2008 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#define SOCI_SOURCE
#include "soci/blob.h"
#include "soci/session.h"
#include "soci/soci-platform.h"

#include <cstddef>

using namespace soci;

#define SOCI_BLOB_ENSURE_INITIALIZED \
    if (!is_valid()) \
    { \
        throw soci_error("Attempted to access invalid blob"); \
    }

blob::blob(session & s)
{
    initialize(s);
}

blob::~blob() = default;

bool blob::is_valid() const
{
    return static_cast<bool>(backEnd_);
}

void blob::initialize(session &session)
{
    backEnd_.reset(session.make_blob_backend());
}

std::size_t blob::get_len()
{
    SOCI_BLOB_ENSURE_INITIALIZED
    return backEnd_->get_len();
}

std::size_t blob::read(std::size_t offset, void *buf, std::size_t toRead)
{
    SOCI_BLOB_ENSURE_INITIALIZED
    SOCI_ALLOW_DEPRECATED_BEGIN
    return backEnd_->read(offset, buf, toRead);
    SOCI_ALLOW_DEPRECATED_END
}

std::size_t blob::read_from_start(void * buf, std::size_t toRead,
    std::size_t offset)
{
    SOCI_BLOB_ENSURE_INITIALIZED
    return backEnd_->read_from_start(buf, toRead, offset);
}

std::size_t blob::write(
    std::size_t offset, const void * buf, std::size_t toWrite)
{
    SOCI_BLOB_ENSURE_INITIALIZED
    SOCI_ALLOW_DEPRECATED_BEGIN
    return backEnd_->write(offset, buf, toWrite);
    SOCI_ALLOW_DEPRECATED_END
}

std::size_t blob::write_from_start(const void * buf, std::size_t toWrite,
    std::size_t offset)
{
    SOCI_BLOB_ENSURE_INITIALIZED
    return backEnd_->write_from_start(buf, toWrite, offset);
}

std::size_t blob::append(const void * buf, std::size_t toWrite)
{
    SOCI_BLOB_ENSURE_INITIALIZED
    return backEnd_->append(buf, toWrite);
}

void blob::trim(std::size_t newLen)
{
    SOCI_BLOB_ENSURE_INITIALIZED
    backEnd_->trim(newLen);
}

#undef SOCI_BLOB_ENSURE_INITIALIZED
