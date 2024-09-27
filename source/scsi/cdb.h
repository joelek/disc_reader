#pragma once

#include "../discs/cd.h"
#include "../type.h"

namespace scsi {
namespace cdb {
	using namespace type;

	#pragma pack(push, 1)

	enum class ReadTOCFormat: ui08_t {
		NORMAL_TOC = 0b0000,
		SESSION_INFO = 0b0001,
		FULL_TOC = 0b0010,
		PMA = 0b0011,
		ATIP = 0b0100,
		CD_TEXT = 0b0101
	};

	static_assert(sizeof(ReadTOCFormat) == 1);

	struct ReadTOC10 {
		ui08_t operation_code = 0x43;
		ui08_t : 1;
		ui08_t time: 1;
		ui08_t : 3;
		ui08_t : 3;
		ReadTOCFormat format: 4;
		ui08_t : 4;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t track_or_session_number: 8;
		ui16_t allocation_length_be: 16;
		ui08_t control: 8;
	};

	static_assert(sizeof(ReadTOC10) == 10);

	struct ReadTOCResponseParameterList {
		ui16_t data_length_be;
		ui08_t first_track_or_session_number: 8;
		ui08_t last_track_or_session_number: 8;
	};

	static_assert(sizeof(ReadTOCResponseParameterList) == 4);

	struct ReadTOCResponseNormalTOCEntry {
		ui08_t : 8;
		ui08_t control: 4;
		ui08_t adr: 4;
		ui08_t track_number: 8;
		ui08_t : 8;
		ui08_t : 8;
		discs::cd::SectorAddress track_start_address;
	};

	static_assert(sizeof(ReadTOCResponseNormalTOCEntry) == 8);

	struct ReadTOCResponseNormalTOC {
		ReadTOCResponseParameterList header;
		ReadTOCResponseNormalTOCEntry entries[100];
	};

	static_assert(sizeof(ReadTOCResponseNormalTOC) == 804);

	struct ReadTOCResponseSessionInfoEntry {
		ui08_t : 8;
		ui08_t control: 4;
		ui08_t adr: 4;
		ui08_t first_track_number_in_last_complete_session: 8;
		ui08_t : 8;
		ui08_t : 8;
		discs::cd::SectorAddress track_start_address;
	};

	static_assert(sizeof(ReadTOCResponseSessionInfoEntry) == 8);

	struct ReadTOCResponseSessionInfo {
		ReadTOCResponseParameterList header;
		ReadTOCResponseSessionInfoEntry entries[100];
	};

	static_assert(sizeof(ReadTOCResponseSessionInfo) == 804);

	struct ReadTOCResponseFullTOCEntry {
		ui08_t session_number: 8;
		ui08_t control: 4;
		ui08_t adr: 4;
		ui08_t tno: 8;
		ui08_t point: 8;
		ui08_t min: 8;
		ui08_t sec: 8;
		ui08_t frame: 8;
		ui08_t phour: 4;
		ui08_t hour: 4;
		ui08_t pmin: 8;
		ui08_t psec: 8;
		ui08_t pframe: 8;
	};

	static_assert(sizeof(ReadTOCResponseFullTOCEntry) == 11);

	struct ReadTOCResponseFullTOC {
		ReadTOCResponseParameterList header;
		ReadTOCResponseFullTOCEntry entries[100];
	};

	static_assert(sizeof(ReadTOCResponseFullTOC) == 1104);

	struct ReadTOCResponsePMAEntry {
		ui08_t : 8;
		ui08_t control: 4;
		ui08_t adr: 4;
		ui08_t tno: 8;
		ui08_t point: 8;
		ui08_t min: 8;
		ui08_t sec: 8;
		ui08_t frame: 8;
		ui08_t phour: 4;
		ui08_t hour: 4;
		ui08_t pmin: 8;
		ui08_t psec: 8;
		ui08_t pframe: 8;
	};

	static_assert(sizeof(ReadTOCResponsePMAEntry) == 11);

	struct ReadTOCResponsePMA {
		ReadTOCResponseParameterList header;
		ReadTOCResponsePMAEntry entries[100];
	};

	static_assert(sizeof(ReadTOCResponsePMA) == 1104);

