// SPDX-License-Identifier: BSD-3-Clause
// SPDX-FileCopyrightText: 2023 The Mangrove Language
// SPDX-FileContributor: Written by Rachel Mant <git@dragonmux.network>
#ifndef ELF64_TYPES_HXX
#define ELF64_TYPES_HXX

#include "io.hxx"
#include "enums.hxx"
#include "commonTypes.hxx"
#include "flags.hxx"

namespace bmpflash::elf::types::elf64
{
	using bmpflash::flags_t;

	struct elfHeader_t final : elfIdent_t
	{
	public:
		elfHeader_t(const memory_t &storage) : elfIdent_t{storage} { }

		[[nodiscard]] auto type() const noexcept { return _storage.read<type_t>(16, _endian); }
		[[nodiscard]] auto machine() const noexcept { return _storage.read<machine_t>(18, _endian); }
		[[nodiscard]] auto version() const noexcept { return _storage.read<version_t>(20, _endian); }
		[[nodiscard]] auto entryPoint() const noexcept { return _storage.read<uint64_t>(24, _endian); }
		[[nodiscard]] auto phdrOffset() const noexcept { return _storage.read<uint64_t>(32, _endian); }
		[[nodiscard]] auto shdrOffset() const noexcept { return _storage.read<uint64_t>(40, _endian); }
		[[nodiscard]] auto flags() const noexcept { return _storage.read<uint32_t>(48, _endian); }
		[[nodiscard]] auto headerSize() const noexcept { return _storage.read<uint16_t>(52, _endian); }
		[[nodiscard]] auto programHeaderSize() const noexcept { return _storage.read<uint16_t>(54, _endian); }
		[[nodiscard]] auto programHeaderCount() const noexcept { return _storage.read<uint16_t>(56, _endian); }
		[[nodiscard]] auto sectionHeaderSize() const noexcept { return _storage.read<uint16_t>(58, _endian); }
		[[nodiscard]] auto sectionHeaderCount() const noexcept { return _storage.read<uint16_t>(60, _endian); }
		[[nodiscard]] auto sectionNamesIndex() const noexcept { return _storage.read<uint16_t>(62, _endian); }

		[[nodiscard]] bool valid() const noexcept
		{
			return
				magic() == elfMagic &&
				elfIdent_t::version() == identVersion_t::current &&
				version() == version_t::current &&
				headerSize() == size();
		}

		[[nodiscard]] constexpr static size_t size() noexcept { return elfIdent_t::size() + 48U; }
	};

	struct programHeader_t final
	{
	private:
		memory_t _storage;
		endian_t _endian;

	public:
		programHeader_t(const memory_t &storage, const endian_t &endian) : _storage{storage}, _endian{endian} { }

		[[nodiscard]] auto type() const noexcept { return _storage.read<programHeaderType_t>(0, _endian); }
		[[nodiscard]] auto flags() const noexcept { return _storage.read<uint32_t>(4, _endian); }
		[[nodiscard]] auto offset() const noexcept { return _storage.read<uint64_t>(8, _endian); }
		[[nodiscard]] auto virtualAddress() const noexcept { return _storage.read<uint64_t>(16, _endian); }
		[[nodiscard]] auto physicalAddress() const noexcept { return _storage.read<uint64_t>(24, _endian); }
		[[nodiscard]] auto fileLength() const noexcept { return _storage.read<uint64_t>(32, _endian); }
		[[nodiscard]] auto memoryLength() const noexcept { return _storage.read<uint64_t>(40, _endian); }
		[[nodiscard]] auto alignment() const noexcept { return _storage.read<uint64_t>(48, _endian); }

		[[nodiscard]] constexpr static size_t size() noexcept { return 56U; }
	};

	struct sectionHeader_t final
	{
	private:
		memory_t _storage;
		endian_t _endian;

	public:
		sectionHeader_t(const memory_t &storage, const endian_t &endian) : _storage{storage}, _endian{endian} { }

		[[nodiscard]] auto nameOffset() const noexcept { return _storage.read<uint32_t>(0, _endian); }
		[[nodiscard]] auto type() const noexcept { return _storage.read<sectionHeaderType_t>(4, _endian); }
		[[nodiscard]] flags_t<sectionFlag_t> flags() const noexcept { return {_storage.read<uint64_t>(8, _endian)}; }
		[[nodiscard]] auto address() const noexcept { return _storage.read<uint64_t>(16, _endian); }
		[[nodiscard]] auto fileOffset() const noexcept { return _storage.read<uint64_t>(24, _endian); }
		[[nodiscard]] auto fileLength() const noexcept { return _storage.read<uint64_t>(32, _endian); }
		[[nodiscard]] auto link() const noexcept { return _storage.read<uint32_t>(40, _endian); }
		[[nodiscard]] auto info() const noexcept { return _storage.read<uint32_t>(44, _endian); }
		[[nodiscard]] auto alignment() const noexcept { return _storage.read<uint64_t>(48, _endian); }
		[[nodiscard]] auto entityLength() const noexcept { return _storage.read<uint64_t>(56, _endian); }

		[[nodiscard]] constexpr static size_t size() noexcept { return 64U; }
	};

	struct elfSymbol_t final
	{
	private:
		memory_t _storage;
		endian_t _endian;

	public:
		elfSymbol_t(const memory_t &storage, const endian_t &endian) : _storage{storage}, _endian{endian} { }

		[[nodiscard]] auto nameOffset() const noexcept { return _storage.read<uint32_t>(0, _endian); }
		[[nodiscard]] auto info() const noexcept { return _storage.read<uint8_t>(4); }
		[[nodiscard]] auto other() const noexcept { return _storage.read<uint8_t>(5); }
		[[nodiscard]] auto sectionIndex() const noexcept { return _storage.read<uint16_t>(6, _endian); }
		[[nodiscard]] auto value() const noexcept { return _storage.read<uint64_t>(8, _endian); }
		[[nodiscard]] auto symbolLength() const noexcept { return _storage.read<uint64_t>(16, _endian); }

		[[nodiscard]] constexpr static size_t size() noexcept { return 24U; }
	};
} // namespace bmpflash::elf::types::elf64

#endif /*ELF64_TYPES_HXX*/
