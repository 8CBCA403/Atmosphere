/*
 * Copyright (c) 2018-2020 Atmosphère-NX
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
#pragma once
#include <vapours/prfile2/prfile2_build_config.hpp>
#include <vapours/prfile2/prfile2_handle.hpp>
#include <vapours/prfile2/pdm/prfile2_pdm_types.hpp>

namespace ams::prfile2::pdm {

    constexpr inline const auto MaxDisks      = 5;
    constexpr inline const auto MaxPartitions = 5;

    struct Disk;
    struct Partition;

    using PartitionEventCallback = void (*)(u32 event, void *param);

    using EraseFunction = pdm::Error (*)(u32, u32);

    struct DiskInfo {
        u32 total_sectors;
        u16 cylinders;
        u8 heads;
        u8 sectors_per_track;
        u16 bytes_per_sector;
        u32 media_attr;
        void *format_param;
        /* ... */
    };

    struct FunctionTable {
        pdm::Error (*initialize)(HandleType disk_handle);
        pdm::Error (*finalize)(HandleType disk_handle);
        pdm::Error (*mount)(HandleType disk_handle);
        pdm::Error (*unmount)(HandleType disk_handle);
        pdm::Error (*format)(HandleType disk_handle, const u8 *);
        pdm::Error (*physical_read)(HandleType disk_handle, u8 *dst, u32 block, u32 count, u32 *num_read);
        pdm::Error (*physical_write)(HandleType disk_handle, const u8 *src, u32 block, u32 count, u32 *num_read);
        pdm::Error (*get_disk_info)(HandleType disk_handle, DiskInfo *out);
    };

    struct DiskTable {
        FunctionTable *function_table;
        u64 ui_ext;
    };

    struct InitDisk {
        pdm::Error (*function)(DiskTable *disk_table, u64 ui_ext);
        u64 ui_ext;
    };

    /* ... */

}