	struct ReadTOCResponseATIPEntry {
		ui08_t reference_speed: 3;
		ui08_t ddcd: 1;
		ui08_t indicative_target_writing_power: 4;
		ui08_t : 6;
		ui08_t uru: 1;
		ui08_t zero: 1;
		ui08_t a3_valid: 1;
		ui08_t a2_valid: 1;
		ui08_t a1_valid: 1;
		ui08_t disc_sub_type: 3;
		ui08_t disc_type: 1;
		ui08_t : 1;
		ui08_t : 8;
		discs::cd::SectorAddress astart_time_of_lead_in;
		ui08_t : 8;
		discs::cd::SectorAddress last_possible_start_time_of_lead_out;
		ui08_t : 8;
		ui08_t a1_values[3];
		ui08_t : 8;
		ui08_t a2_values[3];
		ui08_t : 8;
		ui08_t a3_values[3];
		ui08_t : 8;
		ui08_t s4_values[3];
		ui08_t : 8;
	};

	static_assert(sizeof(ReadTOCResponseATIPEntry) == 28);

	struct ReadTOCResponseATIP {
		ReadTOCResponseParameterList header;
		ReadTOCResponseATIPEntry entries[100];
	};

	static_assert(sizeof(ReadTOCResponseATIP) == 2804);

	struct Inquiry6 {
		ui08_t operation_code = 0x12;
		ui08_t enable_vital_product_data: 1;
		ui08_t : 1;
		ui08_t : 6;
		ui08_t page_code;
		ui16_t allocation_length_be;
		ui08_t control;
	};

	static_assert(sizeof(Inquiry6) == 6);

	struct Inquiry6Response {
		ui08_t peripheral_device_type: 5;
		ui08_t peripheral_qualifier: 3;
		ui08_t : 7;
		ui08_t rmb: 1;
		ui08_t version: 8;
		ui08_t response_data_format: 4;
		ui08_t hisup: 1;
		ui08_t normalca: 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t additional_length: 8;
		ui08_t protect: 1;
		ui08_t : 2;
		ui08_t threepc: 1;
		ui08_t tpgs: 2;
		ui08_t acc: 1;
		ui08_t scss: 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t multip: 1;
		ui08_t vs1: 1;
		ui08_t encserv: 1;
		ui08_t : 1;
		ui08_t vs2: 1;
		ui08_t command_queue: 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 1;
		ch08_t vendor_identification[8];
		ch08_t product_identification[16];
		ui32_t product_revision_level_be;
		ch08_t drive_serial_number[8];
		ui08_t vendor_unique[12];
		ui08_t : 1;
		ui08_t : 1;
		ui08_t : 2;
		ui08_t : 4;
		ui08_t : 8;
		ui16_t vendor_descriptor_be[8];
		ui08_t reserved[22];
	};

	static_assert(sizeof(Inquiry6Response) == 96);

	enum class SensePage: ui08_t {
		ReadWriteErrorRecoveryModePage = 0x01,
		CapabilitiesAndMechanicalStatusPage = 0x2A
	};

	static_assert(sizeof(SensePage) == 1);

	enum class ModeSensePageControl: ui08_t {
		CURRENT_VALUES = 0b00,
		CHANGABLE_VALUES = 0b01,
		DEFAULT_VALUES = 0b10,
		SAVED_VALUES = 0b11
	};

	static_assert(sizeof(ModeSensePageControl) == 1);

	struct ModeSense6 {
		ui08_t operation_code = 0x1A;
		ui08_t : 3;
		ui08_t disable_block_descriptors: 1;
		ui08_t : 4;
		SensePage page_code: 6;
		ModeSensePageControl page_control: 2;
		ui08_t subpage_code;
		ui08_t allocation_length;
		ui08_t control;
	};

	static_assert(sizeof(ModeSense6) == 6);

	struct ModeParameterHeader6 {
		ui08_t mode_data_length;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t block_descriptor_length;
	};

	static_assert(sizeof(ModeParameterHeader6) == 4);

