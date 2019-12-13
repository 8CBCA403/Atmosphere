/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
From musl include/elf.h

Copyright © 2005-2014 Rich Felker, et al.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once
#include <vapours.hpp>

namespace ams::kern::init::Elf::Elf64 {

    /* Type declarations required to perform relocations */
    using Half   = u16;
    using Word   = u32;
    using Sword  = s32;
    using Xword  = u64;
    using SXword = s64;

    using Addr = u64;
    using Off  = u64;

    class Dyn {
        private:
            SXword tag;
            union {
                Xword value;
                Addr ptr;
            };
        public:
            constexpr ALWAYS_INLINE SXword GetTag() const {
                return this->tag;
            }

            constexpr ALWAYS_INLINE Xword GetValue() const {
                return this->value;
            }

            constexpr ALWAYS_INLINE Addr GetPtr() const {
                return this->ptr;
            }
    };

    class Rel {
        private:
            Addr offset;
            Xword info;
        public:
            constexpr ALWAYS_INLINE Addr GetOffset() const {
                return this->offset;
            }

            constexpr ALWAYS_INLINE Xword GetSym() const {
                return this->info >> 32;
            }

            constexpr ALWAYS_INLINE Xword GetType() const {
                return this->info & 0xFFFFFFFF;
            }
    };

    class Rela {
        private:
            Addr offset;
            Xword info;
            SXword addend;
        public:
            constexpr ALWAYS_INLINE Addr GetOffset() const {
                return this->offset;
            }

            constexpr ALWAYS_INLINE Xword GetSym() const {
                return this->info >> 32;
            }

            constexpr ALWAYS_INLINE Xword GetType() const {
                return this->info & 0xFFFFFFFF;
            }

            constexpr ALWAYS_INLINE SXword GetAddend() const {
                return this->addend;
            }
    };

    enum DynamicTag {
        DT_NULL    = 0,
        DT_RELA    = 7,
        DT_RELAENT = 9,
        DT_REL     = 17,
        DT_RELENT  = 19,

        DT_RELACOUNT = 0x6ffffff9,
        DT_RELCOUNT  = 0x6ffffffa
    };

    enum RelocationType {
        R_AARCH64_RELATIVE = 0x403,
    };

    /* API to apply relocations or call init array. */
    void ApplyRelocations(uintptr_t base_address, const Dyn *dynamic);
    void CallInitArrayFuncs(uintptr_t init_array_start, uintptr_t init_array_end);

}