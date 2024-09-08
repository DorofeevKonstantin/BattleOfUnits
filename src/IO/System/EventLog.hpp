#pragma once

#include <iostream>
#include <typeindex>
#include <unordered_map>

namespace sw
{
	class EventLog
	{
	private:
		std::ostringstream os;

	public:
		template <class TEvent>
		void collect(uint64_t tick, TEvent &&event)
		{
			os << "[" << tick << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(os);
			event.visit(visitor);
			os << std::endl;
		}
		template <class TEvent>
		void log(uint64_t tick, TEvent &&event)
		{
			std::cout << "[" << tick << "] " << TEvent::Name << " ";
			PrintFieldVisitor visitor(std::cout);
			event.visit(visitor);
			std::cout << std::endl;
		}
		void print()
		{
			std::cout << os.str();
			os.str("");
		}
	};
}