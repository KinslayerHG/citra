// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include "common/common_types.h"

#include "core/file_sys/archive.h"
#include "core/loader/loader.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
// FileSys namespace

namespace FileSys {

/// File system interface to the SDMC archive
class Archive_SDMC final : public Archive {
public:
    Archive_SDMC(const std::string& mount_point);
    ~Archive_SDMC() override;

    /**
     * Initialize the archive.
     * @return true if it initialized successfully
     */
    bool Initialize();

    /**
     * Get the IdCode of the archive (e.g. RomFS, SaveData, etc.)
     * @return IdCode of the archive
     */
    IdCode GetIdCode() const override { return IdCode::SDMC; };

    /**
     * Open a file specified by its path, using the specified mode
     * @param path Path relative to the archive
     * @param mode Mode to open the file with
     * @return Opened file, or nullptr
     */
    std::unique_ptr<File> OpenFile(const std::string& path, const Mode mode) const override;

    /**
     * Create a directory specified by its path
     * @param path Path relative to the archive
     * @return Whether the directory could be created
     */
    bool CreateDirectory(const std::string& path) const override;

    /**
     * Open a directory specified by its path
     * @param path Path relative to the archive
     * @return Opened directory, or nullptr
     */
    std::unique_ptr<Directory> OpenDirectory(const std::string& path) const override;

    /**
     * Read data from the archive
     * @param offset Offset in bytes to start reading archive from
     * @param length Length in bytes to read data from archive
     * @param buffer Buffer to read data into
     * @return Number of bytes read
     */
    size_t Read(const u64 offset, const u32 length, u8* buffer) const override;

    /**
     * Write data to the archive
     * @param offset Offset in bytes to start writing data to
     * @param length Length in bytes of data to write to archive
     * @param buffer Buffer to write data from
     * @param flush  The flush parameters (0 == do not flush)
     * @return Number of bytes written
     */
    size_t Write(const u64 offset, const u32 length, const u32 flush, u8* buffer) override;

    /**
     * Get the size of the archive in bytes
     * @return Size of the archive in bytes
     */
    size_t GetSize() const override;

    /**
     * Set the size of the archive in bytes
     */
    void SetSize(const u64 size) override;

    /**
     * Getter for the path used for this Archive
     * @return Mount point of that passthrough archive
     */
    std::string GetMountPoint() const;

private:
    std::string mount_point;
};

} // namespace FileSys
