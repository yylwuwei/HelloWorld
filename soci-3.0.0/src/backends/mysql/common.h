//
// Copyright (C) 2004-2006 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOCI_MYSQL_COMMON_H_INCLUDED
#define SOCI_MYSQL_COMMON_H_INCLUDED

#include <sstream>
#include "soci-mysql.h"

namespace soci
{

namespace details
{

namespace mysql
{

// helper function for parsing datetime values
void parse_std_tm(char const *buf, std::tm &t);

template <typename T>
void parse_num(char const *buf, T &x)
{
    std::istringstream iss(buf);
    iss >> x;
    if (iss.fail() || (iss.eof() == false))
    {
        throw soci_error("Cannot convert data.");
    }
}

// helper for escaping strings
char * quote(MYSQL * conn, const char *s, int len);

// helper for vector operations
template <typename T>
std::size_t get_vector_size(void *p)
{
    std::vector<T> *v = static_cast<std::vector<T> *>(p);
    return v->size();
}

} // namespace mysql

} // namespace details

} // namespace soci

#endif // SOCI_MYSQL_COMMON_H_INCLUDED
