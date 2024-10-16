#include "iso.h"

#include <format>
#include <optional>
#include <regex>
#include <set>
#include <string>

namespace commands {
	class ISOOptions {
		public:

		std::string drive;
		std::optional<si_t> read_correction;
		std::optional<std::set<size_t>> track_numbers;
		std::optional<std::string> path;
		size_t min_data_passes;
		size_t max_data_passes;
		size_t max_data_retries;
		size_t min_data_copies;
		size_t max_data_copies;
		size_t min_audio_passes;
		size_t max_audio_passes;
		size_t max_audio_retries;
		size_t min_audio_copies;
		size_t max_audio_copies;

		protected:
	};

	namespace internal {
		auto parse_options(
			const std::vector<std::string>& arguments
		) -> ISOOptions {
			auto options = ISOOptions();
			auto parsers = std::vector<parser::Parser>();
			parsers.push_back(parser::Parser({
				"drive",
				"Specify which drive to read from.",
				std::regex("^([A-Z])[:]?$"),
				"string",
				true,
				std::optional<std::string>(),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.drive = matches.at(0);
				}
			}));
			parsers.push_back(parser::Parser({
				"path",
				"Specify which path to write to.",
				std::regex("^(.+)$"),
				"string",
				true,
				std::optional<std::string>(),
				0,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.path = matches.at(0);
				}
			}));
			parsers.push_back(parser::Parser({
				"read-correction",
				"Specify read offset correction in number of samples.",
				std::regex("^([+-]?(?:[0-9]|[1-9][0-9]+))$"),
				"integer",
				false,
				std::optional<std::string>(),
				0,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.read_correction = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"track-numbers",
				"Specify which track numbers to read.",
				std::regex("^([1-9]|[1-9][0-9])$"),
				"integer",
				false,
				std::optional<std::string>(),
				0,
				99,
				[&](const std::vector<std::string>& matches) -> void {
					auto track_numbers = std::set<size_t>();
					for (auto& match : matches) {
						track_numbers.insert(std::atoi(match.c_str()));
					}
					options.track_numbers = track_numbers;
				}
			}));
			parsers.push_back(parser::Parser({
				"min-data-passes",
				"Specify the minimum number of read passes for data tracks.",
				std::regex("^([1-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("1"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.min_data_passes = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"max-data-passes",
				"Specify the maximum number of read passes for data tracks.",
				std::regex("^([1-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("4"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.max_data_passes = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"max-data-retries",
				"Specify the maximum number of read retires for data tracks.",
				std::regex("^([0-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("16"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.max_data_retries = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"min-data-copies",
				"Specify the minimum acceptable number of identical copies for data tracks.",
				std::regex("^([0-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("1"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.min_data_copies = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"max-data-copies",
				"Specify the maximum acceptable number of identical copies for data tracks.",
				std::regex("^([0-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("1"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.max_data_copies = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"min-audio-passes",
				"Specify the minimum number of read passes for audio tracks.",
				std::regex("^([1-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("2"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.min_audio_passes = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"max-audio-passes",
				"Specify the maximum number of read passes for audio tracks.",
				std::regex("^([1-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("8"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.max_audio_passes = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"max-audio-retries",
				"Specify the maximum number of read retires for audio tracks.",
				std::regex("^([0-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("255"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.max_audio_retries = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"min-audio-copies",
				"Specify the minimum acceptable number of identical copies for audio tracks.",
				std::regex("^([0-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("1"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.min_audio_copies = std::atoi(matches.at(0).c_str());
				}
			}));
			parsers.push_back(parser::Parser({
				"max-audio-copies",
				"Specify the maximum acceptable number of identical copies for audio tracks.",
				std::regex("^([0-9]|[1-9][0-9]|[1][0-9][0-9]|[2][0-4][0-9]|[2][5][0-5])$"),
				"integer",
				false,
				std::optional<std::string>("2"),
				1,
				1,
				[&](const std::vector<std::string>& matches) -> void {
					options.max_audio_copies = std::atoi(matches.at(0).c_str());
				}
			}));
			parser::sort(parsers);
			try {
				parser::parse(arguments, parsers);
				return options;
			} catch (const exceptions::ArgumentException& e) {
				parser::print(parsers);
				throw;
			}
		}

		auto assert_image_compatibility(
			const std::vector<disc::TrackInfo>& tracks
		) -> void {
			for (auto track_index = size_t(0); track_index < tracks.size(); track_index += 1) {
				auto& track = tracks.at(track_index);
				if (disc::is_data_track(track.type)) {
					auto user_data_length = disc::get_user_data_length(track.type);
					if (user_data_length != iso9660::USER_DATA_SIZE) {
						OVERDRIVE_THROW(exceptions::InvalidValueException("user data length", user_data_length, iso9660::USER_DATA_SIZE, iso9660::USER_DATA_SIZE));
					}
				} else {
					// OVERDRIVE_THROW(exceptions::ExpectedDataTrackException(track.number));
				}
			}
		}
	}

	auto iso(
		const std::vector<std::string>& arguments,
		const Detail& detail
	) -> void {
		auto options = internal::parse_options(arguments);
		auto handle = detail.get_handle(options.drive);
		auto drive = drive::create_drive(handle, detail.ioctl);
		auto drive_info = drive.read_drive_info();
		drive_info.print();
		auto disc_info = drive.read_disc_info();
		disc_info.print();
		auto read_correction_samples = options.read_correction ? options.read_correction.value() : drive_info.read_offset_correction ? drive_info.read_offset_correction.value() : 0;
		auto tracks = disc::get_disc_tracks(disc_info, options.track_numbers);
		internal::assert_image_compatibility(tracks);
		for (auto track_index = size_t(0); track_index < tracks.size(); track_index += 1) {
			auto& track = tracks.at(track_index);
			fprintf(stderr, "%s\n", std::format("Extracting track number {} containing {} sectors from {} to {}", track.number, track.length_sectors, track.first_sector_absolute, track.last_sector_absolute).c_str());
			if (disc::is_data_track(track.type)) {
				auto extracted_sectors_vector = copier::read_absolute_sector_range(
					drive,
					track.first_sector_absolute,
					track.last_sector_absolute,
					options.min_data_passes,
					options.max_data_passes,
					options.max_data_retries,
					options.min_data_copies,
					options.max_data_copies
				);
				auto bad_sector_indices = copier::get_bad_sector_indices(extracted_sectors_vector, track.first_sector_absolute);
				copier::log_bad_sector_indices(drive, track, bad_sector_indices);
				auto user_data_offset = disc::get_user_data_offset(track.type);
				auto user_data_length = disc::get_user_data_length(track.type);
				auto iso_path = copier::get_absolute_path_with_extension(options.path.value_or(""), std::format("{:0>2}.iso", track.number));
				copier::write_sector_data_to_file(extracted_sectors_vector, iso_path, user_data_offset, user_data_length);
			} else {
				auto extracted_sectors_vector = copier::read_absolute_sector_range_with_correction(
					drive,
					track.first_sector_absolute,
					track.last_sector_absolute,
					options.min_audio_passes,
					options.max_audio_passes,
					options.max_audio_retries,
					options.min_audio_copies,
					options.max_audio_copies,
					read_correction_samples
				);
				auto bad_sector_indices = copier::get_bad_sector_indices(extracted_sectors_vector, track.first_sector_absolute);
				copier::log_bad_sector_indices(drive, track, bad_sector_indices);
				auto bin_path = copier::get_absolute_path_with_extension(options.path.value_or(""), std::format("{:0>2}.bin", track.number));
				copier::write_sector_data_to_file(extracted_sectors_vector, bin_path, 0, cd::SECTOR_LENGTH);
			}
		}
	};
}
