#pragma once

#include <functional>
#include <optional>
#include "cd.h"
#include "cdb.h"
#include "disc.h"
#include "shared.h"

namespace overdrive {
namespace drive {
	using namespace shared;

	class Drive {
		public:

		Drive(
			void* handle,
			std::optional<size_t> sector_data_offset,
			std::optional<size_t> subchannels_data_offset,
			std::optional<size_t> c2_data_offset,
			const std::function<void(void* handle, byte_t* cdb, size_t cdb_size, byte_t* data, size_t data_size, bool_t write_to_device)>& ioctl
		);

		auto detect_subchannel_timing_offset(
		) const -> si_t;

		auto get_sector_data_offset(
		) const -> std::optional<size_t>;

		auto get_subchannels_data_offset(
		) const -> std::optional<size_t>;

		auto get_c2_data_offset(
		) const -> std::optional<size_t>;

		auto determine_track_type(
			const cdb::ReadTOCResponseFullTOC& toc,
			ui_t track_index
		) const -> disc::TrackType;

		auto read_normal_toc(
		) const -> cdb::ReadTOCResponseNormalTOC;

		auto read_session_info_toc(
		) const -> cdb::ReadTOCResponseSessionInfoTOC;

		auto read_full_toc(
		) const -> cdb::ReadTOCResponseFullTOC;

		auto read_pma_toc(
		) const -> cdb::ReadTOCResponsePMATOC;

		auto read_atip_toc(
		) const -> cdb::ReadTOCResponseATIPTOC;

		auto read_error_recovery_mode_page(
		) const -> cdb::ModeSenseReadWriteErrorRecoveryModePageResponse;

		auto write_error_recovery_mode_page(
			cdb::ModeSenseReadWriteErrorRecoveryModePageResponse& data
		) const -> void;

		auto read_capabilites_and_mechanical_status_page(
		) const -> cdb::ModeSenseCapabilitiesAndMechanicalStatusPageResponse;

		auto read_standard_inquiry(
		) const -> cdb::StandardInquiryResponse;

		auto read_sector(
			size_t sector_index,
			pointer<array<cd::SECTOR_LENGTH, byte_t>> sector_data,
			pointer<array<cd::SUBCHANNELS_LENGTH, byte_t>> subchannels_data,
			pointer<array<cd::C2_LENGTH, byte_t>> c2_data
		) const -> void;

		auto read_drive_info(
		) const -> disc::DriveInfo;

		auto read_disc_info(
		) const -> disc::DiscInfo;

		protected:

		void* handle;
		std::optional<size_t> sector_data_offset;
		std::optional<size_t> subchannels_data_offset;
		std::optional<size_t> c2_data_offset;
		std::function<void(void* handle, byte_t* cdb, size_t cdb_size, byte_t* data, size_t data_size, bool_t write_to_device)> ioctl;
	};

	auto create_drive(
		void* handle,
		const std::function<void(void* handle, byte_t* cdb, size_t cdb_size, byte_t* data, size_t data_size, bool_t write_to_device)>& ioctl
	) -> Drive;
}
}
