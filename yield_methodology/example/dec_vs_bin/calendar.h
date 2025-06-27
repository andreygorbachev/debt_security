// The MIT License (MIT)
//
// Copyright (c) 2025 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <period.h>

#include <schedule.h>
#include <annual_holidays.h>
#include <calendar.h>


inline auto _make_calendar_ANBIMA()
{
	using namespace std::chrono;
	using namespace gregorian;
	using namespace gregorian::util;

	const auto TiradentesDay = named_holiday{ April / 21d };
	const auto LabourDay = named_holiday{ May / 1d };
	const auto ShroveMonday = offset_holiday{ &_Easter, std::chrono::days{ -47 - 1 } }; // should it be in the actual library?
	const auto ShroveTuesday = offset_holiday{ &_Easter, std::chrono::days{ -46 - 1 } }; // should it be in the actual library?
	const auto CorpusChristi = offset_holiday{ &_Easter, std::chrono::days{ 60 } }; // should it be in the actual library?
	const auto IndependenceDay = named_holiday{ September / 7d };
	const auto OurLadyOfAparecida = named_holiday{ October / 12d };
	const auto AllSoulsDay = named_holiday{ November / 2d }; // should it be in the actual library?
	const auto RepublicProclamationDay = named_holiday{ November / 15d };

	const auto rules1 = annual_holiday_storage{
		&NewYearsDay,
		&ShroveMonday,
		&ShroveTuesday,
		&GoodFriday,
		&TiradentesDay,
		&LabourDay,
		&CorpusChristi,
		&IndependenceDay,
		&OurLadyOfAparecida,
		&AllSoulsDay,
		&RepublicProclamationDay,
		&ChristmasDay
	};

	const auto s1 = make_holiday_schedule(
		years_period{ 2001y, 2023y },
		rules1
	);

	const auto BlackConsciousnessDay = named_holiday{ November / 20d };

	const auto rules2 = annual_holiday_storage{
		&NewYearsDay,
		&ShroveMonday,
		&ShroveTuesday,
		&GoodFriday,
		&TiradentesDay,
		&LabourDay,
		&CorpusChristi,
		&IndependenceDay,
		&OurLadyOfAparecida,
		&AllSoulsDay,
		&RepublicProclamationDay,
		&BlackConsciousnessDay,
		&ChristmasDay
	};

	const auto s2 = make_holiday_schedule(
		years_period{ 2024y, 2099y },
		rules2
	);

	return calendar{
		SaturdaySundayWeekend,
		s1 + s2
	};
}

inline auto make_calendar_ANBIMA() -> const gregorian::calendar& // create static library in gregorian?
{
	static const auto s = _make_calendar_ANBIMA();
	return s;
}