	struct ModeSelect6 {
		ui08_t operation_code = 0x15;
		ui08_t save_pages: 1;
		ui08_t revert_to_defaults: 1;
		ui08_t : 2;
		ui08_t page_format: 1;
		ui08_t : 3;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t parameter_list_length;
		ui08_t control;
	};

	static_assert(sizeof(ModeSelect6) == 6);

	struct ModeSense10 {
		ui08_t operation_code = 0x5A;
		ui08_t : 3;
		ui08_t disable_block_descriptors: 1;
		ui08_t long_lba_accepted: 1;
		ui08_t : 3;
		SensePage page_code: 6;
		ModeSensePageControl page_control: 2;
		ui08_t subpage_code;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui16_t allocation_length_be;
		ui08_t control;
	};

	static_assert(sizeof(ModeSense10) == 10);

	struct ModeParameterHeader10 {
		ui16_t mode_data_length_be;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui16_t block_descriptor_length_be;
	};

	static_assert(sizeof(ModeParameterHeader10) == 8);

	struct ModeSelect10 {
		ui08_t operation_code = 0x55;
		ui08_t save_pages: 1;
		ui08_t : 3;
		ui08_t page_format: 1;
		ui08_t : 3;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui16_t parameter_list_length_be;
		ui08_t control;
	};

	static_assert(sizeof(ModeSelect10) == 10);

	struct ReadWriteErrorRecoveryModePage {
		ui08_t page_code: 6;
		ui08_t subpage_format: 1;
		ui08_t parameters_savable: 1;
		ui08_t page_length = 0x0A;
		ui08_t disable_correction: 1;
		ui08_t data_terminate_on_error: 1;
		ui08_t post_error: 1;
		ui08_t enable_early_recovery: 1;
		ui08_t read_continuous: 1;
		ui08_t transfer_block: 1;
		ui08_t automatic_read_reallocation_enabled: 1;
		ui08_t automatic_write_reallocation_enabled: 1;
		ui08_t read_retry_count;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t restricted_for_mmc_6: 2;
		ui08_t : 6;
		ui08_t write_retry_count;
		ui08_t : 8;
		ui16_t recovery_time_limit_be;
	};

	static_assert(sizeof(ReadWriteErrorRecoveryModePage) == 12);

	struct CapabilitiesAndMechanicalStatusPage {
		ui08_t page_code: 6;
		ui08_t : 1;
		ui08_t parameters_savable: 1;
		ui08_t page_length: 8;
		ui08_t cdr_read: 1;
		ui08_t cdrw_read: 1;
		ui08_t method_2: 1;
		ui08_t dvd_rom_read: 1;
		ui08_t dvd_r_read: 1;
		ui08_t dvd_ram_read: 1;
		ui08_t : 2;
		ui08_t cdr_write: 1;
		ui08_t cdrw_write: 1;
		ui08_t test_write: 1;
		ui08_t : 1;
		ui08_t dvd_r_write: 1;
		ui08_t dvd_ram_write: 1;
		ui08_t : 2;
		ui08_t audio_play: 1;
		ui08_t composite: 1;
		ui08_t digital_port_1: 1;
		ui08_t digital_port_2: 1;
		ui08_t mode_2_form_1: 1;
		ui08_t mode_2_form_2: 1;
		ui08_t multi_session: 1;
		ui08_t buf: 1;
		ui08_t cdda_commands_supported: 1;
		ui08_t cdda_stream_is_accurate: 1;
		ui08_t subchannels_rw_supported: 1;
		ui08_t subchannels_rw_deinterleaved_and_corrected: 1;
		ui08_t c2_pointers_supported: 1;
		ui08_t isrc: 1;
		ui08_t upc: 1;
		ui08_t read_bar_code: 1;
		ui08_t lock: 1;
		ui08_t lock_state: 1;
		ui08_t prevent_jumper: 1;
		ui08_t eject: 1;
		ui08_t : 1;
		ui08_t loading_mechanism_type: 3;
		ui08_t separate_volume_levels: 1;
		ui08_t separate_channel_mute: 1;
		ui08_t changer_supports_disc_present: 1;
		ui08_t sw_slot_selection: 1;
		ui08_t side_change_capable: 1;
		ui08_t rw_in_lead_in: 1;
		ui08_t : 2;
		ui08_t : 8;
		ui08_t : 8;
		ui16_t number_of_volume_levels_supported_be: 16;
		ui16_t buffer_size_supported_be: 16;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 1;
		ui08_t bckf: 1;
		ui08_t rck: 1;
		ui08_t lsfbf: 1;
		ui08_t length: 2;
		ui08_t : 2;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui16_t copy_management_revision_supported_be: 16;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t : 8;
		ui08_t rotation_control_selected: 2;
		ui08_t : 6;
		ui16_t current_write_speed_selected_be: 16;
		ui16_t number_of_logical_write_speed_performance_descriptor_tables_be: 16;
	};

