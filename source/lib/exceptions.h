#pragma once

#include <stdexcept>
#include "../type.h"

namespace overdrive {
namespace exceptions {
	using namespace type;

	class InvalidValueException: public std::runtime_error {
		public:

		InvalidValueException(
			si_t value,
			si_t min,
			si_t max
		);

		protected:
	};

	class MissingValueException: public std::runtime_error {
		public:

		MissingValueException();

		protected:
	};

	class AutoDetectFailureException: public std::runtime_error {
		public:

		AutoDetectFailureException();

		protected:
	};

	class UnreachableCodeReachedException: public std::runtime_error {
		public:

		UnreachableCodeReachedException();

		protected:
	};
}
}
