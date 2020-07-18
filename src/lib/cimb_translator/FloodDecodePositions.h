#pragma once

#include "AdjacentCellFinder.h"
#include "CellDrift.h"
#include "CellPositions.h"
#include <queue>
#include <set>
#include <tuple>

class FloodDecodePositions
{
public:
	using iter = std::tuple<unsigned, CellPositions::coordinate, CellDrift>;
	using decode_instructions = std::pair<CellDrift, unsigned>; // drift, best_prio
	using decode_prio = std::tuple<unsigned, unsigned>; // index, prio

	class PrioCompare
	{
	public:
		bool operator()(const decode_prio& a, const decode_prio& b) const
		{
			return std::get<1>(a) > std::get<1>(b);
		}
	};

public:
	FloodDecodePositions(int spacing, int dimensions, int offset, int marker_size);

	size_t size() const;
	void reset();

	bool done() const;
	iter next();
	int update(unsigned index, const CellDrift& drift, unsigned error_distance);

protected:
	unsigned _index;
	unsigned _count;
	std::priority_queue<decode_prio, std::vector<decode_prio>, PrioCompare> _heap;
	std::vector<bool> _remaining;
	std::vector<decode_instructions> _instructions;
	CellPositions::positions_list _positions;
	AdjacentCellFinder _cellFinder;
};
