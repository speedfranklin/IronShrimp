//------------------------------------------------------------------------------
//                    Copyright (c) 2007-2012 Codalogic Ltd.
//
// This file forms part of THE SUPPORTING SOFTWARE of Codalogic's LMX W3C
// Schema to C++ code generator product.  It is derived from various files of
// the libxml2 XML parser.  This file may be modified and used under the same
// terms as the libxml2 code, the terms of which are below.
//
// THIS FILE AND THE SOFTWARE CONTAINED HEREIN IS PROVIDED 'AS IS' AND COMES
// WITH NO WARRANTIES OF ANY KIND.
//
// CODALOGIC LTD SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY ANYONE
// OR ANYTHING DUE TO THE USE OF THIS FILE HOWEVER THEY MAY BE CAUSED.
//
// For more information on the LMX compiler, go to http://www.codalogic.com
//------------------------------------------------------------------------------

// The libxml2 Copyright referred to above is as follows:
/*
Except where otherwise noted in the source code (e.g. the files hash.c,
list.c and the trio files, which are covered by a similar licence but
with different Copyright notices) all the files are:

 Copyright (C) 1998-2012 Daniel Veillard.  All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is fur-
nished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FIT-
NESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
DANIEL VEILLARD BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CON-
NECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Daniel Veillard shall not
be used in advertising or otherwise to promote the sale, use or other deal-
ings in this Software without prior written authorization from him.
*/
/*
 * Summary: regular expressions handling
 * Description: basic API for libxml regular expressions handling used
 *              for XML Schemas and validation.
 *
 * Copy: See Copyright for the status of this software.
 *
 * Author: Daniel Veillard
 */

#include "lmxuser.h"    /* Outside include guards.  Depending on build, lmxuser.h may include lmxregex.h */

#ifndef LMXREGEX_H
#define LMXREGEX_H

#include <string>

namespace lmx {

/**
 * xmlRegexpPtr:
 *
 * A libxml regular expression, they can actually be far more complex
 * than the POSIX regex expressions.
 */
typedef struct _xmlRegexp xmlRegexp;
typedef xmlRegexp * xmlRegexpPtr;

class c_regex
{
private:
    xmlRegexpPtr mp_regex;

public:
    LMX_RDECL c_regex( const std::string & r_pattern );
    LMX_RDECL bool is_compiled() const
    {
        return mp_regex != LMXNULL;
    }
    LMX_RDECL bool is_match( const std::string & r_s ) const;
    LMX_RDECL virtual ~c_regex();
};

} // End of namepsace lmx

#endif /* LMXREGEX_H */
