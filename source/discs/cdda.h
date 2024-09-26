#pragma once

#include "cd.h"
#include "../type.h"

namespace discs {
namespace cdda {
	using namespace type;

	const auto SECTOR_LENGTH = size_t(cd::SECTOR_LENGTH);
	const auto STEREO_SAMPLE_LENGTH = size_t(4);
	const auto STEREO_SAMPLES_PER_FRAME = size_t(6);
	const auto STEREO_FRAME_LENGTH = size_t(STEREO_SAMPLES_PER_FRAME * STEREO_SAMPLE_LENGTH);
	const auto STEREO_SECTOR_LENGTH = size_t(SECTOR_LENGTH);
	const auto STEREO_FRAMES_PER_SECTOR = size_t(STEREO_SECTOR_LENGTH / STEREO_FRAME_LENGTH);

	#pragma pack(push, 1)

	struct StereoFrame {
		byte_t samples[STEREO_SAMPLES_PER_FRAME][STEREO_SAMPLE_LENGTH];
	};

	static_assert(sizeof(StereoFrame) == STEREO_FRAME_LENGTH);

	struct StereoSector {
		StereoFrame frames[STEREO_FRAMES_PER_SECTOR];
	};

	static_assert(sizeof(StereoSector) == STEREO_SECTOR_LENGTH);

	union Sector {
		StereoSector stereo;
	};

	static_assert(sizeof(Sector) == SECTOR_LENGTH);

	#pragma pack(pop)
}
}
