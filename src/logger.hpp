#include <string>

namespace blocklike {
	class Logger {
		public:
			void print(std::string message);
			void print(float message);
			void print(int message);
	};
}