	static_assert(sizeof(CapabilitiesAndMechanicalStatusPage) == 32);

	enum class ReadCD12ExpectedSectorType: ui08_t {
		ANY = 0b000,
		CD_DA = 0b001,
		CD_ROM_MODE_1 = 0b010,
		CD_ROM_MODE_2 = 0b011,
		CD_XA_MODE_2_FORM_1 = 0b100,
		CD_XA_MODE_2_FORM_2 = 0b101,
		RESERVED_6  = 0b110,
		RESERVED_7 = 0b111
	};

	static_assert(sizeof(ReadCD12ExpectedSectorType) == 1);

	enum class ReadCD12HeaderCodes: ui08_t {
		NONE = 0b00,
		HEADER_ONLY = 0b01,
		SUBHEADER_ONLY  = 0b10,
		ALL_HEADERS = 0b11
	};

	static_assert(sizeof(ReadCD12HeaderCodes) == 1);

	enum class ReadCD12Errors: ui08_t {
		NONE = 0b00,
		C2_ERROR_BLOCK_DATA = 0b01,
		C2_AND_BLOCK_ERROR_BITS  = 0b10,
		RESERVED_3 = 0b11
	};

	static_assert(sizeof(ReadCD12Errors) == 1);

	enum class ReadCD12SubchanelBits: ui08_t {
		NONE = 0b000,
		RAW = 0b001,
		Q  = 0b010,
		RESERVED_3 = 0b011,
		P_TO_W = 0b100,
		RESERVED_5 = 0b101,
		RESERVED_6 = 0b110,
		RESERVED_7 = 0b111
	};

	static_assert(sizeof(ReadCD12SubchanelBits) == 1);

	struct ReadCD12 {
		ui08_t operation_code = 0xBE;
		ui08_t real_adr: 1;
		ui08_t : 1;
		ReadCD12ExpectedSectorType expected_sector_type: 3;
		ui08_t : 3;
		ui32_t lba_be;
		ui08_t transfer_length_be[3];
		ui08_t : 1;
		ReadCD12Errors errors: 2;
		ui08_t edc_and_ecc: 1;
		ui08_t user_data: 1;
		ReadCD12HeaderCodes header_codes: 2;
		ui08_t sync: 1;
		ReadCD12SubchanelBits subchannel_selection_bits: 3;
		ui08_t : 5;
		ui08_t control;
	};

	static_assert(sizeof(ReadCD12) == 12);

	struct ReadCDResponseDataA {
		byte_t data[discs::cd::SECTOR_LENGTH];
		byte_t c2_data[discs::cd::C2_ERROR_POINTERS_LENGTH];
		byte_t subchannel_data[discs::cd::SUBCHANNELS_LENGTH];
	};

	static_assert(sizeof(ReadCDResponseDataA) == discs::cd::SECTOR_LENGTH + discs::cd::C2_ERROR_POINTERS_LENGTH + discs::cd::SUBCHANNELS_LENGTH);

	struct ReadCDResponseDataB {
		byte_t data[discs::cd::SECTOR_LENGTH];
		byte_t subchannel_data[discs::cd::SUBCHANNELS_LENGTH];
		byte_t c2_data[discs::cd::C2_ERROR_POINTERS_LENGTH];
	};

	static_assert(sizeof(ReadCDResponseDataB) == discs::cd::SECTOR_LENGTH + discs::cd::SUBCHANNELS_LENGTH +  discs::cd::C2_ERROR_POINTERS_LENGTH);

	#pragma pack(pop)
}
}
