#pragma once

#include "cdb.h"
#include "disc.h"
#include "shared.h"

namespace overdrive {
namespace mds {
	using namespace shared;

	#pragma pack(push, 1)

	enum class TrackMode: ui08_t {
		NONE = 0x0,
		UNKNOWN_1 = 0x1,
		DVD = 0x2,
		UNKNOWN_3 = 0x3,
		UNKNOWN_4 = 0x4,
		UNKNOWN_5 = 0x5,
		UNKNOWN_6 = 0x6,
		UNKNOWN_7 = 0x7,
		UNKNOWN_8 = 0x8,
		AUDIO = 0x9,
		MODE1 = 0xA,
		MODE2 = 0xB,
		MODE2_FORM1 = 0xC,
		MODE2_FORM2 = 0xD,
		UNKNOWN_E = 0xE,
		UNKNOWN_F = 0xF
	};

	static_assert(sizeof(TrackMode) == 1);

	enum class TrackModeFlags: ui08_t {
		UNKNOWN_0 = 0x0,
		UNKNOWN_1 = 0x1,
		UNKNOWN_2 = 0x2,
		UNKNOWN_3 = 0x3,
		UNKNOWN_4 = 0x4,
		UNKNOWN_5 = 0x5,
		UNKNOWN_6 = 0x6,
		UNKNOWN_7 = 0x7,
		UNKNOWN_8 = 0x8,
		UNKNOWN_9 = 0x9,
		UNKNOWN_A = 0xA,
		UNKNOWN_B = 0xB,
		UNKNOWN_C = 0xC,
		UNKNOWN_D = 0xD,
		UNKNOWN_E = 0xE,
		UNKNOWN_F = 0xF
	};

	static_assert(sizeof(TrackModeFlags) == 1);

	enum class SubchannelMode: ui08_t {
		NONE = 0x00,
		INTERLEAVED_96 = 0x08
	};

	static_assert(sizeof(SubchannelMode) == 1);

	struct FormatHeader {
		ch08_t identifier[16] = { 'M','E','D','I','A',' ','D','E','S','C','R','I','P','T','O','R' };
		ui08_t major_version = 1;
		ui08_t minor_version = 3;
		ui16_t medium_type = 0;
		ui16_t session_count = 1;
		ui16_t unknown_a = 2;
		ui08_t unknown_b[56];
		ui32_t absolute_offset_to_session_headers = 88;
		ui32_t absolute_offset_to_footer = 0;
	};

	static_assert(sizeof(FormatHeader) == 88);

	struct SessionHeader {
		si32_t pregap_correction;
		ui32_t sectors_on_disc;
		ui16_t session_number;
		ui08_t entry_count;
		ui08_t entry_count_type_a;
		ui16_t first_track;
		ui16_t last_track;
		ui08_t unknown_a[4];
		ui32_t absolute_offset_to_entry_table;
	};

	static_assert(sizeof(SessionHeader) == 24);

	struct EntryTypeA {
		TrackMode track_mode : 4;
		TrackModeFlags track_mode_flags: 4;
		union {
			cdb::ReadTOCResponseFullTOCEntry entry;
			SubchannelMode subchannel_mode;
		};
		ui08_t unknown_a[68];
	};

	static_assert(sizeof(EntryTypeA) == 80);

	struct EntryTypeB {
		TrackMode track_mode : 4;
		TrackModeFlags track_mode_flags: 4;
		union {
			cdb::ReadTOCResponseFullTOCEntry entry;
			SubchannelMode subchannel_mode;
		};
		ui32_t absolute_offset_to_track_table_entry;
		ui16_t sector_length;
		ui16_t unknown_a;
		ui08_t unknown_b[16];
		ui32_t first_sector_on_disc;
		ui32_t mdf_byte_offset;
		ui08_t unknown_c[4];
		ui32_t unknown_d;
		ui32_t absolute_offset_to_file_table_header;
		ui08_t unknown_e[24];
	};

	static_assert(sizeof(EntryTypeB) == 80);

	union Entry {
		EntryTypeA type_a;
		EntryTypeB type_b;
	};

	static_assert(sizeof(Entry) == 80);

	struct TrackTableHeader {
		ui08_t unknown_a[24];
	};

	static_assert(sizeof(TrackTableHeader) == 24);

	struct TrackTableEntry {
		ui32_t pregap_sectors;
		ui32_t length_sectors;
	};

	static_assert(sizeof(TrackTableEntry) == 8);

	struct FileTableHeader {
		ui32_t absolute_offset_to_file_table_entry;
		ui08_t unknown_a[12];
	};

	static_assert(sizeof(FileTableHeader) == 16);

	struct FileTableEntry {
		ch08_t identifier[6] = "*.mdf";
	};

	static_assert(sizeof(FileTableEntry) == 6);

	struct Footer {
		ui32_t unknown_a = 1;
		ui32_t absolute_offset_to_bad_sectors_table_header;
	};

	static_assert(sizeof(Footer) == 8);

	struct BadSectorTableHeader {
		ui32_t unknown_a = 2;
		ui32_t unknown_b = 4;
		ui32_t unknown_c = 1;
		ui32_t bad_sector_count;
	};

	static_assert(sizeof(BadSectorTableHeader) == 16);

	struct BadSectorTableEntry {
		ui32_t bad_sector_index;
	};

	static_assert(sizeof(BadSectorTableEntry) == 4);

	#pragma pack(pop)

	auto get_track_mode(
		disc::TrackType track_type
	) -> TrackMode;
}
}
